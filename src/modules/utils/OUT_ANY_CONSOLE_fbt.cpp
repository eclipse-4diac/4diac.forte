/*******************************************************************************
 * Copyright (c) 2011 - 2014 AIT, ACIN, Profactor GmbH
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Thomas Strasser, Alois Zoitl, Matthias Plasch
 *   - initial API and implementation and/or initial documentation
 *   Martin Jobst
 *     - refactor for ANY variant
 *******************************************************************************/

#include "OUT_ANY_CONSOLE_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "OUT_ANY_CONSOLE_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_OUT_ANY_CONSOLE, g_nStringIdOUT_ANY_CONSOLE)

const CStringDictionary::TStringId FORTE_OUT_ANY_CONSOLE::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdLABEL, g_nStringIdIN};

const CStringDictionary::TStringId FORTE_OUT_ANY_CONSOLE::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdANY};

const CStringDictionary::TStringId FORTE_OUT_ANY_CONSOLE::scmDataOutputNames[] = {g_nStringIdQO};

const CStringDictionary::TStringId FORTE_OUT_ANY_CONSOLE::scmDataOutputTypeIds[] = {g_nStringIdBOOL};

const TDataIOID FORTE_OUT_ANY_CONSOLE::scmEIWith[] = {0, 2, 1, scmWithListDelimiter};
const TForteInt16 FORTE_OUT_ANY_CONSOLE::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_OUT_ANY_CONSOLE::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_OUT_ANY_CONSOLE::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_OUT_ANY_CONSOLE::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_OUT_ANY_CONSOLE::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_OUT_ANY_CONSOLE::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_OUT_ANY_CONSOLE::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_OUT_ANY_CONSOLE::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  3, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_OUT_ANY_CONSOLE::FORTE_OUT_ANY_CONSOLE(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(CIEC_BOOL(0)),
    var_LABEL(CIEC_STRING("", 0)),
    var_IN(CIEC_ANY_VARIANT()),
    var_QO(CIEC_BOOL(0)),
    var_conn_QO(var_QO),
    conn_CNF(this, 0),
    conn_QI(nullptr),
    conn_LABEL(nullptr),
    conn_IN(nullptr),
    conn_QO(this, 0, &var_conn_QO) {
};

void FORTE_OUT_ANY_CONSOLE::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      var_QO = var_QI;
      if (var_QI) {
        DEVLOG_INFO(" %s = ", var_LABEL.getStorage().c_str());
        size_t bufferSize = var_IN.getToStringBufferSize();
        std::string buffer(bufferSize, 0);
        var_IN.toString(buffer.data(), buffer.capacity());
        DEVLOG_INFO("%s\n", buffer.c_str());
      }
      sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

void FORTE_OUT_ANY_CONSOLE::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_QI, conn_QI);
      readData(2, var_IN, conn_IN);
      readData(1, var_LABEL, conn_LABEL);
      break;
    }
    default:
      break;
  }
}

void FORTE_OUT_ANY_CONSOLE::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_QO, conn_QO);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_OUT_ANY_CONSOLE::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_LABEL;
    case 2: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_OUT_ANY_CONSOLE::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
  }
  return nullptr;
}

CEventConnection *FORTE_OUT_ANY_CONSOLE::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_OUT_ANY_CONSOLE::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_LABEL;
    case 2: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_OUT_ANY_CONSOLE::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
  }
  return nullptr;
}


