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

#include "FB_F_TRIG_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FB_F_TRIG_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_FB_F_TRIG, g_nStringIdFB_F_TRIG)

const CStringDictionary::TStringId FORTE_FB_F_TRIG::scmDataInputNames[] = {g_nStringIdCLK};

const CStringDictionary::TStringId FORTE_FB_F_TRIG::scmDataInputTypeIds[] = {g_nStringIdBOOL};

const CStringDictionary::TStringId FORTE_FB_F_TRIG::scmDataOutputNames[] = {g_nStringIdQ};

const CStringDictionary::TStringId FORTE_FB_F_TRIG::scmDataOutputTypeIds[] = {g_nStringIdBOOL};

const TDataIOID FORTE_FB_F_TRIG::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FB_F_TRIG::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_FB_F_TRIG::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_FB_F_TRIG::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_FB_F_TRIG::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FB_F_TRIG::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_FB_F_TRIG::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_FB_F_TRIG::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_FB_F_TRIG::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

const CStringDictionary::TStringId FORTE_FB_F_TRIG::scmInternalsNames[] = {g_nStringIdMEM};
const CStringDictionary::TStringId FORTE_FB_F_TRIG::scmInternalsTypeIds[] = {g_nStringIdBOOL};
const SInternalVarsInformation FORTE_FB_F_TRIG::scmInternalVars = {1, scmInternalsNames, scmInternalsTypeIds};


FORTE_FB_F_TRIG::FORTE_FB_F_TRIG(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, &scmInternalVars),
    var_MEM(CIEC_BOOL(true)),
    var_CLK(CIEC_BOOL(0)),
    var_Q(CIEC_BOOL(0)),
    var_conn_Q(var_Q),
    conn_CNF(this, 0),
    conn_CLK(nullptr),
    conn_Q(this, 0, &var_conn_Q) {
}

void FORTE_FB_F_TRIG::alg_REQ(void) {
  
  var_Q = func_AND<CIEC_BOOL>(func_NOT<CIEC_BOOL>(var_CLK), func_NOT<CIEC_BOOL>(var_MEM));
  var_MEM = func_NOT<CIEC_BOOL>(var_CLK);
}


void FORTE_FB_F_TRIG::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FB_F_TRIG::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_CLK, conn_CLK);
      break;
    }
    default:
      break;
  }
}

void FORTE_FB_F_TRIG::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_Q, conn_Q);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_FB_F_TRIG::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_CLK;
  }
  return nullptr;
}

CIEC_ANY *FORTE_FB_F_TRIG::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Q;
  }
  return nullptr;
}

CEventConnection *FORTE_FB_F_TRIG::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_FB_F_TRIG::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CLK;
  }
  return nullptr;
}

CDataConnection *FORTE_FB_F_TRIG::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Q;
  }
  return nullptr;
}

CIEC_ANY *FORTE_FB_F_TRIG::getVarInternal(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_MEM;
  }
  return nullptr;
}


