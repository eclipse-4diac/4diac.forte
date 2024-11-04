/*******************************************************************************
 * Copyright (c) 2013 ACIN
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger
 *   - initial API and implementation and/or initial documentation
 *   Martin Jobst
 *     - refactor for ANY variant
 *******************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_any_string_variant.h"
#include "forte_any_int_variant.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_F_DELETE: public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_F_DELETE)

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
  FORTE_F_DELETE(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_ANY_STRING_VARIANT var_IN;
  CIEC_ANY_INT_VARIANT var_L;
  CIEC_ANY_INT_VARIANT var_P;
  CIEC_ANY_STRING_VARIANT var_OUT;
  
  CIEC_ANY_STRING_VARIANT var_conn_OUT;
  CEventConnection conn_CNF;
  CDataConnection *conn_IN;
  CDataConnection *conn_L;
  CDataConnection *conn_P;
  CDataConnection conn_OUT;
  
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  
  void evt_REQ(const CIEC_ANY_STRING &pa_IN, const CIEC_ANY_INT &pa_L, const CIEC_ANY_INT &pa_P, CIEC_ANY_STRING &pa_OUT) {
    var_IN = pa_IN;
    var_L = pa_L;
    var_P = pa_P;
    receiveInputEvent(scmEventREQID, nullptr);
    pa_OUT.setValue(var_OUT.unwrap());
  }
  
  void operator()(const CIEC_ANY_STRING &pa_IN, const CIEC_ANY_INT &pa_L, const CIEC_ANY_INT &pa_P, CIEC_ANY_STRING &pa_OUT) {
    evt_REQ(pa_IN, pa_L, pa_P, pa_OUT);
  }
  
};



