/*************************************************************************
 *** Copyright (c) 2024 HR Agrartechnik GmbH  
 *** This program and the accompanying materials are made available under the  
 *** terms of the Eclipse Public License 2.0 which is available at  
 *** http://www.eclipse.org/legal/epl-2.0.  
 ***  
 *** SPDX-License-Identifier: EPL-2.0  
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: RangeBasedPulse
 *** Description: Distance based Impulse Generator
 *** Version:
 ***     1.0: 2024-10-18/Franz Höpfinger - HR Agrartechnik GmbH - initial Version
 ***     1.1: 2024-10-18/Franz Höpfinger - HR Agrartechnik GmbH - added Offset
 *************************************************************************/

#include "RangeBasedPulse_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RangeBasedPulse_fbt_gen.cpp"
#endif

#include "forte_bool.h"
#include "forte_udint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_signalprocessing__distance__RangeBasedPulse, g_nStringIdsignalprocessing__distance__RangeBasedPulse)

const CStringDictionary::TStringId FORTE_signalprocessing__distance__RangeBasedPulse::scmDataInputNames[] = {g_nStringIdDIST_IN, g_nStringIdDIST_OFF, g_nStringIdDIST_HIGH, g_nStringIdDIST_LOW};
const CStringDictionary::TStringId FORTE_signalprocessing__distance__RangeBasedPulse::scmDataInputTypeIds[] = {g_nStringIdUDINT, g_nStringIdUDINT, g_nStringIdUDINT, g_nStringIdUDINT};
const CStringDictionary::TStringId FORTE_signalprocessing__distance__RangeBasedPulse::scmDataOutputNames[] = {g_nStringIdQ};
const CStringDictionary::TStringId FORTE_signalprocessing__distance__RangeBasedPulse::scmDataOutputTypeIds[] = {g_nStringIdBOOL};
const TDataIOID FORTE_signalprocessing__distance__RangeBasedPulse::scmEIWith[] = {0, 1, 2, 3, scmWithListDelimiter};
const TForteInt16 FORTE_signalprocessing__distance__RangeBasedPulse::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_signalprocessing__distance__RangeBasedPulse::scmEventInputNames[] = {g_nStringIdREQ};
const TDataIOID FORTE_signalprocessing__distance__RangeBasedPulse::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_signalprocessing__distance__RangeBasedPulse::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_signalprocessing__distance__RangeBasedPulse::scmEventOutputNames[] = {g_nStringIdCNF};
const SFBInterfaceSpec FORTE_signalprocessing__distance__RangeBasedPulse::scmFBInterfaceSpec = {
  1, scmEventInputNames, nullptr, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, nullptr, scmEOWith, scmEOWithIndexes,
  4, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

const CStringDictionary::TStringId FORTE_signalprocessing__distance__RangeBasedPulse::scmInternalsNames[] = {g_nStringIdDIST_REMAINDER};
const CStringDictionary::TStringId FORTE_signalprocessing__distance__RangeBasedPulse::scmInternalsTypeIds[] = {g_nStringIdUDINT};
const SInternalVarsInformation FORTE_signalprocessing__distance__RangeBasedPulse::scmInternalVars = {1, scmInternalsNames, scmInternalsTypeIds};

FORTE_signalprocessing__distance__RangeBasedPulse::FORTE_signalprocessing__distance__RangeBasedPulse(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, &scmInternalVars),
    var_conn_Q(var_Q),
    conn_CNF(this, 0),
    conn_DIST_IN(nullptr),
    conn_DIST_OFF(nullptr),
    conn_DIST_HIGH(nullptr),
    conn_DIST_LOW(nullptr),
    conn_Q(this, 0, &var_conn_Q) {
}

void FORTE_signalprocessing__distance__RangeBasedPulse::setInitialValues() {
  var_DIST_REMAINDER = 0_UDINT;
  var_DIST_IN = 0_UDINT;
  var_DIST_OFF = 0_UDINT;
  var_DIST_HIGH = 0_UDINT;
  var_DIST_LOW = 0_UDINT;
  var_Q = 0_BOOL;
}

void FORTE_signalprocessing__distance__RangeBasedPulse::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      enterStateREQ(paECET);
      break;
    default:
      break;
  }
}

void FORTE_signalprocessing__distance__RangeBasedPulse::enterStateREQ(CEventChainExecutionThread *const paECET) {
  alg_REQ();
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_signalprocessing__distance__RangeBasedPulse::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_DIST_IN, conn_DIST_IN);
      readData(1, var_DIST_OFF, conn_DIST_OFF);
      readData(2, var_DIST_HIGH, conn_DIST_HIGH);
      readData(3, var_DIST_LOW, conn_DIST_LOW);
      break;
    }
    default:
      break;
  }
}

void FORTE_signalprocessing__distance__RangeBasedPulse::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_Q, conn_Q);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_signalprocessing__distance__RangeBasedPulse::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_DIST_IN;
    case 1: return &var_DIST_OFF;
    case 2: return &var_DIST_HIGH;
    case 3: return &var_DIST_LOW;
  }
  return nullptr;
}

CIEC_ANY *FORTE_signalprocessing__distance__RangeBasedPulse::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Q;
  }
  return nullptr;
}

CEventConnection *FORTE_signalprocessing__distance__RangeBasedPulse::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_signalprocessing__distance__RangeBasedPulse::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_DIST_IN;
    case 1: return &conn_DIST_OFF;
    case 2: return &conn_DIST_HIGH;
    case 3: return &conn_DIST_LOW;
  }
  return nullptr;
}

CDataConnection *FORTE_signalprocessing__distance__RangeBasedPulse::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Q;
  }
  return nullptr;
}

CIEC_ANY *FORTE_signalprocessing__distance__RangeBasedPulse::getVarInternal(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_DIST_REMAINDER;
  }
  return nullptr;
}

void FORTE_signalprocessing__distance__RangeBasedPulse::alg_REQ(void) {

  #line 3 "RangeBasedPulse.fbt"
  var_DIST_REMAINDER = func_MOD<CIEC_UDINT>(func_ADD<CIEC_UDINT>(var_DIST_IN, var_DIST_OFF), func_ADD<CIEC_UDINT>(var_DIST_HIGH, var_DIST_LOW));
  #line 5 "RangeBasedPulse.fbt"
  var_Q = func_GE(var_DIST_REMAINDER, var_DIST_HIGH);
}
