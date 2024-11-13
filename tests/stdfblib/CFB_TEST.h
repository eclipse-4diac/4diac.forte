/*******************************************************************************
 * Copyright (c) 2014 fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl  - initial API and implementation and/or initial documentation
 *******************************************************************************/

#pragma once

#include "cfb.h"
#include "typelib.h"
#include "forte_bool.h"
#include "E_PERMIT_fbt.h"
#include "E_SR_fbt.h"
#include "E_SWITCH_fbt.h"
#include "GEN_E_DEMUX_fbt.h"
#include "GEN_E_MUX_fbt.h"


class FORTE_CFB_TEST final : public CCompositeFB {
  DECLARE_FIRMWARE_FB(FORTE_CFB_TEST)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventSETID = 0;
    static const TEventID scmEventRESETID = 1;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];
    static const TEventID scmEventCNFID = 0;
    static const TEventID scmEventCHANGEDID = 1;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;


    static const SCFB_FBInstanceData scmInternalFBs[];

    static const SCFB_FBConnectionData scmEventConnections[];

    static const SCFB_FBFannedOutConnectionData scmFannedOutEventConnections[];

    static const SCFB_FBConnectionData scmDataConnections[];

    static const SCFB_FBFannedOutConnectionData scmFannedOutDataConnections[];
    static const SCFB_FBNData scmFBNData;

    forte::core::CInternalFB<FORTE_E_PERMIT> fb_PERMIT_OP;
    forte::core::CInternalFB<FORTE_E_SR> fb_E_SR;
    forte::core::CInternalFB<FORTE_E_SWITCH> fb_SET_CHANGED;
    forte::core::CInternalFB<GEN_E_DEMUX> fb_E_DEMUX_2;
    forte::core::CInternalFB<GEN_E_MUX> fb_E_MUX_2;
    forte::core::CInternalFB<FORTE_E_SWITCH> fb_RESET_CHANGED;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void readInternal2InterfaceOutputData(TEventID paEOID) override;
    void setInitialValues() override;

  public:
    FORTE_CFB_TEST(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BOOL var_QI;

    CIEC_BOOL var_QO;

    CIEC_BOOL var_conn_QO;

    CEventConnection conn_CNF;
    CEventConnection conn_CHANGED;

    CDataConnection *conn_QI;

    CDataConnection conn_QO;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_SET(const CIEC_BOOL &paQI, CIEC_BOOL &paQO) {
      var_QI = paQI;
      executeEvent(scmEventSETID, nullptr);
      paQO = var_QO;
    }

    void evt_RESET(const CIEC_BOOL &paQI, CIEC_BOOL &paQO) {
      var_QI = paQI;
      executeEvent(scmEventRESETID, nullptr);
      paQO = var_QO;
    }

    void operator()(const CIEC_BOOL &paQI, CIEC_BOOL &paQO) {
      evt_SET(paQI, paQO);
    }
};


