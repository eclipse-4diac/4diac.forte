/*******************************************************************************
 * Copyright (c) 2005, 2015 ACIN, Profactor GmbH, fortiss GmbH,
 *                          Primetals Technologies Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer, Rene Smodic, Ingo Hegny
 *    - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include "RMT_DEV.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RMT_DEV_gen.cpp"
#endif
#include <stringdict.h>

const CStringDictionary::TStringId RMT_DEV::scmDINameIds[] = { g_nStringIdMGR_ID };
const CStringDictionary::TStringId RMT_DEV::scmDIDataTypeIds[] = {g_nStringIdWSTRING};

const SFBInterfaceSpec RMT_DEV::scmFBInterfaceSpec = {
  0, nullptr, nullptr, nullptr, nullptr,
  0, nullptr, nullptr, nullptr, nullptr,
  1, scmDINameIds, scmDIDataTypeIds,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

RMT_DEV::RMT_DEV(const std::string &paMGR_ID) :
        CDevice(scmFBInterfaceSpec, CStringDictionary::scmInvalidStringId),
        var_MGR_ID(paMGR_ID.c_str()),
        conn_MGR_ID(nullptr),
        MGR(g_nStringIdMGR, *this) {
}

bool RMT_DEV::initialize() {
  if(!CDevice::initialize()) {
    return false;
  }

  if(!MGR.initialize()) {
    return false;
  }

  //we nee to manually crate this interface2internal connection as the MGR is not managed by device
  mDConnMGR_ID.setSource(this, 0);
  mDConnMGR_ID.connect(&MGR, g_nStringIdMGR_ID);
  return true;
}

RMT_DEV::~RMT_DEV() = default;

int RMT_DEV::startDevice(){
  CDevice::startDevice();
  MGR.changeExecutionState(EMGMCommandType::Start);
  return 0;
}

void RMT_DEV::awaitShutdown() {
  MGR.joinResourceThread();
}

EMGMResponse RMT_DEV::changeExecutionState(EMGMCommandType paCommand){
  EMGMResponse eRetVal = CDevice::changeExecutionState(paCommand);
  if((EMGMResponse::Ready == eRetVal) && (EMGMCommandType::Kill == paCommand)){
    MGR.changeExecutionState(EMGMCommandType::Kill);
  }
  return eRetVal;
}

void RMT_DEV::setMGR_ID(const std::string& paVal){
  var_MGR_ID.fromString(paVal.c_str());
}

CIEC_ANY *RMT_DEV::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_MGR_ID;
  }
  return nullptr;
}

CDataConnection **RMT_DEV::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_MGR_ID;
  }
  return nullptr;
}

