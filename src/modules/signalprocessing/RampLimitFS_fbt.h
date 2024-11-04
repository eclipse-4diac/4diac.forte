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
 *** Name: RampLimitFS
 *** Description: Setpoint Ramp: Step up and down Values with Fast and Slow mode
 *** Version:
 ***     1.0: 2024-09-20/Franz Höpfinger - HR Agrartechnik GmbH -
 ***     1.1: 2024-10-02/Franz Höpfinger - HR Agrartechnik GmbH - Rename to RampLimitFS
 *************************************************************************/

#pragma once

#include "simplefb.h"
#include "forte_dint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

class FORTE_signalprocessing__RampLimitFS final : public CSimpleFB {
  DECLARE_FIRMWARE_FB(FORTE_signalprocessing__RampLimitFS)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventZEROID = 0;
    static const TEventID scmEventUP_SLOWID = 1;
    static const TEventID scmEventUP_FASTID = 2;
    static const TEventID scmEventDOWN_SLOWID = 3;
    static const TEventID scmEventDOWN_FASTID = 4;
    static const TEventID scmEventFULLID = 5;
    static const TEventID scmEventLOADID = 6;
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

    CIEC_ANY *getVarInternal(size_t) override;

    void alg_ZERO(void);
    void alg_UP_SLOW(void);
    void alg_UP_FAST(void);
    void alg_DOWN_SLOW(void);
    void alg_DOWN_FAST(void);
    void alg_FULL(void);
    void alg_LOAD(void);

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

  public:
    FORTE_signalprocessing__RampLimitFS(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_DINT var_PV;
    CIEC_DINT var_VAL_ZERO;
    CIEC_DINT var_SLOW;
    CIEC_DINT var_FAST;
    CIEC_DINT var_VAL_FULL;

    CIEC_DINT var_OUT;

    CIEC_DINT var_conn_OUT;

    CEventConnection conn_CNF;

    CDataConnection *conn_PV;
    CDataConnection *conn_VAL_ZERO;
    CDataConnection *conn_SLOW;
    CDataConnection *conn_FAST;
    CDataConnection *conn_VAL_FULL;

    CDataConnection conn_OUT;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_ZERO(const CIEC_DINT &paPV, const CIEC_DINT &paVAL_ZERO, const CIEC_DINT &paSLOW, const CIEC_DINT &paFAST, const CIEC_DINT &paVAL_FULL, CIEC_DINT &paOUT) {
      var_PV = paPV;
      var_VAL_ZERO = paVAL_ZERO;
      var_SLOW = paSLOW;
      var_FAST = paFAST;
      var_VAL_FULL = paVAL_FULL;
      executeEvent(scmEventZEROID, nullptr);
      paOUT = var_OUT;
    }

    void evt_UP_SLOW(const CIEC_DINT &paPV, const CIEC_DINT &paVAL_ZERO, const CIEC_DINT &paSLOW, const CIEC_DINT &paFAST, const CIEC_DINT &paVAL_FULL, CIEC_DINT &paOUT) {
      var_PV = paPV;
      var_VAL_ZERO = paVAL_ZERO;
      var_SLOW = paSLOW;
      var_FAST = paFAST;
      var_VAL_FULL = paVAL_FULL;
      executeEvent(scmEventUP_SLOWID, nullptr);
      paOUT = var_OUT;
    }

    void evt_UP_FAST(const CIEC_DINT &paPV, const CIEC_DINT &paVAL_ZERO, const CIEC_DINT &paSLOW, const CIEC_DINT &paFAST, const CIEC_DINT &paVAL_FULL, CIEC_DINT &paOUT) {
      var_PV = paPV;
      var_VAL_ZERO = paVAL_ZERO;
      var_SLOW = paSLOW;
      var_FAST = paFAST;
      var_VAL_FULL = paVAL_FULL;
      executeEvent(scmEventUP_FASTID, nullptr);
      paOUT = var_OUT;
    }

    void evt_DOWN_SLOW(const CIEC_DINT &paPV, const CIEC_DINT &paVAL_ZERO, const CIEC_DINT &paSLOW, const CIEC_DINT &paFAST, const CIEC_DINT &paVAL_FULL, CIEC_DINT &paOUT) {
      var_PV = paPV;
      var_VAL_ZERO = paVAL_ZERO;
      var_SLOW = paSLOW;
      var_FAST = paFAST;
      var_VAL_FULL = paVAL_FULL;
      executeEvent(scmEventDOWN_SLOWID, nullptr);
      paOUT = var_OUT;
    }

    void evt_DOWN_FAST(const CIEC_DINT &paPV, const CIEC_DINT &paVAL_ZERO, const CIEC_DINT &paSLOW, const CIEC_DINT &paFAST, const CIEC_DINT &paVAL_FULL, CIEC_DINT &paOUT) {
      var_PV = paPV;
      var_VAL_ZERO = paVAL_ZERO;
      var_SLOW = paSLOW;
      var_FAST = paFAST;
      var_VAL_FULL = paVAL_FULL;
      executeEvent(scmEventDOWN_FASTID, nullptr);
      paOUT = var_OUT;
    }

    void evt_FULL(const CIEC_DINT &paPV, const CIEC_DINT &paVAL_ZERO, const CIEC_DINT &paSLOW, const CIEC_DINT &paFAST, const CIEC_DINT &paVAL_FULL, CIEC_DINT &paOUT) {
      var_PV = paPV;
      var_VAL_ZERO = paVAL_ZERO;
      var_SLOW = paSLOW;
      var_FAST = paFAST;
      var_VAL_FULL = paVAL_FULL;
      executeEvent(scmEventFULLID, nullptr);
      paOUT = var_OUT;
    }

    void evt_LOAD(const CIEC_DINT &paPV, const CIEC_DINT &paVAL_ZERO, const CIEC_DINT &paSLOW, const CIEC_DINT &paFAST, const CIEC_DINT &paVAL_FULL, CIEC_DINT &paOUT) {
      var_PV = paPV;
      var_VAL_ZERO = paVAL_ZERO;
      var_SLOW = paSLOW;
      var_FAST = paFAST;
      var_VAL_FULL = paVAL_FULL;
      executeEvent(scmEventLOADID, nullptr);
      paOUT = var_OUT;
    }

    void operator()(const CIEC_DINT &paPV, const CIEC_DINT &paVAL_ZERO, const CIEC_DINT &paSLOW, const CIEC_DINT &paFAST, const CIEC_DINT &paVAL_FULL, CIEC_DINT &paOUT) {
      evt_ZERO(paPV, paVAL_ZERO, paSLOW, paFAST, paVAL_FULL, paOUT);
    }
};

