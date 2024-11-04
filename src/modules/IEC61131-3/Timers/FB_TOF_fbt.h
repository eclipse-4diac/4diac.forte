/*******************************************************************************
 * Copyright (c) 2009, 2023 ACIN, fortiss GmbH
 *                          Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger, Alois Zoitl, Ingo Hengy
 *   - initial API and implementation and/or initial documentation
 *   Martin Jobst - add readInputData and writeOutputData
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


class FORTE_FB_TOF final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_FB_TOF)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  static const TEventID scmEventREQID = 0;
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

  bool fallingEdge;
  bool notFirstRisingEdge;
  CIEC_TIME start;
  CIEC_TIME count;

  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
  void setInitialValues() override;

public:
  FORTE_FB_TOF(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_BOOL var_IN;
  CIEC_TIME var_PT;
  CIEC_BOOL var_Q;
  CIEC_TIME var_ET;
  CIEC_BOOL var_conn_Q;
  CIEC_TIME var_conn_ET;
  CEventConnection conn_CNF;
  CDataConnection *conn_IN;
  CDataConnection *conn_PT;
  CDataConnection conn_Q;
  CDataConnection conn_ET;
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  void evt_REQ(const CIEC_BOOL &pa_IN, const CIEC_TIME &pa_PT, CIEC_BOOL &pa_Q, CIEC_TIME &pa_ET) {
    var_IN = pa_IN;
    var_PT = pa_PT;
    receiveInputEvent(scmEventREQID, nullptr);
    pa_Q = var_Q;
    pa_ET = var_ET;
  }
  void operator()(const CIEC_BOOL &pa_IN, const CIEC_TIME &pa_PT, CIEC_BOOL &pa_Q, CIEC_TIME &pa_ET) {
    evt_REQ(pa_IN, pa_PT, pa_Q, pa_ET);
  }
};



