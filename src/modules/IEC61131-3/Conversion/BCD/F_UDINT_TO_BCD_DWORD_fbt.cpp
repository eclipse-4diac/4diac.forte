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

#include "F_UDINT_TO_BCD_DWORD_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_UDINT_TO_BCD_DWORD_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_dword.h"
#include "forte_udint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_F_UDINT_TO_BCD_DWORD, g_nStringIdF_UDINT_TO_BCD_DWORD)

const CStringDictionary::TStringId FORTE_F_UDINT_TO_BCD_DWORD::scmDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId FORTE_F_UDINT_TO_BCD_DWORD::scmDataInputTypeIds[] = {g_nStringIdUDINT};

const CStringDictionary::TStringId FORTE_F_UDINT_TO_BCD_DWORD::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_F_UDINT_TO_BCD_DWORD::scmDataOutputTypeIds[] = {g_nStringIdDWORD};

const TDataIOID FORTE_F_UDINT_TO_BCD_DWORD::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_UDINT_TO_BCD_DWORD::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_UDINT_TO_BCD_DWORD::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_F_UDINT_TO_BCD_DWORD::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_F_UDINT_TO_BCD_DWORD::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_UDINT_TO_BCD_DWORD::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_UDINT_TO_BCD_DWORD::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_F_UDINT_TO_BCD_DWORD::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_F_UDINT_TO_BCD_DWORD::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};


FORTE_F_UDINT_TO_BCD_DWORD::FORTE_F_UDINT_TO_BCD_DWORD(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_IN(CIEC_UDINT(0)),
    var_OUT(CIEC_DWORD(0)),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
}

void FORTE_F_UDINT_TO_BCD_DWORD::alg_REQ(void) {
  
  var_OUT = func_UDINT_TO_BCD_DWORD(var_IN);
}


void FORTE_F_UDINT_TO_BCD_DWORD::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_F_UDINT_TO_BCD_DWORD::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_UDINT_TO_BCD_DWORD::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_UDINT_TO_BCD_DWORD::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_UDINT_TO_BCD_DWORD::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_F_UDINT_TO_BCD_DWORD::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_UDINT_TO_BCD_DWORD::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_F_UDINT_TO_BCD_DWORD::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_UDINT_TO_BCD_DWORD::getVarInternal(size_t) {
  return nullptr;
}


