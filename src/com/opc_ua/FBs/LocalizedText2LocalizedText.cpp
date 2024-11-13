/*******************************************************************************
 * Copyright (c) 2019 fortiss GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral - initial implementation
 *******************************************************************************/

#include "LocalizedText2LocalizedText.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "LocalizedText2LocalizedText_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_LocalizedText2LocalizedText, g_nStringIdLocalizedText2LocalizedText)

const CStringDictionary::TStringId FORTE_LocalizedText2LocalizedText::scmDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId FORTE_LocalizedText2LocalizedText::scmDataInputTypeIds[] = {g_nStringIdLocalizedText};

const CStringDictionary::TStringId FORTE_LocalizedText2LocalizedText::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_LocalizedText2LocalizedText::scmDataOutputTypeIds[] = {g_nStringIdLocalizedText};

const TForteInt16 FORTE_LocalizedText2LocalizedText::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_LocalizedText2LocalizedText::scmEIWith[] = {0, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_LocalizedText2LocalizedText::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_LocalizedText2LocalizedText::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_LocalizedText2LocalizedText::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_LocalizedText2LocalizedText::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_LocalizedText2LocalizedText::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_LocalizedText2LocalizedText::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_LocalizedText2LocalizedText::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  1,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr, 0, nullptr
};

FORTE_LocalizedText2LocalizedText::FORTE_LocalizedText2LocalizedText(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_IN(CIEC_LocalizedText()),
    var_OUT(CIEC_LocalizedText()),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
}

void FORTE_LocalizedText2LocalizedText::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  if(scmEventREQID == paEIID) {
    var_OUT = var_IN;
    sendOutputEvent(scmEventCNFID, paECET);
  }
}

void FORTE_LocalizedText2LocalizedText::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_LocalizedText2LocalizedText::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_LocalizedText2LocalizedText::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_LocalizedText2LocalizedText::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_LocalizedText2LocalizedText::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_LocalizedText2LocalizedText::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_LocalizedText2LocalizedText::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

