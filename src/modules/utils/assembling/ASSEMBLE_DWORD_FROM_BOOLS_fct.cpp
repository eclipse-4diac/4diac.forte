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
 *** Name: ASSEMBLE_DWORD_FROM_BOOLS
 *** Description: this Function combines the 32 BOOLS to a DWORD
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-28/Moritz Ortmeier - HR Agrartechnik - rename Function and change Input/Output Variables
 *************************************************************************/

#include "ASSEMBLE_DWORD_FROM_BOOLS_fct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ASSEMBLE_DWORD_FROM_BOOLS_fct_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_dword.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "ASSEMBLE_DWORD_FROM_BOOLS_fct.h"

DEFINE_FIRMWARE_FB(FORTE_ASSEMBLE_DWORD_FROM_BOOLS, g_nStringIdASSEMBLE_DWORD_FROM_BOOLS)

const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_BOOLS::scmDataInputNames[] = {g_nStringIdBIT_00, g_nStringIdBIT_01, g_nStringIdBIT_02, g_nStringIdBIT_03, g_nStringIdBIT_04, g_nStringIdBIT_05, g_nStringIdBIT_06, g_nStringIdBIT_07, g_nStringIdBIT_08, g_nStringIdBIT_09, g_nStringIdBIT_10, g_nStringIdBIT_11, g_nStringIdBIT_12, g_nStringIdBIT_13, g_nStringIdBIT_14, g_nStringIdBIT_15, g_nStringIdBIT_16, g_nStringIdBIT_17, g_nStringIdBIT_18, g_nStringIdBIT_19, g_nStringIdBIT_20, g_nStringIdBIT_21, g_nStringIdBIT_22, g_nStringIdBIT_23, g_nStringIdBIT_24, g_nStringIdBIT_25, g_nStringIdBIT_26, g_nStringIdBIT_27, g_nStringIdBIT_28, g_nStringIdBIT_29, g_nStringIdBIT_30, g_nStringIdBIT_31};
const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_BOOLS::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL};
const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_BOOLS::scmDataOutputNames[] = {g_nStringId};
const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_BOOLS::scmDataOutputTypeIds[] = {g_nStringIdDWORD};
const TDataIOID FORTE_ASSEMBLE_DWORD_FROM_BOOLS::scmEIWith[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, scmWithListDelimiter};
const TForteInt16 FORTE_ASSEMBLE_DWORD_FROM_BOOLS::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_BOOLS::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_BOOLS::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_ASSEMBLE_DWORD_FROM_BOOLS::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_ASSEMBLE_DWORD_FROM_BOOLS::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_BOOLS::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_BOOLS::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_ASSEMBLE_DWORD_FROM_BOOLS::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  32, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_ASSEMBLE_DWORD_FROM_BOOLS::FORTE_ASSEMBLE_DWORD_FROM_BOOLS(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_(var_),
    conn_CNF(this, 0),
    conn_BIT_00(nullptr),
    conn_BIT_01(nullptr),
    conn_BIT_02(nullptr),
    conn_BIT_03(nullptr),
    conn_BIT_04(nullptr),
    conn_BIT_05(nullptr),
    conn_BIT_06(nullptr),
    conn_BIT_07(nullptr),
    conn_BIT_08(nullptr),
    conn_BIT_09(nullptr),
    conn_BIT_10(nullptr),
    conn_BIT_11(nullptr),
    conn_BIT_12(nullptr),
    conn_BIT_13(nullptr),
    conn_BIT_14(nullptr),
    conn_BIT_15(nullptr),
    conn_BIT_16(nullptr),
    conn_BIT_17(nullptr),
    conn_BIT_18(nullptr),
    conn_BIT_19(nullptr),
    conn_BIT_20(nullptr),
    conn_BIT_21(nullptr),
    conn_BIT_22(nullptr),
    conn_BIT_23(nullptr),
    conn_BIT_24(nullptr),
    conn_BIT_25(nullptr),
    conn_BIT_26(nullptr),
    conn_BIT_27(nullptr),
    conn_BIT_28(nullptr),
    conn_BIT_29(nullptr),
    conn_BIT_30(nullptr),
    conn_BIT_31(nullptr),
    conn_(this, 0, &var_conn_) {
}

void FORTE_ASSEMBLE_DWORD_FROM_BOOLS::setInitialValues() {
  var_BIT_00 = 0_BOOL;
  var_BIT_01 = 0_BOOL;
  var_BIT_02 = 0_BOOL;
  var_BIT_03 = 0_BOOL;
  var_BIT_04 = 0_BOOL;
  var_BIT_05 = 0_BOOL;
  var_BIT_06 = 0_BOOL;
  var_BIT_07 = 0_BOOL;
  var_BIT_08 = 0_BOOL;
  var_BIT_09 = 0_BOOL;
  var_BIT_10 = 0_BOOL;
  var_BIT_11 = 0_BOOL;
  var_BIT_12 = 0_BOOL;
  var_BIT_13 = 0_BOOL;
  var_BIT_14 = 0_BOOL;
  var_BIT_15 = 0_BOOL;
  var_BIT_16 = 0_BOOL;
  var_BIT_17 = 0_BOOL;
  var_BIT_18 = 0_BOOL;
  var_BIT_19 = 0_BOOL;
  var_BIT_20 = 0_BOOL;
  var_BIT_21 = 0_BOOL;
  var_BIT_22 = 0_BOOL;
  var_BIT_23 = 0_BOOL;
  var_BIT_24 = 0_BOOL;
  var_BIT_25 = 0_BOOL;
  var_BIT_26 = 0_BOOL;
  var_BIT_27 = 0_BOOL;
  var_BIT_28 = 0_BOOL;
  var_BIT_29 = 0_BOOL;
  var_BIT_30 = 0_BOOL;
  var_BIT_31 = 0_BOOL;
  var_ = 0_DWORD;
}

void FORTE_ASSEMBLE_DWORD_FROM_BOOLS::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_BIT_00, conn_BIT_00);
      readData(1, var_BIT_01, conn_BIT_01);
      readData(2, var_BIT_02, conn_BIT_02);
      readData(3, var_BIT_03, conn_BIT_03);
      readData(4, var_BIT_04, conn_BIT_04);
      readData(5, var_BIT_05, conn_BIT_05);
      readData(6, var_BIT_06, conn_BIT_06);
      readData(7, var_BIT_07, conn_BIT_07);
      readData(8, var_BIT_08, conn_BIT_08);
      readData(9, var_BIT_09, conn_BIT_09);
      readData(10, var_BIT_10, conn_BIT_10);
      readData(11, var_BIT_11, conn_BIT_11);
      readData(12, var_BIT_12, conn_BIT_12);
      readData(13, var_BIT_13, conn_BIT_13);
      readData(14, var_BIT_14, conn_BIT_14);
      readData(15, var_BIT_15, conn_BIT_15);
      readData(16, var_BIT_16, conn_BIT_16);
      readData(17, var_BIT_17, conn_BIT_17);
      readData(18, var_BIT_18, conn_BIT_18);
      readData(19, var_BIT_19, conn_BIT_19);
      readData(20, var_BIT_20, conn_BIT_20);
      readData(21, var_BIT_21, conn_BIT_21);
      readData(22, var_BIT_22, conn_BIT_22);
      readData(23, var_BIT_23, conn_BIT_23);
      readData(24, var_BIT_24, conn_BIT_24);
      readData(25, var_BIT_25, conn_BIT_25);
      readData(26, var_BIT_26, conn_BIT_26);
      readData(27, var_BIT_27, conn_BIT_27);
      readData(28, var_BIT_28, conn_BIT_28);
      readData(29, var_BIT_29, conn_BIT_29);
      readData(30, var_BIT_30, conn_BIT_30);
      readData(31, var_BIT_31, conn_BIT_31);
      break;
    }
    default:
      break;
  }
}

void FORTE_ASSEMBLE_DWORD_FROM_BOOLS::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_, conn_);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_ASSEMBLE_DWORD_FROM_BOOLS::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_BIT_00;
    case 1: return &var_BIT_01;
    case 2: return &var_BIT_02;
    case 3: return &var_BIT_03;
    case 4: return &var_BIT_04;
    case 5: return &var_BIT_05;
    case 6: return &var_BIT_06;
    case 7: return &var_BIT_07;
    case 8: return &var_BIT_08;
    case 9: return &var_BIT_09;
    case 10: return &var_BIT_10;
    case 11: return &var_BIT_11;
    case 12: return &var_BIT_12;
    case 13: return &var_BIT_13;
    case 14: return &var_BIT_14;
    case 15: return &var_BIT_15;
    case 16: return &var_BIT_16;
    case 17: return &var_BIT_17;
    case 18: return &var_BIT_18;
    case 19: return &var_BIT_19;
    case 20: return &var_BIT_20;
    case 21: return &var_BIT_21;
    case 22: return &var_BIT_22;
    case 23: return &var_BIT_23;
    case 24: return &var_BIT_24;
    case 25: return &var_BIT_25;
    case 26: return &var_BIT_26;
    case 27: return &var_BIT_27;
    case 28: return &var_BIT_28;
    case 29: return &var_BIT_29;
    case 30: return &var_BIT_30;
    case 31: return &var_BIT_31;
  }
  return nullptr;
}

CIEC_ANY *FORTE_ASSEMBLE_DWORD_FROM_BOOLS::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_;
  }
  return nullptr;
}

CEventConnection *FORTE_ASSEMBLE_DWORD_FROM_BOOLS::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_ASSEMBLE_DWORD_FROM_BOOLS::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_BIT_00;
    case 1: return &conn_BIT_01;
    case 2: return &conn_BIT_02;
    case 3: return &conn_BIT_03;
    case 4: return &conn_BIT_04;
    case 5: return &conn_BIT_05;
    case 6: return &conn_BIT_06;
    case 7: return &conn_BIT_07;
    case 8: return &conn_BIT_08;
    case 9: return &conn_BIT_09;
    case 10: return &conn_BIT_10;
    case 11: return &conn_BIT_11;
    case 12: return &conn_BIT_12;
    case 13: return &conn_BIT_13;
    case 14: return &conn_BIT_14;
    case 15: return &conn_BIT_15;
    case 16: return &conn_BIT_16;
    case 17: return &conn_BIT_17;
    case 18: return &conn_BIT_18;
    case 19: return &conn_BIT_19;
    case 20: return &conn_BIT_20;
    case 21: return &conn_BIT_21;
    case 22: return &conn_BIT_22;
    case 23: return &conn_BIT_23;
    case 24: return &conn_BIT_24;
    case 25: return &conn_BIT_25;
    case 26: return &conn_BIT_26;
    case 27: return &conn_BIT_27;
    case 28: return &conn_BIT_28;
    case 29: return &conn_BIT_29;
    case 30: return &conn_BIT_30;
    case 31: return &conn_BIT_31;
  }
  return nullptr;
}

CDataConnection *FORTE_ASSEMBLE_DWORD_FROM_BOOLS::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_;
  }
  return nullptr;
}

void FORTE_ASSEMBLE_DWORD_FROM_BOOLS::executeEvent(const TEventID, CEventChainExecutionThread *const paECET) {
  var_ = func_ASSEMBLE_DWORD_FROM_BOOLS(var_BIT_00, var_BIT_01, var_BIT_02, var_BIT_03, var_BIT_04, var_BIT_05, var_BIT_06, var_BIT_07, var_BIT_08, var_BIT_09, var_BIT_10, var_BIT_11, var_BIT_12, var_BIT_13, var_BIT_14, var_BIT_15, var_BIT_16, var_BIT_17, var_BIT_18, var_BIT_19, var_BIT_20, var_BIT_21, var_BIT_22, var_BIT_23, var_BIT_24, var_BIT_25, var_BIT_26, var_BIT_27, var_BIT_28, var_BIT_29, var_BIT_30, var_BIT_31);
  sendOutputEvent(scmEventCNFID, paECET);
}

CIEC_DWORD func_ASSEMBLE_DWORD_FROM_BOOLS(CIEC_BOOL st_lv_BIT_00, CIEC_BOOL st_lv_BIT_01, CIEC_BOOL st_lv_BIT_02, CIEC_BOOL st_lv_BIT_03, CIEC_BOOL st_lv_BIT_04, CIEC_BOOL st_lv_BIT_05, CIEC_BOOL st_lv_BIT_06, CIEC_BOOL st_lv_BIT_07, CIEC_BOOL st_lv_BIT_08, CIEC_BOOL st_lv_BIT_09, CIEC_BOOL st_lv_BIT_10, CIEC_BOOL st_lv_BIT_11, CIEC_BOOL st_lv_BIT_12, CIEC_BOOL st_lv_BIT_13, CIEC_BOOL st_lv_BIT_14, CIEC_BOOL st_lv_BIT_15, CIEC_BOOL st_lv_BIT_16, CIEC_BOOL st_lv_BIT_17, CIEC_BOOL st_lv_BIT_18, CIEC_BOOL st_lv_BIT_19, CIEC_BOOL st_lv_BIT_20, CIEC_BOOL st_lv_BIT_21, CIEC_BOOL st_lv_BIT_22, CIEC_BOOL st_lv_BIT_23, CIEC_BOOL st_lv_BIT_24, CIEC_BOOL st_lv_BIT_25, CIEC_BOOL st_lv_BIT_26, CIEC_BOOL st_lv_BIT_27, CIEC_BOOL st_lv_BIT_28, CIEC_BOOL st_lv_BIT_29, CIEC_BOOL st_lv_BIT_30, CIEC_BOOL st_lv_BIT_31) {
  CIEC_DWORD st_ret_val = 0_DWORD;

  #line 39 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(0) = st_lv_BIT_00;
  #line 40 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(1) = st_lv_BIT_01;
  #line 41 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(2) = st_lv_BIT_02;
  #line 42 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(3) = st_lv_BIT_03;
  #line 43 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(4) = st_lv_BIT_04;
  #line 44 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(5) = st_lv_BIT_05;
  #line 45 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(6) = st_lv_BIT_06;
  #line 46 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(7) = st_lv_BIT_07;
  #line 47 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(8) = st_lv_BIT_08;
  #line 48 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(9) = st_lv_BIT_09;
  #line 49 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(10) = st_lv_BIT_10;
  #line 50 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(11) = st_lv_BIT_11;
  #line 51 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(12) = st_lv_BIT_12;
  #line 52 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(13) = st_lv_BIT_13;
  #line 53 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(14) = st_lv_BIT_14;
  #line 54 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(15) = st_lv_BIT_15;
  #line 55 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(16) = st_lv_BIT_16;
  #line 56 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(17) = st_lv_BIT_17;
  #line 57 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(18) = st_lv_BIT_18;
  #line 58 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(19) = st_lv_BIT_19;
  #line 59 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(20) = st_lv_BIT_20;
  #line 60 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(21) = st_lv_BIT_21;
  #line 61 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(22) = st_lv_BIT_22;
  #line 62 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(23) = st_lv_BIT_23;
  #line 63 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(24) = st_lv_BIT_24;
  #line 64 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(25) = st_lv_BIT_25;
  #line 65 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(26) = st_lv_BIT_26;
  #line 66 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(27) = st_lv_BIT_27;
  #line 67 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(28) = st_lv_BIT_28;
  #line 68 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(29) = st_lv_BIT_29;
  #line 69 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(30) = st_lv_BIT_30;
  #line 70 "ASSEMBLE_DWORD_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(31) = st_lv_BIT_31;

  return st_ret_val;
}

