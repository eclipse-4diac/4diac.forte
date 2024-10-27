#include "TraceReaderSink.h"

#include <inttypes.h> // for printing 
#include <sstream>
#include <iostream>
#include <cstring>

#include "bt2MessageFactory.h"

namespace forte{
  
// initialize the sink instance
EventsReader::EventsReader(bt_self_component_sink *self_component_sink,
        const bt_value *params, 
        MessageStorage& initialize_method_data) 
          : mSelfComponentSink{self_component_sink}, 
            mOutput{initialize_method_data}
{
  // params not used for now
  (void) params;

  bt_self_component_set_data(
    bt_self_component_sink_as_self_component(mSelfComponentSink),
    this);

  bt_self_component_sink_add_input_port(mSelfComponentSink,
      "in", nullptr, nullptr);
}

bt_component_class_sink_graph_is_configured_method_status EventsReader::graphIsConfigured()
{
  // get the input port
  bt_self_component_port_input *in_port =
      bt_self_component_sink_borrow_input_port_by_index(
          mSelfComponentSink, 0);

  // Create the uptream message iterator
  bt_message_iterator_create_from_sink_component(mSelfComponentSink,
      in_port, &mMessageIterator);
    
  return BT_COMPONENT_CLASS_SINK_GRAPH_IS_CONFIGURED_METHOD_STATUS_OK;
}

bt_component_class_sink_consume_method_status EventsReader::consume()
{
  // Consume a batch of messages from the upstream message iterator
  bt_message_array_const messages;
  uint64_t message_count;
  bt_message_iterator_next_status next_status =
      bt_message_iterator_next(mMessageIterator, &messages,
          &message_count);

  switch (next_status) {
  case BT_MESSAGE_ITERATOR_NEXT_STATUS_END:
      /* End of iteration: put the message iterator's reference */
      bt_message_iterator_put_ref(mMessageIterator);
      return BT_COMPONENT_CLASS_SINK_CONSUME_METHOD_STATUS_END;
  case BT_MESSAGE_ITERATOR_NEXT_STATUS_AGAIN:
      return BT_COMPONENT_CLASS_SINK_CONSUME_METHOD_STATUS_AGAIN;
  case BT_MESSAGE_ITERATOR_NEXT_STATUS_MEMORY_ERROR:
      return BT_COMPONENT_CLASS_SINK_CONSUME_METHOD_STATUS_MEMORY_ERROR;
  case BT_MESSAGE_ITERATOR_NEXT_STATUS_ERROR:
      return BT_COMPONENT_CLASS_SINK_CONSUME_METHOD_STATUS_ERROR;
  default:
      break;
  }

  // For each consumed message
  for (uint64_t i = 0; i < message_count; i++) {
      
    // Current message 
    const bt_message *message = messages[i];

    // Discard if it's not an event message
    if (bt_message_get_type(message) != BT_MESSAGE_TYPE_EVENT) {
        continue;
    }
    auto m = Bt2MessageFactory::createMessage(message);
    mOutput.emplace_back(m);  

    // Put this message's reference
    bt_message_put_ref(message);
  }

  return BT_COMPONENT_CLASS_SINK_CONSUME_METHOD_STATUS_OK;
}

}

// ************************** //
// C-Style functions needed   // 
// by the babeltrace2 library //
// to create the components   //
// ************************** //
extern "C" {

static bt_component_class_initialize_method_status forte_events_reader_initialize(
      bt_self_component_sink *self_component_sink,
      bt_self_component_sink_configuration *configuration,
      const bt_value *params, void *initialize_method_data){
    
  (void) configuration; // not used according to the documentation
  
  if(initialize_method_data == nullptr){
    std::cout << "You need to pass a valid pointer initialize_method_data when creating a event_reader sink instance" << std::endl;
    std::abort();
  }

  // the allocated pointer is stored inside the class when "this" is passed to the
  // the user data of self_component_sink, which is deleted later in "finalize" 
  new forte::EventsReader(
      self_component_sink, 
      params, 
      *static_cast<forte::EventsReader::MessageStorage*>(initialize_method_data));
  return BT_COMPONENT_CLASS_INITIALIZE_METHOD_STATUS_OK;
}

// finalze
static void forte_events_reader_finalize(bt_self_component_sink *self_component_sink)
{
  forte::EventsReader* instance = static_cast<forte::EventsReader*>(bt_self_component_get_data(
      bt_self_component_sink_as_self_component(self_component_sink)));

  delete instance;
}

static bt_component_class_sink_graph_is_configured_method_status
forte_events_reader_graph_is_configured(bt_self_component_sink *self_component_sink)
{
  auto instance = static_cast<forte::EventsReader *>(bt_self_component_get_data(
    bt_self_component_sink_as_self_component(self_component_sink)));
 
  return instance->graphIsConfigured();
}

static bt_component_class_sink_consume_method_status forte_events_reader_consume(
        bt_self_component_sink *self_component_sink)
{
  auto instance = static_cast<forte::EventsReader *>(bt_self_component_get_data(
      bt_self_component_sink_as_self_component(self_component_sink)));

  return instance->consume();
}

/* Mandatory */
BT_PLUGIN_MODULE();
 
/* Define the `forte` plugin */
BT_PLUGIN(forte);
 
/* Define the `event_reader` sink component class */
BT_PLUGIN_SINK_COMPONENT_CLASS(event_reader, forte_events_reader_consume);
 
/* Set some of the `event_reader` sink component class's optional methods */
BT_PLUGIN_SINK_COMPONENT_CLASS_INITIALIZE_METHOD(event_reader,
    forte_events_reader_initialize);
BT_PLUGIN_SINK_COMPONENT_CLASS_FINALIZE_METHOD(event_reader, forte_events_reader_finalize);
BT_PLUGIN_SINK_COMPONENT_CLASS_GRAPH_IS_CONFIGURED_METHOD(event_reader,
    forte_events_reader_graph_is_configured);

} // extern "C"