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
 *** Name: ASSEMBLE_BYTE_FROM_BOOLS
 *** Description: this Function combines the 8 BOOLS to a BYTE
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-28/Moritz Ortmeier - HR Agrartechnik - rename Function and change Input/Output Variables
 *************************************************************************/

#include "ASSEMBLE_BYTE_FROM_BOOLS_fct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ASSEMBLE_BYTE_FROM_BOOLS_fct_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_byte.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "ASSEMBLE_BYTE_FROM_BOOLS_fct.h"

DEFINE_FIRMWARE_FB(FORTE_ASSEMBLE_BYTE_FROM_BOOLS, g_nStringIdASSEMBLE_BYTE_FROM_BOOLS)

const CStringDictionary::TStringId FORTE_ASSEMBLE_BYTE_FROM_BOOLS::scmDataInputNames[] = {g_nStringIdBIT_00, g_nStringIdBIT_01, g_nStringIdBIT_02, g_nStringIdBIT_03, g_nStringIdBIT_04, g_nStringIdBIT_05, g_nStringIdBIT_06, g_nStringIdBIT_07};
const CStringDictionary::TStringId FORTE_ASSEMBLE_BYTE_FROM_BOOLS::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL};
const CStringDictionary::TStringId FORTE_ASSEMBLE_BYTE_FROM_BOOLS::scmDataOutputNames[] = {g_nStringId};
const CStringDictionary::TStringId FORTE_ASSEMBLE_BYTE_FROM_BOOLS::scmDataOutputTypeIds[] = {g_nStringIdBYTE};
const TDataIOID FORTE_ASSEMBLE_BYTE_FROM_BOOLS::scmEIWith[] = {0, 1, 2, 3, 4, 5, 6, 7, scmWithListDelimiter};
const TForteInt16 FORTE_ASSEMBLE_BYTE_FROM_BOOLS::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_ASSEMBLE_BYTE_FROM_BOOLS::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_ASSEMBLE_BYTE_FROM_BOOLS::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_ASSEMBLE_BYTE_FROM_BOOLS::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_ASSEMBLE_BYTE_FROM_BOOLS::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_ASSEMBLE_BYTE_FROM_BOOLS::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_ASSEMBLE_BYTE_FROM_BOOLS::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_ASSEMBLE_BYTE_FROM_BOOLS::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  8, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_ASSEMBLE_BYTE_FROM_BOOLS::FORTE_ASSEMBLE_BYTE_FROM_BOOLS(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
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
    conn_(this, 0, &var_conn_) {
}

void FORTE_ASSEMBLE_BYTE_FROM_BOOLS::setInitialValues() {
  var_BIT_00 = 0_BOOL;
  var_BIT_01 = 0_BOOL;
  var_BIT_02 = 0_BOOL;
  var_BIT_03 = 0_BOOL;
  var_BIT_04 = 0_BOOL;
  var_BIT_05 = 0_BOOL;
  var_BIT_06 = 0_BOOL;
  var_BIT_07 = 0_BOOL;
  var_ = 0_BYTE;
}

void FORTE_ASSEMBLE_BYTE_FROM_BOOLS::readInputData(const TEventID paEIID) {
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
      break;
    }
    default:
      break;
  }
}

void FORTE_ASSEMBLE_BYTE_FROM_BOOLS::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_, conn_);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_ASSEMBLE_BYTE_FROM_BOOLS::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_BIT_00;
    case 1: return &var_BIT_01;
    case 2: return &var_BIT_02;
    case 3: return &var_BIT_03;
    case 4: return &var_BIT_04;
    case 5: return &var_BIT_05;
    case 6: return &var_BIT_06;
    case 7: return &var_BIT_07;
  }
  return nullptr;
}

CIEC_ANY *FORTE_ASSEMBLE_BYTE_FROM_BOOLS::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_;
  }
  return nullptr;
}

CEventConnection *FORTE_ASSEMBLE_BYTE_FROM_BOOLS::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_ASSEMBLE_BYTE_FROM_BOOLS::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_BIT_00;
    case 1: return &conn_BIT_01;
    case 2: return &conn_BIT_02;
    case 3: return &conn_BIT_03;
    case 4: return &conn_BIT_04;
    case 5: return &conn_BIT_05;
    case 6: return &conn_BIT_06;
    case 7: return &conn_BIT_07;
  }
  return nullptr;
}

CDataConnection *FORTE_ASSEMBLE_BYTE_FROM_BOOLS::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_;
  }
  return nullptr;
}

void FORTE_ASSEMBLE_BYTE_FROM_BOOLS::executeEvent(const TEventID, CEventChainExecutionThread *const paECET) {
  var_ = func_ASSEMBLE_BYTE_FROM_BOOLS(var_BIT_00, var_BIT_01, var_BIT_02, var_BIT_03, var_BIT_04, var_BIT_05, var_BIT_06, var_BIT_07);
  sendOutputEvent(scmEventCNFID, paECET);
}

CIEC_BYTE func_ASSEMBLE_BYTE_FROM_BOOLS(CIEC_BOOL st_lv_BIT_00, CIEC_BOOL st_lv_BIT_01, CIEC_BOOL st_lv_BIT_02, CIEC_BOOL st_lv_BIT_03, CIEC_BOOL st_lv_BIT_04, CIEC_BOOL st_lv_BIT_05, CIEC_BOOL st_lv_BIT_06, CIEC_BOOL st_lv_BIT_07) {
  CIEC_BYTE st_ret_val = 0_BYTE;

  #line 15 "ASSEMBLE_BYTE_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(0) = st_lv_BIT_00;
  #line 16 "ASSEMBLE_BYTE_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(1) = st_lv_BIT_01;
  #line 17 "ASSEMBLE_BYTE_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(2) = st_lv_BIT_02;
  #line 18 "ASSEMBLE_BYTE_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(3) = st_lv_BIT_03;
  #line 19 "ASSEMBLE_BYTE_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(4) = st_lv_BIT_04;
  #line 20 "ASSEMBLE_BYTE_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(5) = st_lv_BIT_05;
  #line 21 "ASSEMBLE_BYTE_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(6) = st_lv_BIT_06;
  #line 22 "ASSEMBLE_BYTE_FROM_BOOLS.fct"
  st_ret_val.partial<CIEC_BOOL>(7) = st_lv_BIT_07;

  return st_ret_val;
}

