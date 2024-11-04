/*******************************************************************************
 * Copyright (c) 2006 - 2014 ACIN, Profactor GmbH, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer, Ingo Hegny, Monika Wenger,
 *    - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include "RT_E_CYCLE_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RT_E_CYCLE_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_RT_E_CYCLE, g_nStringIdRT_E_CYCLE)

const CStringDictionary::TStringId FORTE_RT_E_CYCLE::scmDataInputNames[] = {g_nStringIdDT, g_nStringIdDeadline, g_nStringIdWCET};
const CStringDictionary::TStringId FORTE_RT_E_CYCLE::scmDataInputTypeIds[] = {g_nStringIdTIME, g_nStringIdTIME, g_nStringIdTIME};
const CStringDictionary::TStringId FORTE_RT_E_CYCLE::scmDataOutputNames[] = {g_nStringIdQO};
const CStringDictionary::TStringId FORTE_RT_E_CYCLE::scmDataOutputTypeIds[] = {g_nStringIdBOOL};
const TDataIOID FORTE_RT_E_CYCLE::scmEIWith[] = {0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_RT_E_CYCLE::scmEIWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_RT_E_CYCLE::scmEventInputNames[] = {g_nStringIdSTART, g_nStringIdSTOP};
const CStringDictionary::TStringId FORTE_RT_E_CYCLE::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const TForteInt16 FORTE_RT_E_CYCLE::scmEOWithIndexes[] = {-1};
const CStringDictionary::TStringId FORTE_RT_E_CYCLE::scmEventOutputNames[] = {g_nStringIdEO};
const CStringDictionary::TStringId FORTE_RT_E_CYCLE::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_RT_E_CYCLE::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, nullptr, scmEOWithIndexes,
  3, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_RT_E_CYCLE::FORTE_RT_E_CYCLE(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
        CEventSourceFB(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    conn_EO(this, 0),
    conn_DT(nullptr),
    conn_Deadline(nullptr),
    conn_WCET(nullptr),
    conn_QO(this, 0, &var_conn_QO) {
  setEventChainExecutor(&mECEO);
};

void FORTE_RT_E_CYCLE::setInitialValues() {
  var_DT = 0_TIME;
  var_Deadline = 0_TIME;
  var_WCET = 0_TIME;
  var_QO = 0_BOOL;
}

void FORTE_RT_E_CYCLE::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case cgExternalEventID:
      sendOutputEvent(scmEventEOID, paECET);
      break;
    case scmEventSTOPID:
      if(mActive){
        mECEO.setDeadline(CIEC_TIME(static_cast<CIEC_TIME::TValueType>(0)));
        getTimer().unregisterTimedFB(this);
        mActive = false;
      }
      break;
    case scmEventSTARTID:
      if(!mActive){
        mECEO.setDeadline(var_Deadline);
        getTimer().registerPeriodicTimedFB(this, var_DT);
        mActive = true;
      }
      break;
  }
}

EMGMResponse FORTE_RT_E_CYCLE::changeExecutionState(EMGMCommandType paCommand){
  mECEO.changeExecutionState(paCommand);
  EMGMResponse eRetVal = CFunctionBlock::changeExecutionState(paCommand);
  if((EMGMResponse::Ready == eRetVal) && ((EMGMCommandType::Stop == paCommand) || (EMGMCommandType::Kill == paCommand)) && mActive) {
    getTimer().unregisterTimedFB(this);
    mActive = false;
  }
  return eRetVal;
}

void FORTE_RT_E_CYCLE::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventSTARTID: {
      readData(0, var_DT, conn_DT);
      readData(1, var_Deadline, conn_Deadline);
      readData(2, var_WCET, conn_WCET);
      break;
    }
    case scmEventSTOPID: {
      break;
    }
    default:
      break;
  }
}

void FORTE_RT_E_CYCLE::writeOutputData(TEventID) {
}

CIEC_ANY *FORTE_RT_E_CYCLE::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_DT;
    case 1: return &var_Deadline;
    case 2: return &var_WCET;
  }
  return nullptr;
}

CIEC_ANY *FORTE_RT_E_CYCLE::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
  }
  return nullptr;
}

CEventConnection *FORTE_RT_E_CYCLE::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_EO;
  }
  return nullptr;
}

CDataConnection **FORTE_RT_E_CYCLE::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_DT;
    case 1: return &conn_Deadline;
    case 2: return &conn_WCET;
  }
  return nullptr;
}

CDataConnection *FORTE_RT_E_CYCLE::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
  }
  return nullptr;
}
