/*******************************************************************************
 * Copyright (c) 2014 Profactor GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Matthias Plasch, Gerhard Ebenhofer - initial API and implementation and/or initial documentation
 *******************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_wstring.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_ST_CREATE_CONN final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_ST_CREATE_CONN)

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

  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;
  void executeRQST();

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
  void setInitialValues() override;

public:
  FORTE_ST_CREATE_CONN(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_BOOL var_QI;
  CIEC_WSTRING var_SRC_FB;
  CIEC_WSTRING var_SRC_FB_OUT;
  CIEC_WSTRING var_DST_FB;
  CIEC_WSTRING var_DST_FB_IN;
  CIEC_WSTRING var_DST;
  CIEC_BOOL var_QO;
  CIEC_WSTRING var_STATUS;
  CIEC_BOOL var_conn_QO;
  CIEC_WSTRING var_conn_STATUS;
  CEventConnection conn_CNF;
  CDataConnection *conn_QI;
  CDataConnection *conn_SRC_FB;
  CDataConnection *conn_SRC_FB_OUT;
  CDataConnection *conn_DST_FB;
  CDataConnection *conn_DST_FB_IN;
  CDataConnection *conn_DST;
  CDataConnection conn_QO;
  CDataConnection conn_STATUS;
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  void evt_REQ(const CIEC_BOOL &pa_QI, const CIEC_WSTRING &pa_SRC_FB, const CIEC_WSTRING &pa_SRC_FB_OUT, const CIEC_WSTRING &pa_DST_FB, const CIEC_WSTRING &pa_DST_FB_IN, const CIEC_WSTRING &pa_DST, CIEC_BOOL &pa_QO, CIEC_WSTRING &pa_STATUS) {
    var_QI = pa_QI;
    var_SRC_FB = pa_SRC_FB;
    var_SRC_FB_OUT = pa_SRC_FB_OUT;
    var_DST_FB = pa_DST_FB;
    var_DST_FB_IN = pa_DST_FB_IN;
    var_DST = pa_DST;
    receiveInputEvent(scmEventREQID, nullptr);
    pa_QO = var_QO;
    pa_STATUS = var_STATUS;
  }
  void operator()(const CIEC_BOOL &pa_QI, const CIEC_WSTRING &pa_SRC_FB, const CIEC_WSTRING &pa_SRC_FB_OUT, const CIEC_WSTRING &pa_DST_FB, const CIEC_WSTRING &pa_DST_FB_IN, const CIEC_WSTRING &pa_DST, CIEC_BOOL &pa_QO, CIEC_WSTRING &pa_STATUS) {
    evt_REQ(pa_QI, pa_SRC_FB, pa_SRC_FB_OUT, pa_DST_FB, pa_DST_FB_IN, pa_DST, pa_QO, pa_STATUS);
  }
};



