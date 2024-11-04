/*******************************************************************************
 * Copyright (c) 2006 - 2013 ACIN, Profactor GmbH, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer, Ingo Hegny
 *     - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "E_REND_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_REND_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_E_REND, g_nStringIdE_REND)

const TForteInt16 FORTE_E_REND::scmEIWithIndexes[] = {-1, -1, -1};
const CStringDictionary::TStringId FORTE_E_REND::scmEventInputNames[] = {g_nStringIdEI1, g_nStringIdEI2, g_nStringIdR};
const CStringDictionary::TStringId FORTE_E_REND::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent};
const TForteInt16 FORTE_E_REND::scmEOWithIndexes[] = {-1};
const CStringDictionary::TStringId FORTE_E_REND::scmEventOutputNames[] = {g_nStringIdEO};
const CStringDictionary::TStringId FORTE_E_REND::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_E_REND::scmFBInterfaceSpec = {
  3, scmEventInputNames, scmEventInputTypeIds, nullptr, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, nullptr, scmEOWithIndexes,
  0, nullptr, nullptr,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

FORTE_E_REND::FORTE_E_REND(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    conn_EO(this, 0) {
}

void FORTE_E_REND::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  do {
    switch(mECCState) {
      case scmStateSTART:
        if(scmEventEI2ID == paEIID) enterStateEI2(paECET);
        else
        if(scmEventEI1ID == paEIID) enterStateEI1(paECET);
        else return; //no transition cleared
        break;
      case scmStateEI1:
        if(scmEventRID == paEIID) enterStateSTART(paECET);
        else
        if(scmEventEI2ID == paEIID) enterStateEO(paECET);
        else return; //no transition cleared
        break;
      case scmStateEO:
        if(1) enterStateSTART(paECET);
        else return; //no transition cleared
        break;
      case scmStateEI2:
        if(scmEventRID == paEIID) enterStateSTART(paECET);
        else
        if(scmEventEI1ID == paEIID) enterStateEO(paECET);
        else return; //no transition cleared
        break;
      default:
        DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 4.", mECCState.operator TForteUInt16 ());
        mECCState = 0; // 0 is always the initial state
        return;
    }
    paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
  } while(true);
}

void FORTE_E_REND::enterStateSTART(CEventChainExecutionThread *const) {
  mECCState = scmStateSTART;
}

void FORTE_E_REND::enterStateEI1(CEventChainExecutionThread *const) {
  mECCState = scmStateEI1;
}

void FORTE_E_REND::enterStateEO(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateEO;
  sendOutputEvent(scmEventEOID, paECET);
}

void FORTE_E_REND::enterStateEI2(CEventChainExecutionThread *const) {
  mECCState = scmStateEI2;
}

void FORTE_E_REND::readInputData(TEventID) {
  // nothing to do
}

void FORTE_E_REND::writeOutputData(TEventID) {
  // nothing to do
}

CIEC_ANY *FORTE_E_REND::getDI(size_t) {
  return nullptr;
}

CIEC_ANY *FORTE_E_REND::getDO(size_t) {
  return nullptr;
}

CEventConnection *FORTE_E_REND::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_EO;
  }
  return nullptr;
}

CDataConnection **FORTE_E_REND::getDIConUnchecked(TPortId) {
  return nullptr;
}

CDataConnection *FORTE_E_REND::getDOConUnchecked(TPortId) {
  return nullptr;
}

CIEC_ANY *FORTE_E_REND::getVarInternal(size_t) {
  return nullptr;
}

