/*******************************************************************************
 * Copyright (c) 2022 Peirlberger Juergen
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Peirlberger Juergen - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "PLCnextAXLSESC.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "PLCnextAXLSESC_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_PLCnextAXLSESC, g_nStringIdPLCnextAXLSESC)

const CStringDictionary::TStringId FORTE_PLCnextAXLSESC::scmDataInputNames[] = {g_nStringIdQI};
const CStringDictionary::TStringId FORTE_PLCnextAXLSESC::scmDataInputTypeIds[] = {g_nStringIdBOOL};
const CStringDictionary::TStringId FORTE_PLCnextAXLSESC::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_PLCnextAXLSESC::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};
const TDataIOID FORTE_PLCnextAXLSESC::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_PLCnextAXLSESC::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_PLCnextAXLSESC::scmEventInputNames[] = {g_nStringIdINIT};
const CStringDictionary::TStringId FORTE_PLCnextAXLSESC::scmEventInputTypeIds[] = {g_nStringIdEInit};
const TDataIOID FORTE_PLCnextAXLSESC::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_PLCnextAXLSESC::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_PLCnextAXLSESC::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdIND};
const CStringDictionary::TStringId FORTE_PLCnextAXLSESC::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const SAdapterInstanceDef FORTE_PLCnextAXLSESC::scmAdapterInstances[] = {
  {g_nStringIdPLCnextBusAdapter, g_nStringIdBusAdapterIn, false},
  {g_nStringIdPLCnextBusAdapter, g_nStringIdBusAdapterOut, true}
};
const SFBInterfaceSpec FORTE_PLCnextAXLSESC::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  2, scmAdapterInstances
};

FORTE_PLCnextAXLSESC::FORTE_PLCnextAXLSESC(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    PLCnextSlaveHandler (PLCnextSlaveHandler::NoUsage, pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId, m_anFBConnData, m_anFBVarsData),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_INITO(this, 0),
    conn_IND(this, 1),
    conn_QI(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS) {
};

void FORTE_PLCnextAXLSESC::setInitialValues() {
  var_QI = 0_BOOL;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_PLCnextAXLSESC::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      break;
    }
    default:
      break;
  }
}

void FORTE_PLCnextAXLSESC::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    case scmEventINDID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_PLCnextAXLSESC::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
  }
  return nullptr;
}

CIEC_ANY *FORTE_PLCnextAXLSESC::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_PLCnextAXLSESC::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_PLCnextAXLSESC::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
  }
  return nullptr;
}

CDataConnection *FORTE_PLCnextAXLSESC::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_PLCnextAXLSESC::initHandles() {

}

const char* FORTE_PLCnextAXLSESC::init(){
    PLCnextDeviceController &controller = *static_cast<PLCnextDeviceController*>(&getController());
    controller.registerSlaveHandler(this);
    return 0;
}
