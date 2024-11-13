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
 *   Michael Gafert - converted to new FB style
 *******************************************************************************/

#pragma once

#include "EplWrapper.h"

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_string.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_POWERLINK_MN final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_POWERLINK_MN)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventINITID = 0;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];
    static const TEventID scmEventINITOID = 0;
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
    FORTE_POWERLINK_MN(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BOOL var_QI;
    CIEC_STRING var_CDC_CFG;
    CIEC_STRING var_APP_CFG;
    CIEC_STRING var_DEV_NAME;

    CIEC_BOOL var_QO;
    CIEC_STRING var_STATUS;

    CIEC_BOOL var_conn_QO;
    CIEC_STRING var_conn_STATUS;

    CEventConnection conn_INITO;

    CDataConnection *conn_QI;
    CDataConnection *conn_CDC_CFG;
    CDataConnection *conn_APP_CFG;
    CDataConnection *conn_DEV_NAME;

    CDataConnection conn_QO;
    CDataConnection conn_STATUS;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_INIT(const CIEC_BOOL &paQI, const CIEC_STRING &paCDC_CFG, const CIEC_STRING &paAPP_CFG, const CIEC_STRING &paDEV_NAME, CIEC_BOOL &paQO, CIEC_STRING &paSTATUS) {
      var_QI = paQI;
      var_CDC_CFG = paCDC_CFG;
      var_APP_CFG = paAPP_CFG;
      var_DEV_NAME = paDEV_NAME;
      executeEvent(scmEventINITID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
    }

    void operator()(const CIEC_BOOL &paQI, const CIEC_STRING &paCDC_CFG, const CIEC_STRING &paAPP_CFG, const CIEC_STRING &paDEV_NAME, CIEC_BOOL &paQO, CIEC_STRING &paSTATUS) {
      evt_INIT(paQI, paCDC_CFG, paAPP_CFG, paDEV_NAME, paQO, paSTATUS);
    }
};


