/*******************************************************************************
 * Copyright (c) 2016 - 2018 Johannes Messmer (admin@jomess.com), fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Johannes Messmer - initial API and implementation and/or initial documentation
 *   Jose Cabral - Cleaning of namespaces
 *******************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_wstring.h"
#include "forte_uint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "EBBusAdapter.h"
#include "Slave.h"


class FORTE_EBSlave2301 final : public EmbrickSlave {
  DECLARE_FIRMWARE_FB(FORTE_EBSlave2301)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  static const TEventID scmEventMAPID = 0;
  static const TDataIOID scmEIWith[];
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];
  static const TEventID scmEventMAPOID = 0;
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
  
  static const TForteUInt8 scmSlaveConfigurationIO[];
  static const TForteUInt8 scmSlaveConfigurationIONum;
  
  virtual void initHandles() override;

public:
  FORTE_EBSlave2301(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_BOOL var_QI;
  CIEC_WSTRING var_Relay_1;
  CIEC_WSTRING var_Relay_2;
  CIEC_WSTRING var_Relay_3;
  CIEC_WSTRING var_Relay_4;
  CIEC_WSTRING var_Relay_5;
  CIEC_WSTRING var_Relay_6;
  CIEC_UINT var_UpdateInterval;

  CIEC_BOOL var_QO;
  CIEC_WSTRING var_STATUS;

  CIEC_BOOL var_conn_QO;
  CIEC_WSTRING var_conn_STATUS;

  CEventConnection conn_MAPO;
  CEventConnection conn_IND;

  CDataConnection *conn_QI;
  CDataConnection *conn_Relay_1;
  CDataConnection *conn_Relay_2;
  CDataConnection *conn_Relay_3;
  CDataConnection *conn_Relay_4;
  CDataConnection *conn_Relay_5;
  CDataConnection *conn_Relay_6;
  CDataConnection *conn_UpdateInterval;

  CDataConnection conn_QO;
  CDataConnection conn_STATUS;

  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  FORTE_EBBusAdapter &var_BusAdapterIn() {
    return *static_cast<FORTE_EBBusAdapter*>(mAdapters[0]);
  };

  FORTE_EBBusAdapter &var_BusAdapterOut() {
    return *static_cast<FORTE_EBBusAdapter*>(mAdapters[1]);
  };

  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;

  void evt_MAP(const CIEC_BOOL &paQI, const CIEC_WSTRING &paRelay_1, const CIEC_WSTRING &paRelay_2, const CIEC_WSTRING &paRelay_3, const CIEC_WSTRING &paRelay_4, const CIEC_WSTRING &paRelay_5, const CIEC_WSTRING &paRelay_6, const CIEC_UINT &paUpdateInterval, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS) {
    var_QI = paQI;
    var_Relay_1 = paRelay_1;
    var_Relay_2 = paRelay_2;
    var_Relay_3 = paRelay_3;
    var_Relay_4 = paRelay_4;
    var_Relay_5 = paRelay_5;
    var_Relay_6 = paRelay_6;
    var_UpdateInterval = paUpdateInterval;
    receiveInputEvent(scmEventMAPID, nullptr);
    paQO = var_QO;
    paSTATUS = var_STATUS;
  }

  void operator()(const CIEC_BOOL &paQI, const CIEC_WSTRING &paRelay_1, const CIEC_WSTRING &paRelay_2, const CIEC_WSTRING &paRelay_3, const CIEC_WSTRING &paRelay_4, const CIEC_WSTRING &paRelay_5, const CIEC_WSTRING &paRelay_6, const CIEC_UINT &paUpdateInterval, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS) {
    evt_MAP(paQI, paRelay_1, paRelay_2, paRelay_3, paRelay_4, paRelay_5, paRelay_6, paUpdateInterval, paQO, paSTATUS);
  }
};


