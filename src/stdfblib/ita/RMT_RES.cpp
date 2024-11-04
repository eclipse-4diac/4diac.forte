/*******************************************************************************
 * Copyright (c) 2005 - 2015 ACIN, Profactor GmbH, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer, Rene Smodic, Thomas Strasser,
 *   Martin Melik Merkumians, Ingo Hegny
 *    - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include "RMT_RES.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RMT_RES_gen.cpp"
#endif

#include "../../core/ecet.h"

DEFINE_FIRMWARE_FB(RMT_RES, g_nStringIdRMT_RES);

const CStringDictionary::TStringId RMT_RES::scmVarInputNameIds[] = {g_nStringIdMGR_ID};
const CStringDictionary::TStringId RMT_RES::scmDIDataTypeIds[] = {g_nStringIdWSTRING};


const SFBInterfaceSpec RMT_RES::scmFBInterfaceSpec = {
  0, nullptr, nullptr, nullptr, nullptr,
  0, nullptr, nullptr, nullptr, nullptr,
  1, scmVarInputNameIds, scmDIDataTypeIds,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};


RMT_RES::RMT_RES(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paDevice):
       CResource(paDevice, scmFBInterfaceSpec, paInstanceNameId),
       var_MGR_ID(""),
       conn_MGR_ID(nullptr),
       fb_START(g_nStringIdSTART, *this),
       fb_MGR_FF(g_nStringIdMGR_FF, *this),
       fb_MGR(g_nStringIdMGR, *this) {
}

bool RMT_RES::initialize() {
  if(!CResource::initialize()) {
    return false;
  }

  forte::core::SManagementCMD command;

  command.mFirstParam.pushBack(g_nStringIdSTART);
  command.mFirstParam.pushBack(g_nStringIdCOLD);
  command.mSecondParam.pushBack(g_nStringIdMGR_FF);
  command.mSecondParam.pushBack(g_nStringIdS);
  createConnection(command);

  command.mFirstParam.clear();
  command.mFirstParam.pushBack(g_nStringIdSTART);
  command.mFirstParam.pushBack(g_nStringIdWARM);
  command.mSecondParam.clear();
  command.mSecondParam.pushBack(g_nStringIdMGR_FF);
  command.mSecondParam.pushBack(g_nStringIdS);
  createConnection(command);

  command.mFirstParam.clear();
  command.mFirstParam.pushBack(g_nStringIdSTART);
  command.mFirstParam.pushBack(g_nStringIdSTOP);
  command.mSecondParam.clear();
  command.mSecondParam.pushBack(g_nStringIdMGR_FF);
  command.mSecondParam.pushBack(g_nStringIdR);
  createConnection(command);

  command.mFirstParam.clear();
  command.mFirstParam.pushBack(g_nStringIdMGR_FF);
  command.mFirstParam.pushBack(g_nStringIdEO);
  command.mSecondParam.clear();
  command.mSecondParam.pushBack(g_nStringIdMGR);
  command.mSecondParam.pushBack(g_nStringIdINIT);
  createConnection(command);

  command.mFirstParam.clear();
  command.mFirstParam.pushBack(g_nStringIdMGR_FF);
  command.mFirstParam.pushBack(g_nStringIdQ);
  command.mSecondParam.clear();
  command.mSecondParam.pushBack(g_nStringIdMGR);
  command.mSecondParam.pushBack(g_nStringIdQI);
  createConnection(command);

  command.mFirstParam.clear();
  command.mFirstParam.pushBack(g_nStringIdMGR_ID);
  command.mSecondParam.clear();
  command.mSecondParam.pushBack(g_nStringIdMGR);
  command.mSecondParam.pushBack(g_nStringIdID);
  createConnection(command);
  return true;
}

RMT_RES::~RMT_RES() = default;

void RMT_RES::joinResourceThread() const {
  getResourceEventExecution()->joinEventChainExecutionThread();
}

CIEC_ANY *RMT_RES::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_MGR_ID;
  }
  return nullptr;
}

CDataConnection **RMT_RES::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_MGR_ID;
  }
  return nullptr;
}

