/*******************************************************************************
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
 *** Name: ASSEMBLE_LWORD_FROM_QUARTERS
 *** Description: this Function combines the 31 QUARTER BYTES to a LWORD
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-28/Moritz Ortmeier - HR Agrartechnik - rename Function and change Input/Output Variables
 *******************************************************************************/

#include "ASSEMBLE_LWORD_FROM_QUARTERS_fct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ASSEMBLE_LWORD_FROM_QUARTERS_fct_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_byte.h"
#include "forte_any_int_variant.h"
#include "forte_any_bit_variant.h"
#include "forte_lword.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "quarterconst_gcf.h"
#include "ASSEMBLE_LWORD_FROM_QUARTERS_fct.h"

DEFINE_FIRMWARE_FB(FORTE_ASSEMBLE_LWORD_FROM_QUARTERS, g_nStringIdASSEMBLE_LWORD_FROM_QUARTERS)

const CStringDictionary::TStringId FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::scmDataInputNames[] = {g_nStringIdQUARTER_BYTE_00, g_nStringIdQUARTER_BYTE_01, g_nStringIdQUARTER_BYTE_02, g_nStringIdQUARTER_BYTE_03, g_nStringIdQUARTER_BYTE_04, g_nStringIdQUARTER_BYTE_05, g_nStringIdQUARTER_BYTE_06, g_nStringIdQUARTER_BYTE_07, g_nStringIdQUARTER_BYTE_08, g_nStringIdQUARTER_BYTE_09, g_nStringIdQUARTER_BYTE_10, g_nStringIdQUARTER_BYTE_11, g_nStringIdQUARTER_BYTE_12, g_nStringIdQUARTER_BYTE_13, g_nStringIdQUARTER_BYTE_14, g_nStringIdQUARTER_BYTE_15, g_nStringIdQUARTER_BYTE_16, g_nStringIdQUARTER_BYTE_17, g_nStringIdQUARTER_BYTE_18, g_nStringIdQUARTER_BYTE_19, g_nStringIdQUARTER_BYTE_20, g_nStringIdQUARTER_BYTE_21, g_nStringIdQUARTER_BYTE_22, g_nStringIdQUARTER_BYTE_23, g_nStringIdQUARTER_BYTE_24, g_nStringIdQUARTER_BYTE_25, g_nStringIdQUARTER_BYTE_26, g_nStringIdQUARTER_BYTE_27, g_nStringIdQUARTER_BYTE_28, g_nStringIdQUARTER_BYTE_29, g_nStringIdQUARTER_BYTE_30, g_nStringIdQUARTER_BYTE_31};
const CStringDictionary::TStringId FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::scmDataInputTypeIds[] = {g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE};
const CStringDictionary::TStringId FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::scmDataOutputNames[] = {g_nStringId};
const CStringDictionary::TStringId FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::scmDataOutputTypeIds[] = {g_nStringIdLWORD};
const TDataIOID FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::scmEIWith[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, scmWithListDelimiter};
const TForteInt16 FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  32, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::FORTE_ASSEMBLE_LWORD_FROM_QUARTERS(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_(var_),
    conn_CNF(this, 0),
    conn_QUARTER_BYTE_00(nullptr),
    conn_QUARTER_BYTE_01(nullptr),
    conn_QUARTER_BYTE_02(nullptr),
    conn_QUARTER_BYTE_03(nullptr),
    conn_QUARTER_BYTE_04(nullptr),
    conn_QUARTER_BYTE_05(nullptr),
    conn_QUARTER_BYTE_06(nullptr),
    conn_QUARTER_BYTE_07(nullptr),
    conn_QUARTER_BYTE_08(nullptr),
    conn_QUARTER_BYTE_09(nullptr),
    conn_QUARTER_BYTE_10(nullptr),
    conn_QUARTER_BYTE_11(nullptr),
    conn_QUARTER_BYTE_12(nullptr),
    conn_QUARTER_BYTE_13(nullptr),
    conn_QUARTER_BYTE_14(nullptr),
    conn_QUARTER_BYTE_15(nullptr),
    conn_QUARTER_BYTE_16(nullptr),
    conn_QUARTER_BYTE_17(nullptr),
    conn_QUARTER_BYTE_18(nullptr),
    conn_QUARTER_BYTE_19(nullptr),
    conn_QUARTER_BYTE_20(nullptr),
    conn_QUARTER_BYTE_21(nullptr),
    conn_QUARTER_BYTE_22(nullptr),
    conn_QUARTER_BYTE_23(nullptr),
    conn_QUARTER_BYTE_24(nullptr),
    conn_QUARTER_BYTE_25(nullptr),
    conn_QUARTER_BYTE_26(nullptr),
    conn_QUARTER_BYTE_27(nullptr),
    conn_QUARTER_BYTE_28(nullptr),
    conn_QUARTER_BYTE_29(nullptr),
    conn_QUARTER_BYTE_30(nullptr),
    conn_QUARTER_BYTE_31(nullptr),
    conn_(this, 0, &var_conn_) {
}

void FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::setInitialValues() {
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
  var_QUARTER_BYTE_16 = 0_BYTE;
  var_QUARTER_BYTE_17 = 0_BYTE;
  var_QUARTER_BYTE_18 = 0_BYTE;
  var_QUARTER_BYTE_19 = 0_BYTE;
  var_QUARTER_BYTE_20 = 0_BYTE;
  var_QUARTER_BYTE_21 = 0_BYTE;
  var_QUARTER_BYTE_22 = 0_BYTE;
  var_QUARTER_BYTE_23 = 0_BYTE;
  var_QUARTER_BYTE_24 = 0_BYTE;
  var_QUARTER_BYTE_25 = 0_BYTE;
  var_QUARTER_BYTE_26 = 0_BYTE;
  var_QUARTER_BYTE_27 = 0_BYTE;
  var_QUARTER_BYTE_28 = 0_BYTE;
  var_QUARTER_BYTE_29 = 0_BYTE;
  var_QUARTER_BYTE_30 = 0_BYTE;
  var_QUARTER_BYTE_31 = 0_BYTE;
  var_ = 0_LWORD;
}

void FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_QUARTER_BYTE_00, conn_QUARTER_BYTE_00);
      readData(1, var_QUARTER_BYTE_01, conn_QUARTER_BYTE_01);
      readData(2, var_QUARTER_BYTE_02, conn_QUARTER_BYTE_02);
      readData(3, var_QUARTER_BYTE_03, conn_QUARTER_BYTE_03);
      readData(4, var_QUARTER_BYTE_04, conn_QUARTER_BYTE_04);
      readData(5, var_QUARTER_BYTE_05, conn_QUARTER_BYTE_05);
      readData(6, var_QUARTER_BYTE_06, conn_QUARTER_BYTE_06);
      readData(7, var_QUARTER_BYTE_07, conn_QUARTER_BYTE_07);
      readData(8, var_QUARTER_BYTE_08, conn_QUARTER_BYTE_08);
      readData(9, var_QUARTER_BYTE_09, conn_QUARTER_BYTE_09);
      readData(10, var_QUARTER_BYTE_10, conn_QUARTER_BYTE_10);
      readData(11, var_QUARTER_BYTE_11, conn_QUARTER_BYTE_11);
      readData(12, var_QUARTER_BYTE_12, conn_QUARTER_BYTE_12);
      readData(13, var_QUARTER_BYTE_13, conn_QUARTER_BYTE_13);
      readData(14, var_QUARTER_BYTE_14, conn_QUARTER_BYTE_14);
      readData(15, var_QUARTER_BYTE_15, conn_QUARTER_BYTE_15);
      readData(16, var_QUARTER_BYTE_16, conn_QUARTER_BYTE_16);
      readData(17, var_QUARTER_BYTE_17, conn_QUARTER_BYTE_17);
      readData(18, var_QUARTER_BYTE_18, conn_QUARTER_BYTE_18);
      readData(19, var_QUARTER_BYTE_19, conn_QUARTER_BYTE_19);
      readData(20, var_QUARTER_BYTE_20, conn_QUARTER_BYTE_20);
      readData(21, var_QUARTER_BYTE_21, conn_QUARTER_BYTE_21);
      readData(22, var_QUARTER_BYTE_22, conn_QUARTER_BYTE_22);
      readData(23, var_QUARTER_BYTE_23, conn_QUARTER_BYTE_23);
      readData(24, var_QUARTER_BYTE_24, conn_QUARTER_BYTE_24);
      readData(25, var_QUARTER_BYTE_25, conn_QUARTER_BYTE_25);
      readData(26, var_QUARTER_BYTE_26, conn_QUARTER_BYTE_26);
      readData(27, var_QUARTER_BYTE_27, conn_QUARTER_BYTE_27);
      readData(28, var_QUARTER_BYTE_28, conn_QUARTER_BYTE_28);
      readData(29, var_QUARTER_BYTE_29, conn_QUARTER_BYTE_29);
      readData(30, var_QUARTER_BYTE_30, conn_QUARTER_BYTE_30);
      readData(31, var_QUARTER_BYTE_31, conn_QUARTER_BYTE_31);
      break;
    }
    default:
      break;
  }
}

void FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_, conn_);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::getDI(const size_t paIndex) {
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
    case 16: return &var_QUARTER_BYTE_16;
    case 17: return &var_QUARTER_BYTE_17;
    case 18: return &var_QUARTER_BYTE_18;
    case 19: return &var_QUARTER_BYTE_19;
    case 20: return &var_QUARTER_BYTE_20;
    case 21: return &var_QUARTER_BYTE_21;
    case 22: return &var_QUARTER_BYTE_22;
    case 23: return &var_QUARTER_BYTE_23;
    case 24: return &var_QUARTER_BYTE_24;
    case 25: return &var_QUARTER_BYTE_25;
    case 26: return &var_QUARTER_BYTE_26;
    case 27: return &var_QUARTER_BYTE_27;
    case 28: return &var_QUARTER_BYTE_28;
    case 29: return &var_QUARTER_BYTE_29;
    case 30: return &var_QUARTER_BYTE_30;
    case 31: return &var_QUARTER_BYTE_31;
  }
  return nullptr;
}

CIEC_ANY *FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_;
  }
  return nullptr;
}

CEventConnection *FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::getDIConUnchecked(const TPortId paIndex) {
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
    case 16: return &conn_QUARTER_BYTE_16;
    case 17: return &conn_QUARTER_BYTE_17;
    case 18: return &conn_QUARTER_BYTE_18;
    case 19: return &conn_QUARTER_BYTE_19;
    case 20: return &conn_QUARTER_BYTE_20;
    case 21: return &conn_QUARTER_BYTE_21;
    case 22: return &conn_QUARTER_BYTE_22;
    case 23: return &conn_QUARTER_BYTE_23;
    case 24: return &conn_QUARTER_BYTE_24;
    case 25: return &conn_QUARTER_BYTE_25;
    case 26: return &conn_QUARTER_BYTE_26;
    case 27: return &conn_QUARTER_BYTE_27;
    case 28: return &conn_QUARTER_BYTE_28;
    case 29: return &conn_QUARTER_BYTE_29;
    case 30: return &conn_QUARTER_BYTE_30;
    case 31: return &conn_QUARTER_BYTE_31;
  }
  return nullptr;
}

CDataConnection *FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_;
  }
  return nullptr;
}

void FORTE_ASSEMBLE_LWORD_FROM_QUARTERS::executeEvent(const TEventID, CEventChainExecutionThread *const paECET) {
  var_ = func_ASSEMBLE_LWORD_FROM_QUARTERS(var_QUARTER_BYTE_00, var_QUARTER_BYTE_01, var_QUARTER_BYTE_02, var_QUARTER_BYTE_03, var_QUARTER_BYTE_04, var_QUARTER_BYTE_05, var_QUARTER_BYTE_06, var_QUARTER_BYTE_07, var_QUARTER_BYTE_08, var_QUARTER_BYTE_09, var_QUARTER_BYTE_10, var_QUARTER_BYTE_11, var_QUARTER_BYTE_12, var_QUARTER_BYTE_13, var_QUARTER_BYTE_14, var_QUARTER_BYTE_15, var_QUARTER_BYTE_16, var_QUARTER_BYTE_17, var_QUARTER_BYTE_18, var_QUARTER_BYTE_19, var_QUARTER_BYTE_20, var_QUARTER_BYTE_21, var_QUARTER_BYTE_22, var_QUARTER_BYTE_23, var_QUARTER_BYTE_24, var_QUARTER_BYTE_25, var_QUARTER_BYTE_26, var_QUARTER_BYTE_27, var_QUARTER_BYTE_28, var_QUARTER_BYTE_29, var_QUARTER_BYTE_30, var_QUARTER_BYTE_31);
  sendOutputEvent(scmEventCNFID, paECET);
}

CIEC_LWORD func_ASSEMBLE_LWORD_FROM_QUARTERS(CIEC_BYTE st_lv_QUARTER_BYTE_00, CIEC_BYTE st_lv_QUARTER_BYTE_01, CIEC_BYTE st_lv_QUARTER_BYTE_02, CIEC_BYTE st_lv_QUARTER_BYTE_03, CIEC_BYTE st_lv_QUARTER_BYTE_04, CIEC_BYTE st_lv_QUARTER_BYTE_05, CIEC_BYTE st_lv_QUARTER_BYTE_06, CIEC_BYTE st_lv_QUARTER_BYTE_07, CIEC_BYTE st_lv_QUARTER_BYTE_08, CIEC_BYTE st_lv_QUARTER_BYTE_09, CIEC_BYTE st_lv_QUARTER_BYTE_10, CIEC_BYTE st_lv_QUARTER_BYTE_11, CIEC_BYTE st_lv_QUARTER_BYTE_12, CIEC_BYTE st_lv_QUARTER_BYTE_13, CIEC_BYTE st_lv_QUARTER_BYTE_14, CIEC_BYTE st_lv_QUARTER_BYTE_15, CIEC_BYTE st_lv_QUARTER_BYTE_16, CIEC_BYTE st_lv_QUARTER_BYTE_17, CIEC_BYTE st_lv_QUARTER_BYTE_18, CIEC_BYTE st_lv_QUARTER_BYTE_19, CIEC_BYTE st_lv_QUARTER_BYTE_20, CIEC_BYTE st_lv_QUARTER_BYTE_21, CIEC_BYTE st_lv_QUARTER_BYTE_22, CIEC_BYTE st_lv_QUARTER_BYTE_23, CIEC_BYTE st_lv_QUARTER_BYTE_24, CIEC_BYTE st_lv_QUARTER_BYTE_25, CIEC_BYTE st_lv_QUARTER_BYTE_26, CIEC_BYTE st_lv_QUARTER_BYTE_27, CIEC_BYTE st_lv_QUARTER_BYTE_28, CIEC_BYTE st_lv_QUARTER_BYTE_29, CIEC_BYTE st_lv_QUARTER_BYTE_30, CIEC_BYTE st_lv_QUARTER_BYTE_31) {
  CIEC_LWORD st_ret_val = 0_LWORD;

  #line 39 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = st_global_LWORD_QUARTER_ZZ;
  #line 40 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_31), st_global_SHIFT_QUARTER_31));
  #line 41 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_30), st_global_SHIFT_QUARTER_30));
  #line 42 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_29), st_global_SHIFT_QUARTER_29));
  #line 43 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_28), st_global_SHIFT_QUARTER_28));
  #line 44 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_27), st_global_SHIFT_QUARTER_27));
  #line 45 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_26), st_global_SHIFT_QUARTER_26));
  #line 46 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_25), st_global_SHIFT_QUARTER_25));
  #line 47 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_24), st_global_SHIFT_QUARTER_24));
  #line 48 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_23), st_global_SHIFT_QUARTER_23));
  #line 49 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_22), st_global_SHIFT_QUARTER_22));
  #line 50 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_21), st_global_SHIFT_QUARTER_21));
  #line 51 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_20), st_global_SHIFT_QUARTER_20));
  #line 52 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_19), st_global_SHIFT_QUARTER_19));
  #line 53 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_18), st_global_SHIFT_QUARTER_18));
  #line 54 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_17), st_global_SHIFT_QUARTER_17));
  #line 55 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_16), st_global_SHIFT_QUARTER_16));
  #line 56 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_15), st_global_SHIFT_QUARTER_15));
  #line 57 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_14), st_global_SHIFT_QUARTER_14));
  #line 58 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_13), st_global_SHIFT_QUARTER_13));
  #line 59 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_12), st_global_SHIFT_QUARTER_12));
  #line 60 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_11), st_global_SHIFT_QUARTER_11));
  #line 61 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_10), st_global_SHIFT_QUARTER_10));
  #line 62 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_09), st_global_SHIFT_QUARTER_09));
  #line 63 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_08), st_global_SHIFT_QUARTER_08));
  #line 64 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_07), st_global_SHIFT_QUARTER_07));
  #line 65 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_06), st_global_SHIFT_QUARTER_06));
  #line 66 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_05), st_global_SHIFT_QUARTER_05));
  #line 67 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_04), st_global_SHIFT_QUARTER_04));
  #line 68 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_03), st_global_SHIFT_QUARTER_03));
  #line 69 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_02), st_global_SHIFT_QUARTER_02));
  #line 70 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_01), st_global_SHIFT_QUARTER_01));
  #line 71 "ASSEMBLE_LWORD_FROM_QUARTERS.fct"
  st_ret_val = func_OR<CIEC_LWORD>(st_ret_val, func_SHL(func_BYTE_TO_LWORD(st_lv_QUARTER_BYTE_00), st_global_SHIFT_QUARTER_00));

  return st_ret_val;
}

