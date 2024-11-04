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
 *    - initial API and implementation and/or initial documentation
 *******************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_time.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

#include "esfb.h"
#include "ecet.h"
#include "../arch/timerha.h"

class FORTE_RT_E_DELAY final : public CEventSourceFB {
  DECLARE_FIRMWARE_FB(FORTE_RT_E_DELAY)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  static const TEventID scmEventINITID = 0;
  static const TEventID scmEventSTARTID = 1;
  static const TEventID scmEventSTOPID = 2;
  static const TDataIOID scmEIWith[];
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];
  static const TEventID scmEventINITOID = 0;
  static const TEventID scmEventEOID = 1;
  static const TDataIOID scmEOWith[];
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;

  bool mActive; //!> flag to indicate that the timed fb is currently active
  bool mInitialized;
  CEventChainExecutionThread mECEO;

  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
  void setInitialValues() override;

public:
  FORTE_RT_E_DELAY(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  EMGMResponse changeExecutionState(EMGMCommandType paCommand) override;

  CIEC_BOOL var_QI;
  CIEC_TIME var_DT;
  CIEC_TIME var_Tmin;
  CIEC_TIME var_Deadline;
  CIEC_TIME var_WCET;
  CIEC_BOOL var_QO;
  CIEC_BOOL var_conn_QO;
  CEventConnection conn_INITO;
  CEventConnection conn_EO;
  CDataConnection *conn_QI;
  CDataConnection *conn_DT;
  CDataConnection *conn_Tmin;
  CDataConnection *conn_Deadline;
  CDataConnection *conn_WCET;
  CDataConnection conn_QO;
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  void evt_INIT(const CIEC_BOOL &pa_QI, const CIEC_TIME &pa_DT, const CIEC_TIME &pa_Tmin, const CIEC_TIME &pa_Deadline, const CIEC_TIME &pa_WCET, CIEC_BOOL &pa_QO) {
    var_QI = pa_QI;
    var_DT = pa_DT;
    var_Tmin = pa_Tmin;
    var_Deadline = pa_Deadline;
    var_WCET = pa_WCET;
    receiveInputEvent(scmEventINITID, nullptr);
    pa_QO = var_QO;
  }
  void evt_START(const CIEC_BOOL &pa_QI, const CIEC_TIME &pa_DT, const CIEC_TIME &pa_Tmin, const CIEC_TIME &pa_Deadline, const CIEC_TIME &pa_WCET, CIEC_BOOL &pa_QO) {
    var_QI = pa_QI;
    var_DT = pa_DT;
    var_Tmin = pa_Tmin;
    var_Deadline = pa_Deadline;
    var_WCET = pa_WCET;
    receiveInputEvent(scmEventSTARTID, nullptr);
    pa_QO = var_QO;
  }
  void evt_STOP(const CIEC_BOOL &pa_QI, const CIEC_TIME &pa_DT, const CIEC_TIME &pa_Tmin, const CIEC_TIME &pa_Deadline, const CIEC_TIME &pa_WCET, CIEC_BOOL &pa_QO) {
    var_QI = pa_QI;
    var_DT = pa_DT;
    var_Tmin = pa_Tmin;
    var_Deadline = pa_Deadline;
    var_WCET = pa_WCET;
    receiveInputEvent(scmEventSTOPID, nullptr);
    pa_QO = var_QO;
  }
  void operator()(const CIEC_BOOL &pa_QI, const CIEC_TIME &pa_DT, const CIEC_TIME &pa_Tmin, const CIEC_TIME &pa_Deadline, const CIEC_TIME &pa_WCET, CIEC_BOOL &pa_QO) {
    evt_INIT(pa_QI, pa_DT, pa_Tmin, pa_Deadline, pa_WCET, pa_QO);
  }
};



