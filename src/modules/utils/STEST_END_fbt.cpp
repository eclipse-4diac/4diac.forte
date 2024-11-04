/*******************************************************************************
 * Copyright (c) 2013 - 2015 Profactor GmbH, ACIN, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Michael Hofmann, Alois Zoitl
 *   - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "STEST_END_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "STEST_END_fbt_gen.cpp"
#endif

#include "../../stdfblib/ita/RMT_DEV.h"
#include "forte_thread.h"

DEFINE_FIRMWARE_FB(FORTE_STEST_END, g_nStringIdSTEST_END)

const TForteInt16 FORTE_STEST_END::scmEIWithIndexes[] = {-1};
const CStringDictionary::TStringId FORTE_STEST_END::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_STEST_END::scmEventInputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_STEST_END::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, nullptr, scmEIWithIndexes,
  0, nullptr, nullptr, nullptr, nullptr,
  0, nullptr, nullptr,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

FORTE_STEST_END::FORTE_STEST_END(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId) {
};

void FORTE_STEST_END::executeEvent(TEventID paEIID, CEventChainExecutionThread *const) {
  if(scmEventREQID == paEIID){
    CThread::sleepThread(250); //avoid killing the device before it was properly started (DEV_MGR still was initializing the ipCommlayer when it was killed)
    getDevice()->changeExecutionState(EMGMCommandType::Kill);
  }
}

void FORTE_STEST_END::readInputData(TEventID) {
  // nothing to do
}

void FORTE_STEST_END::writeOutputData(TEventID) {
  // nothing to do
}

CIEC_ANY *FORTE_STEST_END::getDI(size_t) {
  return nullptr;
}

CIEC_ANY *FORTE_STEST_END::getDO(size_t) {
  return nullptr;
}

CEventConnection *FORTE_STEST_END::getEOConUnchecked(TPortId) {
  return nullptr;
}

CDataConnection **FORTE_STEST_END::getDIConUnchecked(TPortId) {
  return nullptr;
}

CDataConnection *FORTE_STEST_END::getDOConUnchecked(TPortId) {
  return nullptr;
}

