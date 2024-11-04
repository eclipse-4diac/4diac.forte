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
 *** Name: E_TONOF
 *** Description: standard timer function block (on/off-delay timing)
 *** Version:
 ***     1.0: 2024-03-04/Franz Hoepfinger - HR Agrartechnik GmbH -
 ***     1.1: 2024-04-23/Franz Hoepfinger - HR Agrartechnik GmbH - Add a Reset to Timer FBs
 *************************************************************************/

#include "E_TONOF_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_TONOF_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_E_TONOF, g_nStringIdE_TONOF)

const CStringDictionary::TStringId FORTE_E_TONOF::scmDataInputNames[] = {g_nStringIdIN, g_nStringIdPT_ON, g_nStringIdPT_OFF};
const CStringDictionary::TStringId FORTE_E_TONOF::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdTIME, g_nStringIdTIME};
const CStringDictionary::TStringId FORTE_E_TONOF::scmDataOutputNames[] = {g_nStringIdQ};
const CStringDictionary::TStringId FORTE_E_TONOF::scmDataOutputTypeIds[] = {g_nStringIdBOOL};
const TDataIOID FORTE_E_TONOF::scmEIWith[] = {0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_E_TONOF::scmEIWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_E_TONOF::scmEventInputNames[] = {g_nStringIdREQ, g_nStringIdR};
const CStringDictionary::TStringId FORTE_E_TONOF::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const TDataIOID FORTE_E_TONOF::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_E_TONOF::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_E_TONOF::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_E_TONOF::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_E_TONOF::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  3, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_E_TONOF::FORTE_E_TONOF(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CCompositeFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, scmFBNData),
    fb_E_SWITCH(g_nStringIdE_SWITCH, *this),
    fb_E_DELAY_ON(g_nStringIdE_DELAY_ON, *this),
    fb_E_RS(g_nStringIdE_RS, *this),
    fb_E_DELAY_OFF(g_nStringIdE_DELAY_OFF, *this),
    var_conn_Q(var_Q),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_PT_ON(nullptr),
    conn_PT_OFF(nullptr),
    conn_Q(this, 0, &var_conn_Q) {
};

void FORTE_E_TONOF::setInitialValues() {
    var_IN = 0_BOOL;
    var_PT_ON = 0_TIME;
    var_PT_OFF = 0_TIME;
    var_Q = 0_BOOL;
}

const SCFB_FBInstanceData FORTE_E_TONOF::scmInternalFBs[] = {
  {g_nStringIdE_SWITCH, g_nStringIdE_SWITCH},
  {g_nStringIdE_DELAY_ON, g_nStringIdE_DELAY},
  {g_nStringIdE_RS, g_nStringIdE_RS},
  {g_nStringIdE_DELAY_OFF, g_nStringIdE_DELAY}
};


const SCFB_FBConnectionData FORTE_E_TONOF::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdREQ), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdEI), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdEO1), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY_ON, g_nStringIdSTART), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdEO0), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY_ON, g_nStringIdSTOP), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY_ON, g_nStringIdEO), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_RS, g_nStringIdS), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_RS, g_nStringIdEO), 2, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdCNF), -1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY_OFF, g_nStringIdEO), 3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_RS, g_nStringIdR), 2},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdR), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_RS, g_nStringIdR), 2},
};

const SCFB_FBFannedOutConnectionData FORTE_E_TONOF::scmFannedOutEventConnections[] = {
  {1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY_OFF, g_nStringIdSTOP), 3},
  {2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY_OFF, g_nStringIdSTART), 3},
  {6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY_OFF, g_nStringIdSTOP), 3},
};

const SCFB_FBConnectionData FORTE_E_TONOF::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdIN), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdG), 0},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdPT_ON), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY_ON, g_nStringIdDT), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_RS, g_nStringIdQ), 2, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdQ), -1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdPT_OFF), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY_OFF, g_nStringIdDT), 3},
};

const SCFB_FBNData FORTE_E_TONOF::scmFBNData = {
  4, scmInternalFBs,
  7, scmEventConnections,
  3, scmFannedOutEventConnections,
  4, scmDataConnections,
  0, nullptr,
  0, nullptr,
  0, nullptr
};

void FORTE_E_TONOF::readInternal2InterfaceOutputData(const TEventID paEOID) {
  switch(paEOID) {
    case scmEventCNFID: {
      if(CDataConnection *conn = getIn2IfConUnchecked(0); conn) { conn->readData(var_Q); }
      break;
    }
    default:
      break;
  }
}
void FORTE_E_TONOF::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      readData(1, var_PT_ON, conn_PT_ON);
      readData(2, var_PT_OFF, conn_PT_OFF);
      break;
    }
    default:
      break;
  }
}

void FORTE_E_TONOF::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_Q, conn_Q);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_E_TONOF::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
    case 1: return &var_PT_ON;
    case 2: return &var_PT_OFF;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_TONOF::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Q;
  }
  return nullptr;
}

CEventConnection *FORTE_E_TONOF::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_E_TONOF::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
    case 1: return &conn_PT_ON;
    case 2: return &conn_PT_OFF;
  }
  return nullptr;
}

CDataConnection *FORTE_E_TONOF::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Q;
  }
  return nullptr;
}

