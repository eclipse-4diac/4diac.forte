/*******************************************************************************
 * Copyright (c) 2011 - 2013 ACIN, Profactor GmbH
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger, Alois Zoitl, Matthias Plasch, Gerhard Ebenhofer
 *   - initial API and implementation and/or initial documentation
 *   Martin Jobst
 *     - refactor for ANY variant
 *******************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_any_elementary_variant.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_F_MIN: public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_F_MIN)

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
  FORTE_F_MIN(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_ANY_ELEMENTARY_VARIANT var_IN1;
  CIEC_ANY_ELEMENTARY_VARIANT var_IN2;
  CIEC_ANY_ELEMENTARY_VARIANT var_OUT;
  
  CIEC_ANY_ELEMENTARY_VARIANT var_conn_OUT;
  CEventConnection conn_CNF;
  CDataConnection *conn_IN1;
  CDataConnection *conn_IN2;
  CDataConnection conn_OUT;
  
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  
  void evt_REQ(const CIEC_ANY_ELEMENTARY &pa_IN1, const CIEC_ANY_ELEMENTARY &pa_IN2, CIEC_ANY_ELEMENTARY &pa_OUT) {
    var_IN1 = pa_IN1;
    var_IN2 = pa_IN2;
    receiveInputEvent(scmEventREQID, nullptr);
    pa_OUT.setValue(var_OUT.unwrap());
  }
  
  void operator()(const CIEC_ANY_ELEMENTARY &pa_IN1, const CIEC_ANY_ELEMENTARY &pa_IN2, CIEC_ANY_ELEMENTARY &pa_OUT) {
    evt_REQ(pa_IN1, pa_IN2, pa_OUT);
  }
  
};



