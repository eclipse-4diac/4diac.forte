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
 *** Name: SPLIT_DWORD_INTO_QUARTERS
 *** Description: this Function extracts the 16 QUARTER BYTE from a dword
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-24/Moritz Ortmeier - HR Agrartechnik - rename Function and change Output Variables
 *************************************************************************/

#include "SPLIT_DWORD_INTO_QUARTERS_fct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SPLIT_DWORD_INTO_QUARTERS_fct_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_byte.h"
#include "forte_any_int_variant.h"
#include "forte_any_bit_variant.h"
#include "forte_dword.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "quarterconst_gcf.h"

DEFINE_FIRMWARE_FB(FORTE_SPLIT_DWORD_INTO_QUARTERS, g_nStringIdSPLIT_DWORD_INTO_QUARTERS)

const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_QUARTERS::scmDataInputNames[] = {g_nStringIdIN};
const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_QUARTERS::scmDataInputTypeIds[] = {g_nStringIdDWORD};
const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_QUARTERS::scmDataOutputNames[] = {g_nStringIdQUARTER_BYTE_00, g_nStringIdQUARTER_BYTE_01, g_nStringIdQUARTER_BYTE_02, g_nStringIdQUARTER_BYTE_03, g_nStringIdQUARTER_BYTE_04, g_nStringIdQUARTER_BYTE_05, g_nStringIdQUARTER_BYTE_06, g_nStringIdQUARTER_BYTE_07, g_nStringIdQUARTER_BYTE_08, g_nStringIdQUARTER_BYTE_09, g_nStringIdQUARTER_BYTE_10, g_nStringIdQUARTER_BYTE_11, g_nStringIdQUARTER_BYTE_12, g_nStringIdQUARTER_BYTE_13, g_nStringIdQUARTER_BYTE_14, g_nStringIdQUARTER_BYTE_15};
const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_QUARTERS::scmDataOutputTypeIds[] = {g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE};
const TDataIOID FORTE_SPLIT_DWORD_INTO_QUARTERS::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_SPLIT_DWORD_INTO_QUARTERS::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_QUARTERS::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_QUARTERS::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_SPLIT_DWORD_INTO_QUARTERS::scmEOWith[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, scmWithListDelimiter};
const TForteInt16 FORTE_SPLIT_DWORD_INTO_QUARTERS::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_QUARTERS::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_QUARTERS::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_SPLIT_DWORD_INTO_QUARTERS::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  16, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_SPLIT_DWORD_INTO_QUARTERS::FORTE_SPLIT_DWORD_INTO_QUARTERS(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QUARTER_BYTE_00(var_QUARTER_BYTE_00),
    var_conn_QUARTER_BYTE_01(var_QUARTER_BYTE_01),
    var_conn_QUARTER_BYTE_02(var_QUARTER_BYTE_02),
    var_conn_QUARTER_BYTE_03(var_QUARTER_BYTE_03),
    var_conn_QUARTER_BYTE_04(var_QUARTER_BYTE_04),
    var_conn_QUARTER_BYTE_05(var_QUARTER_BYTE_05),
    var_conn_QUARTER_BYTE_06(var_QUARTER_BYTE_06),
    var_conn_QUARTER_BYTE_07(var_QUARTER_BYTE_07),
    var_conn_QUARTER_BYTE_08(var_QUARTER_BYTE_08),
    var_conn_QUARTER_BYTE_09(var_QUARTER_BYTE_09),
    var_conn_QUARTER_BYTE_10(var_QUARTER_BYTE_10),
    var_conn_QUARTER_BYTE_11(var_QUARTER_BYTE_11),
    var_conn_QUARTER_BYTE_12(var_QUARTER_BYTE_12),
    var_conn_QUARTER_BYTE_13(var_QUARTER_BYTE_13),
    var_conn_QUARTER_BYTE_14(var_QUARTER_BYTE_14),
    var_conn_QUARTER_BYTE_15(var_QUARTER_BYTE_15),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_QUARTER_BYTE_00(this, 0, &var_conn_QUARTER_BYTE_00),
    conn_QUARTER_BYTE_01(this, 1, &var_conn_QUARTER_BYTE_01),
    conn_QUARTER_BYTE_02(this, 2, &var_conn_QUARTER_BYTE_02),
    conn_QUARTER_BYTE_03(this, 3, &var_conn_QUARTER_BYTE_03),
    conn_QUARTER_BYTE_04(this, 4, &var_conn_QUARTER_BYTE_04),
    conn_QUARTER_BYTE_05(this, 5, &var_conn_QUARTER_BYTE_05),
    conn_QUARTER_BYTE_06(this, 6, &var_conn_QUARTER_BYTE_06),
    conn_QUARTER_BYTE_07(this, 7, &var_conn_QUARTER_BYTE_07),
    conn_QUARTER_BYTE_08(this, 8, &var_conn_QUARTER_BYTE_08),
    conn_QUARTER_BYTE_09(this, 9, &var_conn_QUARTER_BYTE_09),
    conn_QUARTER_BYTE_10(this, 10, &var_conn_QUARTER_BYTE_10),
    conn_QUARTER_BYTE_11(this, 11, &var_conn_QUARTER_BYTE_11),
    conn_QUARTER_BYTE_12(this, 12, &var_conn_QUARTER_BYTE_12),
    conn_QUARTER_BYTE_13(this, 13, &var_conn_QUARTER_BYTE_13),
    conn_QUARTER_BYTE_14(this, 14, &var_conn_QUARTER_BYTE_14),
    conn_QUARTER_BYTE_15(this, 15, &var_conn_QUARTER_BYTE_15) {
}

void FORTE_SPLIT_DWORD_INTO_QUARTERS::setInitialValues() {
  var_IN = 0_DWORD;
  var_QUARTER_BYTE_00 = 0_BYTE;
  var_QUARTER_BYTE_01 = 0_BYTE;
  var_QUARTER_BYTE_02 = 0_BYTE;
  var_QUARTER_BYTE_03 = 0_BYTE;
  var_QUARTER_BYTE_04 = 0_BYTE;
  var_QUARTER_BYTE_05 = 0_BYTE;
  var_QUARTER_BYTE_06 = 0_BYTE;
  var_QUARTER_BYTE_07 = 0_BYTE;
  var_QUARTER_BYTE_08 = 0_BYTE;
  var_QUARTER_BYTE_09 = 0_BYTE;
  var_QUARTER_BYTE_10 = 0_BYTE;
  var_QUARTER_BYTE_11 = 0_BYTE;
  var_QUARTER_BYTE_12 = 0_BYTE;
  var_QUARTER_BYTE_13 = 0_BYTE;
  var_QUARTER_BYTE_14 = 0_BYTE;
  var_QUARTER_BYTE_15 = 0_BYTE;
}

void FORTE_SPLIT_DWORD_INTO_QUARTERS::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_SPLIT_DWORD_INTO_QUARTERS::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_QUARTER_BYTE_00, conn_QUARTER_BYTE_00);
      writeData(1, var_QUARTER_BYTE_01, conn_QUARTER_BYTE_01);
      writeData(2, var_QUARTER_BYTE_02, conn_QUARTER_BYTE_02);
      writeData(3, var_QUARTER_BYTE_03, conn_QUARTER_BYTE_03);
      writeData(4, var_QUARTER_BYTE_04, conn_QUARTER_BYTE_04);
      writeData(5, var_QUARTER_BYTE_05, conn_QUARTER_BYTE_05);
      writeData(6, var_QUARTER_BYTE_06, conn_QUARTER_BYTE_06);
      writeData(7, var_QUARTER_BYTE_07, conn_QUARTER_BYTE_07);
      writeData(8, var_QUARTER_BYTE_08, conn_QUARTER_BYTE_08);
      writeData(9, var_QUARTER_BYTE_09, conn_QUARTER_BYTE_09);
      writeData(10, var_QUARTER_BYTE_10, conn_QUARTER_BYTE_10);
      writeData(11, var_QUARTER_BYTE_11, conn_QUARTER_BYTE_11);
      writeData(12, var_QUARTER_BYTE_12, conn_QUARTER_BYTE_12);
      writeData(13, var_QUARTER_BYTE_13, conn_QUARTER_BYTE_13);
      writeData(14, var_QUARTER_BYTE_14, conn_QUARTER_BYTE_14);
      writeData(15, var_QUARTER_BYTE_15, conn_QUARTER_BYTE_15);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_SPLIT_DWORD_INTO_QUARTERS::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_SPLIT_DWORD_INTO_QUARTERS::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QUARTER_BYTE_00;
    case 1: return &var_QUARTER_BYTE_01;
    case 2: return &var_QUARTER_BYTE_02;
    case 3: return &var_QUARTER_BYTE_03;
    case 4: return &var_QUARTER_BYTE_04;
    case 5: return &var_QUARTER_BYTE_05;
    case 6: return &var_QUARTER_BYTE_06;
    case 7: return &var_QUARTER_BYTE_07;
    case 8: return &var_QUARTER_BYTE_08;
    case 9: return &var_QUARTER_BYTE_09;
    case 10: return &var_QUARTER_BYTE_10;
    case 11: return &var_QUARTER_BYTE_11;
    case 12: return &var_QUARTER_BYTE_12;
    case 13: return &var_QUARTER_BYTE_13;
    case 14: return &var_QUARTER_BYTE_14;
    case 15: return &var_QUARTER_BYTE_15;
  }
  return nullptr;
}

CEventConnection *FORTE_SPLIT_DWORD_INTO_QUARTERS::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_SPLIT_DWORD_INTO_QUARTERS::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_SPLIT_DWORD_INTO_QUARTERS::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QUARTER_BYTE_00;
    case 1: return &conn_QUARTER_BYTE_01;
    case 2: return &conn_QUARTER_BYTE_02;
    case 3: return &conn_QUARTER_BYTE_03;
    case 4: return &conn_QUARTER_BYTE_04;
    case 5: return &conn_QUARTER_BYTE_05;
    case 6: return &conn_QUARTER_BYTE_06;
    case 7: return &conn_QUARTER_BYTE_07;
    case 8: return &conn_QUARTER_BYTE_08;
    case 9: return &conn_QUARTER_BYTE_09;
    case 10: return &conn_QUARTER_BYTE_10;
    case 11: return &conn_QUARTER_BYTE_11;
    case 12: return &conn_QUARTER_BYTE_12;
    case 13: return &conn_QUARTER_BYTE_13;
    case 14: return &conn_QUARTER_BYTE_14;
    case 15: return &conn_QUARTER_BYTE_15;
  }
  return nullptr;
}

void FORTE_SPLIT_DWORD_INTO_QUARTERS::executeEvent(const TEventID, CEventChainExecutionThread *const paECET) {
  func_SPLIT_DWORD_INTO_QUARTERS(var_IN, var_QUARTER_BYTE_00, var_QUARTER_BYTE_01, var_QUARTER_BYTE_02, var_QUARTER_BYTE_03, var_QUARTER_BYTE_04, var_QUARTER_BYTE_05, var_QUARTER_BYTE_06, var_QUARTER_BYTE_07, var_QUARTER_BYTE_08, var_QUARTER_BYTE_09, var_QUARTER_BYTE_10, var_QUARTER_BYTE_11, var_QUARTER_BYTE_12, var_QUARTER_BYTE_13, var_QUARTER_BYTE_14, var_QUARTER_BYTE_15);
  sendOutputEvent(scmEventCNFID, paECET);
}

void func_SPLIT_DWORD_INTO_QUARTERS(CIEC_DWORD st_lv_IN, CIEC_BYTE &st_lv_QUARTER_BYTE_00, CIEC_BYTE &st_lv_QUARTER_BYTE_01, CIEC_BYTE &st_lv_QUARTER_BYTE_02, CIEC_BYTE &st_lv_QUARTER_BYTE_03, CIEC_BYTE &st_lv_QUARTER_BYTE_04, CIEC_BYTE &st_lv_QUARTER_BYTE_05, CIEC_BYTE &st_lv_QUARTER_BYTE_06, CIEC_BYTE &st_lv_QUARTER_BYTE_07, CIEC_BYTE &st_lv_QUARTER_BYTE_08, CIEC_BYTE &st_lv_QUARTER_BYTE_09, CIEC_BYTE &st_lv_QUARTER_BYTE_10, CIEC_BYTE &st_lv_QUARTER_BYTE_11, CIEC_BYTE &st_lv_QUARTER_BYTE_12, CIEC_BYTE &st_lv_QUARTER_BYTE_13, CIEC_BYTE &st_lv_QUARTER_BYTE_14, CIEC_BYTE &st_lv_QUARTER_BYTE_15) {
  st_lv_QUARTER_BYTE_00 = 0_BYTE;
  st_lv_QUARTER_BYTE_01 = 0_BYTE;
  st_lv_QUARTER_BYTE_02 = 0_BYTE;
  st_lv_QUARTER_BYTE_03 = 0_BYTE;
  st_lv_QUARTER_BYTE_04 = 0_BYTE;
  st_lv_QUARTER_BYTE_05 = 0_BYTE;
  st_lv_QUARTER_BYTE_06 = 0_BYTE;
  st_lv_QUARTER_BYTE_07 = 0_BYTE;
  st_lv_QUARTER_BYTE_08 = 0_BYTE;
  st_lv_QUARTER_BYTE_09 = 0_BYTE;
  st_lv_QUARTER_BYTE_10 = 0_BYTE;
  st_lv_QUARTER_BYTE_11 = 0_BYTE;
  st_lv_QUARTER_BYTE_12 = 0_BYTE;
  st_lv_QUARTER_BYTE_13 = 0_BYTE;
  st_lv_QUARTER_BYTE_14 = 0_BYTE;
  st_lv_QUARTER_BYTE_15 = 0_BYTE;

  #line 27 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_00 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_00), st_global_SHIFT_QUARTER_00));
  #line 28 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_01 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_01), st_global_SHIFT_QUARTER_01));
  #line 29 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_02 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_02), st_global_SHIFT_QUARTER_02));
  #line 30 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_03 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_03), st_global_SHIFT_QUARTER_03));
  #line 31 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_04 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_04), st_global_SHIFT_QUARTER_04));
  #line 32 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_05 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_05), st_global_SHIFT_QUARTER_05));
  #line 33 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_06 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_06), st_global_SHIFT_QUARTER_06));
  #line 34 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_07 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_07), st_global_SHIFT_QUARTER_07));
  #line 35 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_08 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_08), st_global_SHIFT_QUARTER_08));
  #line 36 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_09 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_09), st_global_SHIFT_QUARTER_09));
  #line 37 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_10 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_10), st_global_SHIFT_QUARTER_10));
  #line 38 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_11 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_11), st_global_SHIFT_QUARTER_11));
  #line 39 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_12 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_12), st_global_SHIFT_QUARTER_12));
  #line 40 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_13 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_13), st_global_SHIFT_QUARTER_13));
  #line 41 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_14 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_14), st_global_SHIFT_QUARTER_14));
  #line 42 "SPLIT_DWORD_INTO_QUARTERS.fct"
  st_lv_QUARTER_BYTE_15 = func_DWORD_TO_BYTE(func_SHR(func_AND<CIEC_DWORD>(st_lv_IN, st_global_DWORD_QUARTER_15), st_global_SHIFT_QUARTER_15));

}

