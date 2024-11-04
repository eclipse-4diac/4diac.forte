/*************************************************************************
 *** Copyright (c) 2024 HR Agrartechnik GmbH
 *** This program and the accompanying materials are made available under the
 *** terms of the Eclipse Public License 2.0 which is available at
 *** http://www.eclipse.org/legal/epl-2.0.
 ***
 *** SPDX-License-Identifier: EPL-2.0
 ***
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ASSEMBLE_BYTE_FROM_BOOLS
 *** Description: this Function combines the 8 BOOLS to a BYTE
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-28/Moritz Ortmeier - HR Agrartechnik - rename Function and change Input/Output Variables
 *************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_byte.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

class FORTE_ASSEMBLE_BYTE_FROM_BOOLS final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_ASSEMBLE_BYTE_FROM_BOOLS)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventREQID = 0;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];
    static const TEventID scmEventCNFID = 0;
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
    FORTE_ASSEMBLE_BYTE_FROM_BOOLS(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BOOL var_BIT_00;
    CIEC_BOOL var_BIT_01;
    CIEC_BOOL var_BIT_02;
    CIEC_BOOL var_BIT_03;
    CIEC_BOOL var_BIT_04;
    CIEC_BOOL var_BIT_05;
    CIEC_BOOL var_BIT_06;
    CIEC_BOOL var_BIT_07;

    CIEC_BYTE var_;

    CIEC_BYTE var_conn_;

    CEventConnection conn_CNF;

    CDataConnection *conn_BIT_00;
    CDataConnection *conn_BIT_01;
    CDataConnection *conn_BIT_02;
    CDataConnection *conn_BIT_03;
    CDataConnection *conn_BIT_04;
    CDataConnection *conn_BIT_05;
    CDataConnection *conn_BIT_06;
    CDataConnection *conn_BIT_07;

    CDataConnection conn_;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_REQ(const CIEC_BOOL &paBIT_00, const CIEC_BOOL &paBIT_01, const CIEC_BOOL &paBIT_02, const CIEC_BOOL &paBIT_03, const CIEC_BOOL &paBIT_04, const CIEC_BOOL &paBIT_05, const CIEC_BOOL &paBIT_06, const CIEC_BOOL &paBIT_07, CIEC_BYTE &pa) {
      var_BIT_00 = paBIT_00;
      var_BIT_01 = paBIT_01;
      var_BIT_02 = paBIT_02;
      var_BIT_03 = paBIT_03;
      var_BIT_04 = paBIT_04;
      var_BIT_05 = paBIT_05;
      var_BIT_06 = paBIT_06;
      var_BIT_07 = paBIT_07;
      executeEvent(scmEventREQID, nullptr);
      pa = var_;
    }

    void operator()(const CIEC_BOOL &paBIT_00, const CIEC_BOOL &paBIT_01, const CIEC_BOOL &paBIT_02, const CIEC_BOOL &paBIT_03, const CIEC_BOOL &paBIT_04, const CIEC_BOOL &paBIT_05, const CIEC_BOOL &paBIT_06, const CIEC_BOOL &paBIT_07, CIEC_BYTE &pa) {
      evt_REQ(paBIT_00, paBIT_01, paBIT_02, paBIT_03, paBIT_04, paBIT_05, paBIT_06, paBIT_07, pa);
    }
};

CIEC_BYTE func_ASSEMBLE_BYTE_FROM_BOOLS(CIEC_BOOL st_lv_BIT_00, CIEC_BOOL st_lv_BIT_01, CIEC_BOOL st_lv_BIT_02, CIEC_BOOL st_lv_BIT_03, CIEC_BOOL st_lv_BIT_04, CIEC_BOOL st_lv_BIT_05, CIEC_BOOL st_lv_BIT_06, CIEC_BOOL st_lv_BIT_07);


