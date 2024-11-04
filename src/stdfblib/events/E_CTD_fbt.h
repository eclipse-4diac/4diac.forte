/*******************************************************************************
 * Copyright (c) 2014 ACIN
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger - initial API and implementation and/or initial documentation
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


class FORTE_E_CTD final : public CBasicFB {
  DECLARE_FIRMWARE_FB(FORTE_E_CTD)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  static const TEventID scmEventCDID = 0;
  static const TEventID scmEventLDID = 1;
  static const TDataIOID scmEIWith[];
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];
  static const TEventID scmEventCDOID = 0;
  static const TEventID scmEventLDOID = 1;
  static const TDataIOID scmEOWith[];
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;

  CIEC_ANY *getVarInternal(size_t) override;

  void alg_CD(void);
  void alg_LOAD(void);

  static const TForteInt16 scmStateSTART = 0;
  static const TForteInt16 scmStateCD = 1;
  static const TForteInt16 scmStateLD = 2;

  void enterStateSTART(CEventChainExecutionThread *const paECET);
  void enterStateCD(CEventChainExecutionThread *const paECET);
  void enterStateLD(CEventChainExecutionThread *const paECET);

  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
  void setInitialValues() override;

public:
  FORTE_E_CTD(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_UINT var_PV;

  CIEC_BOOL var_Q;
  CIEC_UINT var_CV;

  CIEC_BOOL var_conn_Q;
  CIEC_UINT var_conn_CV;

  CEventConnection conn_CDO;
  CEventConnection conn_LDO;

  CDataConnection *conn_PV;

  CDataConnection conn_Q;
  CDataConnection conn_CV;

  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;

  void evt_CD(const CIEC_UINT &paPV, CIEC_BOOL &paQ, CIEC_UINT &paCV) {
    var_PV = paPV;
    receiveInputEvent(scmEventCDID, nullptr);
    paQ = var_Q;
    paCV = var_CV;
  }

  void evt_LD(const CIEC_UINT &paPV, CIEC_BOOL &paQ, CIEC_UINT &paCV) {
    var_PV = paPV;
    receiveInputEvent(scmEventLDID, nullptr);
    paQ = var_Q;
    paCV = var_CV;
  }

  void operator()(const CIEC_UINT &paPV, CIEC_BOOL &paQ, CIEC_UINT &paCV) {
    evt_CD(paPV, paQ, paCV);
  }
};


