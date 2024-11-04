/************************************************************************* 
 *** Copyright (c) 2012, 2022 TU Wien ACIN, HR Agrartechnik GmbH 
 *** This program and the accompanying materials are made available under the 
 *** terms of the Eclipse Public License 2.0 which is available at 
 *** http://www.eclipse.org/legal/epl-2.0. 
 *** 
 *** SPDX-License-Identifier: EPL-2.0 
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: F_SEL_E_2
 *** Description: selection (event-based selection)
 *** Version:
 ***     1.0: 2012-03-25/Monika Wenger - TU Wien ACIN -
 ***     1.1: 2022-08-04/Franz Höpfinger - HR Agrartechnik GmbH -
 *************************************************************************/

#include "F_SEL_E_2_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_SEL_E_2_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_F_SEL_E_2, g_nStringIdF_SEL_E_2)

const CStringDictionary::TStringId FORTE_F_SEL_E_2::scmDataInputNames[] = {g_nStringIdIN0, g_nStringIdIN1};
const CStringDictionary::TStringId FORTE_F_SEL_E_2::scmDataInputTypeIds[] = {g_nStringIdANY, g_nStringIdANY};
const CStringDictionary::TStringId FORTE_F_SEL_E_2::scmDataOutputNames[] = {g_nStringIdOUT};
const CStringDictionary::TStringId FORTE_F_SEL_E_2::scmDataOutputTypeIds[] = {g_nStringIdANY};
const TDataIOID FORTE_F_SEL_E_2::scmEIWith[] = {0, scmWithListDelimiter, 1, scmWithListDelimiter};
const TForteInt16 FORTE_F_SEL_E_2::scmEIWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_F_SEL_E_2::scmEventInputNames[] = {g_nStringIdREQ0, g_nStringIdREQ1};
const CStringDictionary::TStringId FORTE_F_SEL_E_2::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const TDataIOID FORTE_F_SEL_E_2::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_SEL_E_2::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_SEL_E_2::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_F_SEL_E_2::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_F_SEL_E_2::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_F_SEL_E_2::FORTE_F_SEL_E_2(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN0(nullptr),
    conn_IN1(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
};

void FORTE_F_SEL_E_2::setInitialValues() {
  var_IN0 = CIEC_ANY_VARIANT();
  var_IN1 = CIEC_ANY_VARIANT();
  var_OUT = CIEC_ANY_VARIANT();
}

void FORTE_F_SEL_E_2::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQ0ID:
      var_OUT = var_IN0;
      sendOutputEvent(scmEventCNFID, paECET);
      break;
    case scmEventREQ1ID:
      var_OUT = var_IN1;
      sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

void FORTE_F_SEL_E_2::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQ0ID: {
      
      readData(0, var_IN0, conn_IN0);
      break;
    }
    case scmEventREQ1ID: {
      
      readData(1, var_IN1, conn_IN1);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_SEL_E_2::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_SEL_E_2::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN0;
    case 1: return &var_IN1;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_SEL_E_2::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_SEL_E_2::getDIO(size_t) {
  return nullptr;
}

CEventConnection *FORTE_F_SEL_E_2::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_SEL_E_2::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN0;
    case 1: return &conn_IN1;
  }
  return nullptr;
}

CDataConnection *FORTE_F_SEL_E_2::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CInOutDataConnection **FORTE_F_SEL_E_2::getDIOInConUnchecked(TPortId) {
  return nullptr;
}

CInOutDataConnection *FORTE_F_SEL_E_2::getDIOOutConUnchecked(TPortId) {
  return nullptr;
}

