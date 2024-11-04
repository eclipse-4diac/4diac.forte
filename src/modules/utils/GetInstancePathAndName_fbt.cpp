/*******************************************************************************
 * Copyright (c) 2024 Primetals Technologies Austria GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Ernst Blecha - initial API and implementation and/or initial documentation
 *******************************************************************************/


#include "GetInstancePathAndName_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GetInstancePathAndName_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_char.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_GetInstancePathAndName, g_nStringIdGetInstancePathAndName)

const CStringDictionary::TStringId FORTE_GetInstancePathAndName::scmDataInputNames[] = {g_nStringIdSep};
const CStringDictionary::TStringId FORTE_GetInstancePathAndName::scmDataInputTypeIds[] = {g_nStringIdCHAR};
const CStringDictionary::TStringId FORTE_GetInstancePathAndName::scmDataOutputNames[] = {g_nStringIdPath, g_nStringIdName};
const CStringDictionary::TStringId FORTE_GetInstancePathAndName::scmDataOutputTypeIds[] = {g_nStringIdSTRING, g_nStringIdSTRING};
const TDataIOID FORTE_GetInstancePathAndName::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_GetInstancePathAndName::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_GetInstancePathAndName::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_GetInstancePathAndName::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_GetInstancePathAndName::scmEOWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_GetInstancePathAndName::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_GetInstancePathAndName::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_GetInstancePathAndName::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_GetInstancePathAndName::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_GetInstancePathAndName::FORTE_GetInstancePathAndName(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_Sep(0x2f_CHAR),
    var_conn_Path(var_Path),
    var_conn_Name(var_Name),
    conn_CNF(this, 0),
    conn_Sep(nullptr),
    conn_Path(this, 0, &var_conn_Path),
    conn_Name(this, 1, &var_conn_Name) {
}

void FORTE_GetInstancePathAndName::setInitialValues() {
  var_Sep = 0x2f_CHAR;
  var_Path = ""_STRING;
  var_Name = ""_STRING;
}

void FORTE_GetInstancePathAndName::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_GetInstancePathAndName::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_Sep, conn_Sep);
      break;
    }
    default:
      break;
  }
}

void FORTE_GetInstancePathAndName::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_Path, conn_Path);
      writeData(1, var_Name, conn_Name);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_GetInstancePathAndName::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Sep;
  }
  return nullptr;
}

CIEC_ANY *FORTE_GetInstancePathAndName::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_Path;
    case 1: return &var_Name;
  }
  return nullptr;
}

CEventConnection *FORTE_GetInstancePathAndName::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_GetInstancePathAndName::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Sep;
  }
  return nullptr;
}

CDataConnection *FORTE_GetInstancePathAndName::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_Path;
    case 1: return &conn_Name;
  }
  return nullptr;
}

CIEC_ANY *FORTE_GetInstancePathAndName::getVarInternal(size_t) {
  return nullptr;
}

void FORTE_GetInstancePathAndName::alg_REQ(void) {
  var_Path = CIEC_STRING(getParent().getFullQualifiedApplicationInstanceName(var_Sep.operator TForteChar()));
  var_Name = CIEC_STRING(getInstanceName(), strlen(getInstanceName()));
}

