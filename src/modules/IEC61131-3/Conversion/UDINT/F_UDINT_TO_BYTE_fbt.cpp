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

#include "F_UDINT_TO_BYTE_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_UDINT_TO_BYTE_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_byte.h"
#include "forte_udint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_F_UDINT_TO_BYTE, g_nStringIdF_UDINT_TO_BYTE)

const CStringDictionary::TStringId FORTE_F_UDINT_TO_BYTE::scmDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId FORTE_F_UDINT_TO_BYTE::scmDataInputTypeIds[] = {g_nStringIdUDINT};

const CStringDictionary::TStringId FORTE_F_UDINT_TO_BYTE::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_F_UDINT_TO_BYTE::scmDataOutputTypeIds[] = {g_nStringIdBYTE};

const TDataIOID FORTE_F_UDINT_TO_BYTE::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_UDINT_TO_BYTE::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_UDINT_TO_BYTE::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_F_UDINT_TO_BYTE::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_F_UDINT_TO_BYTE::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_UDINT_TO_BYTE::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_UDINT_TO_BYTE::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_F_UDINT_TO_BYTE::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_F_UDINT_TO_BYTE::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};


FORTE_F_UDINT_TO_BYTE::FORTE_F_UDINT_TO_BYTE(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_IN(CIEC_UDINT(0)),
    var_OUT(CIEC_BYTE(0)),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
}

void FORTE_F_UDINT_TO_BYTE::alg_REQ(void) {
  
  var_OUT = func_UDINT_TO_BYTE(var_IN);
}


void FORTE_F_UDINT_TO_BYTE::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_F_UDINT_TO_BYTE::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_UDINT_TO_BYTE::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_UDINT_TO_BYTE::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_UDINT_TO_BYTE::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_F_UDINT_TO_BYTE::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_UDINT_TO_BYTE::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_F_UDINT_TO_BYTE::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_UDINT_TO_BYTE::getVarInternal(size_t) {
  return nullptr;
}


