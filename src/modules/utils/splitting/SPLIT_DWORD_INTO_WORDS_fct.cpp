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
 *** Name: SPLIT_DWORD_INTO_WORDS
 *** Description: this Function extracts the 2 WORD from a dword
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-24/Moritz Ortmeier - HR Agrartechnik - rename Function and change Output Variables
 *************************************************************************/

#include "SPLIT_DWORD_INTO_WORDS_fct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SPLIT_DWORD_INTO_WORDS_fct_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_dword.h"
#include "forte_word.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_SPLIT_DWORD_INTO_WORDS, g_nStringIdSPLIT_DWORD_INTO_WORDS)

const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_WORDS::scmDataInputNames[] = {g_nStringIdIN};
const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_WORDS::scmDataInputTypeIds[] = {g_nStringIdDWORD};
const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_WORDS::scmDataOutputNames[] = {g_nStringIdWORD_00, g_nStringIdWORD_01};
const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_WORDS::scmDataOutputTypeIds[] = {g_nStringIdWORD, g_nStringIdWORD};
const TDataIOID FORTE_SPLIT_DWORD_INTO_WORDS::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_SPLIT_DWORD_INTO_WORDS::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_WORDS::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_WORDS::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_SPLIT_DWORD_INTO_WORDS::scmEOWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_SPLIT_DWORD_INTO_WORDS::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_WORDS::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_SPLIT_DWORD_INTO_WORDS::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_SPLIT_DWORD_INTO_WORDS::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_SPLIT_DWORD_INTO_WORDS::FORTE_SPLIT_DWORD_INTO_WORDS(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_WORD_00(var_WORD_00),
    var_conn_WORD_01(var_WORD_01),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_WORD_00(this, 0, &var_conn_WORD_00),
    conn_WORD_01(this, 1, &var_conn_WORD_01) {
}

void FORTE_SPLIT_DWORD_INTO_WORDS::setInitialValues() {
  var_IN = 0_DWORD;
  var_WORD_00 = 0_WORD;
  var_WORD_01 = 0_WORD;
}

void FORTE_SPLIT_DWORD_INTO_WORDS::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_SPLIT_DWORD_INTO_WORDS::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_WORD_00, conn_WORD_00);
      writeData(1, var_WORD_01, conn_WORD_01);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_SPLIT_DWORD_INTO_WORDS::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_SPLIT_DWORD_INTO_WORDS::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_WORD_00;
    case 1: return &var_WORD_01;
  }
  return nullptr;
}

CEventConnection *FORTE_SPLIT_DWORD_INTO_WORDS::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_SPLIT_DWORD_INTO_WORDS::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_SPLIT_DWORD_INTO_WORDS::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_WORD_00;
    case 1: return &conn_WORD_01;
  }
  return nullptr;
}

void FORTE_SPLIT_DWORD_INTO_WORDS::executeEvent(const TEventID, CEventChainExecutionThread *const paECET) {
  func_SPLIT_DWORD_INTO_WORDS(var_IN, var_WORD_00, var_WORD_01);
  sendOutputEvent(scmEventCNFID, paECET);
}

void func_SPLIT_DWORD_INTO_WORDS(CIEC_DWORD st_lv_IN, CIEC_WORD &st_lv_WORD_00, CIEC_WORD &st_lv_WORD_01) {
  st_lv_WORD_00 = 0_WORD;
  st_lv_WORD_01 = 0_WORD;

  #line 13 "SPLIT_DWORD_INTO_WORDS.fct"
  st_lv_WORD_00 = st_lv_IN.cpartial<CIEC_WORD>(0);
  #line 14 "SPLIT_DWORD_INTO_WORDS.fct"
  st_lv_WORD_01 = st_lv_IN.cpartial<CIEC_BOOL>(1);

}

