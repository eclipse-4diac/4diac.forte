/*******************************************************************************
 * Copyright (c) 2006 - 2014 ACIN, Profactor GmbH, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer
 *    - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "RT_E_TRAIN_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RT_E_TRAIN_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_RT_E_TRAIN, g_nStringIdRT_E_TRAIN)

const CStringDictionary::TStringId FORTE_RT_E_TRAIN::scmDataInputNames[] = {g_nStringIdDT, g_nStringIdN, g_nStringIdDeadline, g_nStringIdWCET};
const CStringDictionary::TStringId FORTE_RT_E_TRAIN::scmDataInputTypeIds[] = {g_nStringIdTIME, g_nStringIdUINT, g_nStringIdTIME, g_nStringIdTIME};
const CStringDictionary::TStringId FORTE_RT_E_TRAIN::scmDataOutputNames[] = {g_nStringIdCV};
const CStringDictionary::TStringId FORTE_RT_E_TRAIN::scmDataOutputTypeIds[] = {g_nStringIdUINT};
const TDataIOID FORTE_RT_E_TRAIN::scmEIWith[] = {0, 1, 2, 3, scmWithListDelimiter};
const TForteInt16 FORTE_RT_E_TRAIN::scmEIWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_RT_E_TRAIN::scmEventInputNames[] = {g_nStringIdSTART, g_nStringIdSTOP};
const CStringDictionary::TStringId FORTE_RT_E_TRAIN::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const TDataIOID FORTE_RT_E_TRAIN::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_RT_E_TRAIN::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_RT_E_TRAIN::scmEventOutputNames[] = {g_nStringIdEO};
const CStringDictionary::TStringId FORTE_RT_E_TRAIN::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_RT_E_TRAIN::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  4, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_RT_E_TRAIN::FORTE_RT_E_TRAIN(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CCompositeFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, scmFBNData),
    fb_RT_E_CYCLE(g_nStringIdRT_E_CYCLE, *this),
    fb_E_CTU(g_nStringIdE_CTU, *this),
    fb_E_SWITCH(g_nStringIdE_SWITCH, *this),
    var_conn_CV(var_CV),
    conn_EO(this, 0),
    conn_DT(nullptr),
    conn_N(nullptr),
    conn_Deadline(nullptr),
    conn_WCET(nullptr),
    conn_CV(this, 0, &var_conn_CV) {
};

void FORTE_RT_E_TRAIN::setInitialValues() {
  var_DT = 0_TIME;
  var_N = 0_UINT;
  var_Deadline = 0_TIME;
  var_WCET = 0_TIME;
  var_CV = 0_UINT;
}

const SCFB_FBInstanceData FORTE_RT_E_TRAIN::scmInternalFBs[] = {
  {g_nStringIdRT_E_CYCLE, g_nStringIdRT_E_CYCLE},
  {g_nStringIdE_CTU, g_nStringIdE_CTU},
  {g_nStringIdE_SWITCH, g_nStringIdE_SWITCH}
};


const SCFB_FBConnectionData FORTE_RT_E_TRAIN::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRT_E_CYCLE, g_nStringIdEO), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdCU), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdSTART), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdR), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdSTOP), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRT_E_CYCLE, g_nStringIdSTOP), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdRO), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRT_E_CYCLE, g_nStringIdSTART), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdCUO), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdEI), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdEO0), 2, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdEO), -1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdEO1), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRT_E_CYCLE, g_nStringIdSTOP), 0},
};

const SCFB_FBConnectionData FORTE_RT_E_TRAIN::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDT), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRT_E_CYCLE, g_nStringIdDT), 0},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDeadline), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRT_E_CYCLE, g_nStringIdDeadline), 0},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdWCET), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRT_E_CYCLE, g_nStringIdWCET), 0},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdN), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdPV), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdCV), 1, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdCV), -1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdQ), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdG), 2},
};

const SCFB_FBNData FORTE_RT_E_TRAIN::scmFBNData = {
  3, scmInternalFBs,
  7, scmEventConnections,
  0, nullptr,
  6, scmDataConnections,
  0, nullptr,
  0, nullptr,
  0, nullptr
};


void FORTE_RT_E_TRAIN::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventSTARTID: {
      readData(0, var_DT, conn_DT);
      readData(1, var_N, conn_N);
      readData(2, var_Deadline, conn_Deadline);
      readData(3, var_WCET, conn_WCET);
      break;
    }
    case scmEventSTOPID: {
      break;
    }
    default:
      break;
  }
}

void FORTE_RT_E_TRAIN::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventEOID: {
      writeData(0, var_CV, conn_CV);
      break;
    }
    default:
      break;
  }
}

void FORTE_RT_E_TRAIN::readInternal2InterfaceOutputData(TEventID paEOID) {
  switch(paEOID) {
    case scmEventEOID: {
      if(CDataConnection *conn = getIn2IfConUnchecked(0); conn) { conn->readData(var_CV); }
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_RT_E_TRAIN::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_DT;
    case 1: return &var_N;
    case 2: return &var_Deadline;
    case 3: return &var_WCET;
  }
  return nullptr;
}

CIEC_ANY *FORTE_RT_E_TRAIN::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_CV;
  }
  return nullptr;
}

CEventConnection *FORTE_RT_E_TRAIN::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_EO;
  }
  return nullptr;
}

CDataConnection **FORTE_RT_E_TRAIN::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_DT;
    case 1: return &conn_N;
    case 2: return &conn_Deadline;
    case 3: return &conn_WCET;
  }
  return nullptr;
}

CDataConnection *FORTE_RT_E_TRAIN::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CV;
  }
  return nullptr;
}

