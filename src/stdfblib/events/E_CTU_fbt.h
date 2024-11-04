/*******************************************************************************
 * Copyright (c) 2006 - 2011 ACIN, Profactor GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer
 *     - initial API and implementation and/or initial documentation
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


class FORTE_E_CTU final : public CBasicFB {
  DECLARE_FIRMWARE_FB(FORTE_E_CTU)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  static const TEventID scmEventCUID = 0;
  static const TEventID scmEventRID = 1;
  static const TDataIOID scmEIWith[];
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];
  static const TEventID scmEventCUOID = 0;
  static const TEventID scmEventROID = 1;
  static const TDataIOID scmEOWith[];
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;

  CIEC_ANY *getVarInternal(size_t) override;

  void alg_R(void);
  void alg_CU(void);

  static const TForteInt16 scmStateSTART = 0;
  static const TForteInt16 scmStateCU = 1;
  static const TForteInt16 scmStateR = 2;

  void enterStateSTART(CEventChainExecutionThread *const paECET);
  void enterStateCU(CEventChainExecutionThread *const paECET);
  void enterStateR(CEventChainExecutionThread *const paECET);

  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
  void setInitialValues() override;

public:
  FORTE_E_CTU(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_UINT var_PV;

  CIEC_BOOL var_Q;
  CIEC_UINT var_CV;

  CIEC_BOOL var_conn_Q;
  CIEC_UINT var_conn_CV;

  CEventConnection conn_CUO;
  CEventConnection conn_RO;

  CDataConnection *conn_PV;

  CDataConnection conn_Q;
  CDataConnection conn_CV;

  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;

  void evt_CU(const CIEC_UINT &paPV, CIEC_BOOL &paQ, CIEC_UINT &paCV) {
    var_PV = paPV;
    receiveInputEvent(scmEventCUID, nullptr);
    paQ = var_Q;
    paCV = var_CV;
  }

  void evt_R(const CIEC_UINT &paPV, CIEC_BOOL &paQ, CIEC_UINT &paCV) {
    var_PV = paPV;
    receiveInputEvent(scmEventRID, nullptr);
    paQ = var_Q;
    paCV = var_CV;
  }

  void operator()(const CIEC_UINT &paPV, CIEC_BOOL &paQ, CIEC_UINT &paCV) {
    evt_CU(paPV, paQ, paCV);
  }
};


