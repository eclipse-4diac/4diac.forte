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

#include "F_ULINT_AS_WSTRING_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_ULINT_AS_WSTRING_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_wstring.h"
#include "forte_ulint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_F_ULINT_AS_WSTRING, g_nStringIdF_ULINT_AS_WSTRING)

const CStringDictionary::TStringId FORTE_F_ULINT_AS_WSTRING::scmDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId FORTE_F_ULINT_AS_WSTRING::scmDataInputTypeIds[] = {g_nStringIdULINT};

const CStringDictionary::TStringId FORTE_F_ULINT_AS_WSTRING::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_F_ULINT_AS_WSTRING::scmDataOutputTypeIds[] = {g_nStringIdWSTRING};

const TDataIOID FORTE_F_ULINT_AS_WSTRING::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_ULINT_AS_WSTRING::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_ULINT_AS_WSTRING::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_F_ULINT_AS_WSTRING::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_F_ULINT_AS_WSTRING::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_ULINT_AS_WSTRING::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_ULINT_AS_WSTRING::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_F_ULINT_AS_WSTRING::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_F_ULINT_AS_WSTRING::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};


FORTE_F_ULINT_AS_WSTRING::FORTE_F_ULINT_AS_WSTRING(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_IN(CIEC_ULINT(0)),
    var_OUT(CIEC_WSTRING("")),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
}

void FORTE_F_ULINT_AS_WSTRING::alg_REQ(void) {
  
  var_OUT = func_ULINT_AS_WSTRING(var_IN);
}


void FORTE_F_ULINT_AS_WSTRING::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_F_ULINT_AS_WSTRING::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_ULINT_AS_WSTRING::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_ULINT_AS_WSTRING::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_ULINT_AS_WSTRING::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_F_ULINT_AS_WSTRING::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_ULINT_AS_WSTRING::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_F_ULINT_AS_WSTRING::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_ULINT_AS_WSTRING::getVarInternal(size_t) {
  return nullptr;
}


