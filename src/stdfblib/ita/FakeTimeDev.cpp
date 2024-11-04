/*******************************************************************************
 * Copyright (c) 2005, 2024 ACIN, Profactor GmbH, fortiss GmbH
 *                                Primetals Technologies Austria GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer, Rene Smodic, Ingo Hegny
 *               - initial API and implementation and/or initial documentation
 *   Alois Zoitl - Copied and modified from CFakeTimeDev.h
 *******************************************************************************/
#include "FakeTimeDev.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FakeTimeDev_gen.cpp"
#endif
#include "stringdict.h"
#include "../arch/fake_time/faketimerha.h"

const CStringDictionary::TStringId FakeTimeDev::scmDINameIds[] = { g_nStringIdMGR_ID, g_nStringIdFakeTime};
const CStringDictionary::TStringId FakeTimeDev::scmDIDataTypeIds[] = {g_nStringIdWSTRING, g_nStringIdTIME};

const SFBInterfaceSpec FakeTimeDev::scmFBInterfaceSpec = {
  0, nullptr, nullptr, nullptr, nullptr,
  0, nullptr, nullptr, nullptr, nullptr,
  2, scmDINameIds, scmDIDataTypeIds,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

FakeTimeDev::FakeTimeDev(const std::string &paMGR_ID) :
  CDevice(scmFBInterfaceSpec, CStringDictionary::scmInvalidStringId),
      var_MGR_ID(paMGR_ID.c_str()),
      var_FakeTime(),
      conn_MGR_ID(nullptr),
      conn_FakeTime(nullptr),
      MGR(g_nStringIdMGR, *this){
}

bool FakeTimeDev::initialize() {
  if(!CDevice::initialize()) {
    return false;
  }

  if(!MGR.initialize()) {
    return false;
  }

  //we need to manually crate this interface2internal connection as the MGR is not managed by device
  mDConnMGR_ID.setSource(this, 0);
  mDConnMGR_ID.connect(&MGR, g_nStringIdMGR_ID);
  return true;
}

FakeTimeDev::~FakeTimeDev() = default;

int FakeTimeDev::startDevice(){
  CDevice::startDevice();
  MGR.changeExecutionState(EMGMCommandType::Start);
  return 0;
}

void FakeTimeDev::awaitShutdown() {
  MGR.joinResourceThread();
}

EMGMResponse FakeTimeDev::changeExecutionState(EMGMCommandType paCommand){
  EMGMResponse eRetVal = CDevice::changeExecutionState(paCommand);
  if((EMGMResponse::Ready == eRetVal) && (EMGMCommandType::Kill == paCommand)){
    MGR.changeExecutionState(EMGMCommandType::Kill);
  }
  return eRetVal;
}

CIEC_ANY *FakeTimeDev::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_MGR_ID;
    case 1: return &var_FakeTime;
  }
  return nullptr;
}

CDataConnection **FakeTimeDev::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_MGR_ID;
    case 1: return &conn_FakeTime;
  }
  return nullptr;
}

EMGMResponse FakeTimeDev::writeValue(forte::core::TNameIdentifier &paNameList, const std::string & paValue, bool paForce) {
  // parent writeValue is modifying the name list so we need to get the name as backup here
  CStringDictionary::TStringId portName = paNameList.back();
  EMGMResponse eRetVal = CDevice::writeValue(paNameList, paValue, paForce);
  if((EMGMResponse::Ready == eRetVal) && (g_nStringIdFakeTime == portName)){
    //fake time was written, update CFakeTimerHandler
    static_cast<CFakeTimerHandler&>(getTimer()).sleepToTime(var_FakeTime);
  }
  return eRetVal;
}
