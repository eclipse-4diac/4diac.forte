/*******************************************************************************
 * Copyright (c) 2016 - 2017 fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Ben Schneider
 *      - initial implementation and documentation
 *******************************************************************************/

#include "ServiceCallManager.h"
#include "ROSManager.h"
#include <extevhandlerhelper.h>

#include "TRIGGER_SERVICE_CLIENT.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "TRIGGER_SERVICE_CLIENT_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_TRIGGER_SERVICE_CLIENT, g_nStringIdTRIGGER_SERVICE_CLIENT)

const CStringDictionary::TStringId FORTE_TRIGGER_SERVICE_CLIENT::scmDataInputNames[] = { g_nStringIdQI, g_nStringIdNAMESPACE, g_nStringIdSRVNAME };

const CStringDictionary::TStringId FORTE_TRIGGER_SERVICE_CLIENT::scmDataInputTypeIds[] = { g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING };

const CStringDictionary::TStringId FORTE_TRIGGER_SERVICE_CLIENT::scmDataOutputNames[] = { g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdSUCCESS, g_nStringIdMESSAGE };

const CStringDictionary::TStringId FORTE_TRIGGER_SERVICE_CLIENT::scmDataOutputTypeIds[] = { g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdBOOL, g_nStringIdSTRING };

const TForteInt16 FORTE_TRIGGER_SERVICE_CLIENT::scmEIWithIndexes[] = { 0, 4 };
const TDataIOID FORTE_TRIGGER_SERVICE_CLIENT::scmEIWith[] = { 0, 1, 2, scmWithListDelimiter, 0, scmWithListDelimiter };
const CStringDictionary::TStringId FORTE_TRIGGER_SERVICE_CLIENT::scmEventInputNames[] = { g_nStringIdINIT, g_nStringIdREQ };
const CStringDictionary::TStringId FORTE_TRIGGER_SERVICE_CLIENT::scmEventInputTypeIds[] = {g_nStringIdEInit, g_nStringIdEvent};

const TDataIOID FORTE_TRIGGER_SERVICE_CLIENT::scmEOWith[] = { 0, 1, scmWithListDelimiter, 0, 1, 2, 3, scmWithListDelimiter };
const TForteInt16 FORTE_TRIGGER_SERVICE_CLIENT::scmEOWithIndexes[] = { 0, 3, -1 };
const CStringDictionary::TStringId FORTE_TRIGGER_SERVICE_CLIENT::scmEventOutputNames[] = { g_nStringIdINITO, g_nStringIdCNF };
const CStringDictionary::TStringId FORTE_TRIGGER_SERVICE_CLIENT::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};

const SFBInterfaceSpec FORTE_TRIGGER_SERVICE_CLIENT::scmFBInterfaceSpec = { 2, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes, 2, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes, 3, scmDataInputNames, scmDataInputTypeIds, 4, scmDataOutputNames, scmDataOutputTypeIds, 0, 0 };

void FORTE_TRIGGER_SERVICE_CLIENT::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch (paEIID){
    case scmEventINITID:
      //initiate
      if(!m_Initiated && QI()){
        setEventChainExecutor(paECET);
        m_RosNamespace = getExtEvHandler<CROSManager>(*this).ciecStringToStdString(NAMESPACE());
        m_RosMsgName = getExtEvHandler<CROSManager>(*this).ciecStringToStdString(SRVNAME());
        m_nh = new ros::NodeHandle(m_RosNamespace);
        m_triggerClient = m_nh->serviceClient < std_srvs::Trigger > (m_RosMsgName);
        STATUS() = "Client waits for server";

        getExtEvHandler<CServiceCallManager>(*this).queueConnectWait(this);
      }
      //terminate
      else if(m_Initiated && !QI()){
        m_nh->shutdown();
        STATUS() = "Client terminated";
        QO() = false;
        m_Initiated = false;
        sendOutputEvent(scmEventINITOID, paECET);
      }
      //silently ignore other cases
      else{
        STATUS() = "Unknown init command sequence";
        sendOutputEvent(scmEventINITOID, paECET);
      }
      break;
    case scmEventREQID:
      //call service
      if(m_Initiated && QI()){
        STATUS() = "Request sent";
        //add to queue
        getExtEvHandler<CServiceCallManager>(*this).queueServiceCall(this);
      }
      //uninitialized or REQ-
      else{
        STATUS() = "Sending request not possible";
        QO() = false;
        sendOutputEvent(scmEventCNFID, paECET);
      }
      break;
    case cgExternalEventID:
      //waitForExistence returned
      if(!m_Initiated){
        m_Initiated = true;
        STATUS() = "Client connected to server";
        QO() = true;
        sendOutputEvent(scmEventINITOID, paECET);
      }
      //call returned
      else{
        sendOutputEvent(scmEventCNFID, paECET);
      }
      break;
  }
}

void FORTE_TRIGGER_SERVICE_CLIENT::callService(){
  bool srv_success = m_triggerClient.call(m_srv);

  SUCCESS() = m_srv.response.success;
  MESSAGE() = getExtEvHandler<CROSManager>(*this).stdStringToCiecString(m_srv.response.message);

  if(srv_success){
    QO() = true;
    STATUS() = "Response received";
  }
  else{
    QO() = false;
    STATUS() = "Receiving response failed";
    SUCCESS() = false;
    MESSAGE() = "failed";
  }
  getExtEvHandler<CServiceCallManager>(*this).startChain(this);
}

void FORTE_TRIGGER_SERVICE_CLIENT::waitForServer(){

  if (!m_triggerClient.waitForExistence()){
    DEVLOG_ERROR("[FORTE_TRIGGER_SERVICE_CLIENT] connection failed. Server not existing. \n");
  }
  else {
    getExtEvHandler<CServiceCallManager>(*this).startChain(this);
  }
}
