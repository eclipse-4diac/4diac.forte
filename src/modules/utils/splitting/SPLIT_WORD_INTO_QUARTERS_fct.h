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
 *** Name: SPLIT_WORD_INTO_QUARTERS
 *** Description: this Function extracts the 8 QUARTER BYTE from a word
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-24/Moritz Ortmeier - HR Agrartechnik - rename Function and change Output Variables
 *************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_byte.h"
#include "forte_word.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

class FORTE_SPLIT_WORD_INTO_QUARTERS final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_SPLIT_WORD_INTO_QUARTERS)

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
    FORTE_SPLIT_WORD_INTO_QUARTERS(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_WORD var_IN;

    CIEC_BYTE var_QUARTER_BYTE_00;
    CIEC_BYTE var_QUARTER_BYTE_01;
    CIEC_BYTE var_QUARTER_BYTE_02;
    CIEC_BYTE var_QUARTER_BYTE_03;
    CIEC_BYTE var_QUARTER_BYTE_04;
    CIEC_BYTE var_QUARTER_BYTE_05;
    CIEC_BYTE var_QUARTER_BYTE_06;
    CIEC_BYTE var_QUARTER_BYTE_07;

    CIEC_BYTE var_conn_QUARTER_BYTE_00;
    CIEC_BYTE var_conn_QUARTER_BYTE_01;
    CIEC_BYTE var_conn_QUARTER_BYTE_02;
    CIEC_BYTE var_conn_QUARTER_BYTE_03;
    CIEC_BYTE var_conn_QUARTER_BYTE_04;
    CIEC_BYTE var_conn_QUARTER_BYTE_05;
    CIEC_BYTE var_conn_QUARTER_BYTE_06;
    CIEC_BYTE var_conn_QUARTER_BYTE_07;

    CEventConnection conn_CNF;

    CDataConnection *conn_IN;

    CDataConnection conn_QUARTER_BYTE_00;
    CDataConnection conn_QUARTER_BYTE_01;
    CDataConnection conn_QUARTER_BYTE_02;
    CDataConnection conn_QUARTER_BYTE_03;
    CDataConnection conn_QUARTER_BYTE_04;
    CDataConnection conn_QUARTER_BYTE_05;
    CDataConnection conn_QUARTER_BYTE_06;
    CDataConnection conn_QUARTER_BYTE_07;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_REQ(const CIEC_WORD &paIN, CIEC_BYTE &paQUARTER_BYTE_00, CIEC_BYTE &paQUARTER_BYTE_01, CIEC_BYTE &paQUARTER_BYTE_02, CIEC_BYTE &paQUARTER_BYTE_03, CIEC_BYTE &paQUARTER_BYTE_04, CIEC_BYTE &paQUARTER_BYTE_05, CIEC_BYTE &paQUARTER_BYTE_06, CIEC_BYTE &paQUARTER_BYTE_07) {
      var_IN = paIN;
      executeEvent(scmEventREQID, nullptr);
      paQUARTER_BYTE_00 = var_QUARTER_BYTE_00;
      paQUARTER_BYTE_01 = var_QUARTER_BYTE_01;
      paQUARTER_BYTE_02 = var_QUARTER_BYTE_02;
      paQUARTER_BYTE_03 = var_QUARTER_BYTE_03;
      paQUARTER_BYTE_04 = var_QUARTER_BYTE_04;
      paQUARTER_BYTE_05 = var_QUARTER_BYTE_05;
      paQUARTER_BYTE_06 = var_QUARTER_BYTE_06;
      paQUARTER_BYTE_07 = var_QUARTER_BYTE_07;
    }

    void operator()(const CIEC_WORD &paIN, CIEC_BYTE &paQUARTER_BYTE_00, CIEC_BYTE &paQUARTER_BYTE_01, CIEC_BYTE &paQUARTER_BYTE_02, CIEC_BYTE &paQUARTER_BYTE_03, CIEC_BYTE &paQUARTER_BYTE_04, CIEC_BYTE &paQUARTER_BYTE_05, CIEC_BYTE &paQUARTER_BYTE_06, CIEC_BYTE &paQUARTER_BYTE_07) {
      evt_REQ(paIN, paQUARTER_BYTE_00, paQUARTER_BYTE_01, paQUARTER_BYTE_02, paQUARTER_BYTE_03, paQUARTER_BYTE_04, paQUARTER_BYTE_05, paQUARTER_BYTE_06, paQUARTER_BYTE_07);
    }
};

void func_SPLIT_WORD_INTO_QUARTERS(CIEC_WORD st_lv_IN, CIEC_BYTE &st_lv_QUARTER_BYTE_00, CIEC_BYTE &st_lv_QUARTER_BYTE_01, CIEC_BYTE &st_lv_QUARTER_BYTE_02, CIEC_BYTE &st_lv_QUARTER_BYTE_03, CIEC_BYTE &st_lv_QUARTER_BYTE_04, CIEC_BYTE &st_lv_QUARTER_BYTE_05, CIEC_BYTE &st_lv_QUARTER_BYTE_06, CIEC_BYTE &st_lv_QUARTER_BYTE_07);


