/*************************************************************************
 *** Copyright (c) 2024 HR Agrartechnik GmbH
 *** This program and the accompanying materials are made available under the
 *** terms of the Eclipse Public License 2.0 which is available at
 *** http://www.eclipse.org/legal/epl-2.0.
 ***
 *** SPDX-License-Identifier: EPL-2.0
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: INI
 *** Description: Load and Store Data from settings.ini by Section and Key
 *** Version:
 ***     1.0: 2024-09-17/Franz Höpfinger - HR Agrartechnik GmbH -
 *************************************************************************/

#include "INI_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "INI_fbt_gen.cpp"
#endif

#include "settingsIni.h"

#include "criticalregion.h"
#include "resource.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_INI, g_nStringIdINI)

const CIEC_STRING FORTE_INI::scmOK                 = "OK"_STRING;
const CIEC_STRING FORTE_INI::scmNotInitialised     = "Not initialized"_STRING;
const CIEC_STRING FORTE_INI::scmInitialised        = "initialized"_STRING;
const CIEC_STRING FORTE_INI::scmERR                = "ERROR"_STRING; //Unknown Error
const CIEC_STRING FORTE_INI::scmERR_NVS_NOT_FOUND  = "ESP_ERR_NVS_NOT_FOUND"_STRING; //Unknown Error

const CStringDictionary::TStringId FORTE_INI::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdSECTION, g_nStringIdKEY, g_nStringIdVALUE, g_nStringIdDEFAULT_VALUE};
const CStringDictionary::TStringId FORTE_INI::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdANY_ELEMENTARY, g_nStringIdANY_ELEMENTARY};
const CStringDictionary::TStringId FORTE_INI::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdVALUEO};
const CStringDictionary::TStringId FORTE_INI::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdANY_ELEMENTARY};
const TDataIOID FORTE_INI::scmEIWith[] = {0, 1, 2, 3, 4, scmWithListDelimiter, 3, scmWithListDelimiter, 3, scmWithListDelimiter};
const TForteInt16 FORTE_INI::scmEIWithIndexes[] = {0, 6, 8};
const CStringDictionary::TStringId FORTE_INI::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdSET, g_nStringIdGET};
const TDataIOID FORTE_INI::scmEOWith[] = {0, 1, 2, scmWithListDelimiter, 0, 1, 2, scmWithListDelimiter, 0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_INI::scmEOWithIndexes[] = {0, 4, 8};
const CStringDictionary::TStringId FORTE_INI::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdSETO, g_nStringIdGETO};
const SFBInterfaceSpec FORTE_INI::scmFBInterfaceSpec = {
  3, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  3, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  5, scmDataInputNames, scmDataInputTypeIds,
  3, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_INI::FORTE_INI(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    var_conn_VALUEO(var_VALUEO),
    conn_INITO(this, 0),
    conn_SETO(this, 1),
    conn_GETO(this, 2),
    conn_QI(nullptr),
    conn_SECTION(nullptr),
    conn_KEY(nullptr),
    conn_VALUE(nullptr),
    conn_DEFAULT_VALUE(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS),
    conn_VALUEO(this, 2, &var_conn_VALUEO) {
};

void FORTE_INI::setInitialValues() {
  var_QI = 0_BOOL;
  var_SECTION = ""_STRING;
  var_KEY = ""_STRING;
  var_VALUE = CIEC_ANY_ELEMENTARY_VARIANT();
  var_DEFAULT_VALUE = CIEC_ANY_ELEMENTARY_VARIANT();
  var_QO = 0_BOOL;
  var_STATUS = ""_STRING;
  var_VALUEO = CIEC_ANY_ELEMENTARY_VARIANT();
}

void FORTE_INI::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventINITID:
      section = var_SECTION.c_str();
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

void FORTE_INI::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_SECTION, conn_SECTION);
      readData(2, var_KEY, conn_KEY);
      readData(3, var_VALUE, conn_VALUE);
      readData(4, var_DEFAULT_VALUE, conn_DEFAULT_VALUE);
      break;
    }
    case scmEventSETID: {
      readData(3, var_VALUE, conn_VALUE);
      break;
    }
    case scmEventGETID: {
      readData(3, var_VALUE, conn_VALUE);
      break;
    }
    default:
      break;
  }
}

void FORTE_INI::writeOutputData(const TEventID paEIID) {
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

CIEC_ANY *FORTE_INI::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_SECTION;
    case 2: return &var_KEY;
    case 3: return &var_VALUE;
    case 4: return &var_DEFAULT_VALUE;
  }
  return nullptr;
}

CIEC_ANY *FORTE_INI::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
    case 2: return &var_VALUEO;
  }
  return nullptr;
}

CEventConnection *FORTE_INI::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_SETO;
    case 2: return &conn_GETO;
  }
  return nullptr;
}

CDataConnection **FORTE_INI::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_SECTION;
    case 2: return &conn_KEY;
    case 3: return &conn_VALUE;
    case 4: return &conn_DEFAULT_VALUE;
  }
  return nullptr;
}

CDataConnection *FORTE_INI::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
    case 2: return &conn_VALUEO;
  }
  return nullptr;
}


void FORTE_INI::executeSet() {

  CIEC_ANY &value = var_VALUE.unwrap();
  switch (value.getDataTypeID()) //input Type determines Storage.
  {
    case CIEC_ANY::e_BOOL:
      setU8(section, key, (bool) static_cast<CIEC_BOOL&>(value));
      break;
    case CIEC_ANY::e_SINT:
      setS8(section, key, (TForteInt8) static_cast<CIEC_SINT&>(value));
      break;
    case CIEC_ANY::e_INT:
      setS16(section, key, (TForteInt16) static_cast<CIEC_INT&>(value));
      break;
    case CIEC_ANY::e_DINT:
      setS32(section, key, (TForteInt32) static_cast<CIEC_DINT&>(value));
      break;
    case CIEC_ANY::e_LINT:
      setS64(section, key, (TForteInt64) static_cast<CIEC_LINT&>(value));
      break;
    case CIEC_ANY::e_USINT:
      setU8(section, key, (TForteUInt8) static_cast<CIEC_USINT&>(value));
      break;
    case CIEC_ANY::e_UINT:
      setU16(section, key, (TForteUInt16) static_cast<CIEC_UINT&>(value));
      break;
    case CIEC_ANY::e_UDINT:
      setU32(section, key, (TForteUInt32) static_cast<CIEC_UDINT&>(value));
      break;
    case CIEC_ANY::e_ULINT:
      setU64(section, key, (TForteUInt64) static_cast<CIEC_ULINT&>(value));
      break;
    case CIEC_ANY::e_BYTE:
      setU8(section, key, (TForteByte) static_cast<CIEC_BYTE&>(value));
      break;
    case CIEC_ANY::e_WORD:
      setU16(section, key, (TForteWord) static_cast<CIEC_WORD&>(value));
      break;
    case CIEC_ANY::e_DWORD:
      setU32(section, key, (TForteDWord) static_cast<CIEC_DWORD&>(value));
      break;
    case CIEC_ANY::e_LWORD:
      setX64(section, key, (TForteLWord) static_cast<CIEC_LWORD&>(value));
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
    case CIEC_ANY::e_STRING:{
      CIEC_STRING value_ciecString = static_cast<CIEC_STRING&>(value);
      const char *const value_buf = value_ciecString.c_str();
      setString(section, key, value_buf);
    }
      break;
    case CIEC_ANY::e_WSTRING:
      break;
    default:
      break;
  }
  var_VALUEO = var_VALUE;
  var_STATUS = scmOK;
  saveSettings();
}

void FORTE_INI::executeGet() {

  CIEC_ANY &value  = var_VALUE.unwrap();
  CIEC_ANY &default_value  = var_DEFAULT_VALUE.unwrap();
  switch (value.getDataTypeID()) //input Type determines Storage.
  {
    case CIEC_ANY::e_BOOL:
      var_VALUEO.setValue(CIEC_BOOL(getU8(section, key, (bool) static_cast<CIEC_BOOL&>(default_value))));
      break;
    case CIEC_ANY::e_SINT:
      var_VALUEO.setValue(CIEC_SINT(getS8(section, key, (TForteInt8) static_cast<CIEC_SINT&>(default_value))));
      break;
    case CIEC_ANY::e_INT:
      var_VALUEO.setValue(CIEC_INT(getS16(section, key, (TForteInt16) static_cast<CIEC_INT&>(default_value))));
      break;
    case CIEC_ANY::e_DINT:
      var_VALUEO.setValue(CIEC_DINT(getS32(section, key, (TForteInt32) static_cast<CIEC_DINT&>(default_value))));
      break;
    case CIEC_ANY::e_LINT:
      var_VALUEO.setValue(CIEC_LINT(getS64(section, key, (TForteInt64) static_cast<CIEC_LINT&>(default_value))));
      break;
    case CIEC_ANY::e_USINT:
      var_VALUEO.setValue(CIEC_USINT(getU8(section, key, (TForteUInt8) static_cast<CIEC_USINT&>(default_value))));
      break;
    case CIEC_ANY::e_UINT:
      var_VALUEO.setValue(CIEC_UINT(getU16(section, key, (TForteUInt16) static_cast<CIEC_UINT&>(default_value))));
      break;
    case CIEC_ANY::e_UDINT:
      var_VALUEO.setValue(CIEC_UDINT(getU32(section, key, (TForteUInt32) static_cast<CIEC_UDINT&>(default_value))));
      break;
    case CIEC_ANY::e_ULINT:
      var_VALUEO.setValue(CIEC_ULINT(getU64(section, key, (TForteUInt64) static_cast<CIEC_ULINT&>(default_value))));
      break;
    case CIEC_ANY::e_BYTE:
      var_VALUEO.setValue(CIEC_BYTE(getU8(section, key, (TForteByte) static_cast<CIEC_BYTE&>(default_value))));
      break;
    case CIEC_ANY::e_WORD:
      var_VALUEO.setValue(CIEC_WORD(getU16(section, key, (TForteWord) static_cast<CIEC_WORD&>(default_value))));
      break;
    case CIEC_ANY::e_DWORD:
      var_VALUEO.setValue(CIEC_DWORD(getU32(section, key, (TForteDWord) static_cast<CIEC_DWORD&>(default_value))));
      break;
    case CIEC_ANY::e_LWORD:
      var_VALUEO.setValue(CIEC_LWORD(getX64(section, key, (TForteLWord) static_cast<CIEC_LWORD&>(default_value))));
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
      CIEC_STRING default_value_ciecString = static_cast<CIEC_STRING&>(default_value);
      const char *const default_value_buf = default_value_ciecString.c_str();
      char val[16] = { 0 };
      getString(section, key, default_value_buf, val, 16U);
      var_VALUEO.setValue(CIEC_STRING(val));
    }
      break;
    case CIEC_ANY::e_WSTRING:
      break;
    default:
      break;
  }



  var_STATUS = scmOK;
  saveSettings();
}

void FORTE_INI::executeInit() {
}
