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

#include "F_LWORD_TO_LREAL_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_LWORD_TO_LREAL_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_lreal.h"
#include "forte_lword.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_F_LWORD_TO_LREAL, g_nStringIdF_LWORD_TO_LREAL)

const CStringDictionary::TStringId FORTE_F_LWORD_TO_LREAL::scmDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId FORTE_F_LWORD_TO_LREAL::scmDataInputTypeIds[] = {g_nStringIdLWORD};

const CStringDictionary::TStringId FORTE_F_LWORD_TO_LREAL::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_F_LWORD_TO_LREAL::scmDataOutputTypeIds[] = {g_nStringIdLREAL};

const TDataIOID FORTE_F_LWORD_TO_LREAL::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_LWORD_TO_LREAL::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_LWORD_TO_LREAL::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_F_LWORD_TO_LREAL::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_F_LWORD_TO_LREAL::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_LWORD_TO_LREAL::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_LWORD_TO_LREAL::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_F_LWORD_TO_LREAL::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_F_LWORD_TO_LREAL::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};


FORTE_F_LWORD_TO_LREAL::FORTE_F_LWORD_TO_LREAL(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_IN(CIEC_LWORD(0)),
    var_OUT(CIEC_LREAL(0)),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
}

void FORTE_F_LWORD_TO_LREAL::alg_REQ(void) {
  
  var_OUT = func_LWORD_TO_LREAL(var_IN);
}


void FORTE_F_LWORD_TO_LREAL::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_F_LWORD_TO_LREAL::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_LWORD_TO_LREAL::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_LWORD_TO_LREAL::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_LWORD_TO_LREAL::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_F_LWORD_TO_LREAL::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_LWORD_TO_LREAL::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_F_LWORD_TO_LREAL::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_LWORD_TO_LREAL::getVarInternal(size_t) {
  return nullptr;
}


