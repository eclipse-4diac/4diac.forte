/*************************************************************************
 *** Copyright (c) 2022, 2024 HR Agrartechnik GmbH
 *** This program and the accompanying materials are made available under the
 *** terms of the Eclipse Public License 2.0 which is available at
 *** http://www.eclipse.org/legal/epl-2.0.
 ***
 *** SPDX-License-Identifier: EPL-2.0
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: NVS
 *** Description: Load and Store Data from NVS by Key
 *** Version:
 ***     1.0: 2022-09-23/Franz Höpfinger - HR Agrartechnik GmbH -
 *************************************************************************/

#include "NVS_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "NVS_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_NVS, g_nStringIdNVS)

const CIEC_STRING FORTE_NVS::scmOK                 = "OK"_STRING;
const CIEC_STRING FORTE_NVS::scmNotInitialised     = "Not initialized"_STRING;
const CIEC_STRING FORTE_NVS::scmInitialised        = "initialized"_STRING;
const CIEC_STRING FORTE_NVS::scmERR                = "ERROR"_STRING; //Unknown Error
const CIEC_STRING FORTE_NVS::scmERR_NVS_NOT_FOUND  = "ESP_ERR_NVS_NOT_FOUND"_STRING; //Unknown Error

std::shared_ptr<nvs::NVSHandle> FORTE_NVS::handle;

const CStringDictionary::TStringId FORTE_NVS::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdKEY, g_nStringIdVALUE};
const CStringDictionary::TStringId FORTE_NVS::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdANY_ELEMENTARY};
const CStringDictionary::TStringId FORTE_NVS::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdVALUEO};
const CStringDictionary::TStringId FORTE_NVS::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdANY_ELEMENTARY};
const TDataIOID FORTE_NVS::scmEIWith[] = {0, 1, 2, scmWithListDelimiter, 2, scmWithListDelimiter, 2, scmWithListDelimiter};
const TForteInt16 FORTE_NVS::scmEIWithIndexes[] = {0, 4, 6};
const CStringDictionary::TStringId FORTE_NVS::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdSET, g_nStringIdGET};
const TDataIOID FORTE_NVS::scmEOWith[] = {0, 1, 2, scmWithListDelimiter, 0, 1, 2, scmWithListDelimiter, 0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_NVS::scmEOWithIndexes[] = {0, 4, 8};
const CStringDictionary::TStringId FORTE_NVS::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdSETO, g_nStringIdGETO};
const SFBInterfaceSpec FORTE_NVS::scmFBInterfaceSpec = {
  3, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  3, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  3, scmDataInputNames, scmDataInputTypeIds,
  3, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_NVS::FORTE_NVS(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    var_conn_VALUEO(var_VALUEO),
    conn_INITO(this, 0),
    conn_SETO(this, 1),
    conn_GETO(this, 2),
    conn_QI(nullptr),
    conn_KEY(nullptr),
    conn_VALUE(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS),
    conn_VALUEO(this, 2, &var_conn_VALUEO) {
  key = nullptr;
};

void FORTE_NVS::setInitialValues() {
  var_QI = 0_BOOL;
  var_KEY = ""_STRING;
  var_VALUE = CIEC_ANY_ELEMENTARY_VARIANT();
  var_QO = 0_BOOL;
  var_STATUS = ""_STRING;
  var_VALUEO = CIEC_ANY_ELEMENTARY_VARIANT();
}

void FORTE_NVS::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventINITID:
      key = var_KEY.c_str();
      executeInit();
      var_STATUS = scmInitialised;
      var_QO = var_QI;
      sendOutputEvent(scmEventINITOID, paECET);

      break;
    case scmEventSETID:
      executeSet();
      sendOutputEvent(scmEventSETOID, paECET);

      break;
    case scmEventGETID:
      executeGet();
      sendOutputEvent(scmEventGETOID, paECET);
      break;
  }
}

void FORTE_NVS::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_KEY, conn_KEY);
      readData(2, var_VALUE, conn_VALUE);
      break;
    }
    case scmEventSETID: {
      readData(2, var_VALUE, conn_VALUE);
      break;
    }
    case scmEventGETID: {
      readData(2, var_VALUE, conn_VALUE);
      break;
    }
    default:
      break;
  }
}

void FORTE_NVS::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      writeData(2, var_VALUEO, conn_VALUEO);
      break;
    }
    case scmEventSETOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      writeData(2, var_VALUEO, conn_VALUEO);
      break;
    }
    case scmEventGETOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      writeData(2, var_VALUEO, conn_VALUEO);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_NVS::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_KEY;
    case 2: return &var_VALUE;
  }
  return nullptr;
}

CIEC_ANY *FORTE_NVS::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
    case 2: return &var_VALUEO;
  }
  return nullptr;
}

CEventConnection *FORTE_NVS::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_SETO;
    case 2: return &conn_GETO;
  }
  return nullptr;
}

CDataConnection **FORTE_NVS::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_KEY;
    case 2: return &conn_VALUE;
  }
  return nullptr;
}

CDataConnection *FORTE_NVS::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
    case 2: return &conn_VALUEO;
  }
  return nullptr;
}


void FORTE_NVS::executeSet() {
  esp_err_t err = ESP_FAIL;

  CIEC_ANY &value = var_VALUE.unwrap();
  switch (value.getDataTypeID()) //input Type determines Storage.
  {
    case CIEC_ANY::e_BOOL:
      err = handle->set_item(key, (bool) static_cast<CIEC_BOOL&>(value));
      break;
    case CIEC_ANY::e_SINT:
      err = handle->set_item(key, (TForteInt8) static_cast<CIEC_SINT&>(value));
      break;
    case CIEC_ANY::e_INT:
      err = handle->set_item(key, (TForteInt16) static_cast<CIEC_INT&>(value));
      break;
    case CIEC_ANY::e_DINT:
      err = handle->set_item(key, (TForteInt32) static_cast<CIEC_DINT&>(value));
      break;
    case CIEC_ANY::e_LINT:
      err = handle->set_item(key, (TForteInt64) static_cast<CIEC_LINT&>(value));
      break;
    case CIEC_ANY::e_USINT:
      err = handle->set_item(key, (TForteUInt8) static_cast<CIEC_USINT&>(value));
      break;
    case CIEC_ANY::e_UINT:
      err = handle->set_item(key, (TForteUInt16) static_cast<CIEC_UINT&>(value));
      break;
    case CIEC_ANY::e_UDINT:
      err = handle->set_item(key, (TForteUInt32) static_cast<CIEC_UDINT&>(value));
      break;
    case CIEC_ANY::e_ULINT:
      err = handle->set_item(key, (TForteUInt64) static_cast<CIEC_ULINT&>(value));
      break;
    case CIEC_ANY::e_BYTE:
      err = handle->set_item(key, (TForteByte) static_cast<CIEC_BYTE&>(value));
      break;
    case CIEC_ANY::e_WORD:
      err = handle->set_item(key, (TForteWord) static_cast<CIEC_WORD&>(value));
      break;
    case CIEC_ANY::e_DWORD:
      err = handle->set_item(key, (TForteDWord) static_cast<CIEC_DWORD&>(value));
      break;
    case CIEC_ANY::e_LWORD:
      err = handle->set_item(key, (TForteLWord) static_cast<CIEC_LWORD&>(value));
      break;
    case CIEC_ANY::e_DATE:
      break;
    case CIEC_ANY::e_TIME_OF_DAY:
      break;
    case CIEC_ANY::e_DATE_AND_TIME:
      break;
    case CIEC_ANY::e_TIME:
      break;
    case CIEC_ANY::e_CHAR:
      break;
    case CIEC_ANY::e_WCHAR:
      break;
    case CIEC_ANY::e_LDATE:
      break;
    case CIEC_ANY::e_LTIME_OF_DAY:
      break;
    case CIEC_ANY::e_LDATE_AND_TIME:
      break;
    case CIEC_ANY::e_LTIME:
      break;
    case CIEC_ANY::e_REAL:
      break;
    case CIEC_ANY::e_LREAL:
      break;
    case CIEC_ANY::e_STRING: {
      CIEC_STRING value_ciecString = static_cast<CIEC_STRING&>(value);
      const char *const value_buf = value_ciecString.c_str();
      err = handle->set_string(key, value_buf);
    }
      break;
    case CIEC_ANY::e_WSTRING:
      break;
    default:
      break;
  }

  switch (err) {
    case ESP_OK:
      var_VALUEO = var_VALUE;
      var_STATUS = scmOK;
      break;
    default :
      var_STATUS = scmERR;
      break;
  }
}

void FORTE_NVS::executeGet() {
  esp_err_t err = ESP_FAIL;

  CIEC_ANY &value = var_VALUE.unwrap();
  switch(value.getDataTypeID()) //input Type determines Storage.
  {
    case CIEC_ANY::e_BOOL: {
      bool value_out;
      err = handle->get_item(key, value_out);
      var_VALUEO.setValue(CIEC_BOOL(value_out));
    }
      break;
    case CIEC_ANY::e_SINT: {
      TForteInt8 value_out;
      err = handle->get_item(key, value_out);
      var_VALUEO.setValue(CIEC_SINT(value_out));
    }
      break;
    case CIEC_ANY::e_INT: {
      TForteInt16 value_out;
      err = handle->get_item(key, value_out);
      var_VALUEO.setValue(CIEC_INT(value_out));
    }
      break;
    case CIEC_ANY::e_DINT: {
      TForteInt32 value_out;
      err = handle->get_item(key, value_out);
      var_VALUEO.setValue(CIEC_DINT(value_out));
    }
      break;
    case CIEC_ANY::e_LINT: {
      TForteInt64 value_out;
      err = handle->get_item(key, value_out);
      var_VALUEO.setValue(CIEC_LINT(value_out));
    }
      break;
    case CIEC_ANY::e_USINT: {
      TForteUInt8 value_out;
      err = handle->get_item(key, value_out);
      var_VALUEO.setValue(CIEC_USINT(value_out));
    }
      break;
    case CIEC_ANY::e_UINT: {
      TForteUInt16 value_out;
      err = handle->get_item(key, value_out);
      var_VALUEO.setValue(CIEC_UINT(value_out));
    }
      break;
    case CIEC_ANY::e_UDINT: {
      TForteUInt32 value_out;
      err = handle->get_item(key, value_out);
      var_VALUEO.setValue(CIEC_UDINT(value_out));
    }
      break;
    case CIEC_ANY::e_ULINT: {
      TForteUInt64 value_out;
      err = handle->get_item(key, value_out);
      var_VALUEO.setValue(CIEC_ULINT(value_out));
    }
      break;
    case CIEC_ANY::e_BYTE: {
      TForteByte value_out;
      err = handle->get_item(key, value_out);
      var_VALUEO.setValue(CIEC_BYTE(value_out));
    }
      break;
    case CIEC_ANY::e_WORD: {
      TForteWord value_out;
      err = handle->get_item(key, value_out);
      var_VALUEO.setValue(CIEC_WORD(value_out));
    }
      break;
    case CIEC_ANY::e_DWORD: {
      TForteDWord value_out;
      err = handle->get_item(key, value_out);
      var_VALUEO.setValue(CIEC_DWORD(value_out));
    }
      break;
    case CIEC_ANY::e_LWORD: {
      TForteLWord value_out;
      err = handle->get_item(key, value_out);
      var_VALUEO.setValue(CIEC_LWORD(value_out));
    }
      break;
    case CIEC_ANY::e_DATE:
      break;
    case CIEC_ANY::e_TIME_OF_DAY:
      break;
    case CIEC_ANY::e_DATE_AND_TIME:
      break;
    case CIEC_ANY::e_TIME:
      break;
    case CIEC_ANY::e_CHAR:
      break;
    case CIEC_ANY::e_WCHAR:
      break;
    case CIEC_ANY::e_LDATE:
      break;
    case CIEC_ANY::e_LTIME_OF_DAY:
      break;
    case CIEC_ANY::e_LDATE_AND_TIME:
      break;
    case CIEC_ANY::e_LTIME:
      break;
    case CIEC_ANY::e_REAL:
      break;
    case CIEC_ANY::e_LREAL:
      break;
    case CIEC_ANY::e_STRING: {
      char val[16] = { 0 };
      err = handle->get_string(key, val, 16U);
      var_VALUEO.setValue(CIEC_STRING(val));
    }
      break;
    case CIEC_ANY::e_WSTRING:
      break;
    default:
      break;
  }




  switch (err) {
    case ESP_OK:
      var_STATUS = scmOK;
      break;
    case ESP_ERR_NVS_NOT_FOUND:
      var_STATUS = scmERR_NVS_NOT_FOUND;
      break;
    default :
      var_STATUS = scmERR;
      break;
  }
}

void FORTE_NVS::executeInit() {
  // if handle == nullptr
  if (!handle)
  {
    esp_err_t result;
    handle = nvs::open_nvs_handle("storage", NVS_READWRITE, &result);
  }
}

