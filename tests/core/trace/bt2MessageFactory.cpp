
#include "bt2MessageFactory.h"

#include "iostream"

#include <babeltrace2/babeltrace.h>

// **************** //
// Helper Functions //
// **************** //
namespace {

  /**
   * @brief Read a a field containing a dynamic data array of strings into a vector of strings
   * 
   * @param paField the field container to read from
   * @param paFieldName the name of the field to read in paField 
   * @param paStorage place to store the result
   */
  void readDynamicArrayField(const bt_field* paField, const char* paFieldName, std::vector<std::string>& paStorage){
    auto arrayField = bt_field_structure_borrow_member_field_by_name_const(paField, paFieldName);
    if(arrayField == nullptr){
      std::cout << "Could not find '" << paFieldName << "' member in field" << std::endl;
      std::abort();
    } else if (BT_FIELD_CLASS_TYPE_DYNAMIC_ARRAY_WITH_LENGTH_FIELD != bt_field_get_class_type(arrayField)){
      std::cout <<  paFieldName << " field is not of type array" << std::endl;
      std::abort();
    }

    auto arrayLength = bt_field_array_get_length(arrayField);
    for(decltype(arrayLength) dynamicArrayRunner = 0; dynamicArrayRunner < arrayLength; dynamicArrayRunner++) {
      const auto arrayElementField = bt_field_array_borrow_element_field_by_index_const(arrayField, dynamicArrayRunner);
  
      if (BT_FIELD_CLASS_TYPE_STRING != bt_field_get_class_type(arrayElementField)){
        std::cout << "element of array " << paFieldName << "is not of type string" << std::endl;
        std::abort();
      }
      paStorage.emplace_back(bt_field_string_get_value(arrayElementField));
    } 
  }

  /**
   * @brief Read a uint64 type from a field
   * 
   * @param paField the field container to read from
   * @param paFieldName he name of the field to read in paField
   * @return the read value
   */
  uint64_t readUint64Field(const bt_field* paField, const char* paFieldName){
    auto eventField = bt_field_structure_borrow_member_field_by_name_const(paField, paFieldName);
    if(eventField == nullptr){
      std::cout << "Could not find '" << paFieldName << "' member in field" << std::endl;
      std::abort();
    } else if (BT_FIELD_CLASS_TYPE_UNSIGNED_INTEGER != bt_field_get_class_type(eventField)){
      std::cout << "eventId field is not of type unsigned integer" << std::endl;
      std::abort();
    }
    return bt_field_integer_unsigned_get_value(eventField);
  }

  /**
   * @brief Read the 'typeName' field
   * 
   * @param paField The field container to read from
   * @return the stored type name inside the field
   */
  std::string getTypeName(const bt_field* paField){
    auto const typeNameField = bt_field_structure_borrow_member_field_by_name_const(paField, "typeName");
    if(typeNameField == nullptr){
      std::cout << "Could not find 'typeName' member in field" << std::endl;
      std::abort();
    } else if (BT_FIELD_CLASS_TYPE_STRING != bt_field_get_class_type (typeNameField)){
      std::cout << "typeName field is not of type string" << std::endl;
      std::abort();
    }

    return bt_field_string_get_value(typeNameField);
  }

  /**
   * @brief Read the 'instanceName' field
   * 
   * @param paField The field container to read from
   * @return the stored instance name inside the field
   */
  std::string getInstanceName(const bt_field* paField){
    auto const instanceNameField = bt_field_structure_borrow_member_field_by_name_const(paField, "instanceName");
    if(instanceNameField == nullptr){
      std::cout << "Could not find 'instanceName' member in field" << std::endl;
      std::abort();
    } else if (BT_FIELD_CLASS_TYPE_STRING != bt_field_get_class_type (instanceNameField)){
      std::cout << "instanceName field is not of type string" << std::endl;
      std::abort();
    }
    return bt_field_string_get_value(instanceNameField); 
  }

  /**
   * @brief Read the 'dataId' field
   * 
   * @param paField The field container to read from
   * @return the stored data id inside the field
   */
  uint64_t getDataId(const bt_field* paField){
      auto dataField = bt_field_structure_borrow_member_field_by_name_const(paField, "dataId");
    if(dataField == nullptr){
      std::cout << "Could not find 'dataId' member in field" << std::endl;
      std::abort();
    } else if (BT_FIELD_CLASS_TYPE_UNSIGNED_INTEGER != bt_field_get_class_type(dataField)){
      std::cout << "dataId field is not of type unsigned integer" << std::endl;
      std::abort();
    }

    return bt_field_integer_unsigned_get_value(dataField);
  }

  /**
   * @brief Read the 'value' field
   * 
   * @param paField The field container to read from
   * @return the stored value inside the field
   */
  std::string getValue(const bt_field* paField){
    auto valueField = bt_field_structure_borrow_member_field_by_name_const(paField, "value");
    if(valueField == nullptr){
      std::cout << "Could not find 'value' member in field" << std::endl;
      std::abort();
    } else if (BT_FIELD_CLASS_TYPE_STRING != bt_field_get_class_type(valueField)){
      std::cout << "value field is not of type unsigned string" << std::endl;
      std::abort();
    }
    return bt_field_string_get_value(valueField);
  }

  /**
   * @brief Create a paylaod from a field
   *  
   * @param paEventType the type of payload to create
   * @param paField the field container to read from with the information needed for the payload
   * @return the created payload
   */
  std::unique_ptr<AbstractPayload> createPayload(const std::string& paEventType, const bt_field* paField){

    std::unique_ptr<AbstractPayload> result = nullptr;
    auto typeName = getTypeName(paField);
    auto instanceName = getInstanceName(paField);

    if(paEventType == "receiveInputEvent") {
      result.reset(new FBInputEventPayload(typeName, instanceName, readUint64Field(paField, "eventId")));
    } else if(paEventType == "sendOutputEvent"){
      result.reset(new FBOutputEventPayload(typeName, instanceName, readUint64Field(paField, "eventId")));
    } 
    else if(paEventType == "inputData" || paEventType == "outputData") {
      result.reset(new FBDataPayload(typeName, instanceName, getDataId(paField), getValue(paField)));
    } else if(paEventType == "instanceData") {
        std::vector<std::string> inputs;
        std::vector<std::string> outputs;
        std::vector<std::string> internal;
        std::vector<std::string> internalFB;

        readDynamicArrayField(paField, "inputs", inputs);
        readDynamicArrayField(paField, "outputs", outputs);
        readDynamicArrayField(paField, "internal", internal);
        readDynamicArrayField(paField, "internalFB", internalFB);

        result.reset(new FBInstanceDataPayload(typeName, instanceName, inputs, outputs, internal, internalFB));
    } 
    return result;
  }
}

EventMessage Bt2MessageFactory::createMessage(const bt_message* paMessage){
  // Borrow the event message's event and its class
  const bt_event *event =
    bt_message_event_borrow_event_const(paMessage);
  const bt_event_class *event_class = bt_event_borrow_class_const(event);

  const bt_field *payload_field =
      bt_event_borrow_payload_field_const(event);

  auto eventType = bt_event_class_get_name(event_class);
  auto payload = createPayload(eventType, payload_field);

  if(payload == nullptr){
    std::cout << "Payload for message of " << eventType << " type could not be created" << std::endl;
    std::abort();
  }

  int64_t timestamp;

  if(BT_CLOCK_SNAPSHOT_GET_NS_FROM_ORIGIN_STATUS_OK != 
      bt_clock_snapshot_get_ns_from_origin(
        bt_message_event_borrow_default_clock_snapshot_const(paMessage), 
        &timestamp)){
    std::cout << "Could not retrieve clock for message" << std::endl;
    std::abort();
  }  

  return EventMessage(eventType, std::move(payload), timestamp);
}

