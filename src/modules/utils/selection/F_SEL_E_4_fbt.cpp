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
 *** Name: F_SEL_E_4
 *** Description: selection event-based selection)
 *** Version:
 ***     1.0: 2012-03-25/Monika Wenger - TU Wien ACIN -
 ***     1.1: 2022-08-04/Franz Höpfinger - HR Agrartechnik GmbH -
 *************************************************************************/

#include "F_SEL_E_4_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_SEL_E_4_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_F_SEL_E_4, g_nStringIdF_SEL_E_4)

const CStringDictionary::TStringId FORTE_F_SEL_E_4::scmDataInputNames[] = {g_nStringIdIN0, g_nStringIdIN1, g_nStringIdIN2, g_nStringIdIN3};
const CStringDictionary::TStringId FORTE_F_SEL_E_4::scmDataInputTypeIds[] = {g_nStringIdANY, g_nStringIdANY, g_nStringIdANY, g_nStringIdANY};
const CStringDictionary::TStringId FORTE_F_SEL_E_4::scmDataOutputNames[] = {g_nStringIdOUT};
const CStringDictionary::TStringId FORTE_F_SEL_E_4::scmDataOutputTypeIds[] = {g_nStringIdANY};
const TDataIOID FORTE_F_SEL_E_4::scmEIWith[] = {0, scmWithListDelimiter, 1, scmWithListDelimiter, 2, scmWithListDelimiter, 3, scmWithListDelimiter};
const TForteInt16 FORTE_F_SEL_E_4::scmEIWithIndexes[] = {0, 2, 4, 6};
const CStringDictionary::TStringId FORTE_F_SEL_E_4::scmEventInputNames[] = {g_nStringIdREQ0, g_nStringIdREQ1, g_nStringIdREQ2, g_nStringIdREQ3};
const CStringDictionary::TStringId FORTE_F_SEL_E_4::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent};
const TDataIOID FORTE_F_SEL_E_4::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_SEL_E_4::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_SEL_E_4::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_F_SEL_E_4::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_F_SEL_E_4::scmFBInterfaceSpec = {
  4, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  4, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_F_SEL_E_4::FORTE_F_SEL_E_4(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN0(nullptr),
    conn_IN1(nullptr),
    conn_IN2(nullptr),
    conn_IN3(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
};

void FORTE_F_SEL_E_4::setInitialValues() {
  var_IN0 = CIEC_ANY_VARIANT();
  var_IN1 = CIEC_ANY_VARIANT();
  var_IN2 = CIEC_ANY_VARIANT();
  var_IN3 = CIEC_ANY_VARIANT();
  var_OUT = CIEC_ANY_VARIANT();
}

void FORTE_F_SEL_E_4::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
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
    case scmEventREQ3ID:
      var_OUT = var_IN3;
      sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

void FORTE_F_SEL_E_4::readInputData(const TEventID paEIID) {
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
    case scmEventREQ3ID: {
      
      readData(3, var_IN3, conn_IN3);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_SEL_E_4::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_SEL_E_4::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN0;
    case 1: return &var_IN1;
    case 2: return &var_IN2;
    case 3: return &var_IN3;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_SEL_E_4::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_SEL_E_4::getDIO(size_t) {
  return nullptr;
}

CEventConnection *FORTE_F_SEL_E_4::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_SEL_E_4::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN0;
    case 1: return &conn_IN1;
    case 2: return &conn_IN2;
    case 3: return &conn_IN3;
  }
  return nullptr;
}

CDataConnection *FORTE_F_SEL_E_4::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CInOutDataConnection **FORTE_F_SEL_E_4::getDIOInConUnchecked(TPortId) {
  return nullptr;
}

CInOutDataConnection *FORTE_F_SEL_E_4::getDIOOutConUnchecked(TPortId) {
  return nullptr;
}

