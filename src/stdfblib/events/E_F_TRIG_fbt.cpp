/*******************************************************************************
 * Copyright (c) 2007 - 2013 ACIN, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Ingo Hegny
 *     - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "E_F_TRIG_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_F_TRIG_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_E_F_TRIG, g_nStringIdE_F_TRIG)

const CStringDictionary::TStringId FORTE_E_F_TRIG::scmDataInputNames[] = {g_nStringIdQI};
const CStringDictionary::TStringId FORTE_E_F_TRIG::scmDataInputTypeIds[] = {g_nStringIdBOOL};
const TDataIOID FORTE_E_F_TRIG::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_E_F_TRIG::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_E_F_TRIG::scmEventInputNames[] = {g_nStringIdEI};
const CStringDictionary::TStringId FORTE_E_F_TRIG::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TForteInt16 FORTE_E_F_TRIG::scmEOWithIndexes[] = {-1};
const CStringDictionary::TStringId FORTE_E_F_TRIG::scmEventOutputNames[] = {g_nStringIdEO};
const CStringDictionary::TStringId FORTE_E_F_TRIG::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_E_F_TRIG::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, nullptr, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

FORTE_E_F_TRIG::FORTE_E_F_TRIG(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CCompositeFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, scmFBNData),
    fb_E_D_FF(g_nStringIdE_D_FF, *this),
    fb_E_SWITCH(g_nStringIdE_SWITCH, *this),
    var_QI(CIEC_BOOL(0)),
    conn_EO(this, 0),
    conn_QI(nullptr) {
};

const SCFB_FBInstanceData FORTE_E_F_TRIG::scmInternalFBs[] = {
  {g_nStringIdE_D_FF, g_nStringIdE_D_FF},
  {g_nStringIdE_SWITCH, g_nStringIdE_SWITCH}
};


const SCFB_FBConnectionData FORTE_E_F_TRIG::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdEI), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_D_FF, g_nStringIdCLK), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_D_FF, g_nStringIdEO), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdEI), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdEO0), 1, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdEO), -1},
};

const SCFB_FBConnectionData FORTE_E_F_TRIG::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdQI), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_D_FF, g_nStringIdD), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_D_FF, g_nStringIdQ), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdG), 1},
};

const SCFB_FBNData FORTE_E_F_TRIG::scmFBNData = {
  2, scmInternalFBs,
  3, scmEventConnections,
  0, nullptr,
  2, scmDataConnections,
  0, nullptr,
  0, nullptr,
  0, nullptr
};


void FORTE_E_F_TRIG::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventEIID: {
      readData(0, var_QI, conn_QI);
      break;
    }
    default:
      break;
  }
}

void FORTE_E_F_TRIG::writeOutputData(TEventID) {
}

void FORTE_E_F_TRIG::readInternal2InterfaceOutputData(TEventID) {
}

CIEC_ANY *FORTE_E_F_TRIG::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_F_TRIG::getDO(size_t) {
  return nullptr;
}

CEventConnection *FORTE_E_F_TRIG::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_EO;
  }
  return nullptr;
}

CDataConnection **FORTE_E_F_TRIG::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
  }
  return nullptr;
}

CDataConnection *FORTE_E_F_TRIG::getDOConUnchecked(TPortId) {
  return nullptr;
}


