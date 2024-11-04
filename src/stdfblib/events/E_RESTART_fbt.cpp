/*******************************************************************************
 * Copyright (c) 2005 - 2013 ACIN, Profactor GmbH, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Thomas Strasser, Rene Smodic, Gerhard Ebenhofer,
 *   Martin Melik Merkumians, Ingo Hegny, Matthias Plasch
 *     - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include "E_RESTART_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_RESTART_fbt_gen.cpp"
#endif
#include "../../core/device.h"

DEFINE_FIRMWARE_FB(FORTE_E_RESTART, g_nStringIdE_RESTART)

const TForteInt16 FORTE_E_RESTART::scmEOWithIndexes[] = {-1, -1, -1};
const CStringDictionary::TStringId FORTE_E_RESTART::scmEventOutputNames[] = {g_nStringIdCOLD, g_nStringIdWARM, g_nStringIdSTOP};
const CStringDictionary::TStringId FORTE_E_RESTART::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent};
const SFBInterfaceSpec FORTE_E_RESTART::scmFBInterfaceSpec = {
  0, nullptr, nullptr, nullptr, nullptr,
  3, scmEventOutputNames, scmEventOutputTypeIds, nullptr, scmEOWithIndexes,
  0, nullptr, nullptr,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

FORTE_E_RESTART::FORTE_E_RESTART(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
        CEventSourceFB(paContainer, scmFBInterfaceSpec, paInstanceNameId),
        mEventToSend(cgInvalidEventID),
        conn_COLD(this, 0),
        conn_WARM(this, 1),
        conn_STOP(this, 2) {
  setEventChainExecutor(getResource()->getResourceEventExecution());
};

void FORTE_E_RESTART::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  if(cgExternalEventID == paEIID && cgInvalidEventID != mEventToSend) {
    sendOutputEvent(mEventToSend, paECET);
    if(scmEventSTOPID == mEventToSend) {
      //stop event is sent put the FB finally into the stopped state
      CFunctionBlock::changeExecutionState(EMGMCommandType::Stop);
      // release semaphore to indicate that the stop event was sent now
      mSuspendSemaphore.inc();
    }
  }
}

void FORTE_E_RESTART::readInputData(TEventID) {
  // nothing to do
}

void FORTE_E_RESTART::writeOutputData(TEventID) {
  // nothing to do
}

CIEC_ANY *FORTE_E_RESTART::getDI(size_t) {
  return nullptr;
}

CIEC_ANY *FORTE_E_RESTART::getDO(size_t) {
  return nullptr;
}

CEventConnection *FORTE_E_RESTART::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_COLD;
    case 1: return &conn_WARM;
    case 2: return &conn_STOP;
  }
  return nullptr;
}

CDataConnection **FORTE_E_RESTART::getDIConUnchecked(TPortId) {
  return nullptr;
}

CDataConnection *FORTE_E_RESTART::getDOConUnchecked(TPortId) {
  return nullptr;
}

EMGMResponse FORTE_E_RESTART::changeExecutionState(EMGMCommandType paCommand){
  EMGMResponse eRetVal = CFunctionBlock::changeExecutionState(paCommand);
  if(EMGMResponse::Ready == eRetVal){
    switch(paCommand){
      case EMGMCommandType::Start:
        mEventToSend = (scmEventSTOPID == mEventToSend) ? scmEventWARMID : scmEventCOLDID;
        getDevice()->getDeviceExecution().startNewEventChain(this);
        break;
      case EMGMCommandType::Stop:
        mEventToSend = scmEventSTOPID;
        CFunctionBlock::changeExecutionState(EMGMCommandType::Start);   //keep FB in running state until stop event is delivered.
        getDevice()->getDeviceExecution().startNewEventChain(this);
        // wait until semaphore is released, after STOP eventExecution was completed
        mSuspendSemaphore.waitIndefinitely();
        break;
      default:
        mEventToSend = cgInvalidEventID;
        break;
    }
  }
  return eRetVal;
}
