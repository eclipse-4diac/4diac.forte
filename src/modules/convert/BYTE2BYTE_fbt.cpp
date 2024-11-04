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

#include "BYTE2BYTE_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "BYTE2BYTE_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_byte.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_BYTE2BYTE, g_nStringIdBYTE2BYTE)

const CStringDictionary::TStringId FORTE_BYTE2BYTE::scmDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId FORTE_BYTE2BYTE::scmDataInputTypeIds[] = {g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_BYTE2BYTE::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_BYTE2BYTE::scmDataOutputTypeIds[] = {g_nStringIdBYTE};

const TDataIOID FORTE_BYTE2BYTE::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_BYTE2BYTE::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_BYTE2BYTE::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_BYTE2BYTE::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_BYTE2BYTE::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_BYTE2BYTE::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_BYTE2BYTE::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_BYTE2BYTE::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_BYTE2BYTE::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};


FORTE_BYTE2BYTE::FORTE_BYTE2BYTE(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_IN(CIEC_BYTE(0)),
    var_OUT(CIEC_BYTE(0)),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
}

void FORTE_BYTE2BYTE::alg_REQ(void) {
  
  var_OUT = var_IN;
}


void FORTE_BYTE2BYTE::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_BYTE2BYTE::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_BYTE2BYTE::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_BYTE2BYTE::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_BYTE2BYTE::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_BYTE2BYTE::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_BYTE2BYTE::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_BYTE2BYTE::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_BYTE2BYTE::getVarInternal(size_t) {
  return nullptr;
}


