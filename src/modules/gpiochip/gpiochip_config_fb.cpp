/*******************************************************************************
 * Copyright (c) 2023 OFFIS e.V.
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jörg Walter - initial implementation
 *******************************************************************************/

#include "gpiochip_config_fb.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "gpiochip_config_fb_gen.cpp"
#endif

#include "gpiochip_controller.h"

DEFINE_FIRMWARE_FB(GPIOChipConfigFB, g_nStringIdGPIOChip)


const CStringDictionary::TStringId GPIOChipConfigFB::scmDataInputNames[] = { g_nStringIdQI, g_nStringIdVALUE, g_nStringIdChipNumber, g_nStringIdLineNumber, g_nStringIdReadWriteMode, g_nStringIdBiasMode, g_nStringIdActiveLow };

const CStringDictionary::TStringId GPIOChipConfigFB::scmDataInputTypeIds[] = { g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdUINT, g_nStringIdUINT, g_nStringIdUINT, g_nStringIdUINT, g_nStringIdBOOL };

const CStringDictionary::TStringId GPIOChipConfigFB::scmDataOutputNames[] = { g_nStringIdQO, g_nStringIdSTATUS };

const CStringDictionary::TStringId GPIOChipConfigFB::scmDataOutputTypeIds[] = { g_nStringIdBOOL, g_nStringIdWSTRING };

const TForteInt16 GPIOChipConfigFB::scmEIWithIndexes[] = { 0 };
const TDataIOID GPIOChipConfigFB::scmEIWith[] = { 0, 1, 2, 3, 4, 5, 6, scmWithListDelimiter };
const CStringDictionary::TStringId GPIOChipConfigFB::scmEventInputNames[] = { g_nStringIdINIT };
const CStringDictionary::TStringId GPIOChipConfigFB::scmEventInputTypeIds[] = {g_nStringIdEInit};
const TDataIOID GPIOChipConfigFB::scmEOWith[] = { 0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter };
const TForteInt16 GPIOChipConfigFB::scmEOWithIndexes[] = { 0, 3, -1 };
const CStringDictionary::TStringId GPIOChipConfigFB::scmEventOutputNames[] = { g_nStringIdINITO, g_nStringIdIND };
const CStringDictionary::TStringId GPIOChipConfigFB::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const SFBInterfaceSpec GPIOChipConfigFB::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  2,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,
  7,  scmDataInputNames, scmDataInputTypeIds,
  2,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};

void GPIOChipConfigFB::setInitialValues() {
  ChipNumber() = 0_UINT;
  LineNumber() = 0_UINT;
  ReadWriteMode() = 0_UINT;
  BiasMode() = 0_UINT;
  ActiveLow() = 0_BOOL;
}

void GPIOChipConfigFB::readInputData(const TEventID paEIID) {
  for (auto i = 0; i < 7; i++) {
    readData(i, *mDIs[i], mDIConns[i]);
  }
}

void GPIOChipConfigFB::writeOutputData(const TEventID paEIID) {
  for (auto i = 0; i < 2; i++) {
    writeData(i, *mDOs[i], mDOConns[i]);
  }
}

forte::core::io::IODeviceController* GPIOChipConfigFB::createDeviceController(CDeviceExecution &paDeviceExecution) {
  return new GPIOChipController(paDeviceExecution);
}

void GPIOChipConfigFB::setConfig() {
  GPIOChipController::Config config;
  config.mChipNumber = TForteUInt16(ChipNumber());
  config.mLineNumber = TForteUInt16(LineNumber());
  config.mReadWriteMode = GPIOChipController::Config::ReadWriteMode(TForteUInt16(ReadWriteMode()));
  config.mBiasMode = GPIOChipController::Config::BiasMode(TForteUInt16(BiasMode()));
  config.mActiveLow = ActiveLow();
  getDeviceController()->setConfig(&config);
}

void GPIOChipConfigFB::onStartup(CEventChainExecutionThread * const paECET) {
  GPIOChipController::HandleDescriptor desc = GPIOChipController::HandleDescriptor(
    VALUE().getValue(),
    TForteUInt16(ReadWriteMode())? forte::core::io::IOMapper::Out : forte::core::io::IOMapper::In
  );
  initHandle(&desc);

  forte::core::io::IOConfigFBController::started(paECET);
}



