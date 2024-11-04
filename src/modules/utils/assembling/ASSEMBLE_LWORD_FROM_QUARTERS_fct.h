/*******************************************************************************
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
 *** Name: ASSEMBLE_LWORD_FROM_QUARTERS
 *** Description: this Function combines the 31 QUARTER BYTES to a LWORD
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-28/Moritz Ortmeier - HR Agrartechnik - rename Function and change Input/Output Variables
 *******************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_lword.h"
#include "forte_byte.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

class FORTE_ASSEMBLE_LWORD_FROM_QUARTERS final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_ASSEMBLE_LWORD_FROM_QUARTERS)

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
    FORTE_ASSEMBLE_LWORD_FROM_QUARTERS(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BYTE var_QUARTER_BYTE_00;
    CIEC_BYTE var_QUARTER_BYTE_01;
    CIEC_BYTE var_QUARTER_BYTE_02;
    CIEC_BYTE var_QUARTER_BYTE_03;
    CIEC_BYTE var_QUARTER_BYTE_04;
    CIEC_BYTE var_QUARTER_BYTE_05;
    CIEC_BYTE var_QUARTER_BYTE_06;
    CIEC_BYTE var_QUARTER_BYTE_07;
    CIEC_BYTE var_QUARTER_BYTE_08;
    CIEC_BYTE var_QUARTER_BYTE_09;
    CIEC_BYTE var_QUARTER_BYTE_10;
    CIEC_BYTE var_QUARTER_BYTE_11;
    CIEC_BYTE var_QUARTER_BYTE_12;
    CIEC_BYTE var_QUARTER_BYTE_13;
    CIEC_BYTE var_QUARTER_BYTE_14;
    CIEC_BYTE var_QUARTER_BYTE_15;
    CIEC_BYTE var_QUARTER_BYTE_16;
    CIEC_BYTE var_QUARTER_BYTE_17;
    CIEC_BYTE var_QUARTER_BYTE_18;
    CIEC_BYTE var_QUARTER_BYTE_19;
    CIEC_BYTE var_QUARTER_BYTE_20;
    CIEC_BYTE var_QUARTER_BYTE_21;
    CIEC_BYTE var_QUARTER_BYTE_22;
    CIEC_BYTE var_QUARTER_BYTE_23;
    CIEC_BYTE var_QUARTER_BYTE_24;
    CIEC_BYTE var_QUARTER_BYTE_25;
    CIEC_BYTE var_QUARTER_BYTE_26;
    CIEC_BYTE var_QUARTER_BYTE_27;
    CIEC_BYTE var_QUARTER_BYTE_28;
    CIEC_BYTE var_QUARTER_BYTE_29;
    CIEC_BYTE var_QUARTER_BYTE_30;
    CIEC_BYTE var_QUARTER_BYTE_31;

    CIEC_LWORD var_;

    CIEC_LWORD var_conn_;

    CEventConnection conn_CNF;

    CDataConnection *conn_QUARTER_BYTE_00;
    CDataConnection *conn_QUARTER_BYTE_01;
    CDataConnection *conn_QUARTER_BYTE_02;
    CDataConnection *conn_QUARTER_BYTE_03;
    CDataConnection *conn_QUARTER_BYTE_04;
    CDataConnection *conn_QUARTER_BYTE_05;
    CDataConnection *conn_QUARTER_BYTE_06;
    CDataConnection *conn_QUARTER_BYTE_07;
    CDataConnection *conn_QUARTER_BYTE_08;
    CDataConnection *conn_QUARTER_BYTE_09;
    CDataConnection *conn_QUARTER_BYTE_10;
    CDataConnection *conn_QUARTER_BYTE_11;
    CDataConnection *conn_QUARTER_BYTE_12;
    CDataConnection *conn_QUARTER_BYTE_13;
    CDataConnection *conn_QUARTER_BYTE_14;
    CDataConnection *conn_QUARTER_BYTE_15;
    CDataConnection *conn_QUARTER_BYTE_16;
    CDataConnection *conn_QUARTER_BYTE_17;
    CDataConnection *conn_QUARTER_BYTE_18;
    CDataConnection *conn_QUARTER_BYTE_19;
    CDataConnection *conn_QUARTER_BYTE_20;
    CDataConnection *conn_QUARTER_BYTE_21;
    CDataConnection *conn_QUARTER_BYTE_22;
    CDataConnection *conn_QUARTER_BYTE_23;
    CDataConnection *conn_QUARTER_BYTE_24;
    CDataConnection *conn_QUARTER_BYTE_25;
    CDataConnection *conn_QUARTER_BYTE_26;
    CDataConnection *conn_QUARTER_BYTE_27;
    CDataConnection *conn_QUARTER_BYTE_28;
    CDataConnection *conn_QUARTER_BYTE_29;
    CDataConnection *conn_QUARTER_BYTE_30;
    CDataConnection *conn_QUARTER_BYTE_31;

    CDataConnection conn_;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_REQ(const CIEC_BYTE &paQUARTER_BYTE_00, const CIEC_BYTE &paQUARTER_BYTE_01, const CIEC_BYTE &paQUARTER_BYTE_02, const CIEC_BYTE &paQUARTER_BYTE_03, const CIEC_BYTE &paQUARTER_BYTE_04, const CIEC_BYTE &paQUARTER_BYTE_05, const CIEC_BYTE &paQUARTER_BYTE_06, const CIEC_BYTE &paQUARTER_BYTE_07, const CIEC_BYTE &paQUARTER_BYTE_08, const CIEC_BYTE &paQUARTER_BYTE_09, const CIEC_BYTE &paQUARTER_BYTE_10, const CIEC_BYTE &paQUARTER_BYTE_11, const CIEC_BYTE &paQUARTER_BYTE_12, const CIEC_BYTE &paQUARTER_BYTE_13, const CIEC_BYTE &paQUARTER_BYTE_14, const CIEC_BYTE &paQUARTER_BYTE_15, const CIEC_BYTE &paQUARTER_BYTE_16, const CIEC_BYTE &paQUARTER_BYTE_17, const CIEC_BYTE &paQUARTER_BYTE_18, const CIEC_BYTE &paQUARTER_BYTE_19, const CIEC_BYTE &paQUARTER_BYTE_20, const CIEC_BYTE &paQUARTER_BYTE_21, const CIEC_BYTE &paQUARTER_BYTE_22, const CIEC_BYTE &paQUARTER_BYTE_23, const CIEC_BYTE &paQUARTER_BYTE_24, const CIEC_BYTE &paQUARTER_BYTE_25, const CIEC_BYTE &paQUARTER_BYTE_26, const CIEC_BYTE &paQUARTER_BYTE_27, const CIEC_BYTE &paQUARTER_BYTE_28, const CIEC_BYTE &paQUARTER_BYTE_29, const CIEC_BYTE &paQUARTER_BYTE_30, const CIEC_BYTE &paQUARTER_BYTE_31, CIEC_LWORD &pa) {
      var_QUARTER_BYTE_00 = paQUARTER_BYTE_00;
      var_QUARTER_BYTE_01 = paQUARTER_BYTE_01;
      var_QUARTER_BYTE_02 = paQUARTER_BYTE_02;
      var_QUARTER_BYTE_03 = paQUARTER_BYTE_03;
      var_QUARTER_BYTE_04 = paQUARTER_BYTE_04;
      var_QUARTER_BYTE_05 = paQUARTER_BYTE_05;
      var_QUARTER_BYTE_06 = paQUARTER_BYTE_06;
      var_QUARTER_BYTE_07 = paQUARTER_BYTE_07;
      var_QUARTER_BYTE_08 = paQUARTER_BYTE_08;
      var_QUARTER_BYTE_09 = paQUARTER_BYTE_09;
      var_QUARTER_BYTE_10 = paQUARTER_BYTE_10;
      var_QUARTER_BYTE_11 = paQUARTER_BYTE_11;
      var_QUARTER_BYTE_12 = paQUARTER_BYTE_12;
      var_QUARTER_BYTE_13 = paQUARTER_BYTE_13;
      var_QUARTER_BYTE_14 = paQUARTER_BYTE_14;
      var_QUARTER_BYTE_15 = paQUARTER_BYTE_15;
      var_QUARTER_BYTE_16 = paQUARTER_BYTE_16;
      var_QUARTER_BYTE_17 = paQUARTER_BYTE_17;
      var_QUARTER_BYTE_18 = paQUARTER_BYTE_18;
      var_QUARTER_BYTE_19 = paQUARTER_BYTE_19;
      var_QUARTER_BYTE_20 = paQUARTER_BYTE_20;
      var_QUARTER_BYTE_21 = paQUARTER_BYTE_21;
      var_QUARTER_BYTE_22 = paQUARTER_BYTE_22;
      var_QUARTER_BYTE_23 = paQUARTER_BYTE_23;
      var_QUARTER_BYTE_24 = paQUARTER_BYTE_24;
      var_QUARTER_BYTE_25 = paQUARTER_BYTE_25;
      var_QUARTER_BYTE_26 = paQUARTER_BYTE_26;
      var_QUARTER_BYTE_27 = paQUARTER_BYTE_27;
      var_QUARTER_BYTE_28 = paQUARTER_BYTE_28;
      var_QUARTER_BYTE_29 = paQUARTER_BYTE_29;
      var_QUARTER_BYTE_30 = paQUARTER_BYTE_30;
      var_QUARTER_BYTE_31 = paQUARTER_BYTE_31;
      executeEvent(scmEventREQID, nullptr);
      pa = var_;
    }

    void operator()(const CIEC_BYTE &paQUARTER_BYTE_00, const CIEC_BYTE &paQUARTER_BYTE_01, const CIEC_BYTE &paQUARTER_BYTE_02, const CIEC_BYTE &paQUARTER_BYTE_03, const CIEC_BYTE &paQUARTER_BYTE_04, const CIEC_BYTE &paQUARTER_BYTE_05, const CIEC_BYTE &paQUARTER_BYTE_06, const CIEC_BYTE &paQUARTER_BYTE_07, const CIEC_BYTE &paQUARTER_BYTE_08, const CIEC_BYTE &paQUARTER_BYTE_09, const CIEC_BYTE &paQUARTER_BYTE_10, const CIEC_BYTE &paQUARTER_BYTE_11, const CIEC_BYTE &paQUARTER_BYTE_12, const CIEC_BYTE &paQUARTER_BYTE_13, const CIEC_BYTE &paQUARTER_BYTE_14, const CIEC_BYTE &paQUARTER_BYTE_15, const CIEC_BYTE &paQUARTER_BYTE_16, const CIEC_BYTE &paQUARTER_BYTE_17, const CIEC_BYTE &paQUARTER_BYTE_18, const CIEC_BYTE &paQUARTER_BYTE_19, const CIEC_BYTE &paQUARTER_BYTE_20, const CIEC_BYTE &paQUARTER_BYTE_21, const CIEC_BYTE &paQUARTER_BYTE_22, const CIEC_BYTE &paQUARTER_BYTE_23, const CIEC_BYTE &paQUARTER_BYTE_24, const CIEC_BYTE &paQUARTER_BYTE_25, const CIEC_BYTE &paQUARTER_BYTE_26, const CIEC_BYTE &paQUARTER_BYTE_27, const CIEC_BYTE &paQUARTER_BYTE_28, const CIEC_BYTE &paQUARTER_BYTE_29, const CIEC_BYTE &paQUARTER_BYTE_30, const CIEC_BYTE &paQUARTER_BYTE_31, CIEC_LWORD &pa) {
      evt_REQ(paQUARTER_BYTE_00, paQUARTER_BYTE_01, paQUARTER_BYTE_02, paQUARTER_BYTE_03, paQUARTER_BYTE_04, paQUARTER_BYTE_05, paQUARTER_BYTE_06, paQUARTER_BYTE_07, paQUARTER_BYTE_08, paQUARTER_BYTE_09, paQUARTER_BYTE_10, paQUARTER_BYTE_11, paQUARTER_BYTE_12, paQUARTER_BYTE_13, paQUARTER_BYTE_14, paQUARTER_BYTE_15, paQUARTER_BYTE_16, paQUARTER_BYTE_17, paQUARTER_BYTE_18, paQUARTER_BYTE_19, paQUARTER_BYTE_20, paQUARTER_BYTE_21, paQUARTER_BYTE_22, paQUARTER_BYTE_23, paQUARTER_BYTE_24, paQUARTER_BYTE_25, paQUARTER_BYTE_26, paQUARTER_BYTE_27, paQUARTER_BYTE_28, paQUARTER_BYTE_29, paQUARTER_BYTE_30, paQUARTER_BYTE_31, pa);
    }
};

CIEC_LWORD func_ASSEMBLE_LWORD_FROM_QUARTERS(CIEC_BYTE st_lv_QUARTER_BYTE_00, CIEC_BYTE st_lv_QUARTER_BYTE_01, CIEC_BYTE st_lv_QUARTER_BYTE_02, CIEC_BYTE st_lv_QUARTER_BYTE_03, CIEC_BYTE st_lv_QUARTER_BYTE_04, CIEC_BYTE st_lv_QUARTER_BYTE_05, CIEC_BYTE st_lv_QUARTER_BYTE_06, CIEC_BYTE st_lv_QUARTER_BYTE_07, CIEC_BYTE st_lv_QUARTER_BYTE_08, CIEC_BYTE st_lv_QUARTER_BYTE_09, CIEC_BYTE st_lv_QUARTER_BYTE_10, CIEC_BYTE st_lv_QUARTER_BYTE_11, CIEC_BYTE st_lv_QUARTER_BYTE_12, CIEC_BYTE st_lv_QUARTER_BYTE_13, CIEC_BYTE st_lv_QUARTER_BYTE_14, CIEC_BYTE st_lv_QUARTER_BYTE_15, CIEC_BYTE st_lv_QUARTER_BYTE_16, CIEC_BYTE st_lv_QUARTER_BYTE_17, CIEC_BYTE st_lv_QUARTER_BYTE_18, CIEC_BYTE st_lv_QUARTER_BYTE_19, CIEC_BYTE st_lv_QUARTER_BYTE_20, CIEC_BYTE st_lv_QUARTER_BYTE_21, CIEC_BYTE st_lv_QUARTER_BYTE_22, CIEC_BYTE st_lv_QUARTER_BYTE_23, CIEC_BYTE st_lv_QUARTER_BYTE_24, CIEC_BYTE st_lv_QUARTER_BYTE_25, CIEC_BYTE st_lv_QUARTER_BYTE_26, CIEC_BYTE st_lv_QUARTER_BYTE_27, CIEC_BYTE st_lv_QUARTER_BYTE_28, CIEC_BYTE st_lv_QUARTER_BYTE_29, CIEC_BYTE st_lv_QUARTER_BYTE_30, CIEC_BYTE st_lv_QUARTER_BYTE_31);


