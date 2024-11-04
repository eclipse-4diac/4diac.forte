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

#include "E_CTU_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_CTU_fbt_gen.cpp"
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

DEFINE_FIRMWARE_FB(FORTE_E_CTU, g_nStringIdE_CTU)

const CStringDictionary::TStringId FORTE_E_CTU::scmDataInputNames[] = {g_nStringIdPV};
const CStringDictionary::TStringId FORTE_E_CTU::scmDataInputTypeIds[] = {g_nStringIdUINT};
const CStringDictionary::TStringId FORTE_E_CTU::scmDataOutputNames[] = {g_nStringIdQ, g_nStringIdCV};
const CStringDictionary::TStringId FORTE_E_CTU::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdUINT};
const TDataIOID FORTE_E_CTU::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_E_CTU::scmEIWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_E_CTU::scmEventInputNames[] = {g_nStringIdCU, g_nStringIdR};
const CStringDictionary::TStringId FORTE_E_CTU::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const TDataIOID FORTE_E_CTU::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_E_CTU::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_E_CTU::scmEventOutputNames[] = {g_nStringIdCUO, g_nStringIdRO};
const CStringDictionary::TStringId FORTE_E_CTU::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const SFBInterfaceSpec FORTE_E_CTU::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_E_CTU::FORTE_E_CTU(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_conn_Q(var_Q),
    var_conn_CV(var_CV),
    conn_CUO(this, 0),
    conn_RO(this, 1),
    conn_PV(nullptr),
    conn_Q(this, 0, &var_conn_Q),
    conn_CV(this, 1, &var_conn_CV) {
}

void FORTE_E_CTU::setInitialValues() {
  var_PV = 0_UINT;
  var_Q = 0_BOOL;
  var_CV = 0_UINT;
}

void FORTE_E_CTU::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  do {
    switch(mECCState) {
      case scmStateSTART:
        if((scmEventCUID == paEIID) && (func_LT(var_CV, 65535_UINT))) enterStateCU(paECET);
        else
        if(scmEventRID == paEIID) enterStateR(paECET);
        else return; //no transition cleared
        break;
      case scmStateCU:
        if(1) enterStateSTART(paECET);
        else return; //no transition cleared
        break;
      case scmStateR:
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

void FORTE_E_CTU::enterStateSTART(CEventChainExecutionThread *const) {
  mECCState = scmStateSTART;
}

void FORTE_E_CTU::enterStateCU(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateCU;
  alg_CU();
  sendOutputEvent(scmEventCUOID, paECET);
}

void FORTE_E_CTU::enterStateR(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateR;
  alg_R();
  sendOutputEvent(scmEventROID, paECET);
}

void FORTE_E_CTU::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCUID: {
      readData(0, var_PV, conn_PV);
      break;
    }
    default:
      break;
  }
}

void FORTE_E_CTU::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCUOID: {
      writeData(0, var_Q, conn_Q);
      writeData(1, var_CV, conn_CV);
      break;
    }
    case scmEventROID: {
      writeData(0, var_Q, conn_Q);
      writeData(1, var_CV, conn_CV);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_E_CTU::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_PV;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_CTU::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Q;
    case 1: return &var_CV;
  }
  return nullptr;
}

CEventConnection *FORTE_E_CTU::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CUO;
    case 1: return &conn_RO;
  }
  return nullptr;
}

CDataConnection **FORTE_E_CTU::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_PV;
  }
  return nullptr;
}

CDataConnection *FORTE_E_CTU::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Q;
    case 1: return &conn_CV;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_CTU::getVarInternal(size_t) {
  return nullptr;
}

void FORTE_E_CTU::alg_R(void) {

  #line 2 "E_CTU.fbt"
  var_CV = 0_UINT;
  #line 3 "E_CTU.fbt"
  var_Q = false_BOOL;
}

void FORTE_E_CTU::alg_CU(void) {

  #line 7 "E_CTU.fbt"
  var_CV = func_ADD<CIEC_UINT>(var_CV, 1_UINT);
  #line 8 "E_CTU.fbt"
  var_Q = func_GE(var_CV, var_PV);
}

