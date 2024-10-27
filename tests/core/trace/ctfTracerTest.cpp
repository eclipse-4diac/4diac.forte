/*******************************************************************************
 * Copyright (c) 2024 Jose Cabral
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral- initial API and implementation and/or initial documentation
 *******************************************************************************/
#include <iomanip>
#include <optional>
#include <thread>

#include <babeltrace2/babeltrace.h>
#include <boost/test/unit_test.hpp>

#include "forte_boost_output_support.h"
#include "../stdfblib/ita/EMB_RES.h"
#include "config.h"
#include "ctfTracerTest_gen.cpp"
#include "device.h"
#include "ecet.h"
#include "EventMessage.h"
#include "trace/barectf_platform_forte.h"
#include "../fbtests/fbtesterglobalfixture.h"

/**
 * @brief Get the list of message from a directory containing CTF traces
 * 
 * @param path Directory containing ctf traces and, if needed, the metadata associated to them
 * @return sorted list of events found in path
 */
std::vector<EventMessage> getEventMessages(std::string path);

/**
 * @brief Print messages as babeltrace2 pretty print
 * @param messages List of messages to print
 */
void printPrettyMessages(const std::vector<EventMessage>& messages);

BOOST_AUTO_TEST_SUITE (tracer_test)

BOOST_AUTO_TEST_CASE(sequential_events_test) {

  // remove previous trace files
  std::filesystem::path destMetadata(CTF_OUTPUT_DIR);
  destMetadata /= "metadata";

  std::filesystem::remove_all(CTF_OUTPUT_DIR);
  std::filesystem::create_directory(CTF_OUTPUT_DIR);
  std::filesystem::copy_file(METADATA_FILE, destMetadata);

  BarectfPlatformFORTE::setup(CTF_OUTPUT_DIR);

  // create a FB network with a E_SWITCH and E_CTU 
  // with some connections and let forte trace its data
  // The inner scope is to make sure the destructors of the resources are 
  // called which flushes the output
  {
    CTesterDevice device(g_nStringIdMyDevice);
    device.initialize();
    CResource &resource = device.getTestResource();

    auto startInstanceName = g_nStringIdSTART;
    auto counterInstanceName = g_nStringIdCounter;
    auto switchInstanceName = g_nStringIdSwitch;

    resource.createFB(counterInstanceName, g_nStringIdE_CTU);
    resource.createFB(switchInstanceName, g_nStringIdE_SWITCH);

    forte::core::SManagementCMD command;
    command.mCMD = EMGMCommandType::CreateConnection;
    command.mDestination = CStringDictionary::scmInvalidStringId;

    BOOST_TEST_INFO("Event connection: Start.COLD -> Counter.CU");
    command.mFirstParam.pushBack(startInstanceName);
    command.mFirstParam.pushBack(g_nStringIdCOLD);
    command.mSecondParam.pushBack(counterInstanceName);
    command.mSecondParam.pushBack(g_nStringIdCU);
    BOOST_TEST(EMGMResponse::Ready == resource.executeMGMCommand(command));

    BOOST_TEST_INFO("Event connection: Counter.CUO -> Switch.EI");
    command.mFirstParam.clear();
    command.mFirstParam.pushBack(counterInstanceName);
    command.mFirstParam.pushBack(g_nStringIdCUO);
    command.mSecondParam.clear();
    command.mSecondParam.pushBack(switchInstanceName);
    command.mSecondParam.pushBack(g_nStringIdEI);
    BOOST_TEST(EMGMResponse::Ready == resource.executeMGMCommand(command));

    BOOST_TEST_INFO("Data connection: Counter.Q -> Switch.G ");
    command.mFirstParam.clear();
    command.mFirstParam.pushBack(counterInstanceName);
    command.mFirstParam.pushBack(g_nStringIdQ);
    command.mSecondParam.clear();
    command.mSecondParam.pushBack(switchInstanceName);
    command.mSecondParam.pushBack(g_nStringIdG);
    BOOST_TEST(EMGMResponse::Ready == resource.executeMGMCommand(command));

    BOOST_TEST_INFO(" Data constant value: Counter.PV = 1");
    command.mFirstParam.clear();
    command.mFirstParam.pushBack(counterInstanceName);
    command.mFirstParam.pushBack(g_nStringIdPV);
    BOOST_TEST(EMGMResponse::Ready == resource.writeValue(command.mFirstParam, "1", false));

    BOOST_TEST_INFO("Event connection: Switch.EO1 -> Counter.R ");
    command.mFirstParam.clear();
    command.mFirstParam.pushBack(switchInstanceName);
    command.mFirstParam.pushBack(g_nStringIdEO1);
    command.mSecondParam.clear();
    command.mSecondParam.pushBack(counterInstanceName);
    command.mSecondParam.pushBack(g_nStringIdR);
    BOOST_TEST(EMGMResponse::Ready == resource.executeMGMCommand(command));

    device.startDevice();
    // wait for all events to be triggered
    while(resource.getResourceEventExecution()->isProcessingEvents()){
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    device.changeExecutionState(EMGMCommandType::Stop);
    resource.getResourceEventExecution()->joinEventChainExecutionThread();
  }

  // disable logging 
  BarectfPlatformFORTE::setup("");

  std::vector<EventMessage> expectedMessages;

  // timestamp cannot properly be tested, so setting everythin to zero
  expectedMessages.emplace_back("receiveInputEvent", std::make_unique<FBInputEventPayload>("E_RESTART", "START", 65534),0);
  expectedMessages.emplace_back("sendOutputEvent", std::make_unique<FBOutputEventPayload>("E_RESTART", "START", 0),0);
  expectedMessages.emplace_back("receiveInputEvent", std::make_unique<FBInputEventPayload>("E_CTU", "Counter", 0),0);
  expectedMessages.emplace_back("instanceData", std::make_unique<FBInstanceDataPayload>("E_CTU", "Counter", std::vector<std::string>{"1"}, std::vector<std::string>{"FALSE", "0"}, std::vector<std::string>{}, std::vector<std::string>{}), 0);
  expectedMessages.emplace_back("sendOutputEvent", std::make_unique<FBOutputEventPayload>("E_CTU", "Counter", 0),0);
  expectedMessages.emplace_back("outputData", std::make_unique<FBDataPayload>("E_CTU", "Counter", 0, "TRUE"), 0);
  expectedMessages.emplace_back("outputData", std::make_unique<FBDataPayload>("E_CTU", "Counter", 1, "1"), 0);
  expectedMessages.emplace_back("receiveInputEvent", std::make_unique<FBInputEventPayload>("E_SWITCH", "Switch", 0),0);
  expectedMessages.emplace_back("instanceData", std::make_unique<FBInstanceDataPayload>("E_SWITCH", "Switch", std::vector<std::string>{"FALSE"}, std::vector<std::string>{}, std::vector<std::string>{}, std::vector<std::string>{}), 0);
  expectedMessages.emplace_back("inputData", std::make_unique<FBDataPayload>("E_SWITCH", "Switch", 0, "TRUE"), 0);
  expectedMessages.emplace_back("sendOutputEvent", std::make_unique<FBOutputEventPayload>("E_SWITCH", "Switch", 1),0);
  expectedMessages.emplace_back("receiveInputEvent", std::make_unique<FBInputEventPayload>("E_CTU", "Counter", 1),0);
  expectedMessages.emplace_back("instanceData", std::make_unique<FBInstanceDataPayload>("E_CTU", "Counter", std::vector<std::string>{"1"}, std::vector<std::string>{"TRUE", "1"}, std::vector<std::string>{}, std::vector<std::string>{}),0);
  expectedMessages.emplace_back("sendOutputEvent", std::make_unique<FBOutputEventPayload>("E_CTU", "Counter", 1),0);
  expectedMessages.emplace_back("outputData", std::make_unique<FBDataPayload>("E_CTU", "Counter", 0, "FALSE"), 0);
  expectedMessages.emplace_back("outputData", std::make_unique<FBDataPayload>("E_CTU", "Counter", 1, "0"), 0);
  expectedMessages.emplace_back("receiveInputEvent", std::make_unique<FBInputEventPayload>("E_RESTART", "START", 65534),0);
  expectedMessages.emplace_back("sendOutputEvent", std::make_unique<FBOutputEventPayload>("E_RESTART", "START", 2),0);

  auto ctfMessages = getEventMessages(CTF_OUTPUT_DIR);

  BOOST_TEST_INFO("Expected vs traced: Same size ");
  BOOST_TEST(ctfMessages.size() == expectedMessages.size());

  // although vectors can be check directly, this granularity helps debugging in case some message is different
  for(size_t i = 0; i < expectedMessages.size(); i++ ){
    BOOST_TEST_INFO("Expexted event number " + std::to_string(i));
    BOOST_CHECK(ctfMessages[i] == expectedMessages[i]);
  }

  // add extra event to check that the comparison fails
  expectedMessages.emplace_back("sendOutputEvent", std::make_unique<FBOutputEventPayload>("E_RESTART", "START", 2),0);
  BOOST_TEST(ctfMessages != expectedMessages);
}

BOOST_AUTO_TEST_SUITE_END()

std::vector<EventMessage> getEventMessages(std::string path){
  
  const bt_plugin* ctfPlugin;
  if(BT_PLUGIN_FIND_STATUS_OK != bt_plugin_find("ctf", BT_FALSE, BT_FALSE, BT_TRUE, BT_FALSE, BT_TRUE, &ctfPlugin)){
    std::cout << "Could not load ctf plugin" << std::endl;
    std::abort();
  }
  auto fileSourceClass = bt_plugin_borrow_source_component_class_by_name_const(ctfPlugin, "fs"); 

  const bt_plugin* utilsPlugin;
  if(BT_PLUGIN_FIND_STATUS_OK != bt_plugin_find("utils", BT_FALSE, BT_FALSE, BT_TRUE, BT_FALSE, BT_TRUE, &utilsPlugin)){
    std::cout << "Could not load utils plugin" << std::endl;
    std::abort();
  }
  auto muxerFilterClass = bt_plugin_borrow_filter_component_class_by_name_const(utilsPlugin, "muxer"); 

  const bt_plugin* fortePlugin;
  if(BT_PLUGIN_FIND_STATUS_OK != bt_plugin_find("forte", BT_FALSE, BT_FALSE, BT_FALSE, BT_TRUE, BT_TRUE, &fortePlugin)){
    std::cout << "Could not load forte plugin" << std::endl;
    std::abort();
  }
  auto forteReaderClass = bt_plugin_borrow_sink_component_class_by_name_const(fortePlugin, "event_reader"); 

  // create graph
  auto graph = bt_graph_create(0);
  
  // Source component
  // create parameters to file source component
  const bt_component_source* tracesComponent;
  auto parameters = bt_value_map_create();
  bt_value *dirsArray;

  if(BT_VALUE_MAP_INSERT_ENTRY_STATUS_OK != bt_value_map_insert_empty_array_entry(parameters, "inputs", &dirsArray)){
    std::cout << "Could not add empty array to map parameter for ctf.source.fs component" << std::endl;
    std::abort();
  }

  if(BT_VALUE_ARRAY_APPEND_ELEMENT_STATUS_OK != bt_value_array_append_string_element(dirsArray, path.c_str())){
    std::cout << "Could not add input folder to ctf.source.fs component's input parameter" << std::endl;
    std::abort();
  }

  if(BT_GRAPH_ADD_COMPONENT_STATUS_OK != bt_graph_add_source_component(graph, fileSourceClass, "traces", parameters, BT_LOGGING_LEVEL_TRACE, &tracesComponent)){
    std::cout << "Could not create Source component" << std::endl;
    std::abort();
  }
  
  const bt_component_filter*  muxerComponent;
  if(BT_GRAPH_ADD_COMPONENT_STATUS_OK != bt_graph_add_filter_component(graph, muxerFilterClass, "muxer", nullptr, BT_LOGGING_LEVEL_TRACE, &muxerComponent)){
    std::cout << "Could not " << std::endl;
    std::abort();
  }

  std::vector<EventMessage> messages;
  const bt_component_sink*  forteReaderComponent;
  if(BT_GRAPH_ADD_COMPONENT_STATUS_OK != 
   bt_graph_add_sink_component_with_initialize_method_data(graph, forteReaderClass, "forteReader", nullptr, &messages, BT_LOGGING_LEVEL_TRACE, &forteReaderComponent)){
    std::cout << "Could not create forte event reader component" << std::endl;
    std::abort();
   }

  for(uint64_t i = 0; i < bt_component_source_get_output_port_count(tracesComponent); i++){
    if(BT_GRAPH_CONNECT_PORTS_STATUS_OK !=  bt_graph_connect_ports(graph, 
        bt_component_source_borrow_output_port_by_index_const(tracesComponent, i), 
        bt_component_filter_borrow_input_port_by_index_const(muxerComponent, i), 
        nullptr)){
          std::cout << "Could not add connection " << i << " from source to muxer" << std::endl;
          std::abort();
      }
  }    

  if(BT_GRAPH_CONNECT_PORTS_STATUS_OK !=  bt_graph_connect_ports(graph, 
    bt_component_filter_borrow_output_port_by_index_const(muxerComponent, 0), 
    bt_component_sink_borrow_input_port_by_index_const(forteReaderComponent, 0), 
    nullptr)){
      std::cout << "Could not add connection from muxer to forte reader" << std::endl;
      std::abort();
  }

  if(BT_GRAPH_RUN_STATUS_OK != bt_graph_run(graph)){
    std::cout << "Could not run graph" << std::endl;
    std::abort();
  }

  return messages;
}

void printPrettyMessages(const std::vector<EventMessage>& messages) {

  // get the pretty text of a timestamp difference
  auto getTimestampDifference = [](int64_t current, std::optional<int64_t> prev) -> std::string {
    if(prev == std::nullopt){
      return "(+?.\?\?\?\?\?\?\?\?\?)";
    }

    auto diff = current - prev.value();

    auto seconds = diff / 1000000000;
    diff %= 1000000000;

    std::stringstream ss;
    ss << "(" << (diff < 0 ? "-" : "+") << 
      std::setw(1) << std::setfill('0') << seconds << 
      "." << 
      std::setw(9) << std::setfill('0') << diff  << ")"; 
    
    return ss.str();
  };

  std::optional<int64_t> lastTimestamp = std::nullopt;
  for(const auto& message : messages) {
    std::cout << message.getTimestampString() 
      << " " << getTimestampDifference(message.getTimestamp(), lastTimestamp) << " "
      << message.getPayloadString() << std::endl;
    lastTimestamp = message.getTimestamp();
  }
}

