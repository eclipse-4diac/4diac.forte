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

#include "FB_CTUD_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FB_CTUD_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_bool.h"
#include "forte_int.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_FB_CTUD, g_nStringIdFB_CTUD)

const CStringDictionary::TStringId FORTE_FB_CTUD::scmDataInputNames[] = {g_nStringIdCU, g_nStringIdCD, g_nStringIdR, g_nStringIdLD, g_nStringIdPV};

const CStringDictionary::TStringId FORTE_FB_CTUD::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdINT};

const CStringDictionary::TStringId FORTE_FB_CTUD::scmDataOutputNames[] = {g_nStringIdQU, g_nStringIdQD, g_nStringIdCV};

const CStringDictionary::TStringId FORTE_FB_CTUD::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdINT};

const TDataIOID FORTE_FB_CTUD::scmEIWith[] = {0, 1, 2, 3, 4, scmWithListDelimiter};
const TForteInt16 FORTE_FB_CTUD::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_FB_CTUD::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_FB_CTUD::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_FB_CTUD::scmEOWith[] = {0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_FB_CTUD::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_FB_CTUD::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_FB_CTUD::scmEventOutputTypeIds[] = {g_nStringIdEvent};


const SFBInterfaceSpec FORTE_FB_CTUD::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  5, scmDataInputNames, scmDataInputTypeIds,
  3, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};


FORTE_FB_CTUD::FORTE_FB_CTUD(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CSimpleFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_CU(CIEC_BOOL(0)),
    var_CD(CIEC_BOOL(0)),
    var_R(CIEC_BOOL(0)),
    var_LD(CIEC_BOOL(0)),
    var_PV(CIEC_INT(0)),
    var_QU(CIEC_BOOL(0)),
    var_QD(CIEC_BOOL(0)),
    var_CV(CIEC_INT(0)),
    var_conn_QU(var_QU),
    var_conn_QD(var_QD),
    var_conn_CV(var_CV),
    conn_CNF(this, 0),
    conn_CU(nullptr),
    conn_CD(nullptr),
    conn_R(nullptr),
    conn_LD(nullptr),
    conn_PV(nullptr),
    conn_QU(this, 0, &var_conn_QU),
    conn_QD(this, 1, &var_conn_QD),
    conn_CV(this, 2, &var_conn_CV) {
}

void FORTE_FB_CTUD::alg_REQ(void) {
  
  if (var_R) {
    var_CV = CIEC_INT(0);
  }
  else {
    if (var_LD) {
      var_CV = var_PV;
    }
    else {
      if (func_NOT<CIEC_BOOL>(func_AND<CIEC_BOOL>(var_CU, var_CD))) {
        if (func_AND<CIEC_BOOL>(var_CU, func_LT(var_CV, CIEC_INT(std::numeric_limits<CIEC_INT::TValueType>::max())))) {
          var_CV = func_ADD<CIEC_INT>(var_CV, CIEC_INT(1));
        }
        else if (func_AND<CIEC_BOOL>(var_CD, func_GT(var_CV, CIEC_INT(std::numeric_limits<CIEC_INT::TValueType>::min())))) {
          var_CV = func_SUB<CIEC_INT>(var_CV, CIEC_INT(1));
        }
      }
    }
  }
  var_QU = func_GE(var_CV, var_PV);
  var_QD = func_LE(var_CV, CIEC_INT(0));
}


void FORTE_FB_CTUD::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      alg_REQ();
      break;
    default:
      break;
  }
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FB_CTUD::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_CU, conn_CU);
      readData(1, var_CD, conn_CD);
      readData(2, var_R, conn_R);
      readData(3, var_LD, conn_LD);
      readData(4, var_PV, conn_PV);
      break;
    }
    default:
      break;
  }
}

void FORTE_FB_CTUD::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_QU, conn_QU);
      writeData(1, var_QD, conn_QD);
      writeData(2, var_CV, conn_CV);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_FB_CTUD::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_CU;
    case 1: return &var_CD;
    case 2: return &var_R;
    case 3: return &var_LD;
    case 4: return &var_PV;
  }
  return nullptr;
}

CIEC_ANY *FORTE_FB_CTUD::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QU;
    case 1: return &var_QD;
    case 2: return &var_CV;
  }
  return nullptr;
}

CEventConnection *FORTE_FB_CTUD::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_FB_CTUD::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CU;
    case 1: return &conn_CD;
    case 2: return &conn_R;
    case 3: return &conn_LD;
    case 4: return &conn_PV;
  }
  return nullptr;
}

CDataConnection *FORTE_FB_CTUD::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QU;
    case 1: return &conn_QD;
    case 2: return &conn_CV;
  }
  return nullptr;
}

CIEC_ANY *FORTE_FB_CTUD::getVarInternal(size_t) {
  return nullptr;
}


