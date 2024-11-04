/*******************************************************************************
 * Copyright (c) 2013 ACIN
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger
 *   - initial API and implementation and/or initial documentation
 *   Martin Jobst
 *     - refactor for ANY variant
 *******************************************************************************/

#include "F_DELETE_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_DELETE_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_F_DELETE, g_nStringIdF_DELETE)

const CStringDictionary::TStringId FORTE_F_DELETE::scmDataInputNames[] = {g_nStringIdIN, g_nStringIdL, g_nStringIdP};

const CStringDictionary::TStringId FORTE_F_DELETE::scmDataInputTypeIds[] = {g_nStringIdANY_STRING, g_nStringIdANY_INT, g_nStringIdANY_INT};

const CStringDictionary::TStringId FORTE_F_DELETE::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_F_DELETE::scmDataOutputTypeIds[] = {g_nStringIdANY_STRING};

const TDataIOID FORTE_F_DELETE::scmEIWith[] = {0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_F_DELETE::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_DELETE::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_F_DELETE::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_F_DELETE::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_DELETE::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_DELETE::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_F_DELETE::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_F_DELETE::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  3, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_F_DELETE::FORTE_F_DELETE(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_IN(CIEC_ANY_STRING_VARIANT()),
    var_L(CIEC_ANY_INT_VARIANT()),
    var_P(CIEC_ANY_INT_VARIANT()),
    var_OUT(CIEC_ANY_STRING_VARIANT()),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_L(nullptr),
    conn_P(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
};

void FORTE_F_DELETE::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      var_OUT = std::visit([](auto &&paIN, auto&&paL, auto&&paP) -> CIEC_ANY_STRING_VARIANT {
          return func_DELETE(paIN, paL, paP);
      }, static_cast<CIEC_ANY_STRING_VARIANT::variant&>(var_IN),
         static_cast<CIEC_ANY_INT_VARIANT::variant&>(var_L),
         static_cast<CIEC_ANY_INT_VARIANT::variant&>(var_P));
      sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

void FORTE_F_DELETE::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      readData(1, var_L, conn_L);
      readData(2, var_P, conn_P);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_DELETE::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_DELETE::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
    case 1: return &var_L;
    case 2: return &var_P;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_DELETE::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_F_DELETE::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_DELETE::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
    case 1: return &conn_L;
    case 2: return &conn_P;
  }
  return nullptr;
}

CDataConnection *FORTE_F_DELETE::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}


