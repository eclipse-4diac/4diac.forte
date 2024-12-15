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
#include "ST_CREATE_CONN_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ST_CREATE_CONN_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

#include "device.h"

DEFINE_FIRMWARE_FB(FORTE_ST_CREATE_CONN, g_nStringIdST_CREATE_CONN)

const CStringDictionary::TStringId FORTE_ST_CREATE_CONN::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdSRC_FB, g_nStringIdSRC_FB_OUT, g_nStringIdDST_FB, g_nStringIdDST_FB_IN, g_nStringIdDST};
const CStringDictionary::TStringId FORTE_ST_CREATE_CONN::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING};
const CStringDictionary::TStringId FORTE_ST_CREATE_CONN::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_ST_CREATE_CONN::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};
const TDataIOID FORTE_ST_CREATE_CONN::scmEIWith[] = {1, 2, 3, 4, 5, 0, scmWithListDelimiter};
const TForteInt16 FORTE_ST_CREATE_CONN::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_ST_CREATE_CONN::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_ST_CREATE_CONN::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_ST_CREATE_CONN::scmEOWith[] = {1, 0, scmWithListDelimiter};
const TForteInt16 FORTE_ST_CREATE_CONN::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_ST_CREATE_CONN::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_ST_CREATE_CONN::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_ST_CREATE_CONN::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  6, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_ST_CREATE_CONN::FORTE_ST_CREATE_CONN(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_CNF(this, 0),
    conn_QI(nullptr),
    conn_SRC_FB(nullptr),
    conn_SRC_FB_OUT(nullptr),
    conn_DST_FB(nullptr),
    conn_DST_FB_IN(nullptr),
    conn_DST(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS) {
};

void FORTE_ST_CREATE_CONN::setInitialValues() {
  var_QI = 0_BOOL;
  var_SRC_FB = u""_WSTRING;
  var_SRC_FB_OUT = u""_WSTRING;
  var_DST_FB = u""_WSTRING;
  var_DST_FB_IN = u""_WSTRING;
  var_DST = u""_WSTRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_ST_CREATE_CONN::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

void FORTE_ST_CREATE_CONN::executeRQST(){
  forte::core::SManagementCMD theCommand;

  theCommand.mDestination = CStringDictionary::getInstance().getId(var_DST.getValue());
  theCommand.mFirstParam.pushBack(CStringDictionary::getInstance().getId(var_SRC_FB.getValue()));
  theCommand.mFirstParam.pushBack(CStringDictionary::getInstance().getId(var_SRC_FB_OUT.getValue()));
  theCommand.mSecondParam.pushBack(CStringDictionary::getInstance().getId(var_DST_FB.getValue()));
  theCommand.mSecondParam.pushBack(CStringDictionary::getInstance().getId(var_DST_FB_IN.getValue()));
  theCommand.mCMD = EMGMCommandType::CreateConnection;

  EMGMResponse resp = getDevice()->executeMGMCommand(theCommand);

  //calculate return value
  var_QO = CIEC_BOOL(resp == EMGMResponse::Ready);
  const std::string retVal(forte::mgm_cmd::getResponseText(resp));
  DEVLOG_DEBUG("%s\n", retVal.c_str());
  var_STATUS = CIEC_WSTRING(retVal.c_str());
}

void FORTE_ST_CREATE_CONN::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(1, var_SRC_FB, conn_SRC_FB);
      readData(2, var_SRC_FB_OUT, conn_SRC_FB_OUT);
      readData(3, var_DST_FB, conn_DST_FB);
      readData(4, var_DST_FB_IN, conn_DST_FB_IN);
      readData(5, var_DST, conn_DST);
      readData(0, var_QI, conn_QI);
      break;
    }
    default:
      break;
  }
}

void FORTE_ST_CREATE_CONN::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(1, var_STATUS, conn_STATUS);
      writeData(0, var_QO, conn_QO);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_ST_CREATE_CONN::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_SRC_FB;
    case 2: return &var_SRC_FB_OUT;
    case 3: return &var_DST_FB;
    case 4: return &var_DST_FB_IN;
    case 5: return &var_DST;
  }
  return nullptr;
}

CIEC_ANY *FORTE_ST_CREATE_CONN::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_ST_CREATE_CONN::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_ST_CREATE_CONN::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_SRC_FB;
    case 2: return &conn_SRC_FB_OUT;
    case 3: return &conn_DST_FB;
    case 4: return &conn_DST_FB_IN;
    case 5: return &conn_DST;
  }
  return nullptr;
}

CDataConnection *FORTE_ST_CREATE_CONN::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}
