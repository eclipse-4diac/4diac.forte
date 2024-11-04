/*******************************************************************************
 * Copyright (c) 2013 fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - initial API and implementation and/or initial documentation
 *******************************************************************************/

#pragma once

#include "basicfb.h"
#include "forte_uint.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_E_CTUD final : public CBasicFB {
  DECLARE_FIRMWARE_FB(FORTE_E_CTUD)

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
  FORTE_E_CTUD(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_UINT var_PV;

  CIEC_BOOL var_QU;
  CIEC_BOOL var_QD;
  CIEC_UINT var_CV;

  CIEC_BOOL var_conn_QU;
  CIEC_BOOL var_conn_QD;
  CIEC_UINT var_conn_CV;

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

  void evt_CU(const CIEC_UINT &paPV, CIEC_BOOL &paQU, CIEC_BOOL &paQD, CIEC_UINT &paCV) {
    var_PV = paPV;
    receiveInputEvent(scmEventCUID, nullptr);
    paQU = var_QU;
    paQD = var_QD;
    paCV = var_CV;
  }

  void evt_CD(const CIEC_UINT &paPV, CIEC_BOOL &paQU, CIEC_BOOL &paQD, CIEC_UINT &paCV) {
    var_PV = paPV;
    receiveInputEvent(scmEventCDID, nullptr);
    paQU = var_QU;
    paQD = var_QD;
    paCV = var_CV;
  }

  void evt_R(const CIEC_UINT &paPV, CIEC_BOOL &paQU, CIEC_BOOL &paQD, CIEC_UINT &paCV) {
    var_PV = paPV;
    receiveInputEvent(scmEventRID, nullptr);
    paQU = var_QU;
    paQD = var_QD;
    paCV = var_CV;
  }

  void evt_LD(const CIEC_UINT &paPV, CIEC_BOOL &paQU, CIEC_BOOL &paQD, CIEC_UINT &paCV) {
    var_PV = paPV;
    receiveInputEvent(scmEventLDID, nullptr);
    paQU = var_QU;
    paQD = var_QD;
    paCV = var_CV;
  }

  void operator()(const CIEC_UINT &paPV, CIEC_BOOL &paQU, CIEC_BOOL &paQD, CIEC_UINT &paCV) {
    evt_CU(paPV, paQU, paQD, paCV);
  }
};


