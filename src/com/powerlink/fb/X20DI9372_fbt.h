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

#pragma once

#include "PowerlinkFunctionBlockDI.h"
#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_usint.h"
#include "forte_uint.h"
#include "forte_string.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_X20DI9372 final : public PowerlinkFunctionBlockDI {
  DECLARE_FIRMWARE_FB(FORTE_X20DI9372)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventINITID = 0;
    static const TEventID scmEventREQID = 1;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];
    static const TEventID scmEventINITOID = 0;
    static const TEventID scmEventCNFID = 1;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

  public:
    FORTE_X20DI9372(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BOOL var_QI;
    CIEC_USINT var_CNID;
    CIEC_UINT var_MODID;

    CIEC_BOOL var_QO;
    CIEC_USINT var_CNIDO;
    CIEC_STRING var_STATUS;
    CIEC_BOOL var_DI01;
    CIEC_BOOL var_DI02;
    CIEC_BOOL var_DI03;
    CIEC_BOOL var_DI04;
    CIEC_BOOL var_DI05;
    CIEC_BOOL var_DI06;
    CIEC_BOOL var_DI07;
    CIEC_BOOL var_DI08;
    CIEC_BOOL var_DI09;
    CIEC_BOOL var_DI10;
    CIEC_BOOL var_DI11;
    CIEC_BOOL var_DI12;

    CIEC_BOOL var_conn_QO;
    CIEC_USINT var_conn_CNIDO;
    CIEC_STRING var_conn_STATUS;
    CIEC_BOOL var_conn_DI01;
    CIEC_BOOL var_conn_DI02;
    CIEC_BOOL var_conn_DI03;
    CIEC_BOOL var_conn_DI04;
    CIEC_BOOL var_conn_DI05;
    CIEC_BOOL var_conn_DI06;
    CIEC_BOOL var_conn_DI07;
    CIEC_BOOL var_conn_DI08;
    CIEC_BOOL var_conn_DI09;
    CIEC_BOOL var_conn_DI10;
    CIEC_BOOL var_conn_DI11;
    CIEC_BOOL var_conn_DI12;

    CEventConnection conn_INITO;
    CEventConnection conn_CNF;

    CDataConnection *conn_QI;
    CDataConnection *conn_CNID;
    CDataConnection *conn_MODID;

    CDataConnection conn_QO;
    CDataConnection conn_CNIDO;
    CDataConnection conn_STATUS;
    CDataConnection conn_DI01;
    CDataConnection conn_DI02;
    CDataConnection conn_DI03;
    CDataConnection conn_DI04;
    CDataConnection conn_DI05;
    CDataConnection conn_DI06;
    CDataConnection conn_DI07;
    CDataConnection conn_DI08;
    CDataConnection conn_DI09;
    CDataConnection conn_DI10;
    CDataConnection conn_DI11;
    CDataConnection conn_DI12;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_INIT(const CIEC_BOOL &paQI, const CIEC_USINT &paCNID, const CIEC_UINT &paMODID, CIEC_BOOL &paQO, CIEC_USINT &paCNIDO, CIEC_STRING &paSTATUS, CIEC_BOOL &paDI01, CIEC_BOOL &paDI02, CIEC_BOOL &paDI03, CIEC_BOOL &paDI04, CIEC_BOOL &paDI05, CIEC_BOOL &paDI06, CIEC_BOOL &paDI07, CIEC_BOOL &paDI08, CIEC_BOOL &paDI09, CIEC_BOOL &paDI10, CIEC_BOOL &paDI11, CIEC_BOOL &paDI12) {
      var_QI = paQI;
      var_CNID = paCNID;
      var_MODID = paMODID;
      executeEvent(scmEventINITID, nullptr);
      paQO = var_QO;
      paCNIDO = var_CNIDO;
      paSTATUS = var_STATUS;
      paDI01 = var_DI01;
      paDI02 = var_DI02;
      paDI03 = var_DI03;
      paDI04 = var_DI04;
      paDI05 = var_DI05;
      paDI06 = var_DI06;
      paDI07 = var_DI07;
      paDI08 = var_DI08;
      paDI09 = var_DI09;
      paDI10 = var_DI10;
      paDI11 = var_DI11;
      paDI12 = var_DI12;
    }

    void evt_REQ(const CIEC_BOOL &paQI, const CIEC_USINT &paCNID, const CIEC_UINT &paMODID, CIEC_BOOL &paQO, CIEC_USINT &paCNIDO, CIEC_STRING &paSTATUS, CIEC_BOOL &paDI01, CIEC_BOOL &paDI02, CIEC_BOOL &paDI03, CIEC_BOOL &paDI04, CIEC_BOOL &paDI05, CIEC_BOOL &paDI06, CIEC_BOOL &paDI07, CIEC_BOOL &paDI08, CIEC_BOOL &paDI09, CIEC_BOOL &paDI10, CIEC_BOOL &paDI11, CIEC_BOOL &paDI12) {
      var_QI = paQI;
      var_CNID = paCNID;
      var_MODID = paMODID;
      executeEvent(scmEventREQID, nullptr);
      paQO = var_QO;
      paCNIDO = var_CNIDO;
      paSTATUS = var_STATUS;
      paDI01 = var_DI01;
      paDI02 = var_DI02;
      paDI03 = var_DI03;
      paDI04 = var_DI04;
      paDI05 = var_DI05;
      paDI06 = var_DI06;
      paDI07 = var_DI07;
      paDI08 = var_DI08;
      paDI09 = var_DI09;
      paDI10 = var_DI10;
      paDI11 = var_DI11;
      paDI12 = var_DI12;
    }

    void operator()(const CIEC_BOOL &paQI, const CIEC_USINT &paCNID, const CIEC_UINT &paMODID, CIEC_BOOL &paQO, CIEC_USINT &paCNIDO, CIEC_STRING &paSTATUS, CIEC_BOOL &paDI01, CIEC_BOOL &paDI02, CIEC_BOOL &paDI03, CIEC_BOOL &paDI04, CIEC_BOOL &paDI05, CIEC_BOOL &paDI06, CIEC_BOOL &paDI07, CIEC_BOOL &paDI08, CIEC_BOOL &paDI09, CIEC_BOOL &paDI10, CIEC_BOOL &paDI11, CIEC_BOOL &paDI12) {
      evt_INIT(paQI, paCNID, paMODID, paQO, paCNIDO, paSTATUS, paDI01, paDI02, paDI03, paDI04, paDI05, paDI06, paDI07, paDI08, paDI09, paDI10, paDI11, paDI12);
    }
};


