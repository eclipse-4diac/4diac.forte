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

#include "Esp32EthernetKitIO_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "Esp32EthernetKitIO_fbt_gen.cpp"
#endif

#pragma region includes
#include <handler/IOHandleGPIODescriptor.h>
#include <handler/IOHandleADCDescriptor.h>
#include <handler/IOHandlePWMDescriptor.h>
#include "handler/IODeviceController.h"
#pragma endregion includes

DEFINE_FIRMWARE_FB(FORTE_Esp32EthernetKitIO, g_nStringIdEsp32EthernetKitIO)

const CStringDictionary::TStringId FORTE_Esp32EthernetKitIO::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdLED0, g_nStringIdSW0, g_nStringIdADC_CH_0, g_nStringIdPWM, g_nStringIdUpdateInterval};
const CStringDictionary::TStringId FORTE_Esp32EthernetKitIO::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdTIME};
const CStringDictionary::TStringId FORTE_Esp32EthernetKitIO::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_Esp32EthernetKitIO::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING};
const TDataIOID FORTE_Esp32EthernetKitIO::scmEIWith[] = {0, 5, 1, 2, 3, 4, scmWithListDelimiter};
const TForteInt16 FORTE_Esp32EthernetKitIO::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_Esp32EthernetKitIO::scmEventInputNames[] = {g_nStringIdINIT};
const CStringDictionary::TStringId FORTE_Esp32EthernetKitIO::scmEventInputTypeIds[] = {g_nStringIdEInit};
const TDataIOID FORTE_Esp32EthernetKitIO::scmEOWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_Esp32EthernetKitIO::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_Esp32EthernetKitIO::scmEventOutputNames[] = {g_nStringIdINITO};
const CStringDictionary::TStringId FORTE_Esp32EthernetKitIO::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_Esp32EthernetKitIO::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  6, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_Esp32EthernetKitIO::FORTE_Esp32EthernetKitIO(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
#pragma region base class spec
    FORTE_ZephyrIOBase(paContainer, scmFBInterfaceSpec, paInstanceNameId),
#pragma endregion base class spec
    var_UpdateInterval(40000000_TIME),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_INITO(this, 0),
    conn_QI(nullptr),
    conn_LED0(nullptr),
    conn_SW0(nullptr),
    conn_ADC_CH_0(nullptr),
    conn_PWM(nullptr),
    conn_UpdateInterval(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS) {
};

void FORTE_Esp32EthernetKitIO::setInitialValues() {
  var_QI = 0_BOOL;
  var_LED0 = ""_STRING;
  var_SW0 = ""_STRING;
  var_ADC_CH_0 = ""_STRING;
  var_PWM = ""_STRING;
  var_UpdateInterval = 40000000_TIME;
  var_QO = 0_BOOL;
  var_STATUS = ""_STRING;
}

#pragma region remove executeEvent()
// using FORTE_ZephyrIOBase::executeEvent
#pragma endregion remove executeEvent()

void FORTE_Esp32EthernetKitIO::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(5, var_UpdateInterval, conn_UpdateInterval);
      readData(1, var_LED0, conn_LED0);
      readData(2, var_SW0, conn_SW0);
      readData(3, var_ADC_CH_0, conn_ADC_CH_0);
      readData(4, var_PWM, conn_PWM);
      break;
    }
    default:
      break;
  }
}

void FORTE_Esp32EthernetKitIO::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_Esp32EthernetKitIO::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_LED0;
    case 2: return &var_SW0;
    case 3: return &var_ADC_CH_0;
    case 4: return &var_PWM;
    case 5: return &var_UpdateInterval;
  }
  return nullptr;
}

CIEC_ANY *FORTE_Esp32EthernetKitIO::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_Esp32EthernetKitIO::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
  }
  return nullptr;
}

CDataConnection **FORTE_Esp32EthernetKitIO::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_LED0;
    case 2: return &conn_SW0;
    case 3: return &conn_ADC_CH_0;
    case 4: return &conn_PWM;
    case 5: return &conn_UpdateInterval;
  }
  return nullptr;
}

CDataConnection *FORTE_Esp32EthernetKitIO::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

#pragma region define IOs
namespace {
  struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
  struct gpio_dt_spec sw0 = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);
  struct gpio_spec_mod {
    const gpio_dt_spec* spec;
    gpio_flags_t flags;
  };
  const gpio_spec_mod gpio_spec_mods[] = {
    { &led0, GPIO_OUTPUT },
    { &sw0, GPIO_INPUT | GPIO_INT_EDGE_BOTH },
  };

#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
  !DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
#error "No suitable devicetree overlay specified"
#endif

#define DT_SPEC_AND_COMMA(node_id, prop, idx) \
  ADC_DT_SPEC_GET_BY_IDX(node_id, idx),

/* Data of ADC io-channels specified in devicetree. */
  const struct adc_dt_spec adc_channels[] = {
    DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels,
    DT_SPEC_AND_COMMA)
  };

  struct pwm_dt_spec pwm0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm0));
  pwm_dt_spec* pwm_specs[] = {
    &pwm0,
  };
};

void FORTE_Esp32EthernetKitIO::setConfig() {
  IODeviceController::Config config;
  config.updateInterval = static_cast<CIEC_TIME*>(getDI(
    FORTE_ZephyrIOBase::initialDIOffset +
    FORTE_Esp32EthernetKitIO::numberOfGPIOs +
    FORTE_Esp32EthernetKitIO::numberOfADCChannels +
    FORTE_Esp32EthernetKitIO::numberOfPWMs
    ))->getInMilliSeconds();
  getDeviceController()->setConfig(&config);
}

void FORTE_Esp32EthernetKitIO::onStartup(CEventChainExecutionThread * const paECET) {
  // Initialize handles
  for (size_t i = 0; i < FORTE_Esp32EthernetKitIO::numberOfGPIOs; i++) {
    const auto id = std::string(*static_cast<CIEC_STRING*>(
      getDI(FORTE_ZephyrIOBase::initialDIOffset + i)));
    if (!gpio_spec_mods[i].spec) {
      DEVLOG_ERROR("FORTE_Esp32EthernetKitIO::onStartup: id %s, device spec is null\n", id.c_str());
      continue;
    }
    IOHandleGPIODescriptor descr(
      id,
      (gpio_spec_mods[i].flags & GPIO_OUTPUT) ? IOMapper::Out : IOMapper::In,
      gpio_spec_mods[i].spec,
      gpio_spec_mods[i].flags);
    initHandle(descr);
  }
  if (FORTE_Esp32EthernetKitIO::numberOfADCChannels != ARRAY_SIZE(adc_channels)) {
    DEVLOG_ERROR("FORTE_Esp32EthernetKitIO::onStartup: ADC channel count configuration mismatch\n");
  } else for (size_t i = 0; i < FORTE_Esp32EthernetKitIO::numberOfADCChannels; i++) {
    const auto id = std::string(*static_cast<CIEC_STRING*>(
      getDI(FORTE_ZephyrIOBase::initialDIOffset + FORTE_Esp32EthernetKitIO::numberOfGPIOs + i)));
    if (!adc_is_ready_dt(&adc_channels[i])) {
      DEVLOG_ERROR("FORTE_Esp32EthernetKitIO::onStartup: id %s ADC controller device %s not ready\n",
        id.c_str(), adc_channels[i].dev->name);
      continue;
    }
    IOHandleADCDescriptor descr(
      id,
      &adc_channels[i]);
    initHandle(descr);
  }
  for (size_t i = 0; i < FORTE_Esp32EthernetKitIO::numberOfPWMs; i++) {
    const auto id = std::string(*static_cast<CIEC_STRING*>(getDI(
      FORTE_ZephyrIOBase::initialDIOffset +
      FORTE_Esp32EthernetKitIO::numberOfGPIOs +
      FORTE_Esp32EthernetKitIO::numberOfADCChannels + i)));
    if (!pwm_is_ready_dt(pwm_specs[i])) {
      DEVLOG_ERROR("FORTE_Esp32EthernetKitIO::onStartup: id %s, PWM device %s not ready\n",
        id.c_str(), pwm_specs[i]->dev->name);
      continue;
    }
    IOHandlePWMDescriptor descr(
      id,
      pwm_specs[i]);
    initHandle(descr);
  }

  FORTE_ZephyrIOBase::onStartup(paECET);
}
#pragma endregion define IOs
