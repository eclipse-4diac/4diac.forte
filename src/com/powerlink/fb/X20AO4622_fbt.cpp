/*******************************************************************************
* Copyright (c) 2012 - 2024 AIT
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Filip Andren - initial API and implementation and/or initial documentation
 *   Michael Gafert - moved common functions to super class, changed to new FB style
 *******************************************************************************/

#include "X20AO4622_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "X20AO4622_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_X20AO4622, g_nStringIdX20AO4622)

const CStringDictionary::TStringId FORTE_X20AO4622::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdCNID, g_nStringIdMODID, g_nStringIdAO01, g_nStringIdAO02, g_nStringIdAO03, g_nStringIdAO04};
const CStringDictionary::TStringId FORTE_X20AO4622::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdUSINT, g_nStringIdUINT, g_nStringIdINT, g_nStringIdINT, g_nStringIdINT, g_nStringIdINT};
const CStringDictionary::TStringId FORTE_X20AO4622::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdCNIDO, g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_X20AO4622::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdUSINT, g_nStringIdSTRING};
const TDataIOID FORTE_X20AO4622::scmEIWith[] = {0, 1, 2, scmWithListDelimiter, 3, 4, 5, 6, 0, scmWithListDelimiter};
const TForteInt16 FORTE_X20AO4622::scmEIWithIndexes[] = {0, 4};
const CStringDictionary::TStringId FORTE_X20AO4622::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_X20AO4622::scmEventInputTypeIds[] = {g_nStringIdEInit, g_nStringIdEvent};
const TDataIOID FORTE_X20AO4622::scmEOWith[] = {0, 1, 2, scmWithListDelimiter, 2, 0, scmWithListDelimiter};
const TForteInt16 FORTE_X20AO4622::scmEOWithIndexes[] = {0, 4};
const CStringDictionary::TStringId FORTE_X20AO4622::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_X20AO4622::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const SFBInterfaceSpec FORTE_X20AO4622::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  7, scmDataInputNames, scmDataInputTypeIds,
  3, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_X20AO4622::FORTE_X20AO4622(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
  PowerlinkFunctionBlockAO(paContainer, scmFBInterfaceSpec, paInstanceNameId),
  var_conn_QO(var_QO),
  var_conn_CNIDO(var_CNIDO),
  var_conn_STATUS(var_STATUS),
  conn_INITO(this, 0),
  conn_CNF(this, 1),
  conn_QI(nullptr),
  conn_CNID(nullptr),
  conn_MODID(nullptr),
  conn_AO01(nullptr),
  conn_AO02(nullptr),
  conn_AO03(nullptr),
  conn_AO04(nullptr),
  conn_QO(this, 0, &var_conn_QO),
  conn_CNIDO(this, 1, &var_conn_CNIDO),
  conn_STATUS(this, 2, &var_conn_STATUS) {
};

void FORTE_X20AO4622::setInitialValues() {
  var_QI = 0_BOOL;
  var_CNID = 0_USINT;
  var_MODID = 0_UINT;
  var_AO01 = 0_INT;
  var_AO02 = 0_INT;
  var_AO03 = 0_INT;
  var_AO04 = 0_INT;
  var_QO = 0_BOOL;
  var_CNIDO = 0_USINT;
  var_STATUS = ""_STRING;
}

void FORTE_X20AO4622::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  executePowerlinkEvent(paEIID,
                        paECET,
                        scmEventINITID,
                        scmEventREQID,
                        scmEventINITOID,
                        scmEventCNFID,
                        var_QI,
                        var_QO,
                        var_CNID,
                        var_MODID);
}

void FORTE_X20AO4622::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_CNID, conn_CNID);
      readData(2, var_MODID, conn_MODID);
      break;
    }
    case scmEventREQID: {
      readData(3, var_AO01, conn_AO01);
      readData(4, var_AO02, conn_AO02);
      readData(5, var_AO03, conn_AO03);
      readData(6, var_AO04, conn_AO04);
      readData(0, var_QI, conn_QI);
      break;
    }
    default:
      break;
  }
}

void FORTE_X20AO4622::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_CNIDO, conn_CNIDO);
      writeData(2, var_STATUS, conn_STATUS);
      break;
    }
    case scmEventCNFID: {
      writeData(2, var_STATUS, conn_STATUS);
      writeData(0, var_QO, conn_QO);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_X20AO4622::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_CNID;
    case 2: return &var_MODID;
    case 3: return &var_AO01;
    case 4: return &var_AO02;
    case 5: return &var_AO03;
    case 6: return &var_AO04;
  }
  return nullptr;
}

CIEC_ANY *FORTE_X20AO4622::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_CNIDO;
    case 2: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_X20AO4622::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_X20AO4622::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_CNID;
    case 2: return &conn_MODID;
    case 3: return &conn_AO01;
    case 4: return &conn_AO02;
    case 5: return &conn_AO03;
    case 6: return &conn_AO04;
  }
  return nullptr;
}

CDataConnection *FORTE_X20AO4622::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_CNIDO;
    case 2: return &conn_STATUS;
  }
  return nullptr;
}

