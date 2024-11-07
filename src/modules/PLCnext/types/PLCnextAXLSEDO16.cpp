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

#include "PLCnextAXLSEDO16.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "PLCnextAXLSEDO16_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_PLCnextAXLSEDO16, g_nStringIdPLCnextAXLSEDO16)

const CStringDictionary::TStringId FORTE_PLCnextAXLSEDO16::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdDO_1, g_nStringIdDO_2, g_nStringIdDO_3, g_nStringIdDO_4, g_nStringIdDO_5, g_nStringIdDO_6, g_nStringIdDO_7, g_nStringIdDO_8, g_nStringIdDO_9, g_nStringIdDO_10, g_nStringIdDO_11, g_nStringIdDO_12, g_nStringIdDO_13, g_nStringIdDO_14, g_nStringIdDO_15, g_nStringIdDO_16};
const CStringDictionary::TStringId FORTE_PLCnextAXLSEDO16::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING};
const CStringDictionary::TStringId FORTE_PLCnextAXLSEDO16::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_PLCnextAXLSEDO16::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};
const TDataIOID FORTE_PLCnextAXLSEDO16::scmEIWith[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, scmWithListDelimiter};
const TForteInt16 FORTE_PLCnextAXLSEDO16::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_PLCnextAXLSEDO16::scmEventInputNames[] = {g_nStringIdINIT};
const CStringDictionary::TStringId FORTE_PLCnextAXLSEDO16::scmEventInputTypeIds[] = {g_nStringIdEInit};
const TDataIOID FORTE_PLCnextAXLSEDO16::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_PLCnextAXLSEDO16::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_PLCnextAXLSEDO16::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdIND};
const CStringDictionary::TStringId FORTE_PLCnextAXLSEDO16::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const SAdapterInstanceDef FORTE_PLCnextAXLSEDO16::scmAdapterInstances[] = {
  {g_nStringIdPLCnextBusAdapter, g_nStringIdBusAdapterIn, false},
  {g_nStringIdPLCnextBusAdapter, g_nStringIdBusAdapterOut, true}
};
const SFBInterfaceSpec FORTE_PLCnextAXLSEDO16::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  17, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  2, scmAdapterInstances
};

FORTE_PLCnextAXLSEDO16::FORTE_PLCnextAXLSEDO16(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
   PLCnextSlaveHandler (PLCnextSlaveHandler::Output, pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId, m_anFBConnData, m_anFBVarsData),
    var_DO_1(""_STRING),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_INITO(this, 0),
    conn_IND(this, 1),
    conn_QI(nullptr),
    conn_DO_1(nullptr),
    conn_DO_2(nullptr),
    conn_DO_3(nullptr),
    conn_DO_4(nullptr),
    conn_DO_5(nullptr),
    conn_DO_6(nullptr),
    conn_DO_7(nullptr),
    conn_DO_8(nullptr),
    conn_DO_9(nullptr),
    conn_DO_10(nullptr),
    conn_DO_11(nullptr),
    conn_DO_12(nullptr),
    conn_DO_13(nullptr),
    conn_DO_14(nullptr),
    conn_DO_15(nullptr),
    conn_DO_16(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS) {
};

void FORTE_PLCnextAXLSEDO16::setInitialValues() {
  var_QI = 0_BOOL;
  var_DO_1 = ""_STRING;
  var_DO_2 = ""_STRING;
  var_DO_3 = ""_STRING;
  var_DO_4 = ""_STRING;
  var_DO_5 = ""_STRING;
  var_DO_6 = ""_STRING;
  var_DO_7 = ""_STRING;
  var_DO_8 = ""_STRING;
  var_DO_9 = ""_STRING;
  var_DO_10 = ""_STRING;
  var_DO_11 = ""_STRING;
  var_DO_12 = ""_STRING;
  var_DO_13 = ""_STRING;
  var_DO_14 = ""_STRING;
  var_DO_15 = ""_STRING;
  var_DO_16 = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_PLCnextAXLSEDO16::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_DO_1, conn_DO_1);
      readData(2, var_DO_2, conn_DO_2);
      readData(3, var_DO_3, conn_DO_3);
      readData(4, var_DO_4, conn_DO_4);
      readData(5, var_DO_5, conn_DO_5);
      readData(6, var_DO_6, conn_DO_6);
      readData(7, var_DO_7, conn_DO_7);
      readData(8, var_DO_8, conn_DO_8);
      readData(9, var_DO_9, conn_DO_9);
      readData(10, var_DO_10, conn_DO_10);
      readData(11, var_DO_11, conn_DO_11);
      readData(12, var_DO_12, conn_DO_12);
      readData(13, var_DO_13, conn_DO_13);
      readData(14, var_DO_14, conn_DO_14);
      readData(15, var_DO_15, conn_DO_15);
      readData(16, var_DO_16, conn_DO_16);
      break;
    }
    default:
      break;
  }
}

void FORTE_PLCnextAXLSEDO16::writeOutputData(const TEventID paEIID) {
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

CIEC_ANY *FORTE_PLCnextAXLSEDO16::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_DO_1;
    case 2: return &var_DO_2;
    case 3: return &var_DO_3;
    case 4: return &var_DO_4;
    case 5: return &var_DO_5;
    case 6: return &var_DO_6;
    case 7: return &var_DO_7;
    case 8: return &var_DO_8;
    case 9: return &var_DO_9;
    case 10: return &var_DO_10;
    case 11: return &var_DO_11;
    case 12: return &var_DO_12;
    case 13: return &var_DO_13;
    case 14: return &var_DO_14;
    case 15: return &var_DO_15;
    case 16: return &var_DO_16;
  }
  return nullptr;
}

CIEC_ANY *FORTE_PLCnextAXLSEDO16::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_PLCnextAXLSEDO16::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_PLCnextAXLSEDO16::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_DO_1;
    case 2: return &conn_DO_2;
    case 3: return &conn_DO_3;
    case 4: return &conn_DO_4;
    case 5: return &conn_DO_5;
    case 6: return &conn_DO_6;
    case 7: return &conn_DO_7;
    case 8: return &conn_DO_8;
    case 9: return &conn_DO_9;
    case 10: return &conn_DO_10;
    case 11: return &conn_DO_11;
    case 12: return &conn_DO_12;
    case 13: return &conn_DO_13;
    case 14: return &conn_DO_14;
    case 15: return &conn_DO_15;
    case 16: return &conn_DO_16;
  }
  return nullptr;
}

CDataConnection *FORTE_PLCnextAXLSEDO16::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_PLCnextAXLSEDO16::initHandles() {
    // Initialize handles
    for (int i = 0; i < 16; i++) {
        PLCnextDeviceController::HandleDescriptor desc = PLCnextDeviceController::HandleDescriptor(
            *static_cast<CIEC_WSTRING*>(getDI(i+1)),
            forte::core::io::IOMapper::Out,
            mIndex,
            (uint16_t) i,
            PLCnextDeviceController::Bit);

        initHandle(desc);
    }
}

const char* FORTE_PLCnextAXLSEDO16::init() {
    PLCnextDeviceController &controller = *static_cast<PLCnextDeviceController*>(&getController());

    // initialize buffer with correct size
    initBufferImage(16);
    controller.registerSlaveHandler(this);

    return plcNextDevice.init(mIndex, "OUT01");
}
