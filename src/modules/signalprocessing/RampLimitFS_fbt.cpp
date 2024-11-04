/*************************************************************************  
 *** Copyright (c) 2024 HR Agrartechnik GmbH  
 *** This program and the accompanying materials are made available under the  
 *** terms of the Eclipse Public License 2.0 which is available at  
 *** http://www.eclipse.org/legal/epl-2.0.  
 ***  
 *** SPDX-License-Identifier: EPL-2.0  
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: RampLimitFS
 *** Description: Setpoint Ramp: Step up and down Values with Fast and Slow mode
 *** Version:
 ***     1.0: 2024-09-20/Franz Höpfinger - HR Agrartechnik GmbH -
 ***     1.1: 2024-10-02/Franz Höpfinger - HR Agrartechnik GmbH - Rename to RampLimitFS
 *************************************************************************/

#include "RampLimitFS_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RampLimitFS_fbt_gen.cpp"
#endif

#include "forte_any_elementary_variant.h"
#include "forte_any_num_variant.h"
#include "forte_dint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_signalprocessing__RampLimitFS, g_nStringIdsignalprocessing__RampLimitFS)

const CStringDictionary::TStringId FORTE_signalprocessing__RampLimitFS::scmDataInputNames[] = {g_nStringIdPV, g_nStringIdVAL_ZERO, g_nStringIdSLOW, g_nStringIdFAST, g_nStringIdVAL_FULL};
const CStringDictionary::TStringId FORTE_signalprocessing__RampLimitFS::scmDataInputTypeIds[] = {g_nStringIdDINT, g_nStringIdDINT, g_nStringIdDINT, g_nStringIdDINT, g_nStringIdDINT};
const CStringDictionary::TStringId FORTE_signalprocessing__RampLimitFS::scmDataOutputNames[] = {g_nStringIdOUT};
const CStringDictionary::TStringId FORTE_signalprocessing__RampLimitFS::scmDataOutputTypeIds[] = {g_nStringIdDINT};
const TDataIOID FORTE_signalprocessing__RampLimitFS::scmEIWith[] = {1, scmWithListDelimiter, 2, scmWithListDelimiter, 3, scmWithListDelimiter, 2, scmWithListDelimiter, 3, scmWithListDelimiter, 4, scmWithListDelimiter, 0, scmWithListDelimiter};
const TForteInt16 FORTE_signalprocessing__RampLimitFS::scmEIWithIndexes[] = {0, 2, 4, 6, 8, 10, 12};
const CStringDictionary::TStringId FORTE_signalprocessing__RampLimitFS::scmEventInputNames[] = {g_nStringIdZERO, g_nStringIdUP_SLOW, g_nStringIdUP_FAST, g_nStringIdDOWN_SLOW, g_nStringIdDOWN_FAST, g_nStringIdFULL, g_nStringIdLOAD};
const CStringDictionary::TStringId FORTE_signalprocessing__RampLimitFS::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent};
const TDataIOID FORTE_signalprocessing__RampLimitFS::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_signalprocessing__RampLimitFS::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_signalprocessing__RampLimitFS::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_signalprocessing__RampLimitFS::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_signalprocessing__RampLimitFS::scmFBInterfaceSpec = {
  7, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  5, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_signalprocessing__RampLimitFS::FORTE_signalprocessing__RampLimitFS(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_PV(nullptr),
    conn_VAL_ZERO(nullptr),
    conn_SLOW(nullptr),
    conn_FAST(nullptr),
    conn_VAL_FULL(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
}

void FORTE_signalprocessing__RampLimitFS::setInitialValues() {
  var_PV = 0_DINT;
  var_VAL_ZERO = 0_DINT;
  var_SLOW = 0_DINT;
  var_FAST = 0_DINT;
  var_VAL_FULL = 0_DINT;
  var_OUT = 0_DINT;
}

void FORTE_signalprocessing__RampLimitFS::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventZEROID:
      alg_ZERO();
      break;
    case scmEventUP_SLOWID:
      alg_UP_SLOW();
      break;
    case scmEventUP_FASTID:
      alg_UP_FAST();
      break;
    case scmEventDOWN_SLOWID:
      alg_DOWN_SLOW();
      break;
    case scmEventDOWN_FASTID:
      alg_DOWN_FAST();
      break;
    case scmEventFULLID:
      alg_FULL();
      break;
    case scmEventLOADID:
      alg_LOAD();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_signalprocessing__RampLimitFS::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventZEROID: {
      readData(1, var_VAL_ZERO, conn_VAL_ZERO);
      break;
    }
    case scmEventUP_SLOWID: {
      readData(2, var_SLOW, conn_SLOW);
      break;
    }
    case scmEventUP_FASTID: {
      readData(3, var_FAST, conn_FAST);
      break;
    }
    case scmEventDOWN_SLOWID: {
      readData(2, var_SLOW, conn_SLOW);
      break;
    }
    case scmEventDOWN_FASTID: {
      readData(3, var_FAST, conn_FAST);
      break;
    }
    case scmEventFULLID: {
      readData(4, var_VAL_FULL, conn_VAL_FULL);
      break;
    }
    case scmEventLOADID: {
      readData(0, var_PV, conn_PV);
      break;
    }
    default:
      break;
  }
}

void FORTE_signalprocessing__RampLimitFS::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_signalprocessing__RampLimitFS::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_PV;
    case 1: return &var_VAL_ZERO;
    case 2: return &var_SLOW;
    case 3: return &var_FAST;
    case 4: return &var_VAL_FULL;
  }
  return nullptr;
}

CIEC_ANY *FORTE_signalprocessing__RampLimitFS::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_signalprocessing__RampLimitFS::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_signalprocessing__RampLimitFS::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_PV;
    case 1: return &conn_VAL_ZERO;
    case 2: return &conn_SLOW;
    case 3: return &conn_FAST;
    case 4: return &conn_VAL_FULL;
  }
  return nullptr;
}

CDataConnection *FORTE_signalprocessing__RampLimitFS::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_signalprocessing__RampLimitFS::getVarInternal(size_t) {
  return nullptr;
}

void FORTE_signalprocessing__RampLimitFS::alg_ZERO(void) {

  #line 2 "RampLimitFS.fbt"
  var_OUT = var_VAL_ZERO;
}

void FORTE_signalprocessing__RampLimitFS::alg_UP_SLOW(void) {

  #line 6 "RampLimitFS.fbt"
  var_OUT = func_ADD(var_OUT, var_SLOW);
  #line 7 "RampLimitFS.fbt"
  if (func_GT(var_OUT, var_VAL_FULL)) {
    #line 8 "RampLimitFS.fbt"
    var_OUT = var_VAL_FULL;
  }
}

void FORTE_signalprocessing__RampLimitFS::alg_UP_FAST(void) {

  #line 13 "RampLimitFS.fbt"
  var_OUT = func_ADD(var_OUT, var_FAST);
  #line 14 "RampLimitFS.fbt"
  if (func_GT(var_OUT, var_VAL_FULL)) {
    #line 15 "RampLimitFS.fbt"
    var_OUT = var_VAL_FULL;
  }
}

void FORTE_signalprocessing__RampLimitFS::alg_DOWN_SLOW(void) {

  #line 20 "RampLimitFS.fbt"
  var_OUT = func_SUB(var_OUT, var_SLOW);
  #line 21 "RampLimitFS.fbt"
  if (func_LT(var_OUT, var_VAL_ZERO)) {
    #line 22 "RampLimitFS.fbt"
    var_OUT = var_VAL_ZERO;
  }
}

void FORTE_signalprocessing__RampLimitFS::alg_DOWN_FAST(void) {

  #line 27 "RampLimitFS.fbt"
  var_OUT = func_SUB(var_OUT, var_FAST);
  #line 28 "RampLimitFS.fbt"
  if (func_LT(var_OUT, var_VAL_ZERO)) {
    #line 29 "RampLimitFS.fbt"
    var_OUT = var_VAL_ZERO;
  }
}

void FORTE_signalprocessing__RampLimitFS::alg_FULL(void) {

  #line 34 "RampLimitFS.fbt"
  var_OUT = var_VAL_FULL;
}

void FORTE_signalprocessing__RampLimitFS::alg_LOAD(void) {

  #line 38 "RampLimitFS.fbt"
  var_OUT = var_PV;
}
