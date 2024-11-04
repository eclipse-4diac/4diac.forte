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

#include "E_SWITCH_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_SWITCH_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_E_SWITCH, g_nStringIdE_SWITCH)

const CStringDictionary::TStringId FORTE_E_SWITCH::scmDataInputNames[] = {g_nStringIdG};
const CStringDictionary::TStringId FORTE_E_SWITCH::scmDataInputTypeIds[] = {g_nStringIdBOOL};
const TDataIOID FORTE_E_SWITCH::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_E_SWITCH::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_E_SWITCH::scmEventInputNames[] = {g_nStringIdEI};
const CStringDictionary::TStringId FORTE_E_SWITCH::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TForteInt16 FORTE_E_SWITCH::scmEOWithIndexes[] = {-1, -1};
const CStringDictionary::TStringId FORTE_E_SWITCH::scmEventOutputNames[] = {g_nStringIdEO0, g_nStringIdEO1};
const CStringDictionary::TStringId FORTE_E_SWITCH::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const SFBInterfaceSpec FORTE_E_SWITCH::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEventOutputTypeIds, nullptr, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

FORTE_E_SWITCH::FORTE_E_SWITCH(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    conn_EO0(this, 0),
    conn_EO1(this, 1),
    conn_G(nullptr) {
}

void FORTE_E_SWITCH::setInitialValues() {
  var_G = 0_BOOL;
}

void FORTE_E_SWITCH::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  do {
    switch(mECCState) {
      case scmStateSTART:
        if((scmEventEIID == paEIID) && (func_NOT<CIEC_BOOL>(var_G))) enterStateG0(paECET);
        else
        if((scmEventEIID == paEIID) && (var_G)) enterStateG1(paECET);
        else return; //no transition cleared
        break;
      case scmStateG0:
        if(1) enterStateSTART(paECET);
        else return; //no transition cleared
        break;
      case scmStateG1:
        if(1) enterStateSTART(paECET);
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

void FORTE_E_SWITCH::enterStateSTART(CEventChainExecutionThread *const) {
  mECCState = scmStateSTART;
}

void FORTE_E_SWITCH::enterStateG0(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateG0;
  sendOutputEvent(scmEventEO0ID, paECET);
}

void FORTE_E_SWITCH::enterStateG1(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateG1;
  sendOutputEvent(scmEventEO1ID, paECET);
}

void FORTE_E_SWITCH::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventEIID: {
      readData(0, var_G, conn_G);
      break;
    }
    default:
      break;
  }
}

void FORTE_E_SWITCH::writeOutputData(TEventID) {
  // nothing to do
}

CIEC_ANY *FORTE_E_SWITCH::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_G;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_SWITCH::getDO(size_t) {
  return nullptr;
}

CEventConnection *FORTE_E_SWITCH::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_EO0;
    case 1: return &conn_EO1;
  }
  return nullptr;
}

CDataConnection **FORTE_E_SWITCH::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_G;
  }
  return nullptr;
}

CDataConnection *FORTE_E_SWITCH::getDOConUnchecked(TPortId) {
  return nullptr;
}

CIEC_ANY *FORTE_E_SWITCH::getVarInternal(size_t) {
  return nullptr;
}

