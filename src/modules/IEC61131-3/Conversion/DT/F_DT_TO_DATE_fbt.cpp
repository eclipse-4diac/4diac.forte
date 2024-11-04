/*******************************************************************************
 * Copyright (c) 2023 Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Martin Jobst
 *     - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "F_DT_TO_DATE_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "F_DT_TO_DATE_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_date.h"
#include "forte_date_and_time.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_F_DT_TO_DATE, g_nStringIdF_DT_TO_DATE)

const CStringDictionary::TStringId FORTE_F_DT_TO_DATE::scmDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId FORTE_F_DT_TO_DATE::scmDataInputTypeIds[] = {g_nStringIdDATE_AND_TIME};

const CStringDictionary::TStringId FORTE_F_DT_TO_DATE::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_F_DT_TO_DATE::scmDataOutputTypeIds[] = {g_nStringIdDATE};

const TDataIOID FORTE_F_DT_TO_DATE::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_DT_TO_DATE::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_DT_TO_DATE::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_F_DT_TO_DATE::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_F_DT_TO_DATE::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_F_DT_TO_DATE::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_F_DT_TO_DATE::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_F_DT_TO_DATE::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_F_DT_TO_DATE::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};


FORTE_F_DT_TO_DATE::FORTE_F_DT_TO_DATE(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_IN(CIEC_DATE_AND_TIME(0)),
    var_OUT(CIEC_DATE(0)),
    var_conn_OUT(var_OUT),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_OUT(this, 0, &var_conn_OUT) {
}

void FORTE_F_DT_TO_DATE::alg_REQ(void) {
  
  var_OUT = func_DT_TO_DATE(var_IN);
}


void FORTE_F_DT_TO_DATE::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_F_DT_TO_DATE::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_F_DT_TO_DATE::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_OUT, conn_OUT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_F_DT_TO_DATE::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_DT_TO_DATE::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_OUT;
  }
  return nullptr;
}

CEventConnection *FORTE_F_DT_TO_DATE::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_F_DT_TO_DATE::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_F_DT_TO_DATE::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_OUT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_F_DT_TO_DATE::getVarInternal(size_t) {
  return nullptr;
}


