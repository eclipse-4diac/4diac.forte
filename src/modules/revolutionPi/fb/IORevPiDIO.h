/*******************************************************************************
 * Copyright (c) 2017, 2024 fortiss GmbH, Monika Wenger, Johannes Kepler University Linz
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Johannes Messmer - initial API and implementation and/or initial documentation
 *   Monika Wenger, Alois Zoitl - migration to current runtime
 *******************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_wstring.h"
#include "IORevPiBusAdapter.h"
#include <io/configFB/io_slave_multi.h>

class FORTE_IORevPiDIO: public forte::core::io::IOConfigFBMultiSlave {
DECLARE_FIRMWARE_FB(FORTE_IORevPiDIO)

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

public:
  FORTE_IORevPiDIO(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  virtual ~FORTE_IORevPiDIO() {};

  CIEC_BOOL var_QI;
  CIEC_STRING var_DigitalInput_1;
  CIEC_STRING var_DigitalInput_2;
  CIEC_STRING var_DigitalInput_3;
  CIEC_STRING var_DigitalInput_4;
  CIEC_STRING var_DigitalInput_5;
  CIEC_STRING var_DigitalInput_6;
  CIEC_STRING var_DigitalInput_7;
  CIEC_STRING var_DigitalInput_8;
  CIEC_STRING var_DigitalInput_9;
  CIEC_STRING var_DigitalInput_10;
  CIEC_STRING var_DigitalInput_11;
  CIEC_STRING var_DigitalInput_12;
  CIEC_STRING var_DigitalInput_13;
  CIEC_STRING var_DigitalInput_14;
  CIEC_STRING var_DigitalOutput_1;
  CIEC_STRING var_DigitalOutput_2;
  CIEC_STRING var_DigitalOutput_3;
  CIEC_STRING var_DigitalOutput_4;
  CIEC_STRING var_DigitalOutput_5;
  CIEC_STRING var_DigitalOutput_6;
  CIEC_STRING var_DigitalOutput_7;
  CIEC_STRING var_DigitalOutput_8;
  CIEC_STRING var_DigitalOutput_9;
  CIEC_STRING var_DigitalOutput_10;
  CIEC_STRING var_DigitalOutput_11;
  CIEC_STRING var_DigitalOutput_12;
  CIEC_STRING var_DigitalOutput_13;
  CIEC_STRING var_DigitalOutput_14;

  CIEC_BOOL var_QO;
  CIEC_WSTRING var_STATUS;

  CIEC_BOOL var_conn_QO;
  CIEC_WSTRING var_conn_STATUS;

  CEventConnection conn_MAPO;
  CEventConnection conn_IND;

  CDataConnection *conn_QI;
  CDataConnection *conn_DigitalInput_1;
  CDataConnection *conn_DigitalInput_2;
  CDataConnection *conn_DigitalInput_3;
  CDataConnection *conn_DigitalInput_4;
  CDataConnection *conn_DigitalInput_5;
  CDataConnection *conn_DigitalInput_6;
  CDataConnection *conn_DigitalInput_7;
  CDataConnection *conn_DigitalInput_8;
  CDataConnection *conn_DigitalInput_9;
  CDataConnection *conn_DigitalInput_10;
  CDataConnection *conn_DigitalInput_11;
  CDataConnection *conn_DigitalInput_12;
  CDataConnection *conn_DigitalInput_13;
  CDataConnection *conn_DigitalInput_14;
  CDataConnection *conn_DigitalOutput_1;
  CDataConnection *conn_DigitalOutput_2;
  CDataConnection *conn_DigitalOutput_3;
  CDataConnection *conn_DigitalOutput_4;
  CDataConnection *conn_DigitalOutput_5;
  CDataConnection *conn_DigitalOutput_6;
  CDataConnection *conn_DigitalOutput_7;
  CDataConnection *conn_DigitalOutput_8;
  CDataConnection *conn_DigitalOutput_9;
  CDataConnection *conn_DigitalOutput_10;
  CDataConnection *conn_DigitalOutput_11;
  CDataConnection *conn_DigitalOutput_12;
  CDataConnection *conn_DigitalOutput_13;
  CDataConnection *conn_DigitalOutput_14;

  CDataConnection conn_QO;
  CDataConnection conn_STATUS;

  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  FORTE_IORevPiBusAdapter &var_BusAdapterIn() {
    return *static_cast<FORTE_IORevPiBusAdapter*>(mAdapters[0]);
  };

  FORTE_IORevPiBusAdapter &var_BusAdapterOut() {
    return *static_cast<FORTE_IORevPiBusAdapter*>(mAdapters[1]);
  };

  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;

  void evt_MAP(const CIEC_BOOL &paQI, const CIEC_STRING &paDigitalInput_1, const CIEC_STRING &paDigitalInput_2, const CIEC_STRING &paDigitalInput_3, const CIEC_STRING &paDigitalInput_4, const CIEC_STRING &paDigitalInput_5, const CIEC_STRING &paDigitalInput_6, const CIEC_STRING &paDigitalInput_7, const CIEC_STRING &paDigitalInput_8, const CIEC_STRING &paDigitalInput_9, const CIEC_STRING &paDigitalInput_10, const CIEC_STRING &paDigitalInput_11, const CIEC_STRING &paDigitalInput_12, const CIEC_STRING &paDigitalInput_13, const CIEC_STRING &paDigitalInput_14, const CIEC_STRING &paDigitalOutput_1, const CIEC_STRING &paDigitalOutput_2, const CIEC_STRING &paDigitalOutput_3, const CIEC_STRING &paDigitalOutput_4, const CIEC_STRING &paDigitalOutput_5, const CIEC_STRING &paDigitalOutput_6, const CIEC_STRING &paDigitalOutput_7, const CIEC_STRING &paDigitalOutput_8, const CIEC_STRING &paDigitalOutput_9, const CIEC_STRING &paDigitalOutput_10, const CIEC_STRING &paDigitalOutput_11, const CIEC_STRING &paDigitalOutput_12, const CIEC_STRING &paDigitalOutput_13, const CIEC_STRING &paDigitalOutput_14, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS) {
    var_QI = paQI;
    var_DigitalInput_1 = paDigitalInput_1;
    var_DigitalInput_2 = paDigitalInput_2;
    var_DigitalInput_3 = paDigitalInput_3;
    var_DigitalInput_4 = paDigitalInput_4;
    var_DigitalInput_5 = paDigitalInput_5;
    var_DigitalInput_6 = paDigitalInput_6;
    var_DigitalInput_7 = paDigitalInput_7;
    var_DigitalInput_8 = paDigitalInput_8;
    var_DigitalInput_9 = paDigitalInput_9;
    var_DigitalInput_10 = paDigitalInput_10;
    var_DigitalInput_11 = paDigitalInput_11;
    var_DigitalInput_12 = paDigitalInput_12;
    var_DigitalInput_13 = paDigitalInput_13;
    var_DigitalInput_14 = paDigitalInput_14;
    var_DigitalOutput_1 = paDigitalOutput_1;
    var_DigitalOutput_2 = paDigitalOutput_2;
    var_DigitalOutput_3 = paDigitalOutput_3;
    var_DigitalOutput_4 = paDigitalOutput_4;
    var_DigitalOutput_5 = paDigitalOutput_5;
    var_DigitalOutput_6 = paDigitalOutput_6;
    var_DigitalOutput_7 = paDigitalOutput_7;
    var_DigitalOutput_8 = paDigitalOutput_8;
    var_DigitalOutput_9 = paDigitalOutput_9;
    var_DigitalOutput_10 = paDigitalOutput_10;
    var_DigitalOutput_11 = paDigitalOutput_11;
    var_DigitalOutput_12 = paDigitalOutput_12;
    var_DigitalOutput_13 = paDigitalOutput_13;
    var_DigitalOutput_14 = paDigitalOutput_14;
    executeEvent(scmEventMAPID, nullptr);
    paQO = var_QO;
    paSTATUS = var_STATUS;
  }

  void operator()(const CIEC_BOOL &paQI, const CIEC_STRING &paDigitalInput_1, const CIEC_STRING &paDigitalInput_2, const CIEC_STRING &paDigitalInput_3, const CIEC_STRING &paDigitalInput_4, const CIEC_STRING &paDigitalInput_5, const CIEC_STRING &paDigitalInput_6, const CIEC_STRING &paDigitalInput_7, const CIEC_STRING &paDigitalInput_8, const CIEC_STRING &paDigitalInput_9, const CIEC_STRING &paDigitalInput_10, const CIEC_STRING &paDigitalInput_11, const CIEC_STRING &paDigitalInput_12, const CIEC_STRING &paDigitalInput_13, const CIEC_STRING &paDigitalInput_14, const CIEC_STRING &paDigitalOutput_1, const CIEC_STRING &paDigitalOutput_2, const CIEC_STRING &paDigitalOutput_3, const CIEC_STRING &paDigitalOutput_4, const CIEC_STRING &paDigitalOutput_5, const CIEC_STRING &paDigitalOutput_6, const CIEC_STRING &paDigitalOutput_7, const CIEC_STRING &paDigitalOutput_8, const CIEC_STRING &paDigitalOutput_9, const CIEC_STRING &paDigitalOutput_10, const CIEC_STRING &paDigitalOutput_11, const CIEC_STRING &paDigitalOutput_12, const CIEC_STRING &paDigitalOutput_13, const CIEC_STRING &paDigitalOutput_14, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS) {
    evt_MAP(paQI, paDigitalInput_1, paDigitalInput_2, paDigitalInput_3, paDigitalInput_4, paDigitalInput_5, paDigitalInput_6, paDigitalInput_7, paDigitalInput_8, paDigitalInput_9, paDigitalInput_10, paDigitalInput_11, paDigitalInput_12, paDigitalInput_13, paDigitalInput_14, paDigitalOutput_1, paDigitalOutput_2, paDigitalOutput_3, paDigitalOutput_4, paDigitalOutput_5, paDigitalOutput_6, paDigitalOutput_7, paDigitalOutput_8, paDigitalOutput_9, paDigitalOutput_10, paDigitalOutput_11, paDigitalOutput_12, paDigitalOutput_13, paDigitalOutput_14, paQO, paSTATUS);
  }

  protected:
    void initHandles();
};
