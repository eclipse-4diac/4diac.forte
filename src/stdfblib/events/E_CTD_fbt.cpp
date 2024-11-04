/*******************************************************************************
 * Copyright (c) 2014 ACIN
 *               2019 Johannes Kepler University Linz
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger - initial API and implementation and/or initial documentation
 *   Alois Zoitl - fixed bug in down counting
 *******************************************************************************/

#include "E_CTD_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_CTD_fbt_gen.cpp"
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

DEFINE_FIRMWARE_FB(FORTE_E_CTD, g_nStringIdE_CTD)

const CStringDictionary::TStringId FORTE_E_CTD::scmDataInputNames[] = {g_nStringIdPV};
const CStringDictionary::TStringId FORTE_E_CTD::scmDataInputTypeIds[] = {g_nStringIdUINT};
const CStringDictionary::TStringId FORTE_E_CTD::scmDataOutputNames[] = {g_nStringIdQ, g_nStringIdCV};
const CStringDictionary::TStringId FORTE_E_CTD::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdUINT};
const TDataIOID FORTE_E_CTD::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_E_CTD::scmEIWithIndexes[] = {-1, 0};
const CStringDictionary::TStringId FORTE_E_CTD::scmEventInputNames[] = {g_nStringIdCD, g_nStringIdLD};
const CStringDictionary::TStringId FORTE_E_CTD::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const TDataIOID FORTE_E_CTD::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_E_CTD::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_E_CTD::scmEventOutputNames[] = {g_nStringIdCDO, g_nStringIdLDO};
const CStringDictionary::TStringId FORTE_E_CTD::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const SFBInterfaceSpec FORTE_E_CTD::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_E_CTD::FORTE_E_CTD(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_conn_Q(var_Q),
    var_conn_CV(var_CV),
    conn_CDO(this, 0),
    conn_LDO(this, 1),
    conn_PV(nullptr),
    conn_Q(this, 0, &var_conn_Q),
    conn_CV(this, 1, &var_conn_CV) {
}

void FORTE_E_CTD::setInitialValues() {
  var_PV = 0_UINT;
  var_Q = 0_BOOL;
  var_CV = 0_UINT;
}

void FORTE_E_CTD::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  do {
    switch(mECCState) {
      case scmStateSTART:
        if((scmEventCDID == paEIID) && (func_GT(var_CV, 0_UINT))) enterStateCD(paECET);
        else
        if(scmEventLDID == paEIID) enterStateLD(paECET);
        else return; //no transition cleared
        break;
      case scmStateCD:
        if(1) enterStateSTART(paECET);
        else return; //no transition cleared
        break;
      case scmStateLD:
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

void FORTE_E_CTD::enterStateSTART(CEventChainExecutionThread *const) {
  mECCState = scmStateSTART;
}

void FORTE_E_CTD::enterStateCD(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateCD;
  alg_CD();
  sendOutputEvent(scmEventCDOID, paECET);
}

void FORTE_E_CTD::enterStateLD(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateLD;
  alg_LOAD();
  sendOutputEvent(scmEventLDOID, paECET);
}

void FORTE_E_CTD::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventLDID: {
      readData(0, var_PV, conn_PV);
      break;
    }
    default:
      break;
  }
}

void FORTE_E_CTD::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCDOID: {
      writeData(0, var_Q, conn_Q);
      writeData(1, var_CV, conn_CV);
      break;
    }
    case scmEventLDOID: {
      writeData(0, var_Q, conn_Q);
      writeData(1, var_CV, conn_CV);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_E_CTD::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_PV;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_CTD::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Q;
    case 1: return &var_CV;
  }
  return nullptr;
}

CEventConnection *FORTE_E_CTD::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CDO;
    case 1: return &conn_LDO;
  }
  return nullptr;
}

CDataConnection **FORTE_E_CTD::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_PV;
  }
  return nullptr;
}

CDataConnection *FORTE_E_CTD::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Q;
    case 1: return &conn_CV;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_CTD::getVarInternal(size_t) {
  return nullptr;
}

void FORTE_E_CTD::alg_CD(void) {

  #line 2 "E_CTD.fbt"
  var_CV = func_SUB<CIEC_UINT>(var_CV, 1_UINT);
  #line 3 "E_CTD.fbt"
  var_Q = func_EQ(var_CV, 0_UINT);
}

void FORTE_E_CTD::alg_LOAD(void) {

  #line 8 "E_CTD.fbt"
  var_CV = var_PV;
  #line 9 "E_CTD.fbt"
  var_Q = func_EQ(var_CV, 0_UINT);
}

