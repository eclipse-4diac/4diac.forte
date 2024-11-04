/*******************************************************************************
 * Copyright (c) 2014 Profactor GmbH
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Matthias Plasch
 *   - initial API and implementation and/or initial documentation
 *   Martin Jobst
 *     - refactor for ANY variant
 *******************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_any_variant.h"
#include "forte_uint.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_SET_AT_INDEX: public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_SET_AT_INDEX)

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

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;

public:
  FORTE_SET_AT_INDEX(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_ANY_VARIANT var_IN_ARRAY;
  CIEC_UINT var_INDEX;
  CIEC_ANY_VARIANT var_VALUE;
  CIEC_BOOL var_QO;
  CIEC_ANY_VARIANT var_OUT_ARRAY;
  
  CIEC_BOOL var_conn_QO;
  CIEC_ANY_VARIANT var_conn_OUT_ARRAY;
  CEventConnection conn_CNF;
  CDataConnection *conn_IN_ARRAY;
  CDataConnection *conn_INDEX;
  CDataConnection *conn_VALUE;
  CDataConnection conn_QO;
  CDataConnection conn_OUT_ARRAY;
  
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  
  void evt_REQ(const CIEC_ANY &pa_IN_ARRAY, const CIEC_UINT &pa_INDEX, const CIEC_ANY &pa_VALUE, CIEC_BOOL &pa_QO, CIEC_ANY &pa_OUT_ARRAY) {
    var_IN_ARRAY = pa_IN_ARRAY;
    var_INDEX = pa_INDEX;
    var_VALUE = pa_VALUE;
    receiveInputEvent(scmEventREQID, nullptr);
    pa_QO = var_QO;
    pa_OUT_ARRAY.setValue(var_OUT_ARRAY.unwrap());
  }
  
  void operator()(const CIEC_ANY &pa_IN_ARRAY, const CIEC_UINT &pa_INDEX, const CIEC_ANY &pa_VALUE, CIEC_BOOL &pa_QO, CIEC_ANY &pa_OUT_ARRAY) {
    evt_REQ(pa_IN_ARRAY, pa_INDEX, pa_VALUE, pa_QO, pa_OUT_ARRAY);
  }
  
};



