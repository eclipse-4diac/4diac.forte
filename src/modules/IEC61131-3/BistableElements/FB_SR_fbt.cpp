/*******************************************************************************
 * Copyright (c) 2023 Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Martin Jobst
 *     - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "FB_SR_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FB_SR_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_FB_SR, g_nStringIdFB_SR)

const CStringDictionary::TStringId FORTE_FB_SR::scmDataInputNames[] = {g_nStringIdS1, g_nStringIdR};

const CStringDictionary::TStringId FORTE_FB_SR::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBOOL};

const CStringDictionary::TStringId FORTE_FB_SR::scmDataOutputNames[] = {g_nStringIdQ1};

const CStringDictionary::TStringId FORTE_FB_SR::scmDataOutputTypeIds[] = {g_nStringIdBOOL};

const TDataIOID FORTE_FB_SR::scmEIWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_FB_SR::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_FB_SR::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_FB_SR::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_FB_SR::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FB_SR::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_FB_SR::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_FB_SR::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_FB_SR::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};


FORTE_FB_SR::FORTE_FB_SR(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_S1(CIEC_BOOL(0)),
    var_R(CIEC_BOOL(0)),
    var_Q1(CIEC_BOOL(0)),
    var_conn_Q1(var_Q1),
    conn_CNF(this, 0),
    conn_S1(nullptr),
    conn_R(nullptr),
    conn_Q1(this, 0, &var_conn_Q1) {
}

void FORTE_FB_SR::alg_REQ(void) {
  
  var_Q1 = func_OR<CIEC_BOOL>(var_S1, func_AND<CIEC_BOOL>(func_NOT<CIEC_BOOL>(var_R), var_Q1));
}


void FORTE_FB_SR::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FB_SR::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_S1, conn_S1);
      readData(1, var_R, conn_R);
      break;
    }
    default:
      break;
  }
}

void FORTE_FB_SR::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_Q1, conn_Q1);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_FB_SR::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_S1;
    case 1: return &var_R;
  }
  return nullptr;
}

CIEC_ANY *FORTE_FB_SR::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Q1;
  }
  return nullptr;
}

CEventConnection *FORTE_FB_SR::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_FB_SR::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_S1;
    case 1: return &conn_R;
  }
  return nullptr;
}

CDataConnection *FORTE_FB_SR::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Q1;
  }
  return nullptr;
}

CIEC_ANY *FORTE_FB_SR::getVarInternal(size_t) {
  return nullptr;
}


