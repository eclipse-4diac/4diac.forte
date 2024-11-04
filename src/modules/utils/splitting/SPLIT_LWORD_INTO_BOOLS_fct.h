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
 *** Name: SPLIT_LWORD_INTO_BOOLS
 *** Description: this Function extracts the 64 BOOLS from a lword
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-24/Moritz Ortmeier - HR Agrartechnik - rename Function and change Output Variables
 *************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_lword.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

class FORTE_SPLIT_LWORD_INTO_BOOLS final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_SPLIT_LWORD_INTO_BOOLS)

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
    FORTE_SPLIT_LWORD_INTO_BOOLS(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_LWORD var_IN;

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
    CIEC_BOOL var_BIT_32;
    CIEC_BOOL var_BIT_33;
    CIEC_BOOL var_BIT_34;
    CIEC_BOOL var_BIT_35;
    CIEC_BOOL var_BIT_36;
    CIEC_BOOL var_BIT_37;
    CIEC_BOOL var_BIT_38;
    CIEC_BOOL var_BIT_39;
    CIEC_BOOL var_BIT_40;
    CIEC_BOOL var_BIT_41;
    CIEC_BOOL var_BIT_42;
    CIEC_BOOL var_BIT_43;
    CIEC_BOOL var_BIT_44;
    CIEC_BOOL var_BIT_45;
    CIEC_BOOL var_BIT_46;
    CIEC_BOOL var_BIT_47;
    CIEC_BOOL var_BIT_48;
    CIEC_BOOL var_BIT_49;
    CIEC_BOOL var_BIT_50;
    CIEC_BOOL var_BIT_51;
    CIEC_BOOL var_BIT_52;
    CIEC_BOOL var_BIT_53;
    CIEC_BOOL var_BIT_54;
    CIEC_BOOL var_BIT_55;
    CIEC_BOOL var_BIT_56;
    CIEC_BOOL var_BIT_57;
    CIEC_BOOL var_BIT_58;
    CIEC_BOOL var_BIT_59;
    CIEC_BOOL var_BIT_60;
    CIEC_BOOL var_BIT_61;
    CIEC_BOOL var_BIT_62;
    CIEC_BOOL var_BIT_63;

    CIEC_BOOL var_conn_BIT_00;
    CIEC_BOOL var_conn_BIT_01;
    CIEC_BOOL var_conn_BIT_02;
    CIEC_BOOL var_conn_BIT_03;
    CIEC_BOOL var_conn_BIT_04;
    CIEC_BOOL var_conn_BIT_05;
    CIEC_BOOL var_conn_BIT_06;
    CIEC_BOOL var_conn_BIT_07;
    CIEC_BOOL var_conn_BIT_08;
    CIEC_BOOL var_conn_BIT_09;
    CIEC_BOOL var_conn_BIT_10;
    CIEC_BOOL var_conn_BIT_11;
    CIEC_BOOL var_conn_BIT_12;
    CIEC_BOOL var_conn_BIT_13;
    CIEC_BOOL var_conn_BIT_14;
    CIEC_BOOL var_conn_BIT_15;
    CIEC_BOOL var_conn_BIT_16;
    CIEC_BOOL var_conn_BIT_17;
    CIEC_BOOL var_conn_BIT_18;
    CIEC_BOOL var_conn_BIT_19;
    CIEC_BOOL var_conn_BIT_20;
    CIEC_BOOL var_conn_BIT_21;
    CIEC_BOOL var_conn_BIT_22;
    CIEC_BOOL var_conn_BIT_23;
    CIEC_BOOL var_conn_BIT_24;
    CIEC_BOOL var_conn_BIT_25;
    CIEC_BOOL var_conn_BIT_26;
    CIEC_BOOL var_conn_BIT_27;
    CIEC_BOOL var_conn_BIT_28;
    CIEC_BOOL var_conn_BIT_29;
    CIEC_BOOL var_conn_BIT_30;
    CIEC_BOOL var_conn_BIT_31;
    CIEC_BOOL var_conn_BIT_32;
    CIEC_BOOL var_conn_BIT_33;
    CIEC_BOOL var_conn_BIT_34;
    CIEC_BOOL var_conn_BIT_35;
    CIEC_BOOL var_conn_BIT_36;
    CIEC_BOOL var_conn_BIT_37;
    CIEC_BOOL var_conn_BIT_38;
    CIEC_BOOL var_conn_BIT_39;
    CIEC_BOOL var_conn_BIT_40;
    CIEC_BOOL var_conn_BIT_41;
    CIEC_BOOL var_conn_BIT_42;
    CIEC_BOOL var_conn_BIT_43;
    CIEC_BOOL var_conn_BIT_44;
    CIEC_BOOL var_conn_BIT_45;
    CIEC_BOOL var_conn_BIT_46;
    CIEC_BOOL var_conn_BIT_47;
    CIEC_BOOL var_conn_BIT_48;
    CIEC_BOOL var_conn_BIT_49;
    CIEC_BOOL var_conn_BIT_50;
    CIEC_BOOL var_conn_BIT_51;
    CIEC_BOOL var_conn_BIT_52;
    CIEC_BOOL var_conn_BIT_53;
    CIEC_BOOL var_conn_BIT_54;
    CIEC_BOOL var_conn_BIT_55;
    CIEC_BOOL var_conn_BIT_56;
    CIEC_BOOL var_conn_BIT_57;
    CIEC_BOOL var_conn_BIT_58;
    CIEC_BOOL var_conn_BIT_59;
    CIEC_BOOL var_conn_BIT_60;
    CIEC_BOOL var_conn_BIT_61;
    CIEC_BOOL var_conn_BIT_62;
    CIEC_BOOL var_conn_BIT_63;

    CEventConnection conn_CNF;

    CDataConnection *conn_IN;

    CDataConnection conn_BIT_00;
    CDataConnection conn_BIT_01;
    CDataConnection conn_BIT_02;
    CDataConnection conn_BIT_03;
    CDataConnection conn_BIT_04;
    CDataConnection conn_BIT_05;
    CDataConnection conn_BIT_06;
    CDataConnection conn_BIT_07;
    CDataConnection conn_BIT_08;
    CDataConnection conn_BIT_09;
    CDataConnection conn_BIT_10;
    CDataConnection conn_BIT_11;
    CDataConnection conn_BIT_12;
    CDataConnection conn_BIT_13;
    CDataConnection conn_BIT_14;
    CDataConnection conn_BIT_15;
    CDataConnection conn_BIT_16;
    CDataConnection conn_BIT_17;
    CDataConnection conn_BIT_18;
    CDataConnection conn_BIT_19;
    CDataConnection conn_BIT_20;
    CDataConnection conn_BIT_21;
    CDataConnection conn_BIT_22;
    CDataConnection conn_BIT_23;
    CDataConnection conn_BIT_24;
    CDataConnection conn_BIT_25;
    CDataConnection conn_BIT_26;
    CDataConnection conn_BIT_27;
    CDataConnection conn_BIT_28;
    CDataConnection conn_BIT_29;
    CDataConnection conn_BIT_30;
    CDataConnection conn_BIT_31;
    CDataConnection conn_BIT_32;
    CDataConnection conn_BIT_33;
    CDataConnection conn_BIT_34;
    CDataConnection conn_BIT_35;
    CDataConnection conn_BIT_36;
    CDataConnection conn_BIT_37;
    CDataConnection conn_BIT_38;
    CDataConnection conn_BIT_39;
    CDataConnection conn_BIT_40;
    CDataConnection conn_BIT_41;
    CDataConnection conn_BIT_42;
    CDataConnection conn_BIT_43;
    CDataConnection conn_BIT_44;
    CDataConnection conn_BIT_45;
    CDataConnection conn_BIT_46;
    CDataConnection conn_BIT_47;
    CDataConnection conn_BIT_48;
    CDataConnection conn_BIT_49;
    CDataConnection conn_BIT_50;
    CDataConnection conn_BIT_51;
    CDataConnection conn_BIT_52;
    CDataConnection conn_BIT_53;
    CDataConnection conn_BIT_54;
    CDataConnection conn_BIT_55;
    CDataConnection conn_BIT_56;
    CDataConnection conn_BIT_57;
    CDataConnection conn_BIT_58;
    CDataConnection conn_BIT_59;
    CDataConnection conn_BIT_60;
    CDataConnection conn_BIT_61;
    CDataConnection conn_BIT_62;
    CDataConnection conn_BIT_63;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_REQ(const CIEC_LWORD &paIN, CIEC_BOOL &paBIT_00, CIEC_BOOL &paBIT_01, CIEC_BOOL &paBIT_02, CIEC_BOOL &paBIT_03, CIEC_BOOL &paBIT_04, CIEC_BOOL &paBIT_05, CIEC_BOOL &paBIT_06, CIEC_BOOL &paBIT_07, CIEC_BOOL &paBIT_08, CIEC_BOOL &paBIT_09, CIEC_BOOL &paBIT_10, CIEC_BOOL &paBIT_11, CIEC_BOOL &paBIT_12, CIEC_BOOL &paBIT_13, CIEC_BOOL &paBIT_14, CIEC_BOOL &paBIT_15, CIEC_BOOL &paBIT_16, CIEC_BOOL &paBIT_17, CIEC_BOOL &paBIT_18, CIEC_BOOL &paBIT_19, CIEC_BOOL &paBIT_20, CIEC_BOOL &paBIT_21, CIEC_BOOL &paBIT_22, CIEC_BOOL &paBIT_23, CIEC_BOOL &paBIT_24, CIEC_BOOL &paBIT_25, CIEC_BOOL &paBIT_26, CIEC_BOOL &paBIT_27, CIEC_BOOL &paBIT_28, CIEC_BOOL &paBIT_29, CIEC_BOOL &paBIT_30, CIEC_BOOL &paBIT_31, CIEC_BOOL &paBIT_32, CIEC_BOOL &paBIT_33, CIEC_BOOL &paBIT_34, CIEC_BOOL &paBIT_35, CIEC_BOOL &paBIT_36, CIEC_BOOL &paBIT_37, CIEC_BOOL &paBIT_38, CIEC_BOOL &paBIT_39, CIEC_BOOL &paBIT_40, CIEC_BOOL &paBIT_41, CIEC_BOOL &paBIT_42, CIEC_BOOL &paBIT_43, CIEC_BOOL &paBIT_44, CIEC_BOOL &paBIT_45, CIEC_BOOL &paBIT_46, CIEC_BOOL &paBIT_47, CIEC_BOOL &paBIT_48, CIEC_BOOL &paBIT_49, CIEC_BOOL &paBIT_50, CIEC_BOOL &paBIT_51, CIEC_BOOL &paBIT_52, CIEC_BOOL &paBIT_53, CIEC_BOOL &paBIT_54, CIEC_BOOL &paBIT_55, CIEC_BOOL &paBIT_56, CIEC_BOOL &paBIT_57, CIEC_BOOL &paBIT_58, CIEC_BOOL &paBIT_59, CIEC_BOOL &paBIT_60, CIEC_BOOL &paBIT_61, CIEC_BOOL &paBIT_62, CIEC_BOOL &paBIT_63) {
      var_IN = paIN;
      executeEvent(scmEventREQID, nullptr);
      paBIT_00 = var_BIT_00;
      paBIT_01 = var_BIT_01;
      paBIT_02 = var_BIT_02;
      paBIT_03 = var_BIT_03;
      paBIT_04 = var_BIT_04;
      paBIT_05 = var_BIT_05;
      paBIT_06 = var_BIT_06;
      paBIT_07 = var_BIT_07;
      paBIT_08 = var_BIT_08;
      paBIT_09 = var_BIT_09;
      paBIT_10 = var_BIT_10;
      paBIT_11 = var_BIT_11;
      paBIT_12 = var_BIT_12;
      paBIT_13 = var_BIT_13;
      paBIT_14 = var_BIT_14;
      paBIT_15 = var_BIT_15;
      paBIT_16 = var_BIT_16;
      paBIT_17 = var_BIT_17;
      paBIT_18 = var_BIT_18;
      paBIT_19 = var_BIT_19;
      paBIT_20 = var_BIT_20;
      paBIT_21 = var_BIT_21;
      paBIT_22 = var_BIT_22;
      paBIT_23 = var_BIT_23;
      paBIT_24 = var_BIT_24;
      paBIT_25 = var_BIT_25;
      paBIT_26 = var_BIT_26;
      paBIT_27 = var_BIT_27;
      paBIT_28 = var_BIT_28;
      paBIT_29 = var_BIT_29;
      paBIT_30 = var_BIT_30;
      paBIT_31 = var_BIT_31;
      paBIT_32 = var_BIT_32;
      paBIT_33 = var_BIT_33;
      paBIT_34 = var_BIT_34;
      paBIT_35 = var_BIT_35;
      paBIT_36 = var_BIT_36;
      paBIT_37 = var_BIT_37;
      paBIT_38 = var_BIT_38;
      paBIT_39 = var_BIT_39;
      paBIT_40 = var_BIT_40;
      paBIT_41 = var_BIT_41;
      paBIT_42 = var_BIT_42;
      paBIT_43 = var_BIT_43;
      paBIT_44 = var_BIT_44;
      paBIT_45 = var_BIT_45;
      paBIT_46 = var_BIT_46;
      paBIT_47 = var_BIT_47;
      paBIT_48 = var_BIT_48;
      paBIT_49 = var_BIT_49;
      paBIT_50 = var_BIT_50;
      paBIT_51 = var_BIT_51;
      paBIT_52 = var_BIT_52;
      paBIT_53 = var_BIT_53;
      paBIT_54 = var_BIT_54;
      paBIT_55 = var_BIT_55;
      paBIT_56 = var_BIT_56;
      paBIT_57 = var_BIT_57;
      paBIT_58 = var_BIT_58;
      paBIT_59 = var_BIT_59;
      paBIT_60 = var_BIT_60;
      paBIT_61 = var_BIT_61;
      paBIT_62 = var_BIT_62;
      paBIT_63 = var_BIT_63;
    }

    void operator()(const CIEC_LWORD &paIN, CIEC_BOOL &paBIT_00, CIEC_BOOL &paBIT_01, CIEC_BOOL &paBIT_02, CIEC_BOOL &paBIT_03, CIEC_BOOL &paBIT_04, CIEC_BOOL &paBIT_05, CIEC_BOOL &paBIT_06, CIEC_BOOL &paBIT_07, CIEC_BOOL &paBIT_08, CIEC_BOOL &paBIT_09, CIEC_BOOL &paBIT_10, CIEC_BOOL &paBIT_11, CIEC_BOOL &paBIT_12, CIEC_BOOL &paBIT_13, CIEC_BOOL &paBIT_14, CIEC_BOOL &paBIT_15, CIEC_BOOL &paBIT_16, CIEC_BOOL &paBIT_17, CIEC_BOOL &paBIT_18, CIEC_BOOL &paBIT_19, CIEC_BOOL &paBIT_20, CIEC_BOOL &paBIT_21, CIEC_BOOL &paBIT_22, CIEC_BOOL &paBIT_23, CIEC_BOOL &paBIT_24, CIEC_BOOL &paBIT_25, CIEC_BOOL &paBIT_26, CIEC_BOOL &paBIT_27, CIEC_BOOL &paBIT_28, CIEC_BOOL &paBIT_29, CIEC_BOOL &paBIT_30, CIEC_BOOL &paBIT_31, CIEC_BOOL &paBIT_32, CIEC_BOOL &paBIT_33, CIEC_BOOL &paBIT_34, CIEC_BOOL &paBIT_35, CIEC_BOOL &paBIT_36, CIEC_BOOL &paBIT_37, CIEC_BOOL &paBIT_38, CIEC_BOOL &paBIT_39, CIEC_BOOL &paBIT_40, CIEC_BOOL &paBIT_41, CIEC_BOOL &paBIT_42, CIEC_BOOL &paBIT_43, CIEC_BOOL &paBIT_44, CIEC_BOOL &paBIT_45, CIEC_BOOL &paBIT_46, CIEC_BOOL &paBIT_47, CIEC_BOOL &paBIT_48, CIEC_BOOL &paBIT_49, CIEC_BOOL &paBIT_50, CIEC_BOOL &paBIT_51, CIEC_BOOL &paBIT_52, CIEC_BOOL &paBIT_53, CIEC_BOOL &paBIT_54, CIEC_BOOL &paBIT_55, CIEC_BOOL &paBIT_56, CIEC_BOOL &paBIT_57, CIEC_BOOL &paBIT_58, CIEC_BOOL &paBIT_59, CIEC_BOOL &paBIT_60, CIEC_BOOL &paBIT_61, CIEC_BOOL &paBIT_62, CIEC_BOOL &paBIT_63) {
      evt_REQ(paIN, paBIT_00, paBIT_01, paBIT_02, paBIT_03, paBIT_04, paBIT_05, paBIT_06, paBIT_07, paBIT_08, paBIT_09, paBIT_10, paBIT_11, paBIT_12, paBIT_13, paBIT_14, paBIT_15, paBIT_16, paBIT_17, paBIT_18, paBIT_19, paBIT_20, paBIT_21, paBIT_22, paBIT_23, paBIT_24, paBIT_25, paBIT_26, paBIT_27, paBIT_28, paBIT_29, paBIT_30, paBIT_31, paBIT_32, paBIT_33, paBIT_34, paBIT_35, paBIT_36, paBIT_37, paBIT_38, paBIT_39, paBIT_40, paBIT_41, paBIT_42, paBIT_43, paBIT_44, paBIT_45, paBIT_46, paBIT_47, paBIT_48, paBIT_49, paBIT_50, paBIT_51, paBIT_52, paBIT_53, paBIT_54, paBIT_55, paBIT_56, paBIT_57, paBIT_58, paBIT_59, paBIT_60, paBIT_61, paBIT_62, paBIT_63);
    }
};

void func_SPLIT_LWORD_INTO_BOOLS(CIEC_LWORD st_lv_IN, CIEC_BOOL &st_lv_BIT_00, CIEC_BOOL &st_lv_BIT_01, CIEC_BOOL &st_lv_BIT_02, CIEC_BOOL &st_lv_BIT_03, CIEC_BOOL &st_lv_BIT_04, CIEC_BOOL &st_lv_BIT_05, CIEC_BOOL &st_lv_BIT_06, CIEC_BOOL &st_lv_BIT_07, CIEC_BOOL &st_lv_BIT_08, CIEC_BOOL &st_lv_BIT_09, CIEC_BOOL &st_lv_BIT_10, CIEC_BOOL &st_lv_BIT_11, CIEC_BOOL &st_lv_BIT_12, CIEC_BOOL &st_lv_BIT_13, CIEC_BOOL &st_lv_BIT_14, CIEC_BOOL &st_lv_BIT_15, CIEC_BOOL &st_lv_BIT_16, CIEC_BOOL &st_lv_BIT_17, CIEC_BOOL &st_lv_BIT_18, CIEC_BOOL &st_lv_BIT_19, CIEC_BOOL &st_lv_BIT_20, CIEC_BOOL &st_lv_BIT_21, CIEC_BOOL &st_lv_BIT_22, CIEC_BOOL &st_lv_BIT_23, CIEC_BOOL &st_lv_BIT_24, CIEC_BOOL &st_lv_BIT_25, CIEC_BOOL &st_lv_BIT_26, CIEC_BOOL &st_lv_BIT_27, CIEC_BOOL &st_lv_BIT_28, CIEC_BOOL &st_lv_BIT_29, CIEC_BOOL &st_lv_BIT_30, CIEC_BOOL &st_lv_BIT_31, CIEC_BOOL &st_lv_BIT_32, CIEC_BOOL &st_lv_BIT_33, CIEC_BOOL &st_lv_BIT_34, CIEC_BOOL &st_lv_BIT_35, CIEC_BOOL &st_lv_BIT_36, CIEC_BOOL &st_lv_BIT_37, CIEC_BOOL &st_lv_BIT_38, CIEC_BOOL &st_lv_BIT_39, CIEC_BOOL &st_lv_BIT_40, CIEC_BOOL &st_lv_BIT_41, CIEC_BOOL &st_lv_BIT_42, CIEC_BOOL &st_lv_BIT_43, CIEC_BOOL &st_lv_BIT_44, CIEC_BOOL &st_lv_BIT_45, CIEC_BOOL &st_lv_BIT_46, CIEC_BOOL &st_lv_BIT_47, CIEC_BOOL &st_lv_BIT_48, CIEC_BOOL &st_lv_BIT_49, CIEC_BOOL &st_lv_BIT_50, CIEC_BOOL &st_lv_BIT_51, CIEC_BOOL &st_lv_BIT_52, CIEC_BOOL &st_lv_BIT_53, CIEC_BOOL &st_lv_BIT_54, CIEC_BOOL &st_lv_BIT_55, CIEC_BOOL &st_lv_BIT_56, CIEC_BOOL &st_lv_BIT_57, CIEC_BOOL &st_lv_BIT_58, CIEC_BOOL &st_lv_BIT_59, CIEC_BOOL &st_lv_BIT_60, CIEC_BOOL &st_lv_BIT_61, CIEC_BOOL &st_lv_BIT_62, CIEC_BOOL &st_lv_BIT_63);


