/*************************************************************************  
 *** Copyright (c) 2017, 2024 fortiss GmbH, JKU, HR Agrartechnik GmbH  
 *** This program and the accompanying materials are made available under the  
 *** terms of the Eclipse Public License 2.0 which is available at  
 *** http://www.eclipse.org/legal/epl-2.0.  
 ***  
 *** SPDX-License-Identifier: EPL-2.0  
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: E_CTUD_UDINT
 *** Description: Event-Driven Up-Down Counter
 *** Version:
 ***     1.0: 2017-09-22/Alois Zoitl - fortiss GmbH - initial API and implementation and/or initial documentation (E_CTUD)
 ***     1.1: 2019-07-09/Alois Zoitl - JKU - fixed bug in down counting (E_CTUD)
 ***     1.2: 2024-02-10/Franz Hoepfinger - HR Agrartechnik GmbH - Copy over E_CTUD to E_CTUD_UDINT
 *************************************************************************/

#pragma once

#include "basicfb.h"
#include "forte_udint.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_E_CTUD_UDINT final : public CBasicFB {
  DECLARE_FIRMWARE_FB(FORTE_E_CTUD_UDINT)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventCUID = 0;
    static const TEventID scmEventCDID = 1;
    static const TEventID scmEventRID = 2;
    static const TEventID scmEventLDID = 3;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];
    static const TEventID scmEventCOID = 0;
    static const TEventID scmEventROID = 1;
    static const TEventID scmEventLDOID = 2;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    CIEC_ANY *getVarInternal(size_t) override;

    void alg_CountUp(void);
    void alg_Reset(void);
    void alg_Load(void);
    void alg_UpdateQUQD(void);
    void alg_CountDown(void);

    static const TForteInt16 scmStateSTART = 0;
    static const TForteInt16 scmStateCU = 1;
    static const TForteInt16 scmStateR = 2;
    static const TForteInt16 scmStateCD = 3;
    static const TForteInt16 scmStateLD = 4;

    void enterStateSTART(CEventChainExecutionThread *const paECET);
    void enterStateCU(CEventChainExecutionThread *const paECET);
    void enterStateR(CEventChainExecutionThread *const paECET);
    void enterStateCD(CEventChainExecutionThread *const paECET);
    void enterStateLD(CEventChainExecutionThread *const paECET);

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

  public:
    FORTE_E_CTUD_UDINT(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_UDINT var_PV;

    CIEC_BOOL var_QU;
    CIEC_BOOL var_QD;
    CIEC_UDINT var_CV;

    CIEC_BOOL var_conn_QU;
    CIEC_BOOL var_conn_QD;
    CIEC_UDINT var_conn_CV;

    CEventConnection conn_CO;
    CEventConnection conn_RO;
    CEventConnection conn_LDO;

    CDataConnection *conn_PV;

    CDataConnection conn_QU;
    CDataConnection conn_QD;
    CDataConnection conn_CV;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_CU(const CIEC_UDINT &paPV, CIEC_BOOL &paQU, CIEC_BOOL &paQD, CIEC_UDINT &paCV) {
      var_PV = paPV;
      executeEvent(scmEventCUID, nullptr);
      paQU = var_QU;
      paQD = var_QD;
      paCV = var_CV;
    }

    void evt_CD(const CIEC_UDINT &paPV, CIEC_BOOL &paQU, CIEC_BOOL &paQD, CIEC_UDINT &paCV) {
      var_PV = paPV;
      executeEvent(scmEventCDID, nullptr);
      paQU = var_QU;
      paQD = var_QD;
      paCV = var_CV;
    }

    void evt_R(const CIEC_UDINT &paPV, CIEC_BOOL &paQU, CIEC_BOOL &paQD, CIEC_UDINT &paCV) {
      var_PV = paPV;
      executeEvent(scmEventRID, nullptr);
      paQU = var_QU;
      paQD = var_QD;
      paCV = var_CV;
    }

    void evt_LD(const CIEC_UDINT &paPV, CIEC_BOOL &paQU, CIEC_BOOL &paQD, CIEC_UDINT &paCV) {
      var_PV = paPV;
      executeEvent(scmEventLDID, nullptr);
      paQU = var_QU;
      paQD = var_QD;
      paCV = var_CV;
    }

    void operator()(const CIEC_UDINT &paPV, CIEC_BOOL &paQU, CIEC_BOOL &paQD, CIEC_UDINT &paCV) {
      evt_CU(paPV, paQU, paQD, paCV);
    }
};


