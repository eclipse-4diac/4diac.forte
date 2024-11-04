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
#include "forte_udint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_FB_CTU_UDINT: public CSimpleFB {
  DECLARE_FIRMWARE_FB(FORTE_FB_CTU_UDINT)

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
  FORTE_FB_CTU_UDINT(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);


  CIEC_BOOL var_CU;
  CIEC_BOOL var_R;
  CIEC_UDINT var_PV;
  CIEC_BOOL var_Q;
  CIEC_UDINT var_CV;
  
  CIEC_BOOL var_conn_Q;
  CIEC_UDINT var_conn_CV;
  CEventConnection conn_CNF;
  CDataConnection *conn_CU;
  CDataConnection *conn_R;
  CDataConnection *conn_PV;
  CDataConnection conn_Q;
  CDataConnection conn_CV;
  
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  
  void evt_REQ(const CIEC_BOOL &pa_CU, const CIEC_BOOL &pa_R, const CIEC_UDINT &pa_PV, CIEC_BOOL &pa_Q, CIEC_UDINT &pa_CV) {
    var_CU = pa_CU;
    var_R = pa_R;
    var_PV = pa_PV;
    receiveInputEvent(scmEventREQID, nullptr);
    pa_Q = var_Q;
    pa_CV = var_CV;
  }
  
  void operator()(const CIEC_BOOL &pa_CU, const CIEC_BOOL &pa_R, const CIEC_UDINT &pa_PV, CIEC_BOOL &pa_Q, CIEC_UDINT &pa_CV) {
    evt_REQ(pa_CU, pa_R, pa_PV, pa_Q, pa_CV);
  }
  
};



