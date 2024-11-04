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

#include "REAL2REAL_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "REAL2REAL_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_real.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_REAL2REAL, g_nStringIdREAL2REAL)

const CStringDictionary::TStringId FORTE_REAL2REAL::scmDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId FORTE_REAL2REAL::scmDataInputTypeIds[] = {g_nStringIdREAL};

const CStringDictionary::TStringId FORTE_REAL2REAL::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_REAL2REAL::scmDataOutputTypeIds[] = {g_nStringIdREAL};

const TDataIOID FORTE_REAL2REAL::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_REAL2REAL::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_REAL2REAL::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_REAL2REAL::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_REAL2REAL::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_REAL2REAL::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_REAL2REAL::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_REAL2REAL::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_REAL2REAL::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};


FORTE_REAL2REAL::FORTE_REAL2REAL(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_IN(CIEC_REAL(0)),
    var_OUT(CIEC_REAL(0)),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
}

void FORTE_REAL2REAL::alg_REQ(void) {
  
  var_OUT = var_IN;
}


void FORTE_REAL2REAL::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_REAL2REAL::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_REAL2REAL::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_REAL2REAL::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_REAL2REAL::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_REAL2REAL::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_REAL2REAL::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_REAL2REAL::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_REAL2REAL::getVarInternal(size_t) {
  return nullptr;
}


