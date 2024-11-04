/*******************************************************************************
 * Copyright (c) 2018, 2024 fortiss GmbH, Monika Wenger, Johannes Kepler University Linz
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Jose Cabral - initial implementation
 *   Monika Wenger, Alois Zoitl - migration to current runtime
 *******************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_wstring.h"
#include "IORevPiBusAdapter.h"
#include <io/configFB/io_slave_multi.h>

class FORTE_IORevPiAIO: public forte::core::io::IOConfigFBMultiSlave {
  DECLARE_FIRMWARE_FB(FORTE_IORevPiAIO)

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

  static const TForteUInt8 scmSlaveConfigurationIO[];
  static const TForteUInt8 scmSlaveConfigurationIONum;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
  void setInitialValues() override;

public:
  FORTE_IORevPiAIO(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  virtual ~FORTE_IORevPiAIO(){};

  CIEC_BOOL var_QI;
  CIEC_STRING var_AnalogInput_1;
  CIEC_STRING var_AnalogInput_2;
  CIEC_STRING var_AnalogInput_3;
  CIEC_STRING var_AnalogInput_4;
  CIEC_STRING var_RTD_1;
  CIEC_STRING var_RTD_2;
  CIEC_STRING var_AnalogOutput_1;
  CIEC_STRING var_AnalogOutput_2;

  CIEC_BOOL var_QO;
  CIEC_WSTRING var_STATUS;

  CIEC_BOOL var_conn_QO;
  CIEC_WSTRING var_conn_STATUS;

  CEventConnection conn_MAPO;
  CEventConnection conn_IND;

  CDataConnection *conn_QI;
  CDataConnection *conn_AnalogInput_1;
  CDataConnection *conn_AnalogInput_2;
  CDataConnection *conn_AnalogInput_3;
  CDataConnection *conn_AnalogInput_4;
  CDataConnection *conn_RTD_1;
  CDataConnection *conn_RTD_2;
  CDataConnection *conn_AnalogOutput_1;
  CDataConnection *conn_AnalogOutput_2;

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

  void evt_MAP(const CIEC_BOOL &paQI, const CIEC_STRING &paAnalogInput_1, const CIEC_STRING &paAnalogInput_2, const CIEC_STRING &paAnalogInput_3, const CIEC_STRING &paAnalogInput_4, const CIEC_STRING &paRTD_1, const CIEC_STRING &paRTD_2, const CIEC_STRING &paAnalogOutput_1, const CIEC_STRING &paAnalogOutput_2, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS) {
    var_QI = paQI;
    var_AnalogInput_1 = paAnalogInput_1;
    var_AnalogInput_2 = paAnalogInput_2;
    var_AnalogInput_3 = paAnalogInput_3;
    var_AnalogInput_4 = paAnalogInput_4;
    var_RTD_1 = paRTD_1;
    var_RTD_2 = paRTD_2;
    var_AnalogOutput_1 = paAnalogOutput_1;
    var_AnalogOutput_2 = paAnalogOutput_2;
    executeEvent(scmEventMAPID, nullptr);
    paQO = var_QO;
    paSTATUS = var_STATUS;
  }

  void operator()(const CIEC_BOOL &paQI, const CIEC_STRING &paAnalogInput_1, const CIEC_STRING &paAnalogInput_2, const CIEC_STRING &paAnalogInput_3, const CIEC_STRING &paAnalogInput_4, const CIEC_STRING &paRTD_1, const CIEC_STRING &paRTD_2, const CIEC_STRING &paAnalogOutput_1, const CIEC_STRING &paAnalogOutput_2, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS) {
    evt_MAP(paQI, paAnalogInput_1, paAnalogInput_2, paAnalogInput_3, paAnalogInput_4, paRTD_1, paRTD_2, paAnalogOutput_1, paAnalogOutput_2, paQO, paSTATUS);
  }

protected:
  void initHandles();

};
