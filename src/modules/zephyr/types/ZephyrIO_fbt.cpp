/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ZephyrIO
 *** Description: Template for Modular IO with boards running Zephyr OS
 *** Version:
 ***     1.0: 2024-01-12/Dirk Kaar -  -
 ***
 *** Copyright (c) 2024 KT Elektronik GmbH
 *** This program and the accompanying materials are made available under the
 *** terms of the Eclipse Public License 2.0 which is available at
 *** http://www.eclipse.org/legal/epl-2.0.
 ***
 *** SPDX-License-Identifier: EPL-2.0
 *************************************************************************/

#include "ZephyrIO_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ZephyrIO_fbt_gen.cpp"
#endif

#pragma region includes
#include <handler/IOHandleGPIODescriptor.h>
#include <handler/IOHandleADCDescriptor.h>
#include "handler/IODeviceController.h"
#pragma endregion includes

DEFINE_FIRMWARE_FB(FORTE_ZephyrIO, g_nStringIdZephyrIO)

const CStringDictionary::TStringId FORTE_ZephyrIO::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdUpdateInterval};
const CStringDictionary::TStringId FORTE_ZephyrIO::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdTIME};
const CStringDictionary::TStringId FORTE_ZephyrIO::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_ZephyrIO::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING};
const TDataIOID FORTE_ZephyrIO::scmEIWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_ZephyrIO::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_ZephyrIO::scmEventInputNames[] = {g_nStringIdINIT};
const CStringDictionary::TStringId FORTE_ZephyrIO::scmEventInputTypeIds[] = {g_nStringIdEInit};
const TDataIOID FORTE_ZephyrIO::scmEOWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_ZephyrIO::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_ZephyrIO::scmEventOutputNames[] = {g_nStringIdINITO};
const CStringDictionary::TStringId FORTE_ZephyrIO::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_ZephyrIO::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_ZephyrIO::FORTE_ZephyrIO(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
#pragma region base class spec
    FORTE_ZephyrIOBase(paContainer, scmFBInterfaceSpec, paInstanceNameId),
#pragma endregion base class spec
    var_UpdateInterval(40000000_TIME),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_INITO(this, 0),
    conn_QI(nullptr),
    conn_UpdateInterval(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS) {
};

void FORTE_ZephyrIO::setInitialValues() {
  var_QI = 0_BOOL;
  var_UpdateInterval = 40000000_TIME;
  var_QO = 0_BOOL;
  var_STATUS = ""_STRING;
}

#pragma region remove executeEvent()
// using FORTE_ZephyrIOBase::executeEvent
#pragma endregion remove executeEvent()

void FORTE_ZephyrIO::readInputData(const TEventID paEIID) {
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

void FORTE_ZephyrIO::writeOutputData(const TEventID paEIID) {
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

CIEC_ANY *FORTE_ZephyrIO::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_UpdateInterval;
  }
  return nullptr;
}

CIEC_ANY *FORTE_ZephyrIO::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_ZephyrIO::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
  }
  return nullptr;
}

CDataConnection **FORTE_ZephyrIO::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_UpdateInterval;
  }
  return nullptr;
}

CDataConnection *FORTE_ZephyrIO::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

#pragma region define IOs
void FORTE_ZephyrIO::setConfig() {
  IODeviceController::Config config;
  config.updateInterval = static_cast<CIEC_TIME*>(getDI(
    FORTE_ZephyrIOBase::initialDIOffset +
    FORTE_ZephyrIO::numberOfIOs
    ))->getInMilliSeconds();
  getDeviceController()->setConfig(&config);
}

void FORTE_ZephyrIO::onStartup(CEventChainExecutionThread * const paECET) {
  // Initialize handles
  for (size_t i = 0; i < FORTE_ZephyrIO::numberOfIOs; i++) {
    const auto id = std::string(*static_cast<CIEC_STRING*>(getDI(FORTE_ZephyrIOBase::initialDIOffset + i)));
    // do not use verbatim, only for reference to copy & paste in FBT instance class:
    const gpio_dt_spec* spec = nullptr;
    gpio_flags_t flags = 0;
    if (!spec) {
      DEVLOG_ERROR("FORTE_ZephyrIO::onStartup: id %s, device spec is null\n", id.c_str());
      continue;
    }
    IOHandleGPIODescriptor descr(id, IOMapper::Out, spec, flags);
    initHandle(descr);
  }

  FORTE_ZephyrIOBase::onStartup(paECET);
}
#pragma endregion define IOs
