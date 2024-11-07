/*******************************************************************************
 * Copyright (c) 2016 - 2018 Johannes Messmer (admin@jomess.com), fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Johannes Messmer - initial API and implementation and/or initial documentation
 *   Jose Cabral - Cleaning of namespaces
 *******************************************************************************/

#include "EBMaster.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EBMaster_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_EBMaster, g_nStringIdEBMaster)

const CStringDictionary::TStringId FORTE_EBMaster::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdBusInterface, g_nStringIdBusSelectPin, g_nStringIdBusInitSpeed, g_nStringIdBusLoopSpeed, g_nStringIdSlaveUpdateInterval};
const CStringDictionary::TStringId FORTE_EBMaster::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdUINT, g_nStringIdUINT, g_nStringIdUDINT, g_nStringIdUDINT, g_nStringIdUINT};
const CStringDictionary::TStringId FORTE_EBMaster::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_EBMaster::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};
const TDataIOID FORTE_EBMaster::scmEIWith[] = {0, 3, 5, 4, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_EBMaster::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_EBMaster::scmEventInputNames[] = {g_nStringIdINIT};
const CStringDictionary::TStringId FORTE_EBMaster::scmEventInputTypeIds[] = {g_nStringIdEInit};
const TDataIOID FORTE_EBMaster::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_EBMaster::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_EBMaster::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdIND};
const CStringDictionary::TStringId FORTE_EBMaster::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const SAdapterInstanceDef FORTE_EBMaster::scmAdapterInstances[] = {
  {g_nStringIdEBBusAdapter, g_nStringIdBusAdapterOut, true}
};
const SFBInterfaceSpec FORTE_EBMaster::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  6, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  1, scmAdapterInstances
};

FORTE_EBMaster::FORTE_EBMaster(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    forte::core::io::IOConfigFBMultiMaster(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_BusInterface(1_UINT),
    var_BusSelectPin(49_UINT),
    var_BusInitSpeed(300000_UDINT),
    var_BusLoopSpeed(700000_UDINT),
    var_SlaveUpdateInterval(25_UINT),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_INITO(this, 0),
    conn_IND(this, 1),
    conn_QI(nullptr),
    conn_BusInterface(nullptr),
    conn_BusSelectPin(nullptr),
    conn_BusInitSpeed(nullptr),
    conn_BusLoopSpeed(nullptr),
    conn_SlaveUpdateInterval(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS) {
};

void FORTE_EBMaster::setInitialValues() {
  var_QI = 0_BOOL;
  var_BusInterface = 1_UINT;
  var_BusSelectPin = 49_UINT;
  var_BusInitSpeed = 300000_UDINT;
  var_BusLoopSpeed = 700000_UDINT;
  var_SlaveUpdateInterval = 25_UINT;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_EBMaster::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
       readData(0, var_QI, conn_QI);
      readData(3, var_BusInitSpeed, conn_BusInitSpeed);
      readData(5, var_SlaveUpdateInterval, conn_SlaveUpdateInterval);
      readData(4, var_BusLoopSpeed, conn_BusLoopSpeed);
      readData(1, var_BusInterface, conn_BusInterface);
      readData(2, var_BusSelectPin, conn_BusSelectPin);
      break;
    }
    default:
      break;
  }
}

void FORTE_EBMaster::writeOutputData(const TEventID paEIID) {
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

CIEC_ANY *FORTE_EBMaster::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_BusInterface;
    case 2: return &var_BusSelectPin;
    case 3: return &var_BusInitSpeed;
    case 4: return &var_BusLoopSpeed;
    case 5: return &var_SlaveUpdateInterval;
  }
  return nullptr;
}

CIEC_ANY *FORTE_EBMaster::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_EBMaster::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_EBMaster::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_BusInterface;
    case 2: return &conn_BusSelectPin;
    case 3: return &conn_BusInitSpeed;
    case 4: return &conn_BusLoopSpeed;
    case 5: return &conn_SlaveUpdateInterval;
  }
  return nullptr;
}

CDataConnection *FORTE_EBMaster::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

forte::core::io::IODeviceController* FORTE_EBMaster::createDeviceController(CDeviceExecution& paDeviceExecution) {
  return new EmbrickBusHandler(paDeviceExecution);
}

void FORTE_EBMaster::setConfig() {
  EmbrickBusHandler::Config config;
  config.mBusInterface = var_BusInterface.operator TForteUInt16();
  config.mBusSelectPin = var_BusSelectPin.operator TForteUInt16();
  config.mBusInitSpeed = var_BusInitSpeed.operator TForteUInt32();
  config.mBusLoopSpeed = var_BusLoopSpeed.operator TForteUInt32();
  getDeviceController()->setConfig(&config);
}

void FORTE_EBMaster::onStartup(CEventChainExecutionThread * const paECET) {
  var_BusAdapterOut().var_UpdateInterval() = var_SlaveUpdateInterval;

  forte::core::io::IOConfigFBMultiMaster::onStartup(paECET);
}
