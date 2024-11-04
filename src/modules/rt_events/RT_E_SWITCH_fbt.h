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

#include "ecet.h"

class FORTE_RT_E_SWITCH final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_RT_E_SWITCH)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  static const TEventID scmEventINITID = 0;
  static const TEventID scmEventEIID = 1;
  static const TDataIOID scmEIWith[];
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];
  static const TEventID scmEventINITOID = 0;
  static const TEventID scmEventEO1ID = 1;
  static const TEventID scmEventEO2ID = 2;
  static const TDataIOID scmEOWith[];
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;

  CEventChainExecutionThread mECEO1, mECEO2;
  bool mInitialized;

  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
  void setInitialValues() override;

public:
  FORTE_RT_E_SWITCH(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_BOOL var_QI;
  CIEC_BOOL var_G;
  CIEC_TIME var_Tmin;
  CIEC_TIME var_Deadline_EO1;
  CIEC_TIME var_WCET_EO1;
  CIEC_TIME var_Deadline_EO2;
  CIEC_TIME var_WCET_EO2;
  CIEC_BOOL var_QO;
  CIEC_BOOL var_conn_QO;
  CEventConnection conn_INITO;
  CEventConnection conn_EO1;
  CEventConnection conn_EO2;
  CDataConnection *conn_QI;
  CDataConnection *conn_G;
  CDataConnection *conn_Tmin;
  CDataConnection *conn_Deadline_EO1;
  CDataConnection *conn_WCET_EO1;
  CDataConnection *conn_Deadline_EO2;
  CDataConnection *conn_WCET_EO2;
  CDataConnection conn_QO;
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  void evt_INIT(const CIEC_BOOL &pa_QI, const CIEC_BOOL &pa_G, const CIEC_TIME &pa_Tmin, const CIEC_TIME &pa_Deadline_EO1, const CIEC_TIME &pa_WCET_EO1, const CIEC_TIME &pa_Deadline_EO2, const CIEC_TIME &pa_WCET_EO2, CIEC_BOOL &pa_QO) {
    var_QI = pa_QI;
    var_G = pa_G;
    var_Tmin = pa_Tmin;
    var_Deadline_EO1 = pa_Deadline_EO1;
    var_WCET_EO1 = pa_WCET_EO1;
    var_Deadline_EO2 = pa_Deadline_EO2;
    var_WCET_EO2 = pa_WCET_EO2;
    receiveInputEvent(scmEventINITID, nullptr);
    pa_QO = var_QO;
  }
  void evt_EI(const CIEC_BOOL &pa_QI, const CIEC_BOOL &pa_G, const CIEC_TIME &pa_Tmin, const CIEC_TIME &pa_Deadline_EO1, const CIEC_TIME &pa_WCET_EO1, const CIEC_TIME &pa_Deadline_EO2, const CIEC_TIME &pa_WCET_EO2, CIEC_BOOL &pa_QO) {
    var_QI = pa_QI;
    var_G = pa_G;
    var_Tmin = pa_Tmin;
    var_Deadline_EO1 = pa_Deadline_EO1;
    var_WCET_EO1 = pa_WCET_EO1;
    var_Deadline_EO2 = pa_Deadline_EO2;
    var_WCET_EO2 = pa_WCET_EO2;
    receiveInputEvent(scmEventEIID, nullptr);
    pa_QO = var_QO;
  }
  void operator()(const CIEC_BOOL &pa_QI, const CIEC_BOOL &pa_G, const CIEC_TIME &pa_Tmin, const CIEC_TIME &pa_Deadline_EO1, const CIEC_TIME &pa_WCET_EO1, const CIEC_TIME &pa_Deadline_EO2, const CIEC_TIME &pa_WCET_EO2, CIEC_BOOL &pa_QO) {
    evt_INIT(pa_QI, pa_G, pa_Tmin, pa_Deadline_EO1, pa_WCET_EO1, pa_Deadline_EO2, pa_WCET_EO2, pa_QO);
  }
};



