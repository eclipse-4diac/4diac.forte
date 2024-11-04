/*******************************************************************************
 * Copyright (c) 2005, 2023 ACIN, Profactor GmbH, fortiss GmbH
 *                          Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Gunnar Grabmair, Ingo Hegny, GErhard Ebenhofer
 *    - initial API and implementation and/or initial documentation
 *   Martin Jobst - add generic readInputData and writeOutputData
 *******************************************************************************/
#include "timedfb.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "timedfb_gen.cpp"
#endif

#include "resource.h"
#include "criticalregion.h"

const CStringDictionary::TStringId CTimedFB::scmEINameIds[] = {g_nStringIdSTART, g_nStringIdSTOP};
const CStringDictionary::TStringId CTimedFB::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const CStringDictionary::TStringId CTimedFB::scmEONameIds[] = {g_nStringIdEO};
const CStringDictionary::TStringId CTimedFB::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};

const CStringDictionary::TStringId CTimedFB::scmDINameIds[] = {g_nStringIdDT};
const CStringDictionary::TStringId CTimedFB::scmDIDataTypeNameIds[] = {g_nStringIdTIME};

const SFBInterfaceSpec CTimedFB::scmFBInterfaceSpec = {
  2, scmEINameIds, scmEventInputTypeIds,nullptr, nullptr,
  1, scmEONameIds, scmEventOutputTypeIds,nullptr, nullptr,
  1, scmDINameIds, scmDIDataTypeNameIds,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

CTimedFB::CTimedFB(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
      CEventSourceFB(paContainer, scmFBInterfaceSpec, paInstanceNameId),
      var_DT(0_TIME),
      conn_DT(nullptr),
      conn_EO(this, 0) {
  setEventChainExecutor(getResource()->getResourceEventExecution());
  mActive = false;
}

void CTimedFB::executeEvent(TEventID paEIID, CEventChainExecutionThread * const paECET){
  switch(paEIID){
    case cgExternalEventID:
      sendOutputEvent(csmEOID, paECET);
      break;
    case csmEventSTOPID:
      if(mActive){
        getTimer().unregisterTimedFB(this);
        mActive = false;
      }
      break;
    default:
      break;
  }
}

void CTimedFB::readInputData(TEventID) {
  readData(0, var_DT, conn_DT);
}

void CTimedFB::writeOutputData(TEventID) {
}

CIEC_ANY *CTimedFB::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_DT;
  }
  return nullptr;
}

CIEC_ANY *CTimedFB::getDO(const size_t) {
  return nullptr;
}

CEventConnection *CTimedFB::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_EO;
  }
  return nullptr;
}

CDataConnection **CTimedFB::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_DT;
  }
  return nullptr;
}

CDataConnection *CTimedFB::getDOConUnchecked(const TPortId) {
  return nullptr;
}

EMGMResponse CTimedFB::changeExecutionState(EMGMCommandType paCommand){
  EMGMResponse eRetVal = CFunctionBlock::changeExecutionState(paCommand);
  if((EMGMResponse::Ready == eRetVal) && ((EMGMCommandType::Stop == paCommand) || (EMGMCommandType::Kill == paCommand)) && mActive) {
    getTimer().unregisterTimedFB(this);
    mActive = false;
  }
  return eRetVal;
}
