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

#include "FB_RS_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FB_RS_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_FB_RS, g_nStringIdFB_RS)

const CStringDictionary::TStringId FORTE_FB_RS::scmDataInputNames[] = {g_nStringIdS, g_nStringIdR1};

const CStringDictionary::TStringId FORTE_FB_RS::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBOOL};

const CStringDictionary::TStringId FORTE_FB_RS::scmDataOutputNames[] = {g_nStringIdQ1};

const CStringDictionary::TStringId FORTE_FB_RS::scmDataOutputTypeIds[] = {g_nStringIdBOOL};

const TDataIOID FORTE_FB_RS::scmEIWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_FB_RS::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_FB_RS::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_FB_RS::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_FB_RS::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FB_RS::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_FB_RS::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_FB_RS::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_FB_RS::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};


FORTE_FB_RS::FORTE_FB_RS(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_S(CIEC_BOOL(0)),
    var_R1(CIEC_BOOL(0)),
    var_Q1(CIEC_BOOL(0)),
    var_conn_Q1(var_Q1),
    conn_CNF(this, 0),
    conn_S(nullptr),
    conn_R1(nullptr),
    conn_Q1(this, 0, &var_conn_Q1) {
}

void FORTE_FB_RS::alg_REQ(void) {
  
  var_Q1 = func_AND<CIEC_BOOL>(func_NOT<CIEC_BOOL>(var_R1), func_OR<CIEC_BOOL>(var_S, var_Q1));
}


void FORTE_FB_RS::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FB_RS::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
       readData(0, var_S, conn_S);
      readData(1, var_R1, conn_R1);
      break;
    }
    default:
      break;
  }
}

void FORTE_FB_RS::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_Q1, conn_Q1);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_FB_RS::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_S;
    case 1: return &var_R1;
  }
  return nullptr;
}

CIEC_ANY *FORTE_FB_RS::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Q1;
  }
  return nullptr;
}

CEventConnection *FORTE_FB_RS::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_FB_RS::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_S;
    case 1: return &conn_R1;
  }
  return nullptr;
}

CDataConnection *FORTE_FB_RS::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Q1;
  }
  return nullptr;
}

CIEC_ANY *FORTE_FB_RS::getVarInternal(size_t) {
  return nullptr;
}


