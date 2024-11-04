/*******************************************************************************
 * Copyright (c) 2017 fortiss GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl
 *     - initial API and implementation and/or initial documentation
 *******************************************************************************/

#pragma once

#include "cfb.h"
#include "typelib.h"
#include "forte_time.h"
#include "forte_uint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "E_CTU_fbt.h"
#include "E_SWITCH_fbt.h"
#include "E_DELAY_fbt.h"


class FORTE_E_TRAIN: public CCompositeFB {
  DECLARE_FIRMWARE_FB(FORTE_E_TRAIN)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  static const TEventID scmEventSTARTID = 0;
  static const TEventID scmEventSTOPID = 1;
  static const TDataIOID scmEIWith[];
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];
  static const TEventID scmEventEOID = 0;
  static const TDataIOID scmEOWith[];
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;

  static const SCFB_FBInstanceData scmInternalFBs[];
  static const SCFB_FBParameter scmParamters[];
  static const SCFB_FBConnectionData scmEventConnections[];
  static const SCFB_FBFannedOutConnectionData scmFannedOutEventConnections[];
  static const SCFB_FBConnectionData scmDataConnections[];
  static const SCFB_FBFannedOutConnectionData scmFannedOutDataConnections[];
  static const SCFB_FBNData scmFBNData;

  forte::core::CInternalFB<FORTE_E_CTU> fb_CTR;
  forte::core::CInternalFB<FORTE_E_SWITCH> fb_GATE;
  forte::core::CInternalFB<FORTE_E_DELAY> fb_DLY;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
  void readInternal2InterfaceOutputData(TEventID paEOID) override;

public:
  FORTE_E_TRAIN(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_TIME var_DT;
  CIEC_UINT var_N;
  CIEC_UINT var_CV;
  CIEC_UINT var_conn_CV;
  CEventConnection conn_EO;
  CDataConnection *conn_DT;
  CDataConnection *conn_N;
  CDataConnection conn_CV;
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  void evt_START(const CIEC_TIME &pa_DT, const CIEC_UINT &pa_N, CIEC_UINT &pa_CV) {
    var_DT = pa_DT;
    var_N = pa_N;
    receiveInputEvent(scmEventSTARTID, nullptr);
    pa_CV = var_CV;
  }
  void evt_STOP(const CIEC_TIME &pa_DT, const CIEC_UINT &pa_N, CIEC_UINT &pa_CV) {
    var_DT = pa_DT;
    var_N = pa_N;
    receiveInputEvent(scmEventSTOPID, nullptr);
    pa_CV = var_CV;
  }
  void operator()(const CIEC_TIME &pa_DT, const CIEC_UINT &pa_N, CIEC_UINT &pa_CV) {
    evt_START(pa_DT, pa_N, pa_CV);
  }
};



