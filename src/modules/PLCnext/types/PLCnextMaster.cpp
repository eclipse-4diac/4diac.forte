/*******************************************************************************
 * Copyright (c) 2022 Peirlberger Juergen
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Peirlberger Juergen - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "PLCnextMaster.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "PLCnextMaster_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_PLCnextMaster, g_nStringIdPLCnextMaster)

const CStringDictionary::TStringId FORTE_PLCnextMaster::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdSlaveUpdateInterval};
const CStringDictionary::TStringId FORTE_PLCnextMaster::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdUINT};
const CStringDictionary::TStringId FORTE_PLCnextMaster::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_PLCnextMaster::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};
const TDataIOID FORTE_PLCnextMaster::scmEIWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_PLCnextMaster::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_PLCnextMaster::scmEventInputNames[] = {g_nStringIdINIT};
const CStringDictionary::TStringId FORTE_PLCnextMaster::scmEventInputTypeIds[] = {g_nStringIdEInit};
const TDataIOID FORTE_PLCnextMaster::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_PLCnextMaster::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_PLCnextMaster::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdIND};
const CStringDictionary::TStringId FORTE_PLCnextMaster::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const SAdapterInstanceDef FORTE_PLCnextMaster::scmAdapterInstances[] = {
  {g_nStringIdPLCnextBusAdapter, g_nStringIdBusAdapterOut, true}
};
const SFBInterfaceSpec FORTE_PLCnextMaster::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  1, scmAdapterInstances
};

FORTE_PLCnextMaster::FORTE_PLCnextMaster(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    forte::core::io::IOConfigFBMultiMaster(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_INITO(this, 0),
    conn_IND(this, 1),
    conn_QI(nullptr),
    conn_SlaveUpdateInterval(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS) {
};

void FORTE_PLCnextMaster::setInitialValues() {
  var_QI = 0_BOOL;
  var_SlaveUpdateInterval = 25_UINT;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_PLCnextMaster::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_SlaveUpdateInterval, conn_SlaveUpdateInterval);
      break;
    }
    default:
      break;
  }
}

void FORTE_PLCnextMaster::writeOutputData(const TEventID paEIID) {
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

CIEC_ANY *FORTE_PLCnextMaster::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_SlaveUpdateInterval;
  }
  return nullptr;
}

CIEC_ANY *FORTE_PLCnextMaster::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}


CEventConnection *FORTE_PLCnextMaster::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_PLCnextMaster::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_SlaveUpdateInterval;
  }
  return nullptr;
}

CDataConnection *FORTE_PLCnextMaster::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

forte::core::io::IODeviceController* FORTE_PLCnextMaster::createDeviceController(CDeviceExecution& paDeviceExecution) {
    return new PLCnextDeviceController(paDeviceExecution);
}

void FORTE_PLCnextMaster::setConfig() {
    PLCnextDeviceController::PLCnextConfig config;
    config.updateInterval = st_SlaveUpdateInterval();
    getDeviceController()->setConfig(&config);
}
