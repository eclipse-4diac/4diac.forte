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

#include "rtesingle.h"

class FORTE_RT_E_F_TRIG final : public CRTEventSingle {
  DECLARE_FIRMWARE_FB(FORTE_RT_E_F_TRIG)

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
  static const TEventID scmEventEOID = 1;
  static const TDataIOID scmEOWith[];
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;

  bool mWasHigh;

  bool checkActivation(TEventID paEIID) override;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
  void setInitialValues() override;

public:
  FORTE_RT_E_F_TRIG(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_TIME var_Tmin;
  CIEC_TIME var_WCET;
  CIEC_BOOL var_conn_QO;
  CEventConnection conn_INITO;
  CEventConnection conn_EO;
  CDataConnection *conn_QI;
  CDataConnection *conn_Tmin;
  CDataConnection *conn_Deadline;
  CDataConnection *conn_WCET;
  CDataConnection conn_QO;
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  void evt_INIT(const CIEC_BOOL &pa_QI, const CIEC_TIME &pa_Tmin, const CIEC_TIME &pa_Deadline, const CIEC_TIME &pa_WCET, CIEC_BOOL &pa_QO) {
    var_QI = pa_QI;
    var_Tmin = pa_Tmin;
    var_Deadline = pa_Deadline;
    var_WCET = pa_WCET;
    receiveInputEvent(scmEventINITID, nullptr);
    pa_QO = var_QO;
  }
  void evt_EI(const CIEC_BOOL &pa_QI, const CIEC_TIME &pa_Tmin, const CIEC_TIME &pa_Deadline, const CIEC_TIME &pa_WCET, CIEC_BOOL &pa_QO) {
    var_QI = pa_QI;
    var_Tmin = pa_Tmin;
    var_Deadline = pa_Deadline;
    var_WCET = pa_WCET;
    receiveInputEvent(scmEventEIID, nullptr);
    pa_QO = var_QO;
  }
  void operator()(const CIEC_BOOL &pa_QI, const CIEC_TIME &pa_Tmin, const CIEC_TIME &pa_Deadline, const CIEC_TIME &pa_WCET, CIEC_BOOL &pa_QO) {
    evt_INIT(pa_QI, pa_Tmin, pa_Deadline, pa_WCET, pa_QO);
  }
};



