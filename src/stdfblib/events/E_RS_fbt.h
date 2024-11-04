/*******************************************************************************
 * Copyright (c) 2006 - 2011 ACIN, Profactor GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer, Ingo Hegny
 *     - initial API and implementation and/or initial documentation
 *******************************************************************************/

#pragma once

#include "basicfb.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_E_RS final : public CBasicFB {
  DECLARE_FIRMWARE_FB(FORTE_E_RS)

private:
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  static const TEventID scmEventRID = 0;
  static const TEventID scmEventSID = 1;
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];
  static const TEventID scmEventEOID = 0;
  static const TDataIOID scmEOWith[];
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;

  CIEC_ANY *getVarInternal(size_t) override;

  void alg_SET(void);
  void alg_RESET(void);

  static const TForteInt16 scmStateSTART = 0;
  static const TForteInt16 scmStateSET = 1;
  static const TForteInt16 scmStateRESET = 2;

  void enterStateSTART(CEventChainExecutionThread *const paECET);
  void enterStateSET(CEventChainExecutionThread *const paECET);
  void enterStateRESET(CEventChainExecutionThread *const paECET);

  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
  void setInitialValues() override;

public:
  FORTE_E_RS(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_BOOL var_Q;

  CIEC_BOOL var_conn_Q;

  CEventConnection conn_EO;

  CDataConnection conn_Q;

  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;

  void evt_R(CIEC_BOOL &paQ) {
    receiveInputEvent(scmEventRID, nullptr);
    paQ = var_Q;
  }

  void evt_S(CIEC_BOOL &paQ) {
    receiveInputEvent(scmEventSID, nullptr);
    paQ = var_Q;
  }

  void operator()(CIEC_BOOL &paQ) {
    evt_R(paQ);
  }
};


