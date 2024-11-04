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
 *** Name: SPLIT_WORD_INTO_BYTES
 *** Description: this Function extracts the 2 BYTE from a word
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-24/Moritz Ortmeier - HR Agrartechnik - rename Function and change Output Variables
 *************************************************************************/

#include "SPLIT_WORD_INTO_BYTES_fct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SPLIT_WORD_INTO_BYTES_fct_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_byte.h"
#include "forte_word.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_SPLIT_WORD_INTO_BYTES, g_nStringIdSPLIT_WORD_INTO_BYTES)

const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BYTES::scmDataInputNames[] = {g_nStringIdIN};
const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BYTES::scmDataInputTypeIds[] = {g_nStringIdWORD};
const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BYTES::scmDataOutputNames[] = {g_nStringIdBYTE_00, g_nStringIdBYTE_01};
const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BYTES::scmDataOutputTypeIds[] = {g_nStringIdBYTE, g_nStringIdBYTE};
const TDataIOID FORTE_SPLIT_WORD_INTO_BYTES::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_SPLIT_WORD_INTO_BYTES::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BYTES::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BYTES::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_SPLIT_WORD_INTO_BYTES::scmEOWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_SPLIT_WORD_INTO_BYTES::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BYTES::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_SPLIT_WORD_INTO_BYTES::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_SPLIT_WORD_INTO_BYTES::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_SPLIT_WORD_INTO_BYTES::FORTE_SPLIT_WORD_INTO_BYTES(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_BYTE_00(var_BYTE_00),
    var_conn_BYTE_01(var_BYTE_01),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_BYTE_00(this, 0, &var_conn_BYTE_00),
    conn_BYTE_01(this, 1, &var_conn_BYTE_01) {
}

void FORTE_SPLIT_WORD_INTO_BYTES::setInitialValues() {
  var_IN = 0_WORD;
  var_BYTE_00 = 0_BYTE;
  var_BYTE_01 = 0_BYTE;
}

void FORTE_SPLIT_WORD_INTO_BYTES::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_SPLIT_WORD_INTO_BYTES::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_BYTE_00, conn_BYTE_00);
      writeData(1, var_BYTE_01, conn_BYTE_01);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_SPLIT_WORD_INTO_BYTES::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_SPLIT_WORD_INTO_BYTES::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_BYTE_00;
    case 1: return &var_BYTE_01;
  }
  return nullptr;
}

CEventConnection *FORTE_SPLIT_WORD_INTO_BYTES::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_SPLIT_WORD_INTO_BYTES::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_SPLIT_WORD_INTO_BYTES::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_BYTE_00;
    case 1: return &conn_BYTE_01;
  }
  return nullptr;
}

void FORTE_SPLIT_WORD_INTO_BYTES::executeEvent(const TEventID, CEventChainExecutionThread *const paECET) {
  func_SPLIT_WORD_INTO_BYTES(var_IN, var_BYTE_00, var_BYTE_01);
  sendOutputEvent(scmEventCNFID, paECET);
}

void func_SPLIT_WORD_INTO_BYTES(CIEC_WORD st_lv_IN, CIEC_BYTE &st_lv_BYTE_00, CIEC_BYTE &st_lv_BYTE_01) {
  st_lv_BYTE_00 = 0_BYTE;
  st_lv_BYTE_01 = 0_BYTE;

  #line 13 "SPLIT_WORD_INTO_BYTES.fct"
  st_lv_BYTE_00 = st_lv_IN.cpartial<CIEC_BYTE>(0);
  #line 14 "SPLIT_WORD_INTO_BYTES.fct"
  st_lv_BYTE_01 = st_lv_IN.cpartial<CIEC_BYTE>(1);

}

