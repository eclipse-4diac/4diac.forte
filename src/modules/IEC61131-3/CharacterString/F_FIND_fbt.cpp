/*******************************************************************************
 * Copyright (c) 2013, 2018 ACIN, fortiss GmbH
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger, Alois Zoitl
 *   - initial API and implementation and/or initial documentation
 *   Martin Jobst
 *     - refactor for ANY variant
 *******************************************************************************/

#include "F_FIND_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_FIND_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_F_FIND, g_nStringIdF_FIND)

const CStringDictionary::TStringId FORTE_F_FIND::scmDataInputNames[] = {g_nStringIdIN1, g_nStringIdIN2};

const CStringDictionary::TStringId FORTE_F_FIND::scmDataInputTypeIds[] = {g_nStringIdANY_STRING, g_nStringIdANY_STRING};

const CStringDictionary::TStringId FORTE_F_FIND::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_F_FIND::scmDataOutputTypeIds[] = {g_nStringIdANY_INT};

const TDataIOID FORTE_F_FIND::scmEIWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_F_FIND::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_FIND::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_F_FIND::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_F_FIND::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_FIND::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_FIND::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_F_FIND::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_F_FIND::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_F_FIND::FORTE_F_FIND(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_IN1(CIEC_ANY_STRING_VARIANT()),
    var_IN2(CIEC_ANY_STRING_VARIANT()),
    var_OUT(CIEC_ANY_INT_VARIANT()),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN1(nullptr),
    conn_IN2(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
};

void FORTE_F_FIND::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      std::visit([](auto &&paIN1, auto&&paIN2, auto&&paOUT) -> void {
        using T = std::decay_t<decltype(paIN1)>;
        using U = std::decay_t<decltype(paIN2)>;
        if constexpr ((std::is_same_v<T, CIEC_STRING> && (std::is_same_v<U, CIEC_STRING> || std::is_same_v<U, CIEC_CHAR>)) || (std::is_same_v<T, CIEC_WSTRING> && (std::is_same_v<U, CIEC_WSTRING> || std::is_same_v<U, CIEC_WCHAR>))) {
          paOUT = func_FIND<std::remove_reference_t<decltype(paOUT)>>(paIN1, paIN2);
        } else {
          DEVLOG_ERROR("Incompatible types IN1:%s and IN2:%s for FIND\n",
                     CStringDictionary::getInstance().get(paIN1.getTypeNameID()),
                     CStringDictionary::getInstance().get(paIN2.getTypeNameID()));
        }
      }, static_cast<CIEC_ANY_STRING_VARIANT::variant&>(var_IN1),
         static_cast<CIEC_ANY_STRING_VARIANT::variant&>(var_IN2),
         static_cast<CIEC_ANY_INT_VARIANT::variant&>(var_OUT));
      sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

void FORTE_F_FIND::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN1, conn_IN1);
      readData(1, var_IN2, conn_IN2);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_FIND::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_FIND::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN1;
    case 1: return &var_IN2;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_FIND::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_F_FIND::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_FIND::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN1;
    case 1: return &conn_IN2;
  }
  return nullptr;
}

CDataConnection *FORTE_F_FIND::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}


