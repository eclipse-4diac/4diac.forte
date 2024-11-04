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
 *** Name: E_TONOF
 *** Description: standard timer function block (on/off-delay timing)
 *** Version:
 ***     1.0: 2024-03-04/Franz Hoepfinger - HR Agrartechnik GmbH -
 ***     1.1: 2024-04-23/Franz Hoepfinger - HR Agrartechnik GmbH - Add a Reset to Timer FBs
 *************************************************************************/

#pragma once

#include "cfb.h"
#include "typelib.h"
#include "forte_bool.h"
#include "forte_time.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "E_SWITCH_fbt.h"
#include "E_DELAY_fbt.h"
#include "E_RS_fbt.h"


class FORTE_E_TONOF final : public CCompositeFB {
  DECLARE_FIRMWARE_FB(FORTE_E_TONOF)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventREQID = 0;
    static const TEventID scmEventRID = 1;
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

    static const SCFB_FBInstanceData scmInternalFBs[];
    static const SCFB_FBParameter scmParamters[];
    static const SCFB_FBConnectionData scmEventConnections[];
    static const SCFB_FBFannedOutConnectionData scmFannedOutEventConnections[];
    static const SCFB_FBConnectionData scmDataConnections[];
    static const SCFB_FBFannedOutConnectionData scmFannedOutDataConnections[];
    static const SCFB_FBNData scmFBNData;

    forte::core::CInternalFB<FORTE_E_SWITCH> fb_E_SWITCH;
    forte::core::CInternalFB<FORTE_E_DELAY> fb_E_DELAY_ON;
    forte::core::CInternalFB<FORTE_E_RS> fb_E_RS;
    forte::core::CInternalFB<FORTE_E_DELAY> fb_E_DELAY_OFF;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void readInternal2InterfaceOutputData(TEventID paEOID) override;
    void setInitialValues() override;

  public:
    FORTE_E_TONOF(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BOOL var_IN;
    CIEC_TIME var_PT_ON;
    CIEC_TIME var_PT_OFF;

    CIEC_BOOL var_Q;

    CIEC_BOOL var_conn_Q;

    CEventConnection conn_CNF;

    CDataConnection *conn_IN;
    CDataConnection *conn_PT_ON;
    CDataConnection *conn_PT_OFF;

    CDataConnection conn_Q;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_REQ(const CIEC_BOOL &paIN, const CIEC_TIME &paPT_ON, const CIEC_TIME &paPT_OFF, CIEC_BOOL &paQ) {
      var_IN = paIN;
      var_PT_ON = paPT_ON;
      var_PT_OFF = paPT_OFF;
      executeEvent(scmEventREQID, nullptr);
      paQ = var_Q;
    }

    void evt_R(const CIEC_BOOL &paIN, const CIEC_TIME &paPT_ON, const CIEC_TIME &paPT_OFF, CIEC_BOOL &paQ) {
      var_IN = paIN;
      var_PT_ON = paPT_ON;
      var_PT_OFF = paPT_OFF;
      executeEvent(scmEventRID, nullptr);
      paQ = var_Q;
    }

    void operator()(const CIEC_BOOL &paIN, const CIEC_TIME &paPT_ON, const CIEC_TIME &paPT_OFF, CIEC_BOOL &paQ) {
      evt_REQ(paIN, paPT_ON, paPT_OFF, paQ);
    }
};


