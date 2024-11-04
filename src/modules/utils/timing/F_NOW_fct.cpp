/*******************************************************************************
 * Copyright (c) 2024 HR Agrartechnik GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0

 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: F_NOW
 *** Description: return the current time
 *** Version:
 ***     1.0: 2024-10-01/Franz Höpfinger - HR Agrartechnik GmbH    -
 *************************************************************************/

#include "F_NOW_fct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_NOW_fct_gen.cpp"
#endif

#include "forte_date_and_time.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "F_NOW_fct.h"

DEFINE_FIRMWARE_FB(FORTE_utils__timing__F_NOW, g_nStringIdutils__timing__F_NOW)

const CStringDictionary::TStringId FORTE_utils__timing__F_NOW::scmDataOutputNames[] = {g_nStringId};
const CStringDictionary::TStringId FORTE_utils__timing__F_NOW::scmDataOutputTypeIds[] = {g_nStringIdDATE_AND_TIME};
const TForteInt16 FORTE_utils__timing__F_NOW::scmEIWithIndexes[] = {-1};
const CStringDictionary::TStringId FORTE_utils__timing__F_NOW::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_utils__timing__F_NOW::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_utils__timing__F_NOW::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_utils__timing__F_NOW::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_utils__timing__F_NOW::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_utils__timing__F_NOW::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_utils__timing__F_NOW::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, nullptr, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  0, nullptr, nullptr,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_utils__timing__F_NOW::FORTE_utils__timing__F_NOW(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_(var_),
    conn_CNF(this, 0),
    conn_(this, 0, &var_conn_) {
}

void FORTE_utils__timing__F_NOW::setInitialValues() {
  var_ = 0_DATE_AND_TIME;
}

void FORTE_utils__timing__F_NOW::readInputData(TEventID) {
  // nothing to do
}

void FORTE_utils__timing__F_NOW::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_, conn_);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_utils__timing__F_NOW::getDI(size_t) {
  return nullptr;
}

CIEC_ANY *FORTE_utils__timing__F_NOW::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_;
  }
  return nullptr;
}

CEventConnection *FORTE_utils__timing__F_NOW::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_utils__timing__F_NOW::getDIConUnchecked(TPortId) {
  return nullptr;
}

CDataConnection *FORTE_utils__timing__F_NOW::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_;
  }
  return nullptr;
}

void FORTE_utils__timing__F_NOW::executeEvent(const TEventID, CEventChainExecutionThread *const paECET) {
  var_ = func_F_NOW();
  sendOutputEvent(scmEventCNFID, paECET);
}

CIEC_DATE_AND_TIME func_F_NOW() {
  CIEC_DATE_AND_TIME st_ret_val = 0_DATE_AND_TIME;

  #line 5 "F_NOW.fct"
  st_ret_val = func_NOW();

  return st_ret_val;
}
