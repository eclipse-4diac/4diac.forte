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

#include "F_MUX_2_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_MUX_2_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_F_MUX_2, g_nStringIdF_MUX_2)

const CStringDictionary::TStringId FORTE_F_MUX_2::scmDataInputNames[] = {g_nStringIdK, g_nStringIdIN1, g_nStringIdIN2};

const CStringDictionary::TStringId FORTE_F_MUX_2::scmDataInputTypeIds[] = {g_nStringIdANY_INT, g_nStringIdANY, g_nStringIdANY};

const CStringDictionary::TStringId FORTE_F_MUX_2::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_F_MUX_2::scmDataOutputTypeIds[] = {g_nStringIdANY};

const TDataIOID FORTE_F_MUX_2::scmEIWith[] = {1, 2, 0, scmWithListDelimiter};
const TForteInt16 FORTE_F_MUX_2::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_MUX_2::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_F_MUX_2::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_F_MUX_2::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_MUX_2::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_MUX_2::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_F_MUX_2::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_F_MUX_2::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  3, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_F_MUX_2::FORTE_F_MUX_2(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_K(CIEC_ANY_INT_VARIANT()),
    var_IN1(CIEC_ANY_VARIANT()),
    var_IN2(CIEC_ANY_VARIANT()),
    var_OUT(CIEC_ANY_VARIANT()),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_K(nullptr),
    conn_IN1(nullptr),
    conn_IN2(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
};

void FORTE_F_MUX_2::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      var_OUT = std::visit([this](auto &&paK) -> CIEC_ANY_VARIANT {
        using T = std::decay_t<decltype(paK)>;
        typename T::TValueType valueK = static_cast<typename T::TValueType>(paK);
        switch(valueK) {
          case 0:
            return var_IN1;
          case 1:
            return var_IN2;
          default:
            break;
        }
        DEVLOG_ERROR("value of input K is not between 0 and 1\n");
        return CIEC_ANY_VARIANT();
      }, static_cast<CIEC_ANY_INT_VARIANT::variant&>(var_K));
      sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

void FORTE_F_MUX_2::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(1, var_IN1, conn_IN1);
      readData(2, var_IN2, conn_IN2);
      readData(0, var_K, conn_K);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_MUX_2::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_MUX_2::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_K;
    case 1: return &var_IN1;
    case 2: return &var_IN2;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_MUX_2::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_F_MUX_2::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_MUX_2::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_K;
    case 1: return &conn_IN1;
    case 2: return &conn_IN2;
  }
  return nullptr;
}

CDataConnection *FORTE_F_MUX_2::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}


