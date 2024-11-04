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

#include "LREAL2LREAL_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "LREAL2LREAL_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_lreal.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_LREAL2LREAL, g_nStringIdLREAL2LREAL)

const CStringDictionary::TStringId FORTE_LREAL2LREAL::scmDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId FORTE_LREAL2LREAL::scmDataInputTypeIds[] = {g_nStringIdLREAL};

const CStringDictionary::TStringId FORTE_LREAL2LREAL::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_LREAL2LREAL::scmDataOutputTypeIds[] = {g_nStringIdLREAL};

const TDataIOID FORTE_LREAL2LREAL::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_LREAL2LREAL::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_LREAL2LREAL::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_LREAL2LREAL::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_LREAL2LREAL::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_LREAL2LREAL::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_LREAL2LREAL::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_LREAL2LREAL::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_LREAL2LREAL::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};


FORTE_LREAL2LREAL::FORTE_LREAL2LREAL(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_IN(CIEC_LREAL(0)),
    var_OUT(CIEC_LREAL(0)),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
}

void FORTE_LREAL2LREAL::alg_REQ(void) {
  
  var_OUT = var_IN;
}


void FORTE_LREAL2LREAL::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_LREAL2LREAL::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_LREAL2LREAL::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_LREAL2LREAL::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_LREAL2LREAL::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_LREAL2LREAL::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_LREAL2LREAL::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_LREAL2LREAL::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_LREAL2LREAL::getVarInternal(size_t) {
  return nullptr;
}


