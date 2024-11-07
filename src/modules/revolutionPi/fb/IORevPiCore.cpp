/*******************************************************************************
 * Copyright (c) 2017, 2024 fortiss GmbH, Monika Wenger, Johannes Kepler University Linz
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Johannes Messmer - initial API and implementation and/or initial documentation
 *   Monika Wenger, Alois Zoitl - migration to current runtime
 *******************************************************************************/

#include "IORevPiCore.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "IORevPiCore_gen.cpp"
#endif

#include "../RevPiController.h"

DEFINE_FIRMWARE_FB(FORTE_IORevPiCore, g_nStringIdIORevPiCore)

const CStringDictionary::TStringId FORTE_IORevPiCore::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdUpdateInterval};
const CStringDictionary::TStringId FORTE_IORevPiCore::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdUINT};
const CStringDictionary::TStringId FORTE_IORevPiCore::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_IORevPiCore::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};
const TDataIOID FORTE_IORevPiCore::scmEIWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_IORevPiCore::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_IORevPiCore::scmEventInputNames[] = {g_nStringIdINIT};
const CStringDictionary::TStringId FORTE_IORevPiCore::scmEventInputTypeIds[] = {g_nStringIdEInit};
const TDataIOID FORTE_IORevPiCore::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_IORevPiCore::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_IORevPiCore::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdIND};
const CStringDictionary::TStringId FORTE_IORevPiCore::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const SAdapterInstanceDef FORTE_IORevPiCore::scmAdapterInstances[] = {
  {g_nStringIdIORevPiBusAdapter, g_nStringIdBusAdapterOut, true}
};
const SFBInterfaceSpec FORTE_IORevPiCore::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  1, scmAdapterInstances
};

FORTE_IORevPiCore::FORTE_IORevPiCore(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
  forte::core::io::IOConfigFBMultiMaster(paContainer, scmFBInterfaceSpec, paInstanceNameId),
     var_UpdateInterval(25_UINT),
     var_conn_QO(var_QO),
     var_conn_STATUS(var_STATUS),
     conn_INITO(this, 0),
     conn_IND(this, 1),
     conn_QI(nullptr),
     conn_UpdateInterval(nullptr),
     conn_QO(this, 0, &var_conn_QO),
     conn_STATUS(this, 1, &var_conn_STATUS) {

}

void FORTE_IORevPiCore::setInitialValues() {
  var_QI = 0_BOOL;
  var_UpdateInterval = 25_UINT;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_IORevPiCore::setConfig() {
  RevPiController::Config config;
  config.updateInterval = static_cast<CIEC_UINT::TValueType>(var_UpdateInterval);
  getDeviceController()->setConfig(&config);
}

forte::core::io::IODeviceController* FORTE_IORevPiCore::createDeviceController(CDeviceExecution& paDeviceExecution) {
  return new RevPiController(paDeviceExecution);
}

void FORTE_IORevPiCore::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_UpdateInterval, conn_UpdateInterval);
      break;
    }
    default:
      break;
  }
}

void FORTE_IORevPiCore::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    case scmEventINDID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_IORevPiCore::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_UpdateInterval;
  }
  return nullptr;
}

CIEC_ANY *FORTE_IORevPiCore::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_IORevPiCore::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_IORevPiCore::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_UpdateInterval;
  }
  return nullptr;
}

CDataConnection *FORTE_IORevPiCore::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}
