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
 *** Name: SCALE_LIM
 *** Description: Scaling Function Block with limits
 *** Version:
 ***     1.0: 2024-09-19/Franz Höpfinger - HR Agrartechnik GmbH -
 *************************************************************************/

#include "SCALE_LIM_fct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SCALE_LIM_fct_gen.cpp"
#endif

#include "forte_real.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "SCALE_LIM_fct.h"

DEFINE_FIRMWARE_FB(FORTE_signalprocessing__SCALE_LIM, g_nStringIdsignalprocessing__SCALE_LIM)

const CStringDictionary::TStringId FORTE_signalprocessing__SCALE_LIM::scmDataInputNames[] = {g_nStringIdIN, g_nStringIdMAX_IN, g_nStringIdMIN_IN, g_nStringIdMAX_IN_LIM, g_nStringIdMIN_IN_LIM, g_nStringIdMAX_OUT, g_nStringIdMIN_OUT, g_nStringIdMAX_OUT_FIX, g_nStringIdMIN_OUT_FIX};
const CStringDictionary::TStringId FORTE_signalprocessing__SCALE_LIM::scmDataInputTypeIds[] = {g_nStringIdREAL, g_nStringIdREAL, g_nStringIdREAL, g_nStringIdREAL, g_nStringIdREAL, g_nStringIdREAL, g_nStringIdREAL, g_nStringIdREAL, g_nStringIdREAL};
const CStringDictionary::TStringId FORTE_signalprocessing__SCALE_LIM::scmDataOutputNames[] = {g_nStringId};
const CStringDictionary::TStringId FORTE_signalprocessing__SCALE_LIM::scmDataOutputTypeIds[] = {g_nStringIdREAL};
const TDataIOID FORTE_signalprocessing__SCALE_LIM::scmEIWith[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, scmWithListDelimiter};
const TForteInt16 FORTE_signalprocessing__SCALE_LIM::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_signalprocessing__SCALE_LIM::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_signalprocessing__SCALE_LIM::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_signalprocessing__SCALE_LIM::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_signalprocessing__SCALE_LIM::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_signalprocessing__SCALE_LIM::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_signalprocessing__SCALE_LIM::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_signalprocessing__SCALE_LIM::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  9, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_signalprocessing__SCALE_LIM::FORTE_signalprocessing__SCALE_LIM(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_(var_),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_MAX_IN(nullptr),
    conn_MIN_IN(nullptr),
    conn_MAX_IN_LIM(nullptr),
    conn_MIN_IN_LIM(nullptr),
    conn_MAX_OUT(nullptr),
    conn_MIN_OUT(nullptr),
    conn_MAX_OUT_FIX(nullptr),
    conn_MIN_OUT_FIX(nullptr),
    conn_(this, 0, &var_conn_) {
}

void FORTE_signalprocessing__SCALE_LIM::setInitialValues() {
  var_IN = 0_REAL;
  var_MAX_IN = 0_REAL;
  var_MIN_IN = 0_REAL;
  var_MAX_IN_LIM = 0_REAL;
  var_MIN_IN_LIM = 0_REAL;
  var_MAX_OUT = 0_REAL;
  var_MIN_OUT = 0_REAL;
  var_MAX_OUT_FIX = 0_REAL;
  var_MIN_OUT_FIX = 0_REAL;
  var_ = 0_REAL;
}

void FORTE_signalprocessing__SCALE_LIM::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      readData(1, var_MAX_IN, conn_MAX_IN);
      readData(2, var_MIN_IN, conn_MIN_IN);
      readData(3, var_MAX_IN_LIM, conn_MAX_IN_LIM);
      readData(4, var_MIN_IN_LIM, conn_MIN_IN_LIM);
      readData(5, var_MAX_OUT, conn_MAX_OUT);
      readData(6, var_MIN_OUT, conn_MIN_OUT);
      readData(7, var_MAX_OUT_FIX, conn_MAX_OUT_FIX);
      readData(8, var_MIN_OUT_FIX, conn_MIN_OUT_FIX);
      break;
    }
    default:
      break;
  }
}

void FORTE_signalprocessing__SCALE_LIM::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_, conn_);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_signalprocessing__SCALE_LIM::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
    case 1: return &var_MAX_IN;
    case 2: return &var_MIN_IN;
    case 3: return &var_MAX_IN_LIM;
    case 4: return &var_MIN_IN_LIM;
    case 5: return &var_MAX_OUT;
    case 6: return &var_MIN_OUT;
    case 7: return &var_MAX_OUT_FIX;
    case 8: return &var_MIN_OUT_FIX;
  }
  return nullptr;
}

CIEC_ANY *FORTE_signalprocessing__SCALE_LIM::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_;
  }
  return nullptr;
}

CEventConnection *FORTE_signalprocessing__SCALE_LIM::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_signalprocessing__SCALE_LIM::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
    case 1: return &conn_MAX_IN;
    case 2: return &conn_MIN_IN;
    case 3: return &conn_MAX_IN_LIM;
    case 4: return &conn_MIN_IN_LIM;
    case 5: return &conn_MAX_OUT;
    case 6: return &conn_MIN_OUT;
    case 7: return &conn_MAX_OUT_FIX;
    case 8: return &conn_MIN_OUT_FIX;
  }
  return nullptr;
}

CDataConnection *FORTE_signalprocessing__SCALE_LIM::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_;
  }
  return nullptr;
}

void FORTE_signalprocessing__SCALE_LIM::executeEvent(const TEventID, CEventChainExecutionThread *const paECET) {
  var_ = func_SCALE_LIM(var_IN, var_MAX_IN, var_MIN_IN, var_MAX_IN_LIM, var_MIN_IN_LIM, var_MAX_OUT, var_MIN_OUT, var_MAX_OUT_FIX, var_MIN_OUT_FIX);
  sendOutputEvent(scmEventCNFID, paECET);
}

CIEC_REAL func_SCALE_LIM(CIEC_REAL st_lv_IN, CIEC_REAL st_lv_MAX_IN, CIEC_REAL st_lv_MIN_IN, CIEC_REAL st_lv_MAX_IN_LIM, CIEC_REAL st_lv_MIN_IN_LIM, CIEC_REAL st_lv_MAX_OUT, CIEC_REAL st_lv_MIN_OUT, CIEC_REAL st_lv_MAX_OUT_FIX, CIEC_REAL st_lv_MIN_OUT_FIX) {
  CIEC_REAL st_ret_val = 0_REAL;

  #line 17 "SCALE_LIM.fct"
  if (func_LT(st_lv_IN, st_lv_MIN_IN_LIM)) {
    #line 18 "SCALE_LIM.fct"
    st_ret_val = st_lv_MIN_OUT_FIX;
  }
  else if (func_GT(st_lv_IN, st_lv_MAX_IN_LIM)) {
    #line 20 "SCALE_LIM.fct"
    st_ret_val = st_lv_MAX_OUT_FIX;
  }
  else {
    #line 22 "SCALE_LIM.fct"
    st_ret_val = func_ADD<CIEC_REAL>(func_DIV<CIEC_REAL>(func_MUL<CIEC_REAL>(func_SUB<CIEC_REAL>(st_lv_IN, st_lv_MIN_IN), func_SUB<CIEC_REAL>(st_lv_MAX_OUT, st_lv_MIN_OUT)), func_SUB<CIEC_REAL>(st_lv_MAX_IN, st_lv_MIN_IN)), st_lv_MIN_OUT);
  }

  return st_ret_val;
}
