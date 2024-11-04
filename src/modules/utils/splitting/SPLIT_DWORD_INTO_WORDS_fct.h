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
 *** Name: SPLIT_DWORD_INTO_WORDS
 *** Description: this Function extracts the 2 WORD from a dword
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-24/Moritz Ortmeier - HR Agrartechnik - rename Function and change Output Variables
 *************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_dword.h"
#include "forte_word.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

class FORTE_SPLIT_DWORD_INTO_WORDS final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_SPLIT_DWORD_INTO_WORDS)

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
    FORTE_SPLIT_DWORD_INTO_WORDS(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_DWORD var_IN;

    CIEC_WORD var_WORD_00;
    CIEC_WORD var_WORD_01;

    CIEC_WORD var_conn_WORD_00;
    CIEC_WORD var_conn_WORD_01;

    CEventConnection conn_CNF;

    CDataConnection *conn_IN;

    CDataConnection conn_WORD_00;
    CDataConnection conn_WORD_01;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_REQ(const CIEC_DWORD &paIN, CIEC_WORD &paWORD_00, CIEC_WORD &paWORD_01) {
      var_IN = paIN;
      executeEvent(scmEventREQID, nullptr);
      paWORD_00 = var_WORD_00;
      paWORD_01 = var_WORD_01;
    }

    void operator()(const CIEC_DWORD &paIN, CIEC_WORD &paWORD_00, CIEC_WORD &paWORD_01) {
      evt_REQ(paIN, paWORD_00, paWORD_01);
    }
};

void func_SPLIT_DWORD_INTO_WORDS(CIEC_DWORD st_lv_IN, CIEC_WORD &st_lv_WORD_00, CIEC_WORD &st_lv_WORD_01);


