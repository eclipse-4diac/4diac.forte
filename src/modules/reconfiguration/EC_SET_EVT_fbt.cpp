/*******************************************************************************
 * Copyright (c) 2014, 2015 Profactor GmbH, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Matthias Plasch, Gerhard Ebenhofer, Alois Zoitl - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include "EC_SET_EVT_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EC_SET_EVT_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

#include "device.h"
#include "mgmcmdstruct.h"

DEFINE_FIRMWARE_FB(FORTE_EC_SET_EVT, g_nStringIdEC_SET_EVT)

const CStringDictionary::TStringId FORTE_EC_SET_EVT::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdFB_NAME, g_nStringIdFB_EVENT_IO, g_nStringIdDST};
const CStringDictionary::TStringId FORTE_EC_SET_EVT::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING};
const CStringDictionary::TStringId FORTE_EC_SET_EVT::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_EC_SET_EVT::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};
const TDataIOID FORTE_EC_SET_EVT::scmEIWith[] = {0, 3, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_EC_SET_EVT::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_EC_SET_EVT::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_EC_SET_EVT::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_EC_SET_EVT::scmEOWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_EC_SET_EVT::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_EC_SET_EVT::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_EC_SET_EVT::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_EC_SET_EVT::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  4, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_EC_SET_EVT::FORTE_EC_SET_EVT(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_CNF(this, 0),
    conn_QI(nullptr),
    conn_FB_NAME(nullptr),
    conn_FB_EVENT_IO(nullptr),
    conn_DST(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS) {
};

void FORTE_EC_SET_EVT::setInitialValues() {
  var_QI = 0_BOOL;
  var_FB_NAME = u""_WSTRING;
  var_FB_EVENT_IO = u""_WSTRING;
  var_DST = u""_WSTRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_EC_SET_EVT::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      var_QO = var_QI;
      if(var_QI) {
        executeRQST();
      } else {
        var_STATUS = u"Not Ready"_WSTRING;
      }
      sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

void FORTE_EC_SET_EVT::executeRQST(){
  forte::core::SManagementCMD theCommand;
  theCommand.mDestination = CStringDictionary::getInstance().getId(var_DST.getValue());
  theCommand.mFirstParam.pushBack(CStringDictionary::getInstance().getId(var_FB_NAME.getValue()));
  theCommand.mFirstParam.pushBack(CStringDictionary::getInstance().getId(var_FB_EVENT_IO.getValue()));
  theCommand.mCMD = EMGMCommandType::MonitoringTriggerEvent;

  EMGMResponse resp = getDevice()->executeMGMCommand(theCommand);

  //calculate return value
  var_QO = CIEC_BOOL(resp == EMGMResponse::Ready);
  const std::string retVal(forte::mgm_cmd::getResponseText(resp));
  DEVLOG_DEBUG("%s\n", retVal.c_str());
  var_STATUS = CIEC_WSTRING(retVal.c_str());
}

void FORTE_EC_SET_EVT::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_QI, conn_QI);
      readData(3, var_DST, conn_DST);
      readData(1, var_FB_NAME, conn_FB_NAME);
      readData(2, var_FB_EVENT_IO, conn_FB_EVENT_IO);
      break;
    }
    default:
      break;
  }
}

void FORTE_EC_SET_EVT::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_EC_SET_EVT::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_FB_NAME;
    case 2: return &var_FB_EVENT_IO;
    case 3: return &var_DST;
  }
  return nullptr;
}

CIEC_ANY *FORTE_EC_SET_EVT::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}


CEventConnection *FORTE_EC_SET_EVT::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_EC_SET_EVT::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_FB_NAME;
    case 2: return &conn_FB_EVENT_IO;
    case 3: return &conn_DST;
  }
  return nullptr;
}

CDataConnection *FORTE_EC_SET_EVT::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

