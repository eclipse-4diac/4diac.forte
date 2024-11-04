/*************************************************************************  
 *** Copyright (c) 2012, 2023 TU Wien ACIN, HR Agrartechnik GmbH  
 *** This program and the accompanying materials are made available under the  
 *** terms of the Eclipse Public License 2.0 which is available at  
 *** http://www.eclipse.org/legal/epl-2.0.  
 ***  
 *** SPDX-License-Identifier: EPL-2.0  
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: FIELDBUS_PERCENT_TO_WORD
 *** Description: Convert a WORD Value Range 0-FAFF to a REAL in the Range 0.0 to 100.0
 *** Version:
 ***     1.0: 2023-10-21/Franz Höpfinger - HR Agrartechnik GmbH -
 ***     1.1: 2024-09-19/Franz Höpfinger - HR Agrartechnik GmbH - Update to a more Function like Interface
 *************************************************************************/

#include "FIELDBUS_PERCENT_TO_WORD_fct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FIELDBUS_PERCENT_TO_WORD_fct_gen.cpp"
#endif

#include "forte_real.h"
#include "forte_udint.h"
#include "forte_word.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "FIELDBUS_PERCENT_TO_WORD_fct.h"
#include "FIELDBUS_SIGNAL_gcf.h"

DEFINE_FIRMWARE_FB(FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD, g_nStringIdsignalprocessing__FIELDBUS_PERCENT_TO_WORD)

const CStringDictionary::TStringId FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::scmDataInputNames[] = {g_nStringIdRI};
const CStringDictionary::TStringId FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::scmDataInputTypeIds[] = {g_nStringIdREAL};
const CStringDictionary::TStringId FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::scmDataOutputNames[] = {g_nStringId};
const CStringDictionary::TStringId FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::scmDataOutputTypeIds[] = {g_nStringIdWORD};
const TDataIOID FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_(var_),
    conn_CNF(this, 0),
    conn_RI(nullptr),
    conn_(this, 0, &var_conn_) {
}

void FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::setInitialValues() {
  var_RI = 0_REAL;
  var_ = 0_WORD;
}

void FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_RI, conn_RI);
      break;
    }
    default:
      break;
  }
}

void FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_, conn_);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_RI;
  }
  return nullptr;
}

CIEC_ANY *FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_;
  }
  return nullptr;
}

CEventConnection *FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_RI;
  }
  return nullptr;
}

CDataConnection *FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_;
  }
  return nullptr;
}

void FORTE_signalprocessing__FIELDBUS_PERCENT_TO_WORD::executeEvent(const TEventID, CEventChainExecutionThread *const paECET) {
  var_ = func_FIELDBUS_PERCENT_TO_WORD(var_RI);
  sendOutputEvent(scmEventCNFID, paECET);
}

CIEC_WORD func_FIELDBUS_PERCENT_TO_WORD(CIEC_REAL st_lv_RI) {
  CIEC_WORD st_ret_val = 0_WORD;

  #line 9 "FIELDBUS_PERCENT_TO_WORD.fct"
  st_ret_val = func_UDINT_TO_WORD(func_REAL_TO_UDINT(func_MUL<CIEC_REAL>(st_lv_RI, func_UDINT_TO_REAL(func_WORD_TO_UDINT(st_global_FIELDBUS_VALID_SIGNAL_W)))));

  return st_ret_val;
}
