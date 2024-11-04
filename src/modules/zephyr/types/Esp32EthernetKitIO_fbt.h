/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: Esp32EthernetKitIO
 *** Description: Template for Modular IO with Esp32EthernetKit board
 *** Version:
 ***     1.0: 2024-01-13/Dirk O. Kaar -  -
 ***
 *** Copyright (c) 2024 KT Elektronik GmbH
 *** This program and the accompanying materials are made available under the
 *** terms of the Eclipse Public License 2.0 which is available at
 *** http://www.eclipse.org/legal/epl-2.0.
 ***
 *** SPDX-License-Identifier: EPL-2.0
 *************************************************************************/

#pragma once

#pragma region includes
#include <types/ZephyrIOBase.h>
#pragma endregion includes

#pragma region base class spec
class FORTE_Esp32EthernetKitIO final : public FORTE_ZephyrIOBase {
#pragma endregion base class spec
  DECLARE_FIRMWARE_FB(FORTE_Esp32EthernetKitIO)

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
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

#pragma region remove executeEvent()
    // using FORTE_ZephyrIOBase::executeEvent
#pragma endregion remove executeEvent()

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

#pragma region define IOs
    static constexpr size_t numberOfGPIOs = 2;
    static constexpr size_t numberOfADCChannels = 1;
    static constexpr size_t numberOfPWMs = 1;

    void setConfig() override;

  protected:
    void onStartup(CEventChainExecutionThread * const paECET) override;
#pragma endregion define IOs

  public:
    FORTE_Esp32EthernetKitIO(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BOOL var_QI;
    CIEC_STRING var_LED0;
    CIEC_STRING var_SW0;
    CIEC_STRING var_ADC_CH_0;
    CIEC_STRING var_PWM;
    CIEC_TIME var_UpdateInterval;

    CIEC_BOOL var_QO;
    CIEC_STRING var_STATUS;

    CIEC_BOOL var_conn_QO;
    CIEC_STRING var_conn_STATUS;

    CEventConnection conn_INITO;

    CDataConnection *conn_QI;
    CDataConnection *conn_LED0;
    CDataConnection *conn_SW0;
    CDataConnection *conn_ADC_CH_0;
    CDataConnection *conn_PWM;
    CDataConnection *conn_UpdateInterval;

    CDataConnection conn_QO;
    CDataConnection conn_STATUS;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_INIT(const CIEC_BOOL &paQI, const CIEC_STRING &paLED0, const CIEC_STRING &paSW0, const CIEC_STRING &paADC_CH_0, const CIEC_STRING &paPWM, const CIEC_TIME &paUpdateInterval, CIEC_BOOL &paQO, CIEC_STRING &paSTATUS) {
      var_QI = paQI;
      var_LED0 = paLED0;
      var_SW0 = paSW0;
      var_ADC_CH_0 = paADC_CH_0;
      var_PWM = paPWM;
      var_UpdateInterval = paUpdateInterval;
      executeEvent(scmEventINITID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
    }

    void operator()(const CIEC_BOOL &paQI, const CIEC_STRING &paLED0, const CIEC_STRING &paSW0, const CIEC_STRING &paADC_CH_0, const CIEC_STRING &paPWM, const CIEC_TIME &paUpdateInterval, CIEC_BOOL &paQO, CIEC_STRING &paSTATUS) {
      evt_INIT(paQI, paLED0, paSW0, paADC_CH_0, paPWM, paUpdateInterval, paQO, paSTATUS);
    }
};


