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

#include "UDINT2UDINT_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "UDINT2UDINT_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_udint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_UDINT2UDINT, g_nStringIdUDINT2UDINT)

const CStringDictionary::TStringId FORTE_UDINT2UDINT::scmDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId FORTE_UDINT2UDINT::scmDataInputTypeIds[] = {g_nStringIdUDINT};

const CStringDictionary::TStringId FORTE_UDINT2UDINT::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_UDINT2UDINT::scmDataOutputTypeIds[] = {g_nStringIdUDINT};

const TDataIOID FORTE_UDINT2UDINT::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_UDINT2UDINT::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_UDINT2UDINT::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_UDINT2UDINT::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_UDINT2UDINT::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_UDINT2UDINT::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_UDINT2UDINT::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_UDINT2UDINT::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_UDINT2UDINT::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};


FORTE_UDINT2UDINT::FORTE_UDINT2UDINT(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_IN(CIEC_UDINT(0)),
    var_OUT(CIEC_UDINT(0)),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
}

void FORTE_UDINT2UDINT::alg_REQ(void) {
  
  var_OUT = var_IN;
}


void FORTE_UDINT2UDINT::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_UDINT2UDINT::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_UDINT2UDINT::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_UDINT2UDINT::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_UDINT2UDINT::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_UDINT2UDINT::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_UDINT2UDINT::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_UDINT2UDINT::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_UDINT2UDINT::getVarInternal(size_t) {
  return nullptr;
}


