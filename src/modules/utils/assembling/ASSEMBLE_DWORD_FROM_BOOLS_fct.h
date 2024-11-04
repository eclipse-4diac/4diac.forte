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
 *** Name: ASSEMBLE_DWORD_FROM_BOOLS
 *** Description: this Function combines the 32 BOOLS to a DWORD
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-28/Moritz Ortmeier - HR Agrartechnik - rename Function and change Input/Output Variables
 *************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_dword.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

class FORTE_ASSEMBLE_DWORD_FROM_BOOLS final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_ASSEMBLE_DWORD_FROM_BOOLS)

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
    FORTE_ASSEMBLE_DWORD_FROM_BOOLS(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BOOL var_BIT_00;
    CIEC_BOOL var_BIT_01;
    CIEC_BOOL var_BIT_02;
    CIEC_BOOL var_BIT_03;
    CIEC_BOOL var_BIT_04;
    CIEC_BOOL var_BIT_05;
    CIEC_BOOL var_BIT_06;
    CIEC_BOOL var_BIT_07;
    CIEC_BOOL var_BIT_08;
    CIEC_BOOL var_BIT_09;
    CIEC_BOOL var_BIT_10;
    CIEC_BOOL var_BIT_11;
    CIEC_BOOL var_BIT_12;
    CIEC_BOOL var_BIT_13;
    CIEC_BOOL var_BIT_14;
    CIEC_BOOL var_BIT_15;
    CIEC_BOOL var_BIT_16;
    CIEC_BOOL var_BIT_17;
    CIEC_BOOL var_BIT_18;
    CIEC_BOOL var_BIT_19;
    CIEC_BOOL var_BIT_20;
    CIEC_BOOL var_BIT_21;
    CIEC_BOOL var_BIT_22;
    CIEC_BOOL var_BIT_23;
    CIEC_BOOL var_BIT_24;
    CIEC_BOOL var_BIT_25;
    CIEC_BOOL var_BIT_26;
    CIEC_BOOL var_BIT_27;
    CIEC_BOOL var_BIT_28;
    CIEC_BOOL var_BIT_29;
    CIEC_BOOL var_BIT_30;
    CIEC_BOOL var_BIT_31;

    CIEC_DWORD var_;

    CIEC_DWORD var_conn_;

    CEventConnection conn_CNF;

    CDataConnection *conn_BIT_00;
    CDataConnection *conn_BIT_01;
    CDataConnection *conn_BIT_02;
    CDataConnection *conn_BIT_03;
    CDataConnection *conn_BIT_04;
    CDataConnection *conn_BIT_05;
    CDataConnection *conn_BIT_06;
    CDataConnection *conn_BIT_07;
    CDataConnection *conn_BIT_08;
    CDataConnection *conn_BIT_09;
    CDataConnection *conn_BIT_10;
    CDataConnection *conn_BIT_11;
    CDataConnection *conn_BIT_12;
    CDataConnection *conn_BIT_13;
    CDataConnection *conn_BIT_14;
    CDataConnection *conn_BIT_15;
    CDataConnection *conn_BIT_16;
    CDataConnection *conn_BIT_17;
    CDataConnection *conn_BIT_18;
    CDataConnection *conn_BIT_19;
    CDataConnection *conn_BIT_20;
    CDataConnection *conn_BIT_21;
    CDataConnection *conn_BIT_22;
    CDataConnection *conn_BIT_23;
    CDataConnection *conn_BIT_24;
    CDataConnection *conn_BIT_25;
    CDataConnection *conn_BIT_26;
    CDataConnection *conn_BIT_27;
    CDataConnection *conn_BIT_28;
    CDataConnection *conn_BIT_29;
    CDataConnection *conn_BIT_30;
    CDataConnection *conn_BIT_31;

    CDataConnection conn_;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_REQ(const CIEC_BOOL &paBIT_00, const CIEC_BOOL &paBIT_01, const CIEC_BOOL &paBIT_02, const CIEC_BOOL &paBIT_03, const CIEC_BOOL &paBIT_04, const CIEC_BOOL &paBIT_05, const CIEC_BOOL &paBIT_06, const CIEC_BOOL &paBIT_07, const CIEC_BOOL &paBIT_08, const CIEC_BOOL &paBIT_09, const CIEC_BOOL &paBIT_10, const CIEC_BOOL &paBIT_11, const CIEC_BOOL &paBIT_12, const CIEC_BOOL &paBIT_13, const CIEC_BOOL &paBIT_14, const CIEC_BOOL &paBIT_15, const CIEC_BOOL &paBIT_16, const CIEC_BOOL &paBIT_17, const CIEC_BOOL &paBIT_18, const CIEC_BOOL &paBIT_19, const CIEC_BOOL &paBIT_20, const CIEC_BOOL &paBIT_21, const CIEC_BOOL &paBIT_22, const CIEC_BOOL &paBIT_23, const CIEC_BOOL &paBIT_24, const CIEC_BOOL &paBIT_25, const CIEC_BOOL &paBIT_26, const CIEC_BOOL &paBIT_27, const CIEC_BOOL &paBIT_28, const CIEC_BOOL &paBIT_29, const CIEC_BOOL &paBIT_30, const CIEC_BOOL &paBIT_31, CIEC_DWORD &pa) {
      var_BIT_00 = paBIT_00;
      var_BIT_01 = paBIT_01;
      var_BIT_02 = paBIT_02;
      var_BIT_03 = paBIT_03;
      var_BIT_04 = paBIT_04;
      var_BIT_05 = paBIT_05;
      var_BIT_06 = paBIT_06;
      var_BIT_07 = paBIT_07;
      var_BIT_08 = paBIT_08;
      var_BIT_09 = paBIT_09;
      var_BIT_10 = paBIT_10;
      var_BIT_11 = paBIT_11;
      var_BIT_12 = paBIT_12;
      var_BIT_13 = paBIT_13;
      var_BIT_14 = paBIT_14;
      var_BIT_15 = paBIT_15;
      var_BIT_16 = paBIT_16;
      var_BIT_17 = paBIT_17;
      var_BIT_18 = paBIT_18;
      var_BIT_19 = paBIT_19;
      var_BIT_20 = paBIT_20;
      var_BIT_21 = paBIT_21;
      var_BIT_22 = paBIT_22;
      var_BIT_23 = paBIT_23;
      var_BIT_24 = paBIT_24;
      var_BIT_25 = paBIT_25;
      var_BIT_26 = paBIT_26;
      var_BIT_27 = paBIT_27;
      var_BIT_28 = paBIT_28;
      var_BIT_29 = paBIT_29;
      var_BIT_30 = paBIT_30;
      var_BIT_31 = paBIT_31;
      executeEvent(scmEventREQID, nullptr);
      pa = var_;
    }

    void operator()(const CIEC_BOOL &paBIT_00, const CIEC_BOOL &paBIT_01, const CIEC_BOOL &paBIT_02, const CIEC_BOOL &paBIT_03, const CIEC_BOOL &paBIT_04, const CIEC_BOOL &paBIT_05, const CIEC_BOOL &paBIT_06, const CIEC_BOOL &paBIT_07, const CIEC_BOOL &paBIT_08, const CIEC_BOOL &paBIT_09, const CIEC_BOOL &paBIT_10, const CIEC_BOOL &paBIT_11, const CIEC_BOOL &paBIT_12, const CIEC_BOOL &paBIT_13, const CIEC_BOOL &paBIT_14, const CIEC_BOOL &paBIT_15, const CIEC_BOOL &paBIT_16, const CIEC_BOOL &paBIT_17, const CIEC_BOOL &paBIT_18, const CIEC_BOOL &paBIT_19, const CIEC_BOOL &paBIT_20, const CIEC_BOOL &paBIT_21, const CIEC_BOOL &paBIT_22, const CIEC_BOOL &paBIT_23, const CIEC_BOOL &paBIT_24, const CIEC_BOOL &paBIT_25, const CIEC_BOOL &paBIT_26, const CIEC_BOOL &paBIT_27, const CIEC_BOOL &paBIT_28, const CIEC_BOOL &paBIT_29, const CIEC_BOOL &paBIT_30, const CIEC_BOOL &paBIT_31, CIEC_DWORD &pa) {
      evt_REQ(paBIT_00, paBIT_01, paBIT_02, paBIT_03, paBIT_04, paBIT_05, paBIT_06, paBIT_07, paBIT_08, paBIT_09, paBIT_10, paBIT_11, paBIT_12, paBIT_13, paBIT_14, paBIT_15, paBIT_16, paBIT_17, paBIT_18, paBIT_19, paBIT_20, paBIT_21, paBIT_22, paBIT_23, paBIT_24, paBIT_25, paBIT_26, paBIT_27, paBIT_28, paBIT_29, paBIT_30, paBIT_31, pa);
    }
};

CIEC_DWORD func_ASSEMBLE_DWORD_FROM_BOOLS(CIEC_BOOL st_lv_BIT_00, CIEC_BOOL st_lv_BIT_01, CIEC_BOOL st_lv_BIT_02, CIEC_BOOL st_lv_BIT_03, CIEC_BOOL st_lv_BIT_04, CIEC_BOOL st_lv_BIT_05, CIEC_BOOL st_lv_BIT_06, CIEC_BOOL st_lv_BIT_07, CIEC_BOOL st_lv_BIT_08, CIEC_BOOL st_lv_BIT_09, CIEC_BOOL st_lv_BIT_10, CIEC_BOOL st_lv_BIT_11, CIEC_BOOL st_lv_BIT_12, CIEC_BOOL st_lv_BIT_13, CIEC_BOOL st_lv_BIT_14, CIEC_BOOL st_lv_BIT_15, CIEC_BOOL st_lv_BIT_16, CIEC_BOOL st_lv_BIT_17, CIEC_BOOL st_lv_BIT_18, CIEC_BOOL st_lv_BIT_19, CIEC_BOOL st_lv_BIT_20, CIEC_BOOL st_lv_BIT_21, CIEC_BOOL st_lv_BIT_22, CIEC_BOOL st_lv_BIT_23, CIEC_BOOL st_lv_BIT_24, CIEC_BOOL st_lv_BIT_25, CIEC_BOOL st_lv_BIT_26, CIEC_BOOL st_lv_BIT_27, CIEC_BOOL st_lv_BIT_28, CIEC_BOOL st_lv_BIT_29, CIEC_BOOL st_lv_BIT_30, CIEC_BOOL st_lv_BIT_31);


