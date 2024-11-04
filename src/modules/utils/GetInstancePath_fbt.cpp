/*******************************************************************************
 * Copyright (c) 2023 Primetals Technologies Austria GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "GetInstancePath_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GetInstancePath_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_GetInstancePath, g_nStringIdGetInstancePath)

const CStringDictionary::TStringId FORTE_GetInstancePath::scmDataInputNames[] = {g_nStringIdSep};
const CStringDictionary::TStringId FORTE_GetInstancePath::scmDataInputTypeIds[] = {g_nStringIdCHAR};
const CStringDictionary::TStringId FORTE_GetInstancePath::scmDataOutputNames[] = {g_nStringIdPath};
const CStringDictionary::TStringId FORTE_GetInstancePath::scmDataOutputTypeIds[] = {g_nStringIdSTRING};
const TDataIOID FORTE_GetInstancePath::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_GetInstancePath::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_GetInstancePath::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_GetInstancePath::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_GetInstancePath::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_GetInstancePath::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_GetInstancePath::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_GetInstancePath::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_GetInstancePath::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_GetInstancePath::FORTE_GetInstancePath(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_Sep(0x2f_CHAR),
    var_conn_Path(var_Path),
    conn_CNF(this, 0),
    conn_Sep(nullptr),
    conn_Path(this, 0, &var_conn_Path) {
};

void FORTE_GetInstancePath::setInitialValues() {
  var_Sep = 0x2f_CHAR;
  var_Path = ""_STRING;
}

void FORTE_GetInstancePath::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  if(paEIID == scmEventREQID){
    var_Path = CIEC_STRING(getFullQualifiedApplicationInstanceName(var_Sep.operator TForteChar()));
    sendOutputEvent(scmEventCNFID, paECET);
  }
}

void FORTE_GetInstancePath::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_Sep, conn_Sep);
      break;
    }
    default:
      break;
  }
}

void FORTE_GetInstancePath::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_Path, conn_Path);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_GetInstancePath::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Sep;
  }
  return nullptr;
}

CIEC_ANY *FORTE_GetInstancePath::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Path;
  }
  return nullptr;
}

CEventConnection *FORTE_GetInstancePath::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_GetInstancePath::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Sep;
  }
  return nullptr;
}

CDataConnection *FORTE_GetInstancePath::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Path;
  }
  return nullptr;
}

