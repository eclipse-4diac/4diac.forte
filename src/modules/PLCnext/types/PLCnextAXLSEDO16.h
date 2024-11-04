/*******************************************************************************
 * Copyright (c) 2022 Peirlberger Juergen
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Peirlberger Juergen - initial API and implementation and/or initial documentation
 *******************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_string.h"
#include "forte_wstring.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "PLCnextBusAdapter.h"

#include "../../../core/io/configFB/io_adapter_multi.h"
#include "../deviceController.h"
#include "../slaveHandler.h"

class FORTE_PLCnextAXLSEDO16 final : public PLCnextSlaveHandler {
  DECLARE_FIRMWARE_FB(FORTE_PLCnextAXLSEDO16)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  static const TEventID scmEventINITID = 0;
  static const TDataIOID scmEIWith[];
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];
  static const TEventID scmEventINITOID = 0;
  static const TEventID scmEventINDID = 1;
  static const TDataIOID scmEOWith[];
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];
  static const int scmBusAdapterInAdpNum = 0;
  static const int scmBusAdapterOutAdpNum = 1;
  static const SAdapterInstanceDef scmAdapterInstances[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
  void setInitialValues() override;
  
  const char* init() override;
  void initHandles() override;

public:
  FORTE_PLCnextAXLSEDO16(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_BOOL var_QI;
  CIEC_STRING var_DO_1;
  CIEC_STRING var_DO_2;
  CIEC_STRING var_DO_3;
  CIEC_STRING var_DO_4;
  CIEC_STRING var_DO_5;
  CIEC_STRING var_DO_6;
  CIEC_STRING var_DO_7;
  CIEC_STRING var_DO_8;
  CIEC_STRING var_DO_9;
  CIEC_STRING var_DO_10;
  CIEC_STRING var_DO_11;
  CIEC_STRING var_DO_12;
  CIEC_STRING var_DO_13;
  CIEC_STRING var_DO_14;
  CIEC_STRING var_DO_15;
  CIEC_STRING var_DO_16;

  CIEC_BOOL var_QO;
  CIEC_WSTRING var_STATUS;

  CIEC_BOOL var_conn_QO;
  CIEC_WSTRING var_conn_STATUS;

  CEventConnection conn_INITO;
  CEventConnection conn_IND;

  CDataConnection *conn_QI;
  CDataConnection *conn_DO_1;
  CDataConnection *conn_DO_2;
  CDataConnection *conn_DO_3;
  CDataConnection *conn_DO_4;
  CDataConnection *conn_DO_5;
  CDataConnection *conn_DO_6;
  CDataConnection *conn_DO_7;
  CDataConnection *conn_DO_8;
  CDataConnection *conn_DO_9;
  CDataConnection *conn_DO_10;
  CDataConnection *conn_DO_11;
  CDataConnection *conn_DO_12;
  CDataConnection *conn_DO_13;
  CDataConnection *conn_DO_14;
  CDataConnection *conn_DO_15;
  CDataConnection *conn_DO_16;

  CDataConnection conn_QO;
  CDataConnection conn_STATUS;

  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  FORTE_PLCnextBusAdapter &var_BusAdapterIn() {
    return *static_cast<FORTE_PLCnextBusAdapter*>(mAdapters[0]);
  };

  FORTE_PLCnextBusAdapter &var_BusAdapterOut() {
    return *static_cast<FORTE_PLCnextBusAdapter*>(mAdapters[1]);
  };

  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;

  void evt_INIT(const CIEC_BOOL &paQI, const CIEC_STRING &paDO_1, const CIEC_STRING &paDO_2, const CIEC_STRING &paDO_3, const CIEC_STRING &paDO_4, const CIEC_STRING &paDO_5, const CIEC_STRING &paDO_6, const CIEC_STRING &paDO_7, const CIEC_STRING &paDO_8, const CIEC_STRING &paDO_9, const CIEC_STRING &paDO_10, const CIEC_STRING &paDO_11, const CIEC_STRING &paDO_12, const CIEC_STRING &paDO_13, const CIEC_STRING &paDO_14, const CIEC_STRING &paDO_15, const CIEC_STRING &paDO_16, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS) {
    var_QI = paQI;
    var_DO_1 = paDO_1;
    var_DO_2 = paDO_2;
    var_DO_3 = paDO_3;
    var_DO_4 = paDO_4;
    var_DO_5 = paDO_5;
    var_DO_6 = paDO_6;
    var_DO_7 = paDO_7;
    var_DO_8 = paDO_8;
    var_DO_9 = paDO_9;
    var_DO_10 = paDO_10;
    var_DO_11 = paDO_11;
    var_DO_12 = paDO_12;
    var_DO_13 = paDO_13;
    var_DO_14 = paDO_14;
    var_DO_15 = paDO_15;
    var_DO_16 = paDO_16;
    receiveInputEvent(scmEventINITID, nullptr);
    paQO = var_QO;
    paSTATUS = var_STATUS;
  }

  void operator()(const CIEC_BOOL &paQI, const CIEC_STRING &paDO_1, const CIEC_STRING &paDO_2, const CIEC_STRING &paDO_3, const CIEC_STRING &paDO_4, const CIEC_STRING &paDO_5, const CIEC_STRING &paDO_6, const CIEC_STRING &paDO_7, const CIEC_STRING &paDO_8, const CIEC_STRING &paDO_9, const CIEC_STRING &paDO_10, const CIEC_STRING &paDO_11, const CIEC_STRING &paDO_12, const CIEC_STRING &paDO_13, const CIEC_STRING &paDO_14, const CIEC_STRING &paDO_15, const CIEC_STRING &paDO_16, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS) {
    evt_INIT(paQI, paDO_1, paDO_2, paDO_3, paDO_4, paDO_5, paDO_6, paDO_7, paDO_8, paDO_9, paDO_10, paDO_11, paDO_12, paDO_13, paDO_14, paDO_15, paDO_16, paQO, paSTATUS);
  }
};


