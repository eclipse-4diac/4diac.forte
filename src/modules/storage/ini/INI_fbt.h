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

#pragma once

#include "funcbloc.h"
#include "forte_any_elementary_variant.h"
#include "forte_bool.h"
#include "forte_string.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

class FORTE_INI final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_INI)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventINITID = 0;
    static const TEventID scmEventSETID = 1;
    static const TEventID scmEventGETID = 2;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const TEventID scmEventINITOID = 0;
    static const TEventID scmEventSETOID = 1;
    static const TEventID scmEventGETOID = 2;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void executeSet();
    void executeGet();
    void executeInit();

    const char *section;
    const char *key;

    static const CIEC_STRING scmOK;
    static const CIEC_STRING scmNotInitialised;
    static const CIEC_STRING scmInitialised;
    static const CIEC_STRING scmERR;
    static const CIEC_STRING scmERR_NVS_NOT_FOUND;



    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

  public:
    FORTE_INI(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BOOL var_QI;
    CIEC_STRING var_SECTION;
    CIEC_STRING var_KEY;
    CIEC_ANY_ELEMENTARY_VARIANT var_VALUE;
    CIEC_ANY_ELEMENTARY_VARIANT var_DEFAULT_VALUE;

    CIEC_BOOL var_QO;
    CIEC_STRING var_STATUS;
    CIEC_ANY_ELEMENTARY_VARIANT var_VALUEO;

    CIEC_BOOL var_conn_QO;
    CIEC_STRING var_conn_STATUS;
    CIEC_ANY_ELEMENTARY_VARIANT var_conn_VALUEO;

    CEventConnection conn_INITO;
    CEventConnection conn_SETO;
    CEventConnection conn_GETO;

    CDataConnection *conn_QI;
    CDataConnection *conn_SECTION;
    CDataConnection *conn_KEY;
    CDataConnection *conn_VALUE;
    CDataConnection *conn_DEFAULT_VALUE;

    CDataConnection conn_QO;
    CDataConnection conn_STATUS;
    CDataConnection conn_VALUEO;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_INIT(const CIEC_BOOL &paQI, const CIEC_STRING &paSECTION, const CIEC_STRING &paKEY, const CIEC_ANY_ELEMENTARY &paVALUE, const CIEC_ANY_ELEMENTARY &paDEFAULT_VALUE, CIEC_BOOL &paQO, CIEC_STRING &paSTATUS, CIEC_ANY_ELEMENTARY &paVALUEO) {
      var_QI = paQI;
      var_SECTION = paSECTION;
      var_KEY = paKEY;
      var_VALUE = paVALUE;
      var_DEFAULT_VALUE = paDEFAULT_VALUE;
      executeEvent(scmEventINITID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
      paVALUEO.setValue(var_VALUEO.unwrap());
    }

    void evt_SET(const CIEC_BOOL &paQI, const CIEC_STRING &paSECTION, const CIEC_STRING &paKEY, const CIEC_ANY_ELEMENTARY &paVALUE, const CIEC_ANY_ELEMENTARY &paDEFAULT_VALUE, CIEC_BOOL &paQO, CIEC_STRING &paSTATUS, CIEC_ANY_ELEMENTARY &paVALUEO) {
      var_QI = paQI;
      var_SECTION = paSECTION;
      var_KEY = paKEY;
      var_VALUE = paVALUE;
      var_DEFAULT_VALUE = paDEFAULT_VALUE;
      executeEvent(scmEventSETID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
      paVALUEO.setValue(var_VALUEO.unwrap());
    }

    void evt_GET(const CIEC_BOOL &paQI, const CIEC_STRING &paSECTION, const CIEC_STRING &paKEY, const CIEC_ANY_ELEMENTARY &paVALUE, const CIEC_ANY_ELEMENTARY &paDEFAULT_VALUE, CIEC_BOOL &paQO, CIEC_STRING &paSTATUS, CIEC_ANY_ELEMENTARY &paVALUEO) {
      var_QI = paQI;
      var_SECTION = paSECTION;
      var_KEY = paKEY;
      var_VALUE = paVALUE;
      var_DEFAULT_VALUE = paDEFAULT_VALUE;
      executeEvent(scmEventGETID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
      paVALUEO.setValue(var_VALUEO.unwrap());
    }

    void operator()(const CIEC_BOOL &paQI, const CIEC_STRING &paSECTION, const CIEC_STRING &paKEY, const CIEC_ANY_ELEMENTARY &paVALUE, const CIEC_ANY_ELEMENTARY &paDEFAULT_VALUE, CIEC_BOOL &paQO, CIEC_STRING &paSTATUS, CIEC_ANY_ELEMENTARY &paVALUEO) {
      evt_INIT(paQI, paSECTION, paKEY, paVALUE, paDEFAULT_VALUE, paQO, paSTATUS, paVALUEO);
    }
};

