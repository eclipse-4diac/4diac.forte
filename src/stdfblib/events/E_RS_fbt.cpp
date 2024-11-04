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

#include "E_RS_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_RS_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_E_RS, g_nStringIdE_RS)

const CStringDictionary::TStringId FORTE_E_RS::scmDataOutputNames[] = {g_nStringIdQ};
const CStringDictionary::TStringId FORTE_E_RS::scmDataOutputTypeIds[] = {g_nStringIdBOOL};
const TForteInt16 FORTE_E_RS::scmEIWithIndexes[] = {-1, -1};
const CStringDictionary::TStringId FORTE_E_RS::scmEventInputNames[] = {g_nStringIdR, g_nStringIdS};
const CStringDictionary::TStringId FORTE_E_RS::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const TDataIOID FORTE_E_RS::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_E_RS::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_E_RS::scmEventOutputNames[] = {g_nStringIdEO};
const CStringDictionary::TStringId FORTE_E_RS::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_E_RS::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEventInputTypeIds, nullptr, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  0, nullptr, nullptr,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_E_RS::FORTE_E_RS(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_conn_Q(var_Q),
    conn_EO(this, 0),
    conn_Q(this, 0, &var_conn_Q) {
}

void FORTE_E_RS::setInitialValues() {
  var_Q = 0_BOOL;
}

void FORTE_E_RS::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  do {
    switch(mECCState) {
      case scmStateSTART:
        if(scmEventSID == paEIID) enterStateSET(paECET);
        else return; //no transition cleared
        break;
      case scmStateSET:
        if(scmEventRID == paEIID) enterStateRESET(paECET);
        else return; //no transition cleared
        break;
      case scmStateRESET:
        if(scmEventSID == paEIID) enterStateSET(paECET);
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

void FORTE_E_RS::enterStateSTART(CEventChainExecutionThread *const) {
  mECCState = scmStateSTART;
}

void FORTE_E_RS::enterStateSET(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateSET;
  alg_SET();
  sendOutputEvent(scmEventEOID, paECET);
}

void FORTE_E_RS::enterStateRESET(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateRESET;
  alg_RESET();
  sendOutputEvent(scmEventEOID, paECET);
}

void FORTE_E_RS::readInputData(TEventID) {
  // nothing to do
}

void FORTE_E_RS::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventEOID: {
      writeData(0, var_Q, conn_Q);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_E_RS::getDI(size_t) {
  return nullptr;
}

CIEC_ANY *FORTE_E_RS::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Q;
  }
  return nullptr;
}

CEventConnection *FORTE_E_RS::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_EO;
  }
  return nullptr;
}

CDataConnection **FORTE_E_RS::getDIConUnchecked(TPortId) {
  return nullptr;
}

CDataConnection *FORTE_E_RS::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Q;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_RS::getVarInternal(size_t) {
  return nullptr;
}

void FORTE_E_RS::alg_SET(void) {

  #line 2 "E_RS.fbt"
  var_Q = true_BOOL;
}

void FORTE_E_RS::alg_RESET(void) {

  #line 6 "E_RS.fbt"
  var_Q = false_BOOL;
}

