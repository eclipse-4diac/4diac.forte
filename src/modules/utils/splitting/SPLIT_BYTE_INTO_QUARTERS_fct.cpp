/*************************************************************************
 *** Copyright (c) 2024 HR Agrartechnik GmbH
 *** This program and the accompanying materials are made available under the
 *** terms of the Eclipse Public License 2.0 which is available at
 *** http://www.eclipse.org/legal/epl-2.0.
 ***
 *** SPDX-License-Identifier: EPL-2.0
 ***
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: SPLIT_BYTE_INTO_QUARTERS
 *** Description: this Function extracts the 4 QUARTER BYTE from a byte
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-24/Moritz Ortmeier - HR Agrartechnik - rename Function and change Output Variables
 *************************************************************************/

#include "SPLIT_BYTE_INTO_QUARTERS_fct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SPLIT_BYTE_INTO_QUARTERS_fct_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_any_int_variant.h"
#include "forte_byte.h"
#include "forte_any_bit_variant.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "quarterconst_gcf.h"

DEFINE_FIRMWARE_FB(FORTE_SPLIT_BYTE_INTO_QUARTERS, g_nStringIdSPLIT_BYTE_INTO_QUARTERS)

const CStringDictionary::TStringId FORTE_SPLIT_BYTE_INTO_QUARTERS::scmDataInputNames[] = {g_nStringIdIN};
const CStringDictionary::TStringId FORTE_SPLIT_BYTE_INTO_QUARTERS::scmDataInputTypeIds[] = {g_nStringIdBYTE};
const CStringDictionary::TStringId FORTE_SPLIT_BYTE_INTO_QUARTERS::scmDataOutputNames[] = {g_nStringIdQUARTER_BYTE_00, g_nStringIdQUARTER_BYTE_01, g_nStringIdQUARTER_BYTE_02, g_nStringIdQUARTER_BYTE_03};
const CStringDictionary::TStringId FORTE_SPLIT_BYTE_INTO_QUARTERS::scmDataOutputTypeIds[] = {g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE};
const TDataIOID FORTE_SPLIT_BYTE_INTO_QUARTERS::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_SPLIT_BYTE_INTO_QUARTERS::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_SPLIT_BYTE_INTO_QUARTERS::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_SPLIT_BYTE_INTO_QUARTERS::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_SPLIT_BYTE_INTO_QUARTERS::scmEOWith[] = {0, 1, 2, 3, scmWithListDelimiter};
const TForteInt16 FORTE_SPLIT_BYTE_INTO_QUARTERS::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_SPLIT_BYTE_INTO_QUARTERS::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_SPLIT_BYTE_INTO_QUARTERS::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_SPLIT_BYTE_INTO_QUARTERS::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  4, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_SPLIT_BYTE_INTO_QUARTERS::FORTE_SPLIT_BYTE_INTO_QUARTERS(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QUARTER_BYTE_00(var_QUARTER_BYTE_00),
    var_conn_QUARTER_BYTE_01(var_QUARTER_BYTE_01),
    var_conn_QUARTER_BYTE_02(var_QUARTER_BYTE_02),
    var_conn_QUARTER_BYTE_03(var_QUARTER_BYTE_03),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_QUARTER_BYTE_00(this, 0, &var_conn_QUARTER_BYTE_00),
    conn_QUARTER_BYTE_01(this, 1, &var_conn_QUARTER_BYTE_01),
    conn_QUARTER_BYTE_02(this, 2, &var_conn_QUARTER_BYTE_02),
    conn_QUARTER_BYTE_03(this, 3, &var_conn_QUARTER_BYTE_03) {
}

void FORTE_SPLIT_BYTE_INTO_QUARTERS::setInitialValues() {
  var_IN = 0_BYTE;
  var_QUARTER_BYTE_00 = 0_BYTE;
  var_QUARTER_BYTE_01 = 0_BYTE;
  var_QUARTER_BYTE_02 = 0_BYTE;
  var_QUARTER_BYTE_03 = 0_BYTE;
}

void FORTE_SPLIT_BYTE_INTO_QUARTERS::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_SPLIT_BYTE_INTO_QUARTERS::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_QUARTER_BYTE_00, conn_QUARTER_BYTE_00);
      writeData(1, var_QUARTER_BYTE_01, conn_QUARTER_BYTE_01);
      writeData(2, var_QUARTER_BYTE_02, conn_QUARTER_BYTE_02);
      writeData(3, var_QUARTER_BYTE_03, conn_QUARTER_BYTE_03);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_SPLIT_BYTE_INTO_QUARTERS::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_SPLIT_BYTE_INTO_QUARTERS::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QUARTER_BYTE_00;
    case 1: return &var_QUARTER_BYTE_01;
    case 2: return &var_QUARTER_BYTE_02;
    case 3: return &var_QUARTER_BYTE_03;
  }
  return nullptr;
}

CEventConnection *FORTE_SPLIT_BYTE_INTO_QUARTERS::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_SPLIT_BYTE_INTO_QUARTERS::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_SPLIT_BYTE_INTO_QUARTERS::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QUARTER_BYTE_00;
    case 1: return &conn_QUARTER_BYTE_01;
    case 2: return &conn_QUARTER_BYTE_02;
    case 3: return &conn_QUARTER_BYTE_03;
  }
  return nullptr;
}

void FORTE_SPLIT_BYTE_INTO_QUARTERS::executeEvent(const TEventID, CEventChainExecutionThread *const paECET) {
  func_SPLIT_BYTE_INTO_QUARTERS(var_IN, var_QUARTER_BYTE_00, var_QUARTER_BYTE_01, var_QUARTER_BYTE_02, var_QUARTER_BYTE_03);
  sendOutputEvent(scmEventCNFID, paECET);
}

void func_SPLIT_BYTE_INTO_QUARTERS(CIEC_BYTE st_lv_IN, CIEC_BYTE &st_lv_QUARTER_BYTE_00, CIEC_BYTE &st_lv_QUARTER_BYTE_01, CIEC_BYTE &st_lv_QUARTER_BYTE_02, CIEC_BYTE &st_lv_QUARTER_BYTE_03) {
  st_lv_QUARTER_BYTE_00 = 0_BYTE;
  st_lv_QUARTER_BYTE_01 = 0_BYTE;
  st_lv_QUARTER_BYTE_02 = 0_BYTE;
  st_lv_QUARTER_BYTE_03 = 0_BYTE;

  #line 15 "SPLIT_BYTE_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_00 = func_SHR(func_AND<CIEC_BYTE>(st_lv_IN, st_global_BYTE_QUARTER_00), st_global_SHIFT_QUARTER_00);
  #line 16 "SPLIT_BYTE_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_01 = func_SHR(func_AND<CIEC_BYTE>(st_lv_IN, st_global_BYTE_QUARTER_01), st_global_SHIFT_QUARTER_01);
  #line 17 "SPLIT_BYTE_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_02 = func_SHR(func_AND<CIEC_BYTE>(st_lv_IN, st_global_BYTE_QUARTER_02), st_global_SHIFT_QUARTER_02);
  #line 18 "SPLIT_BYTE_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_03 = func_SHR(func_AND<CIEC_BYTE>(st_lv_IN, st_global_BYTE_QUARTER_03), st_global_SHIFT_QUARTER_03);

}

