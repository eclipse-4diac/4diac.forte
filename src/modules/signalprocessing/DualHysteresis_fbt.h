/*************************************************************************  
 *** Copyright (c) 2023 HR Agrartechnik GmbH  
 *** This program and the accompanying materials are made available under the  
 *** terms of the Eclipse Public License 2.0 which is available at  
 *** http://www.eclipse.org/legal/epl-2.0.  
 ***  
 *** SPDX-License-Identifier: EPL-2.0  
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: DualHysteresis
 *** Description: 2-way conversion of Analog to Digital with Hysteresis
 *** Version:
 ***     1.0: 2023-06-06/Franz Höpfinger - HR Agrartechnik GmbH -
 *************************************************************************/

#pragma once

#include "basicfb.h"
#include "forte_bool.h"
#include "forte_real.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

class FORTE_signalprocessing__DualHysteresis final : public CBasicFB {
  DECLARE_FIRMWARE_FB(FORTE_signalprocessing__DualHysteresis)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventINITID = 0;
    static const TEventID scmEventREQID = 1;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];
    static const TEventID scmEventINITOID = 0;
    static const TEventID scmEventCNFID = 1;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    CIEC_ANY *getVarInternal(size_t) override;

    void alg_initialize(void);
    void alg_deInitialize(void);
    void alg_alNeutral(void);
    void alg_alUp(void);
    void alg_alDown(void);

    static const TForteInt16 scmStateSTART = 0;
    static const TForteInt16 scmStateInit = 1;
    static const TForteInt16 scmStateUP = 2;
    static const TForteInt16 scmStateNeutral = 3;
    static const TForteInt16 scmStateDeInit = 4;
    static const TForteInt16 scmStateDOWN = 5;

    void enterStateSTART(CEventChainExecutionThread *const paECET);
    void enterStateInit(CEventChainExecutionThread *const paECET);
    void enterStateUP(CEventChainExecutionThread *const paECET);
    void enterStateNeutral(CEventChainExecutionThread *const paECET);
    void enterStateDeInit(CEventChainExecutionThread *const paECET);
    void enterStateDOWN(CEventChainExecutionThread *const paECET);

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

  public:
    FORTE_signalprocessing__DualHysteresis(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BOOL var_QI;
    CIEC_REAL var_MI;
    CIEC_REAL var_DEAD;
    CIEC_REAL var_HYSTERESIS;
    CIEC_REAL var_INPUT;

    CIEC_BOOL var_QO;
    CIEC_BOOL var_DO_UP;
    CIEC_BOOL var_DO_DOWN;

    CIEC_BOOL var_conn_QO;
    CIEC_BOOL var_conn_DO_UP;
    CIEC_BOOL var_conn_DO_DOWN;

    CEventConnection conn_INITO;
    CEventConnection conn_CNF;

    CDataConnection *conn_QI;
    CDataConnection *conn_MI;
    CDataConnection *conn_DEAD;
    CDataConnection *conn_HYSTERESIS;
    CDataConnection *conn_INPUT;

    CDataConnection conn_QO;
    CDataConnection conn_DO_UP;
    CDataConnection conn_DO_DOWN;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_INIT(const CIEC_BOOL &paQI, const CIEC_REAL &paMI, const CIEC_REAL &paDEAD, const CIEC_REAL &paHYSTERESIS, const CIEC_REAL &paINPUT, CIEC_BOOL &paQO, CIEC_BOOL &paDO_UP, CIEC_BOOL &paDO_DOWN) {
      var_QI = paQI;
      var_MI = paMI;
      var_DEAD = paDEAD;
      var_HYSTERESIS = paHYSTERESIS;
      var_INPUT = paINPUT;
      executeEvent(scmEventINITID, nullptr);
      paQO = var_QO;
      paDO_UP = var_DO_UP;
      paDO_DOWN = var_DO_DOWN;
    }

    void evt_REQ(const CIEC_BOOL &paQI, const CIEC_REAL &paMI, const CIEC_REAL &paDEAD, const CIEC_REAL &paHYSTERESIS, const CIEC_REAL &paINPUT, CIEC_BOOL &paQO, CIEC_BOOL &paDO_UP, CIEC_BOOL &paDO_DOWN) {
      var_QI = paQI;
      var_MI = paMI;
      var_DEAD = paDEAD;
      var_HYSTERESIS = paHYSTERESIS;
      var_INPUT = paINPUT;
      executeEvent(scmEventREQID, nullptr);
      paQO = var_QO;
      paDO_UP = var_DO_UP;
      paDO_DOWN = var_DO_DOWN;
    }

    void operator()(const CIEC_BOOL &paQI, const CIEC_REAL &paMI, const CIEC_REAL &paDEAD, const CIEC_REAL &paHYSTERESIS, const CIEC_REAL &paINPUT, CIEC_BOOL &paQO, CIEC_BOOL &paDO_UP, CIEC_BOOL &paDO_DOWN) {
      evt_INIT(paQI, paMI, paDEAD, paHYSTERESIS, paINPUT, paQO, paDO_UP, paDO_DOWN);
    }
};

