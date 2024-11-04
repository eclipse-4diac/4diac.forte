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
 *** Name: ASSEMBLE_DWORD_FROM_WORDS
 *** Description: this Function combines the 2 WORDS to a dword
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-28/Moritz Ortmeier - HR Agrartechnik - rename Function and change Input/Output Variables
 *************************************************************************/

#include "ASSEMBLE_DWORD_FROM_WORDS_fct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ASSEMBLE_DWORD_FROM_WORDS_fct_gen.cpp"
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
#include "ASSEMBLE_DWORD_FROM_WORDS_fct.h"

DEFINE_FIRMWARE_FB(FORTE_ASSEMBLE_DWORD_FROM_WORDS, g_nStringIdASSEMBLE_DWORD_FROM_WORDS)

const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_WORDS::scmDataInputNames[] = {g_nStringIdWORD_00, g_nStringIdWORD_01};
const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_WORDS::scmDataInputTypeIds[] = {g_nStringIdWORD, g_nStringIdWORD};
const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_WORDS::scmDataOutputNames[] = {g_nStringId};
const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_WORDS::scmDataOutputTypeIds[] = {g_nStringIdDWORD};
const TDataIOID FORTE_ASSEMBLE_DWORD_FROM_WORDS::scmEIWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_ASSEMBLE_DWORD_FROM_WORDS::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_WORDS::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_WORDS::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_ASSEMBLE_DWORD_FROM_WORDS::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_ASSEMBLE_DWORD_FROM_WORDS::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_WORDS::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_ASSEMBLE_DWORD_FROM_WORDS::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_ASSEMBLE_DWORD_FROM_WORDS::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_ASSEMBLE_DWORD_FROM_WORDS::FORTE_ASSEMBLE_DWORD_FROM_WORDS(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_(var_),
    conn_CNF(this, 0),
    conn_WORD_00(nullptr),
    conn_WORD_01(nullptr),
    conn_(this, 0, &var_conn_) {
}

void FORTE_ASSEMBLE_DWORD_FROM_WORDS::setInitialValues() {
  var_WORD_00 = 0_WORD;
  var_WORD_01 = 0_WORD;
  var_ = 0_DWORD;
}

void FORTE_ASSEMBLE_DWORD_FROM_WORDS::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_WORD_00, conn_WORD_00);
      readData(1, var_WORD_01, conn_WORD_01);
      break;
    }
    default:
      break;
  }
}

void FORTE_ASSEMBLE_DWORD_FROM_WORDS::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_, conn_);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_ASSEMBLE_DWORD_FROM_WORDS::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_WORD_00;
    case 1: return &var_WORD_01;
  }
  return nullptr;
}

CIEC_ANY *FORTE_ASSEMBLE_DWORD_FROM_WORDS::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_;
  }
  return nullptr;
}

CEventConnection *FORTE_ASSEMBLE_DWORD_FROM_WORDS::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_ASSEMBLE_DWORD_FROM_WORDS::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_WORD_00;
    case 1: return &conn_WORD_01;
  }
  return nullptr;
}

CDataConnection *FORTE_ASSEMBLE_DWORD_FROM_WORDS::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_;
  }
  return nullptr;
}

void FORTE_ASSEMBLE_DWORD_FROM_WORDS::executeEvent(const TEventID, CEventChainExecutionThread *const paECET) {
  var_ = func_ASSEMBLE_DWORD_FROM_WORDS(var_WORD_00, var_WORD_01);
  sendOutputEvent(scmEventCNFID, paECET);
}

CIEC_DWORD func_ASSEMBLE_DWORD_FROM_WORDS(CIEC_WORD st_lv_WORD_00, CIEC_WORD st_lv_WORD_01) {
  CIEC_DWORD st_ret_val = 0_DWORD;

  #line 9 "ASSEMBLE_DWORD_FROM_WORDS.fct"
  st_ret_val.partial<CIEC_WORD>(0) = st_lv_WORD_00;
  #line 10 "ASSEMBLE_DWORD_FROM_WORDS.fct"
  st_ret_val.partial<CIEC_WORD>(1) = st_lv_WORD_01;

  return st_ret_val;
}

