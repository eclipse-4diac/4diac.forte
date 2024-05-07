/*******************************************************************************
 * Copyright (c) 2024 Primetals Technologies Austria GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Markus Meingast - initial implementation
 *******************************************************************************/

#include "opcua_event_layer.h"
#include "../../core/utils/parameterParser.h"
#include "../../core/cominfra/basecommfb.h"
#include "opcua_local_handler.h"

using namespace forte::com_infra;

char COPC_UA_Event_Layer::smEmptyString[] = "";

char COPC_UA_Event_Layer::smEventTimeProperty[] = "Time";
char COPC_UA_Event_Layer::smEventSeverityProperty[] = "Severity";
char COPC_UA_Event_Layer::smEventMessageProperty[] = "Message";
char COPC_UA_Event_Layer::smEventSourceProperty[] = "SourceName";

COPC_UA_Event_Layer::COPC_UA_Event_Layer(CComLayer *paUpperLayer, CBaseCommFB *paComFB) :
  CComLayer(paUpperLayer, paComFB), mHandler(nullptr) {

}

COPC_UA_Event_Layer::~COPC_UA_Event_Layer() = default;

EComResponse COPC_UA_Event_Layer::openConnection(char *paLayerParameter) {
  EComResponse eRetVal = e_InitTerminated;
  CParameterParser parser(paLayerParameter, ',', 1);
  size_t nrOfParams = parser.parseParameters();
  if(nrOfParams != scmNumberOfParameters) {
    DEVLOG_ERROR("[OPC UA EVENT LAYER]: Too many layer arguments! Number of arguments: %d\n", nrOfParams);
    return eRetVal;
  }
  mEventTypeName = parser[0];
  mHandler = static_cast<COPC_UA_HandlerAbstract*>(&getExtEvHandler<COPC_UA_Local_Handler>());
  COPC_UA_Local_Handler* localHandler = static_cast<COPC_UA_Local_Handler*>(mHandler);
  localHandler->enableHandler();
  UA_Server *server = localHandler->getUAServer();
  return createOPCUAEvent(server);
}

void COPC_UA_Event_Layer::closeConnection() {
  // TODO
}

EComResponse COPC_UA_Event_Layer::recvData(const void*, unsigned int) {
  return e_ProcessDataOk;
}

EComResponse COPC_UA_Event_Layer::sendData(void*, unsigned int) {
  EComResponse eRetVal = e_ProcessDataInhibited;
  COPC_UA_Local_Handler* localHandler = static_cast<COPC_UA_Local_Handler*>(mHandler);
  UA_Server *server = localHandler->getUAServer();
  if(addNewEventInstance(server, mEventTypeNode, mEventInstanceNode) != UA_STATUSCODE_GOOD) {
    DEVLOG_ERROR("[OPC UA EVENT LAYER]: Failed to create OPC UA Event %s.\n", mEventTypeName.c_str());
    return eRetVal;
  }
  UA_StatusCode status = UA_Server_triggerEvent(server, mEventInstanceNode, 
                                                UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER),
                                                nullptr, UA_TRUE);
  if(status != UA_STATUSCODE_GOOD) {
    DEVLOG_ERROR("[OPC UA EVENT LAYER]: Failed to trigger OPC UA Event %s.\n", mEventTypeName.c_str());
    return eRetVal;
  }
  return e_ProcessDataOk;
}

EComResponse COPC_UA_Event_Layer::processInterrupt() {
  // TODO
  return e_ProcessDataOk;
}

forte::com_infra::EComResponse COPC_UA_Event_Layer::createOPCUAEvent(UA_Server *paServer) {
  if(addNewEventType(paServer, mEventTypeNode, mEventTypeName) != UA_STATUSCODE_GOOD) {
    DEVLOG_ERROR("[OPC UA EVENT LAYER]: Failed to create OPC UA Event %s.\n", mEventTypeName.c_str());
    return e_InitTerminated;
  }
  return e_InitOk;
}

UA_StatusCode COPC_UA_Event_Layer::addNewEventType(UA_Server *paServer, UA_NodeId &paEventType, std::string paEventTypeName) {
    UA_ObjectTypeAttributes attr = UA_ObjectTypeAttributes_default;
    std::string eventTypeName(paEventTypeName);
    attr.displayName = UA_LOCALIZEDTEXT(smEmptyString, eventTypeName.data());
    UA_StatusCode status = UA_Server_addObjectTypeNode(paServer, UA_NODEID_NULL,
                                       UA_NODEID_NUMERIC(0, UA_NS0ID_BASEEVENTTYPE),
                                       UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                       UA_QUALIFIEDNAME(0, eventTypeName.data()),
                                       attr, NULL, &paEventType);
    if(status != UA_STATUSCODE_GOOD) {
    DEVLOG_ERROR("[OPC UA EVENT LAYER]: Failed to add EventType. Status: %s\n", UA_StatusCode_name(status));
  }
  return status;
}

UA_StatusCode COPC_UA_Event_Layer::addNewEventInstance(UA_Server *paServer, UA_NodeId &paEventType, UA_NodeId &paNodeId) {
  UA_StatusCode status = UA_Server_createEvent(paServer, paEventType, &paNodeId);
  if(status != UA_STATUSCODE_GOOD) {
    DEVLOG_ERROR("[OPC UA EVENT LAYER]: Failed to create Event Instance. Status: %s\n", UA_StatusCode_name(status));
    return status;
  }
  UA_DateTime eventTime = UA_DateTime_now();
  status = UA_Server_writeObjectProperty_scalar(paServer, paNodeId, UA_QUALIFIEDNAME(scmServerNSIndex, smEventTimeProperty),
                                              &eventTime, &UA_TYPES[UA_TYPES_DATETIME]);
  if(status != UA_STATUSCODE_GOOD) {
    DEVLOG_ERROR("[OPC UA EVENT LAYER]: Failed to write TimeProperty for OPC UA Event Instance. Status: %s\n", UA_StatusCode_name(status));
    return status;
  }
  UA_UInt16 eventSeverity = 100;
  status = UA_Server_writeObjectProperty_scalar(paServer, paNodeId, UA_QUALIFIEDNAME(scmServerNSIndex, smEventSeverityProperty),
                                         &eventSeverity, &UA_TYPES[UA_TYPES_UINT16]);
  if(status != UA_STATUSCODE_GOOD) {
    DEVLOG_ERROR("[OPC UA EVENT LAYER]: Failed to write SeverityProperty for OPC UA Event Instance. Status: %s\n", UA_StatusCode_name(status));
    return status;
  }
  UA_LocalizedText eventMessage = UA_LOCALIZEDTEXT(smEmptyString, "An event has been generated.");
  status = UA_Server_writeObjectProperty_scalar(paServer, paNodeId, UA_QUALIFIEDNAME(scmServerNSIndex, smEventMessageProperty),
                                        &eventMessage, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);
  if(status != UA_STATUSCODE_GOOD) {
    DEVLOG_ERROR("[OPC UA EVENT LAYER]: Failed to write MessageProperty for OPC UA Event Instance. Status: %s\n", UA_StatusCode_name(status));
    return status;
  }
  UA_String eventSourceName = UA_STRING("Server");
  status = UA_Server_writeObjectProperty_scalar(paServer, paNodeId, UA_QUALIFIEDNAME(scmServerNSIndex, smEventSourceProperty),
                                        &eventSourceName, &UA_TYPES[UA_TYPES_STRING]);
  if(status != UA_STATUSCODE_GOOD) {
    DEVLOG_ERROR("[OPC UA EVENT LAYER]: Failed to write SourceProperty for OPC UA Event Instance. Status: %s\n", UA_StatusCode_name(status));
  }
  return status;
}