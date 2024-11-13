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

#include "X20DI4653_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "X20DI4653_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_X20DI4653, g_nStringIdX20DI4653)

const CStringDictionary::TStringId FORTE_X20DI4653::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdCNID, g_nStringIdMODID};
const CStringDictionary::TStringId FORTE_X20DI4653::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdUSINT, g_nStringIdUINT};
const CStringDictionary::TStringId FORTE_X20DI4653::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdCNIDO, g_nStringIdSTATUS, g_nStringIdDI01, g_nStringIdDI02, g_nStringIdDI03, g_nStringIdDI04};
const CStringDictionary::TStringId FORTE_X20DI4653::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdUSINT, g_nStringIdSTRING, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL};
const TDataIOID FORTE_X20DI4653::scmEIWith[] = {0, 1, 2, scmWithListDelimiter, 0, scmWithListDelimiter};
const TForteInt16 FORTE_X20DI4653::scmEIWithIndexes[] = {0, 4};
const CStringDictionary::TStringId FORTE_X20DI4653::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_X20DI4653::scmEventInputTypeIds[] = {g_nStringIdEInit, g_nStringIdEvent};
const TDataIOID FORTE_X20DI4653::scmEOWith[] = {0, 2, 1, scmWithListDelimiter, 3, 4, 5, 6, 2, 0, scmWithListDelimiter};
const TForteInt16 FORTE_X20DI4653::scmEOWithIndexes[] = {0, 4};
const CStringDictionary::TStringId FORTE_X20DI4653::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_X20DI4653::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const SFBInterfaceSpec FORTE_X20DI4653::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  3, scmDataInputNames, scmDataInputTypeIds,
  7, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_X20DI4653::FORTE_X20DI4653(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
  PowerlinkFunctionBlockDI(paContainer, scmFBInterfaceSpec, paInstanceNameId),
  var_conn_QO(var_QO),
  var_conn_CNIDO(var_CNIDO),
  var_conn_STATUS(var_STATUS),
  var_conn_DI01(var_DI01),
  var_conn_DI02(var_DI02),
  var_conn_DI03(var_DI03),
  var_conn_DI04(var_DI04),
  conn_INITO(this, 0),
  conn_CNF(this, 1),
  conn_QI(nullptr),
  conn_CNID(nullptr),
  conn_MODID(nullptr),
  conn_QO(this, 0, &var_conn_QO),
  conn_CNIDO(this, 1, &var_conn_CNIDO),
  conn_STATUS(this, 2, &var_conn_STATUS),
  conn_DI01(this, 3, &var_conn_DI01),
  conn_DI02(this, 4, &var_conn_DI02),
  conn_DI03(this, 5, &var_conn_DI03),
  conn_DI04(this, 6, &var_conn_DI04) {
};

void FORTE_X20DI4653::setInitialValues() {
  var_QI = 0_BOOL;
  var_CNID = 0_USINT;
  var_MODID = 0_UINT;
  var_QO = 0_BOOL;
  var_CNIDO = 0_USINT;
  var_STATUS = ""_STRING;
  var_DI01 = 0_BOOL;
  var_DI02 = 0_BOOL;
  var_DI03 = 0_BOOL;
  var_DI04 = 0_BOOL;
}

void FORTE_X20DI4653::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
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

void FORTE_X20DI4653::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_CNID, conn_CNID);
      readData(2, var_MODID, conn_MODID);
      break;
    }
    case scmEventREQID: {
      readData(0, var_QI, conn_QI);
      break;
    }
    default:
      break;
  }
}

void FORTE_X20DI4653::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(2, var_STATUS, conn_STATUS);
      writeData(1, var_CNIDO, conn_CNIDO);
      break;
    }
    case scmEventCNFID: {
      writeData(3, var_DI01, conn_DI01);
      writeData(4, var_DI02, conn_DI02);
      writeData(5, var_DI03, conn_DI03);
      writeData(6, var_DI04, conn_DI04);
      writeData(2, var_STATUS, conn_STATUS);
      writeData(0, var_QO, conn_QO);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_X20DI4653::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_CNID;
    case 2: return &var_MODID;
  }
  return nullptr;
}

CIEC_ANY *FORTE_X20DI4653::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_CNIDO;
    case 2: return &var_STATUS;
    case 3: return &var_DI01;
    case 4: return &var_DI02;
    case 5: return &var_DI03;
    case 6: return &var_DI04;
  }
  return nullptr;
}

CEventConnection *FORTE_X20DI4653::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_X20DI4653::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_CNID;
    case 2: return &conn_MODID;
  }
  return nullptr;
}

CDataConnection *FORTE_X20DI4653::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_CNIDO;
    case 2: return &conn_STATUS;
    case 3: return &conn_DI01;
    case 4: return &conn_DI02;
    case 5: return &conn_DI03;
    case 6: return &conn_DI04;
  }
  return nullptr;
}

