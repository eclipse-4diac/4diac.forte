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

#include "EliteBoard.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EliteBoard_gen.cpp"
#endif

#include <handle/PinHandle.h>
#include <extevhandlerhelper.h>
#include <stm32h743xx.h>
#include <stm32h7xx_hal_gpio.h>

DEFINE_FIRMWARE_FB(FORTE_EliteBoard, g_nStringIdEliteBoard)

const TForteInt16 FORTE_EliteBoard::scmEIWithIndexes[] = {-1};
const CStringDictionary::TStringId FORTE_EliteBoard::scmEventInputNames[] = {g_nStringIdMAP};
const CStringDictionary::TStringId FORTE_EliteBoard::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TForteInt16 FORTE_EliteBoard::scmEOWithIndexes[] = {-1};
const CStringDictionary::TStringId FORTE_EliteBoard::scmEventOutputNames[] = {g_nStringIdMAPO};
const CStringDictionary::TStringId FORTE_EliteBoard::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SAdapterInstanceDef FORTE_EliteBoard::scmAdapterInstances[] = {
    {g_nStringIdPortAdapter, g_nStringIdPortA, true},
    {g_nStringIdPortAdapter, g_nStringIdPortB, true},
    {g_nStringIdPortAdapter, g_nStringIdPortC, true},
    {g_nStringIdPortAdapter, g_nStringIdPortD, true},
    {g_nStringIdPortAdapter, g_nStringIdPortE, true},
    {g_nStringIdPortAdapter, g_nStringIdPortF, true},
    {g_nStringIdPortAdapter, g_nStringIdPortG, true},
    {g_nStringIdPortAdapter, g_nStringIdPortH, true},
    {g_nStringIdPortAdapter, g_nStringIdPortI, true},
    {g_nStringIdPortAdapter, g_nStringIdPortJ, true},
    {g_nStringIdPortAdapter, g_nStringIdPortK, true}};

const SFBInterfaceSpec FORTE_EliteBoard::scmFBInterfaceSpec = {
    1,       scmEventInputNames, scmEventInputTypeIds,
    nullptr, scmEIWithIndexes,
    1,       scmEventOutputNames, scmEventOutputTypeIds,nullptr,
    nullptr, scmEOWithIndexes,
    0,       nullptr,
    nullptr, 0,
    nullptr, nullptr,
    11,      scmAdapterInstances};

FORTE_EliteBoard::FORTE_EliteBoard(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer)
    : forte::core::io::IOConfigFBController(paContainer, scmFBInterfaceSpec,
                                            paInstanceNameId, mFBConnData,
                                            mFBVarsData),
      mEventHandler{getExtEvHandler<EliteBoardDeviceController>(*this)} {};

forte::core::io::IODeviceController *
FORTE_EliteBoard::createDeviceController(CDeviceExecution &paDeviceExecution) {
  return &mEventHandler;
}

// The base addresses of the MMIO GPIO ports. Provided by the vendor.
constexpr uint32_t port_addresses[] = {
    GPIOA_BASE, GPIOB_BASE, GPIOC_BASE, GPIOD_BASE, GPIOE_BASE, GPIOF_BASE,
    GPIOG_BASE, GPIOH_BASE, GPIOI_BASE, GPIOJ_BASE, GPIOK_BASE,
};

FORTE_PortAdapter &FORTE_EliteBoard::getPortAdapterByIndex(int index) {
  return (*static_cast<FORTE_PortAdapter *>(mAdapters[index]));
}

bool FORTE_EliteBoard::configurePortFB(int index) {
  auto &adapter = getPortAdapterByIndex(index);
  if (adapter.getPeer() == nullptr) {
    // Adapter is not connected.
    return false;
  }

  adapter.GPIO_Port_Addr() = port_addresses[index];

  sendAdapterEvent(index, FORTE_PortAdapter::scmEventMAPID);
  return true;
}

void FORTE_EliteBoard::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {

  if (paEIID == scmEventMAPID) {
    // start initialisation chain
    mCurrentAdapterIndex = 0;

    while (mCurrentAdapterIndex < mAdapterCount &&
           !configurePortFB(mCurrentAdapterIndex)) {
      mCurrentAdapterIndex++;
    }

    mCurrentAdapterIndex++;
  } else if (paEIID == getPortAdapterByIndex(mCurrentAdapterIndex).MAPO()) {
    // previous adapter finished initialisation
    if (mCurrentAdapterIndex < mAdapterCount) {
      // not completed yet

      while (mCurrentAdapterIndex < mAdapterCount &&
             !configurePortFB(mCurrentAdapterIndex)) {
        mCurrentAdapterIndex++;
      }

      if (mCurrentAdapterIndex >= mAdapterCount) {
        // initialisation complete
        sendOutputEvent(scmEventMAPOID, paECET);
      } else {
        // not completed yet
        mCurrentAdapterIndex++;
      }
    } else {
      // initialisation complete
      sendOutputEvent(scmEventMAPOID, paECET);
    }
  }
}
