/*******************************************************************************
 * Copyright (c) 2012, 20113, 2015 Profactor GmbH, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Gerhard Ebenhofer, Alois Zoitl
 *   - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "FB_RANDOM_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FB_RANDOM_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_uint.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_FB_RANDOM, g_nStringIdFB_RANDOM)

const CStringDictionary::TStringId FORTE_FB_RANDOM::scmDataInputNames[] = {g_nStringIdSEED};
const CStringDictionary::TStringId FORTE_FB_RANDOM::scmDataInputTypeIds[] = {g_nStringIdUINT};
const CStringDictionary::TStringId FORTE_FB_RANDOM::scmDataOutputNames[] = {g_nStringIdVAL};
const CStringDictionary::TStringId FORTE_FB_RANDOM::scmDataOutputTypeIds[] = {g_nStringIdREAL};
const TDataIOID FORTE_FB_RANDOM::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FB_RANDOM::scmEIWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_FB_RANDOM::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_FB_RANDOM::scmEventInputTypeIds[] = {g_nStringIdEInit, g_nStringIdEvent};
const TDataIOID FORTE_FB_RANDOM::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FB_RANDOM::scmEOWithIndexes[] = {-1, 0};
const CStringDictionary::TStringId FORTE_FB_RANDOM::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_FB_RANDOM::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const SFBInterfaceSpec FORTE_FB_RANDOM::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_FB_RANDOM::FORTE_FB_RANDOM(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_SEED(0_UINT),
    var_conn_VAL(var_VAL),
    conn_INITO(this, 0),
    conn_CNF(this, 1),
    conn_SEED(nullptr),
    conn_VAL(this, 0, &var_conn_VAL) {
      mRandomGenerator.seed(mRandomDevice());
}

void FORTE_FB_RANDOM::setInitialValues() {
  var_SEED = 0_UINT;
  var_VAL = 0_REAL;
}

void FORTE_FB_RANDOM::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  do {
    switch(mECCState) {
      case scmStateSTART:
        if(scmEventREQID == paEIID) enterStateREQ(paECET);
        else
        if(scmEventINITID == paEIID) enterStateState(paECET);
        else return; //no transition cleared
        break;
      case scmStateREQ:
        if(1) enterStateSTART(paECET);
        else return; //no transition cleared
        break;
      case scmStateState:
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

void FORTE_FB_RANDOM::enterStateSTART(CEventChainExecutionThread *const) {
  mECCState = scmStateSTART;
}

void FORTE_FB_RANDOM::enterStateREQ(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateREQ;
  alg_REQ();
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FB_RANDOM::enterStateState(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateState;
  alg_INIT();
  sendOutputEvent(scmEventINITOID, paECET);
}

void FORTE_FB_RANDOM::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_SEED, conn_SEED);
      break;
    }
    default:
      break;
  }
}

void FORTE_FB_RANDOM::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_VAL, conn_VAL);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_FB_RANDOM::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_SEED;
  }
  return nullptr;
}

CIEC_ANY *FORTE_FB_RANDOM::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_VAL;
  }
  return nullptr;
}

CEventConnection *FORTE_FB_RANDOM::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_FB_RANDOM::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_SEED;
  }
  return nullptr;
}

CDataConnection *FORTE_FB_RANDOM::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_VAL;
  }
  return nullptr;
}

CIEC_ANY *FORTE_FB_RANDOM::getVarInternal(size_t) {
  return nullptr;
}

void FORTE_FB_RANDOM::alg_INIT(void) {
  if (static_cast<CIEC_UINT::TValueType>(var_SEED) == 0) {
    mRandomGenerator.seed(mRandomDevice());
  } else {
    const CIEC_UINT::TValueType seedValue = static_cast<CIEC_UINT::TValueType>(var_SEED);
    mRandomGenerator.seed(seedValue);
  }
}


void FORTE_FB_RANDOM::alg_REQ(void) {
  var_VAL = CIEC_REAL(mDistribution(mRandomGenerator));
}


