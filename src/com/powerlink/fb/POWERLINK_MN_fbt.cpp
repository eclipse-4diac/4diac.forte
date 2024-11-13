/*******************************************************************************
* Copyright (c) 2012 - 2024 AIT
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Filip Andren - initial API and implementation and/or initial documentation
 *   Michael Gafert - converted to new FB style
 *******************************************************************************/

#include "POWERLINK_MN_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "POWERLINK_MN_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_POWERLINK_MN, g_nStringIdPOWERLINK_MN)

const CStringDictionary::TStringId FORTE_POWERLINK_MN::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdCDC_CFG, g_nStringIdAPP_CFG, g_nStringIdDEV_NAME};
const CStringDictionary::TStringId FORTE_POWERLINK_MN::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING};
const CStringDictionary::TStringId FORTE_POWERLINK_MN::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_POWERLINK_MN::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING};
const TDataIOID FORTE_POWERLINK_MN::scmEIWith[] = {0, 1, 2, 3, scmWithListDelimiter};
const TForteInt16 FORTE_POWERLINK_MN::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_POWERLINK_MN::scmEventInputNames[] = {g_nStringIdINIT};
const CStringDictionary::TStringId FORTE_POWERLINK_MN::scmEventInputTypeIds[] = {g_nStringIdEInit};
const TDataIOID FORTE_POWERLINK_MN::scmEOWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_POWERLINK_MN::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_POWERLINK_MN::scmEventOutputNames[] = {g_nStringIdINITO};
const CStringDictionary::TStringId FORTE_POWERLINK_MN::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_POWERLINK_MN::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  4, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_POWERLINK_MN::FORTE_POWERLINK_MN(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
  CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
  var_conn_QO(var_QO),
  var_conn_STATUS(var_STATUS),
  conn_INITO(this, 0),
  conn_QI(nullptr),
  conn_CDC_CFG(nullptr),
  conn_APP_CFG(nullptr),
  conn_DEV_NAME(nullptr),
  conn_QO(this, 0, &var_conn_QO),
  conn_STATUS(this, 1, &var_conn_STATUS) {
};

void FORTE_POWERLINK_MN::setInitialValues() {
  var_QI = 0_BOOL;
  var_CDC_CFG = ""_STRING;
  var_APP_CFG = ""_STRING;
  var_DEV_NAME = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = ""_STRING;
}

void FORTE_POWERLINK_MN::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventINITID:

      CEplStackWrapper* eplStack = &CEplStackWrapper::getInstance();

      eplStack->waitUntilOperational(false);
      eplStack->eplStackInit(var_APP_CFG.c_str(),
        var_CDC_CFG.c_str(),
        var_DEV_NAME.c_str());

      // TODO check if error occured during initialization

      sendOutputEvent(scmEventINITOID, paECET);

      break;
  }
}

void FORTE_POWERLINK_MN::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_CDC_CFG, conn_CDC_CFG);
      readData(2, var_APP_CFG, conn_APP_CFG);
      readData(3, var_DEV_NAME, conn_DEV_NAME);
      break;
    }
    default:
      break;
  }
}

void FORTE_POWERLINK_MN::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_POWERLINK_MN::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_CDC_CFG;
    case 2: return &var_APP_CFG;
    case 3: return &var_DEV_NAME;
  }
  return nullptr;
}

CIEC_ANY *FORTE_POWERLINK_MN::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_POWERLINK_MN::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
  }
  return nullptr;
}

CDataConnection **FORTE_POWERLINK_MN::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_CDC_CFG;
    case 2: return &conn_APP_CFG;
    case 3: return &conn_DEV_NAME;
  }
  return nullptr;
}

CDataConnection *FORTE_POWERLINK_MN::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

