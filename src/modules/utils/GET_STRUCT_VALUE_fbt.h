/*******************************************************************************
 * Copyright (c) 2018, fortiss GmbH
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral - initial implementation
 *   Martin Jobst
 *     - refactor for ANY variant
 *******************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_any_variant.h"
#include "forte_string.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_GET_STRUCT_VALUE: public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_GET_STRUCT_VALUE)

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

  CIEC_ANY *lookForMember(CIEC_STRUCT &paWhereToLook, char *paMemberName);

  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;

public:
  FORTE_GET_STRUCT_VALUE(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_ANY_VARIANT var_in_struct;
  CIEC_STRING var_member;
  CIEC_BOOL var_QO;
  CIEC_ANY_VARIANT var_output;
  
  CIEC_BOOL var_conn_QO;
  CIEC_ANY_VARIANT var_conn_output;
  CEventConnection conn_CNF;
  CDataConnection *conn_in_struct;
  CDataConnection *conn_member;
  CDataConnection conn_QO;
  CDataConnection conn_output;
  
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  
  void evt_REQ(const CIEC_ANY &pa_in_struct, const CIEC_STRING &pa_member, CIEC_BOOL &pa_QO, CIEC_ANY &pa_output) {
    var_in_struct = pa_in_struct;
    var_member = pa_member;
    receiveInputEvent(scmEventREQID, nullptr);
    pa_QO = var_QO;
    pa_output.setValue(var_output.unwrap());
  }
  
  void operator()(const CIEC_ANY &pa_in_struct, const CIEC_STRING &pa_member, CIEC_BOOL &pa_QO, CIEC_ANY &pa_output) {
    evt_REQ(pa_in_struct, pa_member, pa_QO, pa_output);
  }
  
};



