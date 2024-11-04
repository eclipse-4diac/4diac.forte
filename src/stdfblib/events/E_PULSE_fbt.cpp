/*************************************************************************
 *** Copyright (c) 2023, 2024 HR Agrartechnik GmbH  
 *** This program and the accompanying materials are made available under the  
 *** terms of the Eclipse Public License 2.0 which is available at  
 *** http://www.eclipse.org/legal/epl-2.0.  
 ***  
 *** SPDX-License-Identifier: EPL-2.0  
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: E_PULSE
 *** Description: standard timer function block (pulse)
 *** Version:
 ***     1.0: 2023-08-21/Franz Hoepfinger - HR Agrartechnik GmbH - initial implementation as E_IMPULSE
 ***     1.0: 2024-03-05/Franz Hoepfinger - HR Agrartechnik GmbH - renamed to E_PULSE
 ***     1.1: 2024-04-23/Franz Hoepfinger - HR Agrartechnik GmbH - Add a Reset to Timer FBs
 *************************************************************************/

#include "E_PULSE_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_PULSE_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_E_PULSE, g_nStringIdE_PULSE)

const CStringDictionary::TStringId FORTE_E_PULSE::scmDataInputNames[] = {g_nStringIdPT};
const CStringDictionary::TStringId FORTE_E_PULSE::scmDataInputTypeIds[] = {g_nStringIdTIME};
const CStringDictionary::TStringId FORTE_E_PULSE::scmDataOutputNames[] = {g_nStringIdQ};
const CStringDictionary::TStringId FORTE_E_PULSE::scmDataOutputTypeIds[] = {g_nStringIdBOOL};
const TDataIOID FORTE_E_PULSE::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_E_PULSE::scmEIWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_E_PULSE::scmEventInputNames[] = {g_nStringIdREQ, g_nStringIdR};
const CStringDictionary::TStringId FORTE_E_PULSE::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const TDataIOID FORTE_E_PULSE::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_E_PULSE::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_E_PULSE::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_E_PULSE::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_E_PULSE::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_E_PULSE::FORTE_E_PULSE(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CCompositeFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, scmFBNData),
    fb_E_DELAY(g_nStringIdE_DELAY, *this),
    fb_E_SR(g_nStringIdE_SR, *this),
    var_conn_Q(var_Q),
    conn_CNF(this, 0),
    conn_PT(nullptr),
    conn_Q(this, 0, &var_conn_Q) {
};

void FORTE_E_PULSE::setInitialValues() {
    var_PT = 0_TIME;
    var_Q = 0_BOOL;
}

const SCFB_FBInstanceData FORTE_E_PULSE::scmInternalFBs[] = {
  {g_nStringIdE_DELAY, g_nStringIdE_DELAY},
  {g_nStringIdE_SR, g_nStringIdE_SR}
};


const SCFB_FBConnectionData FORTE_E_PULSE::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdREQ), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY, g_nStringIdSTART), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY, g_nStringIdEO), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SR, g_nStringIdR), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SR, g_nStringIdEO), 1, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdCNF), -1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdR), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY, g_nStringIdSTOP), 0},
};

const SCFB_FBFannedOutConnectionData FORTE_E_PULSE::scmFannedOutEventConnections[] = {
  {0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SR, g_nStringIdS), 1},
  {3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SR, g_nStringIdR), 1},
};

const SCFB_FBConnectionData FORTE_E_PULSE::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdPT), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY, g_nStringIdDT), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SR, g_nStringIdQ), 1, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdQ), -1},
};

const SCFB_FBNData FORTE_E_PULSE::scmFBNData = {
  2, scmInternalFBs,
  4, scmEventConnections,
  2, scmFannedOutEventConnections,
  2, scmDataConnections,
  0, nullptr,
  0, nullptr,
  0, nullptr
};

void FORTE_E_PULSE::readInternal2InterfaceOutputData(const TEventID paEOID) {
  switch(paEOID) {
    case scmEventCNFID: {
      if(CDataConnection *conn = getIn2IfConUnchecked(0); conn) { conn->readData(var_Q); }
      break;
    }
    default:
      break;
  }
}
void FORTE_E_PULSE::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_PT, conn_PT);
      break;
    }
    default:
      break;
  }
}

void FORTE_E_PULSE::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_Q, conn_Q);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_E_PULSE::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_PT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_PULSE::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Q;
  }
  return nullptr;
}

CEventConnection *FORTE_E_PULSE::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_E_PULSE::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_PT;
  }
  return nullptr;
}

CDataConnection *FORTE_E_PULSE::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Q;
  }
  return nullptr;
}

