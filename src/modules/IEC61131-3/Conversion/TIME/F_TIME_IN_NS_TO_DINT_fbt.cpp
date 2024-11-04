/*************************************************************************   
 *** Copyright (c) 2023 Martin Jobst, HR Agrartechnik GmbH   
 *** This program and the accompanying materials are made available under the   
 *** terms of the Eclipse Public License 2.0 which is available at   
 *** http://www.eclipse.org/legal/epl-2.0.   
 ***   
 *** SPDX-License-Identifier: EPL-2.0   
 ***  
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG! 
 ***
 *** Name: F_TIME_IN_NS_TO_DINT
 *** Description: Convert TIME in NS to UDINT
 *** Version:
 ***     1.0: 2023-04-28/Martin Jobst -  -
 ***     1.1: 2023-08-21/Franz Höpfinger - HR Agrartechnik GmbH -
 *************************************************************************/

#include "F_TIME_IN_NS_TO_DINT_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_TIME_IN_NS_TO_DINT_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_dint.h"
#include "forte_lint.h"
#include "forte_any_duration_variant.h"
#include "forte_time.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_F_TIME_IN_NS_TO_DINT, g_nStringIdF_TIME_IN_NS_TO_DINT)

const CStringDictionary::TStringId FORTE_F_TIME_IN_NS_TO_DINT::scmDataInputNames[] = {g_nStringIdIN};
const CStringDictionary::TStringId FORTE_F_TIME_IN_NS_TO_DINT::scmDataInputTypeIds[] = {g_nStringIdTIME};
const CStringDictionary::TStringId FORTE_F_TIME_IN_NS_TO_DINT::scmDataOutputNames[] = {g_nStringIdOUT};
const CStringDictionary::TStringId FORTE_F_TIME_IN_NS_TO_DINT::scmDataOutputTypeIds[] = {g_nStringIdDINT};
const TDataIOID FORTE_F_TIME_IN_NS_TO_DINT::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_TIME_IN_NS_TO_DINT::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_TIME_IN_NS_TO_DINT::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_F_TIME_IN_NS_TO_DINT::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_F_TIME_IN_NS_TO_DINT::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_TIME_IN_NS_TO_DINT::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_TIME_IN_NS_TO_DINT::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_F_TIME_IN_NS_TO_DINT::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_F_TIME_IN_NS_TO_DINT::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_F_TIME_IN_NS_TO_DINT::FORTE_F_TIME_IN_NS_TO_DINT(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
}

void FORTE_F_TIME_IN_NS_TO_DINT::setInitialValues() {
  var_IN = 0_TIME;
  var_OUT = 0_DINT;
}

void FORTE_F_TIME_IN_NS_TO_DINT::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_F_TIME_IN_NS_TO_DINT::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_TIME_IN_NS_TO_DINT::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_TIME_IN_NS_TO_DINT::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_TIME_IN_NS_TO_DINT::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_TIME_IN_NS_TO_DINT::getDIO(size_t) {
  return nullptr;
}

CEventConnection *FORTE_F_TIME_IN_NS_TO_DINT::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_TIME_IN_NS_TO_DINT::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_F_TIME_IN_NS_TO_DINT::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CInOutDataConnection **FORTE_F_TIME_IN_NS_TO_DINT::getDIOInConUnchecked(TPortId) {
  return nullptr;
}

CInOutDataConnection *FORTE_F_TIME_IN_NS_TO_DINT::getDIOOutConUnchecked(TPortId) {
  return nullptr;
}

CIEC_ANY *FORTE_F_TIME_IN_NS_TO_DINT::getVarInternal(size_t) {
  return nullptr;
}

void FORTE_F_TIME_IN_NS_TO_DINT::alg_REQ(void) {

  var_OUT = func_TIME_IN_NS_TO_DINT(var_IN);
}

