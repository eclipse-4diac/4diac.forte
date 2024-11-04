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
 *** Name: F_SEL_E_3
 *** Description: selection event-based selection)
 *** Version:
 ***     1.0: 2012-03-25/Monika Wenger - TU Wien ACIN -
 ***     1.1: 2022-08-04/Franz Höpfinger - HR Agrartechnik GmbH -
 *************************************************************************/

#include "F_SEL_E_3_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_SEL_E_3_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_F_SEL_E_3, g_nStringIdF_SEL_E_3)

const CStringDictionary::TStringId FORTE_F_SEL_E_3::scmDataInputNames[] = {g_nStringIdIN0, g_nStringIdIN1, g_nStringIdIN2};
const CStringDictionary::TStringId FORTE_F_SEL_E_3::scmDataInputTypeIds[] = {g_nStringIdANY, g_nStringIdANY, g_nStringIdANY};
const CStringDictionary::TStringId FORTE_F_SEL_E_3::scmDataOutputNames[] = {g_nStringIdOUT};
const CStringDictionary::TStringId FORTE_F_SEL_E_3::scmDataOutputTypeIds[] = {g_nStringIdANY};
const TDataIOID FORTE_F_SEL_E_3::scmEIWith[] = {0, scmWithListDelimiter, 1, scmWithListDelimiter, 2, scmWithListDelimiter};
const TForteInt16 FORTE_F_SEL_E_3::scmEIWithIndexes[] = {0, 2, 4};
const CStringDictionary::TStringId FORTE_F_SEL_E_3::scmEventInputNames[] = {g_nStringIdREQ0, g_nStringIdREQ1, g_nStringIdREQ2};
const CStringDictionary::TStringId FORTE_F_SEL_E_3::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent};
const TDataIOID FORTE_F_SEL_E_3::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_SEL_E_3::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_SEL_E_3::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_F_SEL_E_3::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_F_SEL_E_3::scmFBInterfaceSpec = {
  3, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  3, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_F_SEL_E_3::FORTE_F_SEL_E_3(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN0(nullptr),
    conn_IN1(nullptr),
    conn_IN2(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
};

void FORTE_F_SEL_E_3::setInitialValues() {
  var_IN0 = CIEC_ANY_VARIANT();
  var_IN1 = CIEC_ANY_VARIANT();
  var_IN2 = CIEC_ANY_VARIANT();
  var_OUT = CIEC_ANY_VARIANT();
}

void FORTE_F_SEL_E_3::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQ0ID:
      var_OUT = var_IN0;
      sendOutputEvent(scmEventCNFID, paECET);
      break;
    case scmEventREQ1ID:
      var_OUT = var_IN1;
      sendOutputEvent(scmEventCNFID, paECET);
      break;
    case scmEventREQ2ID:
      var_OUT = var_IN2;
      sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

void FORTE_F_SEL_E_3::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQ0ID: {
      
      readData(0, var_IN0, conn_IN0);
      break;
    }
    case scmEventREQ1ID: {
      
      readData(1, var_IN1, conn_IN1);
      break;
    }
    case scmEventREQ2ID: {
      
      readData(2, var_IN2, conn_IN2);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_SEL_E_3::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_SEL_E_3::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN0;
    case 1: return &var_IN1;
    case 2: return &var_IN2;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_SEL_E_3::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_SEL_E_3::getDIO(size_t) {
  return nullptr;
}

CEventConnection *FORTE_F_SEL_E_3::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_SEL_E_3::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN0;
    case 1: return &conn_IN1;
    case 2: return &conn_IN2;
  }
  return nullptr;
}

CDataConnection *FORTE_F_SEL_E_3::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CInOutDataConnection **FORTE_F_SEL_E_3::getDIOInConUnchecked(TPortId) {
  return nullptr;
}

CInOutDataConnection *FORTE_F_SEL_E_3::getDIOOutConUnchecked(TPortId) {
  return nullptr;
}

