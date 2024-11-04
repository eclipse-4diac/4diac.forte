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
 *** Name: SPLIT_WORD_INTO_BOOLS
 *** Description: this Function extracts the 16 BOOLS from a word
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-24/Moritz Ortmeier - HR Agrartechnik - rename Function and change Output Variables
 *************************************************************************/

#include "SPLIT_WORD_INTO_BOOLS_fct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SPLIT_WORD_INTO_BOOLS_fct_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_bool.h"
#include "forte_word.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_SPLIT_WORD_INTO_BOOLS, g_nStringIdSPLIT_WORD_INTO_BOOLS)

const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BOOLS::scmDataInputNames[] = {g_nStringIdIN};
const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BOOLS::scmDataInputTypeIds[] = {g_nStringIdWORD};
const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BOOLS::scmDataOutputNames[] = {g_nStringIdBIT_00, g_nStringIdBIT_01, g_nStringIdBIT_02, g_nStringIdBIT_03, g_nStringIdBIT_04, g_nStringIdBIT_05, g_nStringIdBIT_06, g_nStringIdBIT_07, g_nStringIdBIT_08, g_nStringIdBIT_09, g_nStringIdBIT_10, g_nStringIdBIT_11, g_nStringIdBIT_12, g_nStringIdBIT_13, g_nStringIdBIT_14, g_nStringIdBIT_15};
const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BOOLS::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL};
const TDataIOID FORTE_SPLIT_WORD_INTO_BOOLS::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_SPLIT_WORD_INTO_BOOLS::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BOOLS::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BOOLS::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_SPLIT_WORD_INTO_BOOLS::scmEOWith[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, scmWithListDelimiter};
const TForteInt16 FORTE_SPLIT_WORD_INTO_BOOLS::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BOOLS::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BOOLS::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_SPLIT_WORD_INTO_BOOLS::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  16, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_SPLIT_WORD_INTO_BOOLS::FORTE_SPLIT_WORD_INTO_BOOLS(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_BIT_00(var_BIT_00),
    var_conn_BIT_01(var_BIT_01),
    var_conn_BIT_02(var_BIT_02),
    var_conn_BIT_03(var_BIT_03),
    var_conn_BIT_04(var_BIT_04),
    var_conn_BIT_05(var_BIT_05),
    var_conn_BIT_06(var_BIT_06),
    var_conn_BIT_07(var_BIT_07),
    var_conn_BIT_08(var_BIT_08),
    var_conn_BIT_09(var_BIT_09),
    var_conn_BIT_10(var_BIT_10),
    var_conn_BIT_11(var_BIT_11),
    var_conn_BIT_12(var_BIT_12),
    var_conn_BIT_13(var_BIT_13),
    var_conn_BIT_14(var_BIT_14),
    var_conn_BIT_15(var_BIT_15),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_BIT_00(this, 0, &var_conn_BIT_00),
    conn_BIT_01(this, 1, &var_conn_BIT_01),
    conn_BIT_02(this, 2, &var_conn_BIT_02),
    conn_BIT_03(this, 3, &var_conn_BIT_03),
    conn_BIT_04(this, 4, &var_conn_BIT_04),
    conn_BIT_05(this, 5, &var_conn_BIT_05),
    conn_BIT_06(this, 6, &var_conn_BIT_06),
    conn_BIT_07(this, 7, &var_conn_BIT_07),
    conn_BIT_08(this, 8, &var_conn_BIT_08),
    conn_BIT_09(this, 9, &var_conn_BIT_09),
    conn_BIT_10(this, 10, &var_conn_BIT_10),
    conn_BIT_11(this, 11, &var_conn_BIT_11),
    conn_BIT_12(this, 12, &var_conn_BIT_12),
    conn_BIT_13(this, 13, &var_conn_BIT_13),
    conn_BIT_14(this, 14, &var_conn_BIT_14),
    conn_BIT_15(this, 15, &var_conn_BIT_15) {
}

void FORTE_SPLIT_WORD_INTO_BOOLS::setInitialValues() {
  var_IN = 0_WORD;
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
}

void FORTE_SPLIT_WORD_INTO_BOOLS::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_SPLIT_WORD_INTO_BOOLS::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_BIT_00, conn_BIT_00);
      writeData(1, var_BIT_01, conn_BIT_01);
      writeData(2, var_BIT_02, conn_BIT_02);
      writeData(3, var_BIT_03, conn_BIT_03);
      writeData(4, var_BIT_04, conn_BIT_04);
      writeData(5, var_BIT_05, conn_BIT_05);
      writeData(6, var_BIT_06, conn_BIT_06);
      writeData(7, var_BIT_07, conn_BIT_07);
      writeData(8, var_BIT_08, conn_BIT_08);
      writeData(9, var_BIT_09, conn_BIT_09);
      writeData(10, var_BIT_10, conn_BIT_10);
      writeData(11, var_BIT_11, conn_BIT_11);
      writeData(12, var_BIT_12, conn_BIT_12);
      writeData(13, var_BIT_13, conn_BIT_13);
      writeData(14, var_BIT_14, conn_BIT_14);
      writeData(15, var_BIT_15, conn_BIT_15);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_SPLIT_WORD_INTO_BOOLS::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_SPLIT_WORD_INTO_BOOLS::getDO(const size_t paIndex) {
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
  }
  return nullptr;
}

CEventConnection *FORTE_SPLIT_WORD_INTO_BOOLS::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_SPLIT_WORD_INTO_BOOLS::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_SPLIT_WORD_INTO_BOOLS::getDOConUnchecked(const TPortId paIndex) {
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
  }
  return nullptr;
}

void FORTE_SPLIT_WORD_INTO_BOOLS::executeEvent(const TEventID, CEventChainExecutionThread *const paECET) {
  func_SPLIT_WORD_INTO_BOOLS(var_IN, var_BIT_00, var_BIT_01, var_BIT_02, var_BIT_03, var_BIT_04, var_BIT_05, var_BIT_06, var_BIT_07, var_BIT_08, var_BIT_09, var_BIT_10, var_BIT_11, var_BIT_12, var_BIT_13, var_BIT_14, var_BIT_15);
  sendOutputEvent(scmEventCNFID, paECET);
}

void func_SPLIT_WORD_INTO_BOOLS(CIEC_WORD st_lv_IN, CIEC_BOOL &st_lv_BIT_00, CIEC_BOOL &st_lv_BIT_01, CIEC_BOOL &st_lv_BIT_02, CIEC_BOOL &st_lv_BIT_03, CIEC_BOOL &st_lv_BIT_04, CIEC_BOOL &st_lv_BIT_05, CIEC_BOOL &st_lv_BIT_06, CIEC_BOOL &st_lv_BIT_07, CIEC_BOOL &st_lv_BIT_08, CIEC_BOOL &st_lv_BIT_09, CIEC_BOOL &st_lv_BIT_10, CIEC_BOOL &st_lv_BIT_11, CIEC_BOOL &st_lv_BIT_12, CIEC_BOOL &st_lv_BIT_13, CIEC_BOOL &st_lv_BIT_14, CIEC_BOOL &st_lv_BIT_15) {
  st_lv_BIT_00 = 0_BOOL;
  st_lv_BIT_01 = 0_BOOL;
  st_lv_BIT_02 = 0_BOOL;
  st_lv_BIT_03 = 0_BOOL;
  st_lv_BIT_04 = 0_BOOL;
  st_lv_BIT_05 = 0_BOOL;
  st_lv_BIT_06 = 0_BOOL;
  st_lv_BIT_07 = 0_BOOL;
  st_lv_BIT_08 = 0_BOOL;
  st_lv_BIT_09 = 0_BOOL;
  st_lv_BIT_10 = 0_BOOL;
  st_lv_BIT_11 = 0_BOOL;
  st_lv_BIT_12 = 0_BOOL;
  st_lv_BIT_13 = 0_BOOL;
  st_lv_BIT_14 = 0_BOOL;
  st_lv_BIT_15 = 0_BOOL;

  #line 27 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_00 = st_lv_IN.cpartial<CIEC_BOOL>(0);
  #line 28 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_01 = st_lv_IN.cpartial<CIEC_BOOL>(1);
  #line 29 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_02 = st_lv_IN.cpartial<CIEC_BOOL>(2);
  #line 30 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_03 = st_lv_IN.cpartial<CIEC_BOOL>(3);
  #line 31 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_04 = st_lv_IN.cpartial<CIEC_BOOL>(4);
  #line 32 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_05 = st_lv_IN.cpartial<CIEC_BOOL>(5);
  #line 33 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_06 = st_lv_IN.cpartial<CIEC_BOOL>(6);
  #line 34 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_07 = st_lv_IN.cpartial<CIEC_BOOL>(7);
  #line 35 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_08 = st_lv_IN.cpartial<CIEC_BOOL>(8);
  #line 36 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_09 = st_lv_IN.cpartial<CIEC_BOOL>(9);
  #line 37 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_10 = st_lv_IN.cpartial<CIEC_BOOL>(10);
  #line 38 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_11 = st_lv_IN.cpartial<CIEC_BOOL>(11);
  #line 39 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_12 = st_lv_IN.cpartial<CIEC_BOOL>(12);
  #line 40 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_13 = st_lv_IN.cpartial<CIEC_BOOL>(13);
  #line 41 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_14 = st_lv_IN.cpartial<CIEC_BOOL>(14);
  #line 42 "SPLIT_WORD_INTO_BOOLS.fct"
  st_lv_BIT_15 = st_lv_IN.cpartial<CIEC_BOOL>(15);

}

