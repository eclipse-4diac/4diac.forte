/*******************************************************************************
 * Copyright (c) 2011 - 2013 ACIN, fortiss GmbH
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

#include "F_SEL_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_SEL_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_F_SEL, g_nStringIdF_SEL)

const CStringDictionary::TStringId FORTE_F_SEL::scmDataInputNames[] = {g_nStringIdG, g_nStringIdIN0, g_nStringIdIN1};

const CStringDictionary::TStringId FORTE_F_SEL::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdANY, g_nStringIdANY};

const CStringDictionary::TStringId FORTE_F_SEL::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_F_SEL::scmDataOutputTypeIds[] = {g_nStringIdANY};

const TDataIOID FORTE_F_SEL::scmEIWith[] = {0, 2, 1, scmWithListDelimiter};
const TForteInt16 FORTE_F_SEL::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_SEL::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_F_SEL::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_F_SEL::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_SEL::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_SEL::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_F_SEL::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_F_SEL::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  3, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_F_SEL::FORTE_F_SEL(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_G(CIEC_BOOL(0)),
    var_IN0(CIEC_ANY_VARIANT()),
    var_IN1(CIEC_ANY_VARIANT()),
    var_OUT(CIEC_ANY_VARIANT()),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_G(nullptr),
    conn_IN0(nullptr),
    conn_IN1(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
};

void FORTE_F_SEL::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      var_OUT = var_G ? var_IN1 : var_IN0;
      sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

void FORTE_F_SEL::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_G, conn_G);
      readData(2, var_IN1, conn_IN1);
      readData(1, var_IN0, conn_IN0);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_SEL::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_SEL::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_G;
    case 1: return &var_IN0;
    case 2: return &var_IN1;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_SEL::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_F_SEL::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_SEL::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_G;
    case 1: return &conn_IN0;
    case 2: return &conn_IN1;
  }
  return nullptr;
}

CDataConnection *FORTE_F_SEL::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}


