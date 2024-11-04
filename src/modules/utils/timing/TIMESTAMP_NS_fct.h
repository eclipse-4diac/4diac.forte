/*************************************************************************
 * Copyright (c) 2024
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * This file was generated using the 4DIAC FORTE Export Filter
 *
 * Name: TIMESTAMP_NS
 * Description: creates default a Unix-Epoch-Timestamp in nanoseconds use other start dates for other timestamp types
 * Version:
 *     1.0: 2024-10-14/Monika Wenger - initial commit -
 *************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_date_and_time.h"
#include "forte_ulint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

class FORTE_TIMESTAMP_NS final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_TIMESTAMP_NS)

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
    FORTE_TIMESTAMP_NS(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_DATE_AND_TIME var_startDate;

    CIEC_ULINT var_;

    CIEC_ULINT var_conn_;

    CEventConnection conn_CNF;

    CDataConnection *conn_startDate;

    CDataConnection conn_;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_REQ(const CIEC_DATE_AND_TIME &pastartDate) {
      var_startDate = pastartDate;
      executeEvent(scmEventREQID, nullptr);
    }

    void operator()(const CIEC_DATE_AND_TIME &pastartDate) {
      evt_REQ(pastartDate);
    }
};

CIEC_ULINT func_TIMESTAMP_NS(CIEC_DATE_AND_TIME st_lv_startDate);

