/*******************************************************************************
 * Copyright (c) 2023 Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Martin Jobst
 *     - initial API and implementation and/or initial documentation
 *******************************************************************************/

#pragma once

#include "simplefb.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_FB_RS: public CSimpleFB {
  DECLARE_FIRMWARE_FB(FORTE_FB_RS)

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
  CIEC_ANY *getVarInternal(size_t) override;
  void alg_REQ(void);

  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;

public:
  FORTE_FB_RS(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);


  CIEC_BOOL var_S;
  CIEC_BOOL var_R1;
  CIEC_BOOL var_Q1;
  
  CIEC_BOOL var_conn_Q1;
  CEventConnection conn_CNF;
  CDataConnection *conn_S;
  CDataConnection *conn_R1;
  CDataConnection conn_Q1;
  
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  
  void evt_REQ(const CIEC_BOOL &pa_S, const CIEC_BOOL &pa_R1, CIEC_BOOL &pa_Q1) {
    var_S = pa_S;
    var_R1 = pa_R1;
    receiveInputEvent(scmEventREQID, nullptr);
    pa_Q1 = var_Q1;
  }
  
  void operator()(const CIEC_BOOL &pa_S, const CIEC_BOOL &pa_R1, CIEC_BOOL &pa_Q1) {
    evt_REQ(pa_S, pa_R1, pa_Q1);
  }
  
};



