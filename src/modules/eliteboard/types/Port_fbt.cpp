/*******************************************************************************
 * Copyright (c) 2021, 2022 Jonathan Lainer (kontakt@lainer.co.at)
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jonathan Lainer - Initial implementation.
 *******************************************************************************/

#include "Port_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "Port_fbt_gen.cpp"
#endif

#include "core/io/mapper/io_mapper.h"
#include <handler/EliteBoardDeviceController.h>
#include <handle/PinHandle.h>
#include <extevhandlerhelper.h>
#include <stm32h743xx.h>
#include <stm32h7xx_hal_gpio.h>

using namespace forte::core::io;

DEFINE_FIRMWARE_FB(FORTE_Port, g_nStringIdPort)

const CStringDictionary::TStringId FORTE_Port::scmDataInputNames[] = {
    g_nStringIdPin0,  g_nStringIdPin1,  g_nStringIdPin2,  g_nStringIdPin3,
    g_nStringIdPin4,  g_nStringIdPin5,  g_nStringIdPin6,  g_nStringIdPin7,
    g_nStringIdPin8,  g_nStringIdPin9,  g_nStringIdPin10, g_nStringIdPin11,
    g_nStringIdPin12, g_nStringIdPin13, g_nStringIdPin14, g_nStringIdPin15};

const CStringDictionary::TStringId FORTE_Port::scmDataInputTypeIds[] = {
    g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING,
    g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING,
    g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING,
    g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING,
    g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING,
    g_nStringIdWSTRING};

const SAdapterInstanceDef FORTE_Port::scmAdapterInstances[] = {
    {g_nStringIdPortAdapter, g_nStringIdPortInAdapter, false}};

const SFBInterfaceSpec FORTE_Port::scmFBInterfaceSpec = {
    0,
    nullptr, nullptr,
    nullptr,
    nullptr,
    0,
    nullptr, nullptr,
    nullptr,
    nullptr,
    16,
    scmDataInputNames,
    scmDataInputTypeIds,
    0,
    nullptr,
    nullptr,
    1,
    scmAdapterInstances};

void FORTE_Port::deregister_handles() {
  for (int i = 0; i < pin_cnt; i++) {
    if (mRegistered[i] != nullptr) {
      IOMapper::getInstance().deregisterHandle(*mRegistered[i]);
    }
  }
}

void FORTE_Port::register_handles() {
  uint32_t base = st_PortInAdapter().GPIO_Port_Addr();
  auto port = reinterpret_cast<GPIO_TypeDef *>(base);

  for (int i = 0; i < pin_cnt; i++) {
    auto id = static_cast<CIEC_WSTRING *>(getDI(i));

    // Only initialize pins that have an id.
    if (id->empty())
      continue;

    mRegistered[i] = id;

    // Create a GPIO pin handle using the port struct to identify the MMIO port and 
    // a bit mask to identify the pin.
    EliteBoardDeviceController::EliteBoardHandleDescriptor descr(id->getValue(), port, 1 << i);
    auto ctrl = getExtEvHandler<EliteBoardDeviceController>(*this);

    IOMapper::getInstance().registerHandle(id->getValue(), ctrl.createIOHandle(descr));
  }
}

void FORTE_Port::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  if (paEIID == st_PortInAdapter().MAP()) {
    deregister_handles();
    register_handles();

    sendAdapterEvent(0, FORTE_PortAdapter::scmEventMAPOID, paECET);
  }
}
