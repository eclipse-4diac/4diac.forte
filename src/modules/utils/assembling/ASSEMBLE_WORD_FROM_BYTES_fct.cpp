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
 *** Name: ASSEMBLE_WORD_FROM_BYTES
 *** Description: this Function combines the 2 BYTES to a WORD
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-28/Moritz Ortmeier - HR Agrartechnik - rename Function and change Input/Output Variables
 *************************************************************************/

#include "ASSEMBLE_WORD_FROM_BYTES_fct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ASSEMBLE_WORD_FROM_BYTES_fct_gen.cpp"
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
#include "ASSEMBLE_WORD_FROM_BYTES_fct.h"

DEFINE_FIRMWARE_FB(FORTE_ASSEMBLE_WORD_FROM_BYTES, g_nStringIdASSEMBLE_WORD_FROM_BYTES)

const CStringDictionary::TStringId FORTE_ASSEMBLE_WORD_FROM_BYTES::scmDataInputNames[] = {g_nStringIdBYTE_00, g_nStringIdBYTE_01};
const CStringDictionary::TStringId FORTE_ASSEMBLE_WORD_FROM_BYTES::scmDataInputTypeIds[] = {g_nStringIdBYTE, g_nStringIdBYTE};
const CStringDictionary::TStringId FORTE_ASSEMBLE_WORD_FROM_BYTES::scmDataOutputNames[] = {g_nStringId};
const CStringDictionary::TStringId FORTE_ASSEMBLE_WORD_FROM_BYTES::scmDataOutputTypeIds[] = {g_nStringIdWORD};
const TDataIOID FORTE_ASSEMBLE_WORD_FROM_BYTES::scmEIWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_ASSEMBLE_WORD_FROM_BYTES::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_ASSEMBLE_WORD_FROM_BYTES::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_ASSEMBLE_WORD_FROM_BYTES::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_ASSEMBLE_WORD_FROM_BYTES::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_ASSEMBLE_WORD_FROM_BYTES::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_ASSEMBLE_WORD_FROM_BYTES::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_ASSEMBLE_WORD_FROM_BYTES::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_ASSEMBLE_WORD_FROM_BYTES::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_ASSEMBLE_WORD_FROM_BYTES::FORTE_ASSEMBLE_WORD_FROM_BYTES(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_(var_),
    conn_CNF(this, 0),
    conn_BYTE_00(nullptr),
    conn_BYTE_01(nullptr),
    conn_(this, 0, &var_conn_) {
}

void FORTE_ASSEMBLE_WORD_FROM_BYTES::setInitialValues() {
  var_BYTE_00 = 0_BYTE;
  var_BYTE_01 = 0_BYTE;
  var_ = 0_WORD;
}

void FORTE_ASSEMBLE_WORD_FROM_BYTES::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_BYTE_00, conn_BYTE_00);
      readData(1, var_BYTE_01, conn_BYTE_01);
      break;
    }
    default:
      break;
  }
}

void FORTE_ASSEMBLE_WORD_FROM_BYTES::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_, conn_);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_ASSEMBLE_WORD_FROM_BYTES::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_BYTE_00;
    case 1: return &var_BYTE_01;
  }
  return nullptr;
}

CIEC_ANY *FORTE_ASSEMBLE_WORD_FROM_BYTES::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_;
  }
  return nullptr;
}

CEventConnection *FORTE_ASSEMBLE_WORD_FROM_BYTES::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_ASSEMBLE_WORD_FROM_BYTES::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_BYTE_00;
    case 1: return &conn_BYTE_01;
  }
  return nullptr;
}

CDataConnection *FORTE_ASSEMBLE_WORD_FROM_BYTES::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_;
  }
  return nullptr;
}

void FORTE_ASSEMBLE_WORD_FROM_BYTES::executeEvent(const TEventID, CEventChainExecutionThread *const paECET) {
  var_ = func_ASSEMBLE_WORD_FROM_BYTES(var_BYTE_00, var_BYTE_01);
  sendOutputEvent(scmEventCNFID, paECET);
}

CIEC_WORD func_ASSEMBLE_WORD_FROM_BYTES(CIEC_BYTE st_lv_BYTE_00, CIEC_BYTE st_lv_BYTE_01) {
  CIEC_WORD st_ret_val = 0_WORD;

  #line 9 "ASSEMBLE_WORD_FROM_BYTES.fct"
  st_ret_val.partial<CIEC_BYTE>(0) = st_lv_BYTE_00;
  #line 10 "ASSEMBLE_WORD_FROM_BYTES.fct"
  st_ret_val.partial<CIEC_BYTE>(1) = st_lv_BYTE_01;

  return st_ret_val;
}

