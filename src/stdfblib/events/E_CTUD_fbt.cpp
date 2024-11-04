/*******************************************************************************
 * Copyright (c) 2013 fortiss GmbH
 *               2019 Johannes Kepler University Linz
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - initial API and implementation and/or initial documentation
 *   Alois Zoitl - fixed bug in down counting
 *******************************************************************************/

#include "E_CTUD_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_CTUD_fbt_gen.cpp"
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

DEFINE_FIRMWARE_FB(FORTE_E_CTUD, g_nStringIdE_CTUD)

const CStringDictionary::TStringId FORTE_E_CTUD::scmDataInputNames[] = {g_nStringIdPV};
const CStringDictionary::TStringId FORTE_E_CTUD::scmDataInputTypeIds[] = {g_nStringIdUINT};
const CStringDictionary::TStringId FORTE_E_CTUD::scmDataOutputNames[] = {g_nStringIdQU, g_nStringIdQD, g_nStringIdCV};
const CStringDictionary::TStringId FORTE_E_CTUD::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdUINT};
const TDataIOID FORTE_E_CTUD::scmEIWith[] = {0, scmWithListDelimiter, 0, scmWithListDelimiter};
const TForteInt16 FORTE_E_CTUD::scmEIWithIndexes[] = {0, -1, -1, 2};
const CStringDictionary::TStringId FORTE_E_CTUD::scmEventInputNames[] = {g_nStringIdCU, g_nStringIdCD, g_nStringIdR, g_nStringIdLD};
const CStringDictionary::TStringId FORTE_E_CTUD::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent};
const TDataIOID FORTE_E_CTUD::scmEOWith[] = {0, 2, 1, scmWithListDelimiter, 0, 2, 1, scmWithListDelimiter, 0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_E_CTUD::scmEOWithIndexes[] = {0, 4, 8};
const CStringDictionary::TStringId FORTE_E_CTUD::scmEventOutputNames[] = {g_nStringIdCO, g_nStringIdRO, g_nStringIdLDO};
const CStringDictionary::TStringId FORTE_E_CTUD::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent};
const SFBInterfaceSpec FORTE_E_CTUD::scmFBInterfaceSpec = {
  4, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  3, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  3, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_E_CTUD::FORTE_E_CTUD(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_conn_QU(var_QU),
    var_conn_QD(var_QD),
    var_conn_CV(var_CV),
    conn_CO(this, 0),
    conn_RO(this, 1),
    conn_LDO(this, 2),
    conn_PV(nullptr),
    conn_QU(this, 0, &var_conn_QU),
    conn_QD(this, 1, &var_conn_QD),
    conn_CV(this, 2, &var_conn_CV) {
}

void FORTE_E_CTUD::setInitialValues() {
  var_PV = 0_UINT;
  var_QU = 0_BOOL;
  var_QD = 0_BOOL;
  var_CV = 0_UINT;
}

void FORTE_E_CTUD::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  do {
    switch(mECCState) {
      case scmStateSTART:
        if((scmEventCUID == paEIID) && (func_LT(var_CV, 65535_UINT))) enterStateCU(paECET);
        else
        if(scmEventRID == paEIID) enterStateR(paECET);
        else
        if((scmEventCDID == paEIID) && (func_GT(var_CV, 0_UINT))) enterStateCD(paECET);
        else
        if(scmEventLDID == paEIID) enterStateLD(paECET);
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
      case scmStateCD:
        if(1) enterStateSTART(paECET);
        else return; //no transition cleared
        break;
      case scmStateLD:
        if(1) enterStateSTART(paECET);
        else return; //no transition cleared
        break;
      default:
        DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 5.", mECCState.operator TForteUInt16 ());
        mECCState = 0; // 0 is always the initial state
        return;
    }
    paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
  } while(true);
}

void FORTE_E_CTUD::enterStateSTART(CEventChainExecutionThread *const) {
  mECCState = scmStateSTART;
}

void FORTE_E_CTUD::enterStateCU(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateCU;
  alg_CountUp();
  alg_UpdateQUQD();
  sendOutputEvent(scmEventCOID, paECET);
}

void FORTE_E_CTUD::enterStateR(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateR;
  alg_Reset();
  alg_UpdateQUQD();
  sendOutputEvent(scmEventROID, paECET);
}

void FORTE_E_CTUD::enterStateCD(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateCD;
  alg_CountDown();
  alg_UpdateQUQD();
  sendOutputEvent(scmEventCOID, paECET);
}

void FORTE_E_CTUD::enterStateLD(CEventChainExecutionThread *const paECET) {
  mECCState = scmStateLD;
  alg_Load();
  alg_UpdateQUQD();
  sendOutputEvent(scmEventLDOID, paECET);
}

void FORTE_E_CTUD::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCUID: {
      readData(0, var_PV, conn_PV);
      break;
    }
    case scmEventLDID: {
      readData(0, var_PV, conn_PV);
      break;
    }
    default:
      break;
  }
}

void FORTE_E_CTUD::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCOID: {
      writeData(0, var_QU, conn_QU);
      writeData(2, var_CV, conn_CV);
      writeData(1, var_QD, conn_QD);
      break;
    }
    case scmEventROID: {
      writeData(0, var_QU, conn_QU);
      writeData(2, var_CV, conn_CV);
      writeData(1, var_QD, conn_QD);
      break;
    }
    case scmEventLDOID: {
      writeData(0, var_QU, conn_QU);
      writeData(1, var_QD, conn_QD);
      writeData(2, var_CV, conn_CV);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_E_CTUD::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_PV;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_CTUD::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QU;
    case 1: return &var_QD;
    case 2: return &var_CV;
  }
  return nullptr;
}

CEventConnection *FORTE_E_CTUD::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CO;
    case 1: return &conn_RO;
    case 2: return &conn_LDO;
  }
  return nullptr;
}

CDataConnection **FORTE_E_CTUD::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_PV;
  }
  return nullptr;
}

CDataConnection *FORTE_E_CTUD::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QU;
    case 1: return &conn_QD;
    case 2: return &conn_CV;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_CTUD::getVarInternal(size_t) {
  return nullptr;
}

void FORTE_E_CTUD::alg_CountUp(void) {

  #line 2 "E_CTUD.fbt"
  var_CV = func_ADD<CIEC_UINT>(var_CV, 1_UINT);
}

void FORTE_E_CTUD::alg_Reset(void) {

  #line 7 "E_CTUD.fbt"
  var_CV = 0_UINT;
}

void FORTE_E_CTUD::alg_Load(void) {

  #line 11 "E_CTUD.fbt"
  var_CV = var_PV;
}

void FORTE_E_CTUD::alg_UpdateQUQD(void) {

  #line 15 "E_CTUD.fbt"
  var_QU = func_GE(var_CV, var_PV);
  #line 16 "E_CTUD.fbt"
  var_QD = func_EQ(var_CV, 0_UINT);
}

void FORTE_E_CTUD::alg_CountDown(void) {

  #line 20 "E_CTUD.fbt"
  var_CV = func_SUB<CIEC_UINT>(var_CV, 1_UINT);
}

