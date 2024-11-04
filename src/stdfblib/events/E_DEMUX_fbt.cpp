/*******************************************************************************
 * Copyright (c) 2006 - 2013 ACIN, Profactor GmbH, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer, Martin Melik Merkumians, Ingo Hegny
 *     - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "E_DEMUX_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_DEMUX_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_bool.h"
#include "forte_uint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_E_DEMUX, g_nStringIdE_DEMUX)

const CStringDictionary::TStringId FORTE_E_DEMUX::scmDataInputNames[] = {g_nStringIdK};
const CStringDictionary::TStringId FORTE_E_DEMUX::scmDataInputTypeIds[] = {g_nStringIdUINT};
const TDataIOID FORTE_E_DEMUX::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_E_DEMUX::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_E_DEMUX::scmEventInputNames[] = {g_nStringIdEI};
const CStringDictionary::TStringId FORTE_E_DEMUX::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TForteInt16 FORTE_E_DEMUX::scmEOWithIndexes[] = {-1, -1, -1, -1};
const CStringDictionary::TStringId FORTE_E_DEMUX::scmEventOutputNames[] = {g_nStringIdEO0, g_nStringIdEO1, g_nStringIdEO2, g_nStringIdEO3};
const CStringDictionary::TStringId FORTE_E_DEMUX::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent};
const SFBInterfaceSpec FORTE_E_DEMUX::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  4, scmEventOutputNames, scmEventOutputTypeIds, nullptr, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

FORTE_E_DEMUX::FORTE_E_DEMUX(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    conn_EO0(this, 0),
    conn_EO1(this, 1),
    conn_EO2(this, 2),
    conn_EO3(this, 3),
    conn_K(nullptr) {
}

void FORTE_E_DEMUX::setInitialValues() {
  var_K = 0_UINT;
}

void FORTE_E_DEMUX::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  do {
    switch(mECCState) {
      case scmStateSTART:
        if(scmEventEIID == paEIID) enterStateState(paECET);
        else return; //no transition cleared
        break;
      case scmStateState:
        if(func_EQ(var_K, 0_UINT)) enterStateState_1(paECET);
        else
        if(func_EQ(var_K, 1_UINT)) enterStateState_2(paECET);
        else
        if(func_EQ(var_K, 2_UINT)) enterStateState_3(paECET);
        else
        if(func_EQ(var_K, 3_UINT)) enterStateState_4(paECET);
        else
        if(func_GT(var_K, 3_UINT)) enterStateSTART(paECET);
        else return; //no transition cleared
        break;
      case scmStateState_1:
        if(1) enterStateSTART(paECET);
        else return; //no transition cleared
        break;
      case scmStateState_2:
        if(1) enterStateSTART(paECET);
        else return; //no transition cleared
        break;
      case scmStateState_3:
        if(1) enterStateSTART(paECET);
        else return; //no transition cleared
        break;
      case scmStateState_4:
        if(1) enterStateSTART(paECET);
        else return; //no transition cleared
        break;
      default:
        DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 6.", mECCState.operator TForteUInt16 ());
        mECCState = 0; // 0 is always the initial state
        return;
    }
    paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
  } while(true);
}

void FORTE_E_DEMUX::enterStateSTART(CEventChainExecutionThread *const) {
  mECCState = scmStateSTART;
}

void FORTE_E_DEMUX::enterStateState(CEventChainExecutionThread *const) {
  mECCState = scmStateState;
}

void FORTE_E_DEMUX::enterStateState_1(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateState_1;
  sendOutputEvent(scmEventEO0ID, paECET);
}

void FORTE_E_DEMUX::enterStateState_2(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateState_2;
  sendOutputEvent(scmEventEO1ID, paECET);
}

void FORTE_E_DEMUX::enterStateState_3(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateState_3;
  sendOutputEvent(scmEventEO2ID, paECET);
}

void FORTE_E_DEMUX::enterStateState_4(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateState_4;
  sendOutputEvent(scmEventEO3ID, paECET);
}

void FORTE_E_DEMUX::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventEIID: {
      readData(0, var_K, conn_K);
      break;
    }
    default:
      break;
  }
}

void FORTE_E_DEMUX::writeOutputData(TEventID) {
  // nothing to do
}

CIEC_ANY *FORTE_E_DEMUX::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_K;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_DEMUX::getDO(size_t) {
  return nullptr;
}

CEventConnection *FORTE_E_DEMUX::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_EO0;
    case 1: return &conn_EO1;
    case 2: return &conn_EO2;
    case 3: return &conn_EO3;
  }
  return nullptr;
}

CDataConnection **FORTE_E_DEMUX::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_K;
  }
  return nullptr;
}

CDataConnection *FORTE_E_DEMUX::getDOConUnchecked(TPortId) {
  return nullptr;
}

CIEC_ANY *FORTE_E_DEMUX::getVarInternal(size_t) {
  return nullptr;
}

