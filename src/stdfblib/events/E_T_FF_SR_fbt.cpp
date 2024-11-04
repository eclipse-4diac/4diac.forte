/*************************************************************************
 *** Copyright (c) 2014, 2024 fortiss GmbH, HR Agrartechnik GmbH
 *** This program and the accompanying materials are made available under the
 *** terms of the Eclipse Public License 2.0 which is available at
 *** http://www.eclipse.org/legal/epl-2.0.
 ***
 *** SPDX-License-Identifier: EPL-2.0
 ***
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: E_T_FF_SR
 *** Description: Event-driven bistable and Toggle
 *** Version:
 ***     1.0: 2017-09-22/Alois Zoitl - fortiss GmbH - initial API and implementation and/or initial documentation
 ***     1.1: 2024-08-27/Franz Höpfinger - HR Agrartechnik GmbH - Copy E_SR and make this FB
 *************************************************************************/

#include "E_T_FF_SR_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_T_FF_SR_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_E_T_FF_SR, g_nStringIdE_T_FF_SR)

const CStringDictionary::TStringId FORTE_E_T_FF_SR::scmDataOutputNames[] = {g_nStringIdQ};
const CStringDictionary::TStringId FORTE_E_T_FF_SR::scmDataOutputTypeIds[] = {g_nStringIdBOOL};
const TForteInt16 FORTE_E_T_FF_SR::scmEIWithIndexes[] = {-1, -1, -1};
const CStringDictionary::TStringId FORTE_E_T_FF_SR::scmEventInputNames[] = {g_nStringIdS, g_nStringIdR, g_nStringIdCLK};
const CStringDictionary::TStringId FORTE_E_T_FF_SR::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent};
const TDataIOID FORTE_E_T_FF_SR::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_E_T_FF_SR::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_E_T_FF_SR::scmEventOutputNames[] = {g_nStringIdEO};
const CStringDictionary::TStringId FORTE_E_T_FF_SR::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_E_T_FF_SR::scmFBInterfaceSpec = {
  3, scmEventInputNames, scmEventInputTypeIds, nullptr, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  0, nullptr, nullptr,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_E_T_FF_SR::FORTE_E_T_FF_SR(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_conn_Q(var_Q),
    conn_EO(this, 0),
    conn_Q(this, 0, &var_conn_Q) {
}

void FORTE_E_T_FF_SR::setInitialValues() {
  var_Q = 0_BOOL;
}

void FORTE_E_T_FF_SR::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  do {
    switch(mECCState) {
      case scmStateSTART:
        if(scmEventSID == paEIID) enterStateSET(paECET);
        else
        if(scmEventCLKID == paEIID) enterStateSET(paECET);
        else return; //no transition cleared
        break;
      case scmStateSET:
        if(scmEventRID == paEIID) enterStateRESET(paECET);
        else
        if(scmEventCLKID == paEIID) enterStateRESET(paECET);
        else return; //no transition cleared
        break;
      case scmStateRESET:
        if(scmEventSID == paEIID) enterStateSET(paECET);
        else
        if(scmEventCLKID == paEIID) enterStateSET(paECET);
        else return; //no transition cleared
        break;
      default:
        DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 3.", mECCState.operator TForteUInt16 ());
        mECCState = 0; // 0 is always the initial state
        return;
    }
    paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
  } while(true);
}

void FORTE_E_T_FF_SR::enterStateSTART(CEventChainExecutionThread *const) {
  mECCState = scmStateSTART;
}

void FORTE_E_T_FF_SR::enterStateSET(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateSET;
  alg_SET();
  sendOutputEvent(scmEventEOID, paECET);
}

void FORTE_E_T_FF_SR::enterStateRESET(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateRESET;
  alg_RESET();
  sendOutputEvent(scmEventEOID, paECET);
}

void FORTE_E_T_FF_SR::readInputData(TEventID) {
  // nothing to do
}

void FORTE_E_T_FF_SR::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventEOID: {
      writeData(0, var_Q, conn_Q);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_E_T_FF_SR::getDI(size_t) {
  return nullptr;
}

CIEC_ANY *FORTE_E_T_FF_SR::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Q;
  }
  return nullptr;
}

CEventConnection *FORTE_E_T_FF_SR::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_EO;
  }
  return nullptr;
}

CDataConnection **FORTE_E_T_FF_SR::getDIConUnchecked(TPortId) {
  return nullptr;
}

CDataConnection *FORTE_E_T_FF_SR::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Q;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_T_FF_SR::getVarInternal(size_t) {
  return nullptr;
}

void FORTE_E_T_FF_SR::alg_SET(void) {

  #line 2 "E_T_FF_SR.fbt"
  var_Q = true_BOOL;
}

void FORTE_E_T_FF_SR::alg_RESET(void) {

  #line 6 "E_T_FF_SR.fbt"
  var_Q = false_BOOL;
}

