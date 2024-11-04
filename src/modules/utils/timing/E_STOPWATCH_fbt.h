/*******************************************************************************
 * Copyright (c) 2018, 2024 fortiss GmbH, Johannes Kepler University Linz, HR Agrartechnik GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0

 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: E_STOPWATCH
 *** Description: FB for stopping time between events
 *** Version:
 ***     1.0: 2018-08-29/Ben Schneider - fortiss GmbH - initial API and implementation and/or initial documentation
 ***     1.1: 2020-05-24/alois Zoitl - Johannes Kepler University Linz - Changed to a full basic FB implementation utilizing the new NOW_MONOTONIC function
 ***     1.2: 2024-09-19/Franz Höpfinger - HR Agrartechnik GmbH - Added additional Events
 *************************************************************************/

#pragma once

#include "basicfb.h"
#include "forte_time.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

class FORTE_E_STOPWATCH final : public CBasicFB {
  DECLARE_FIRMWARE_FB(FORTE_E_STOPWATCH)

  private:
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventSTARTID = 0;
    static const TEventID scmEventETID = 1;
    static const TEventID scmEventSTOPID = 2;
    static const TEventID scmEventRESETID = 3;
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];
    static const TEventID scmEventEOID = 0;
    static const TEventID scmEventETOID = 1;
    static const TEventID scmEventRESETOID = 2;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    static const CStringDictionary::TStringId scmInternalsNames[];
    static const CStringDictionary::TStringId scmInternalsTypeIds[];
    static const SInternalVarsInformation scmInternalVars;

    CIEC_TIME var_startTime;

    CIEC_ANY *getVarInternal(size_t) override;

    void alg_captureStartTime(void);
    void alg_calcDiff(void);
    void alg_reset(void);

    static const TForteInt16 scmStateSTART = 0;
    static const TForteInt16 scmStateMeasure = 1;
    static const TForteInt16 scmStateSTOP = 2;
    static const TForteInt16 scmStateTrig = 3;
    static const TForteInt16 scmStateRESET = 4;

    void enterStateSTART(CEventChainExecutionThread *const paECET);
    void enterStateMeasure(CEventChainExecutionThread *const paECET);
    void enterStateSTOP(CEventChainExecutionThread *const paECET);
    void enterStateTrig(CEventChainExecutionThread *const paECET);
    void enterStateRESET(CEventChainExecutionThread *const paECET);

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

  public:
    FORTE_E_STOPWATCH(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_TIME var_TD;

    CIEC_TIME var_conn_TD;

    CEventConnection conn_EO;
    CEventConnection conn_ETO;
    CEventConnection conn_RESETO;

    CDataConnection conn_TD;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_START(CIEC_TIME &paTD) {
      executeEvent(scmEventSTARTID, nullptr);
      paTD = var_TD;
    }

    void evt_ET(CIEC_TIME &paTD) {
      executeEvent(scmEventETID, nullptr);
      paTD = var_TD;
    }

    void evt_STOP(CIEC_TIME &paTD) {
      executeEvent(scmEventSTOPID, nullptr);
      paTD = var_TD;
    }

    void evt_RESET(CIEC_TIME &paTD) {
      executeEvent(scmEventRESETID, nullptr);
      paTD = var_TD;
    }

    void operator()(CIEC_TIME &paTD) {
      evt_START(paTD);
    }
};

