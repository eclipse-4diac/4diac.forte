/*******************************************************************************
 * Copyright (c) 2024 Primetals Technologies Austria GmbH, Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Alois Zoitl, Martin Jobst - initial implementation and rework communication
 *                                infrastructure
 *******************************************************************************/

#include "forteinstance.h"
#include "deviceFactory.h"


std::unique_ptr<CDevice> C4diacFORTEInstance::createDev(const std::string &paMGRID) {
  auto dev = DeviceFactory::createDevice(paMGRID);
  dev->initialize();
  return dev;
}

bool C4diacFORTEInstance::startupNewDevice(const std::string &paMGRID){
  if(mActiveDevice){
    //we have a current active device stop it
    triggerDeviceShutdown();
    awaitDeviceShutdown();
  }
  mActiveDevice = createDev(paMGRID);
  if(mActiveDevice){
    mActiveDevice->startDevice();
  }
  return mActiveDevice.operator bool();
}

void C4diacFORTEInstance::triggerDeviceShutdown() {
  if(mActiveDevice) {
    mActiveDevice->changeExecutionState(EMGMCommandType::Kill);
  }
}

void C4diacFORTEInstance::awaitDeviceShutdown() {
  if(mActiveDevice) {
    mActiveDevice->awaitShutdown();
  }
}



