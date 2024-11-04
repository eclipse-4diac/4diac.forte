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

#include "BOOL2BOOL_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "BOOL2BOOL_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_BOOL2BOOL, g_nStringIdBOOL2BOOL)

const CStringDictionary::TStringId FORTE_BOOL2BOOL::scmDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId FORTE_BOOL2BOOL::scmDataInputTypeIds[] = {g_nStringIdBOOL};

const CStringDictionary::TStringId FORTE_BOOL2BOOL::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_BOOL2BOOL::scmDataOutputTypeIds[] = {g_nStringIdBOOL};

const TDataIOID FORTE_BOOL2BOOL::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_BOOL2BOOL::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_BOOL2BOOL::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_BOOL2BOOL::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_BOOL2BOOL::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_BOOL2BOOL::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_BOOL2BOOL::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_BOOL2BOOL::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_BOOL2BOOL::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};


FORTE_BOOL2BOOL::FORTE_BOOL2BOOL(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_IN(CIEC_BOOL(0)),
    var_OUT(CIEC_BOOL(0)),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
}

void FORTE_BOOL2BOOL::alg_REQ(void) {
  
  var_OUT = var_IN;
}


void FORTE_BOOL2BOOL::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_BOOL2BOOL::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_BOOL2BOOL::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_BOOL2BOOL::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_BOOL2BOOL::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_BOOL2BOOL::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_BOOL2BOOL::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_BOOL2BOOL::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_BOOL2BOOL::getVarInternal(size_t) {
  return nullptr;
}


