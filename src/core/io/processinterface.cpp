/*******************************************************************************
 * Copyright (c) 2016, 2023 Johannes Messmer (admin@jomess.com), fortiss GmbH,
 *                          Johannes Kepler University Linz
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Johannes Messmer - initial API and implementation and/or initial documentation
 *   Jose Cabral - Cleaning of namespaces
 *   Alois Zoitl - further clean-ups and performance improvements on IOHandle
 *******************************************************************************/

#include "processinterface.h"
#include "criticalregion.h"

using namespace forte::core::io;
using namespace std::string_literals;

const CIEC_STRING ProcessInterface::scmOK("OK"_STRING);
const CIEC_STRING ProcessInterface::scmWaitingForHandle("Waiting for handle.."_STRING);
const CIEC_STRING ProcessInterface::scmFailedToRegister("Failed to register observer."_STRING);
const CIEC_STRING ProcessInterface::scmMappedWrongDirectionOutput("Mapped invalid direction. A Q block requires an output handle."_STRING);
const CIEC_STRING ProcessInterface::scmMappedWrongDirectionInput("Mapped invalid direction. An I block requires an input handle."_STRING);
const CIEC_STRING ProcessInterface::scmMappedWrongDataType("Mapped invalid data type."_STRING);


ProcessInterface::ProcessInterface(forte::core::CFBContainer &paContainer, const SFBInterfaceSpec& paInterfaceSpec, const CStringDictionary::TStringId paInstanceNameId) :
    CProcessInterfaceBase(paContainer, paInterfaceSpec, paInstanceNameId), IOObserver() {
  mIsListening = false;
  mIsReady = false;
}

ProcessInterface::~ProcessInterface() {
  deinitialise();
}

bool ProcessInterface::initialise(bool paIsInput, CEventChainExecutionThread *const paECET) {
  mDirection = paIsInput ? IOMapper::In : IOMapper::Out;
  if(paIsInput && (getFBInterfaceSpec().mNumDOs < 3)) {
    mType = CIEC_ANY::e_Max; //we assume that any FB which has no "IN" Output must be a EVENT-Only FB.
  }
  else if(!paIsInput && (getFBInterfaceSpec()->mNumDIs < 3)) {
    mType = CIEC_ANY::e_Max; //we assume that any FB which has no "OUT" Input must be a EVENT-Only FB.
  }
  else {
    //as it has a index 2 here, we safely can do this
    mType = (paIsInput ? getDO(2) : getDI(2))->getDataTypeID();
  }

  mIsReady = false;
  STATUS() = CIEC_STRING(scmWaitingForHandle);

  // Reset before initialization
  deinitialise();

  // Register interface
  if(!(mIsListening = IOMapper::getInstance().registerObserver(getFullQualifiedApplicationInstanceName('.'), this))) {
    STATUS() = scmFailedToRegister;
    return false;
  }

  if(mDirection == IOMapper::In) {
    setEventChainExecutor(paECET);
  }

  return mIsReady;
}

bool ProcessInterface::deinitialise() {
  // Deregister interface
  if(mIsListening) {
    IOMapper::getInstance().deregisterObserver(this);
  }

  return !mIsReady;
}

bool ProcessInterface::read(CIEC_ANY &paData) {
  CCriticalRegion criticalRegion(mSyncMutex);
  if(!mIsReady) {
    return false;
  }

  mHandle->get(paData);

  return true;
}

bool ProcessInterface::write(CIEC_ANY &paData) {
  CCriticalRegion criticalRegion(mSyncMutex);
  if(!mIsReady) {
    return false;
  }

  mHandle->set(paData);

  return true;
}

bool ProcessInterface::read() {
  CCriticalRegion criticalRegion(mSyncMutex);
  if(!mIsReady) {
    return false;
  }

  switch(mHandle->getIOHandleDataType()){
    case CIEC_ANY::e_BOOL:
      mHandle->get(IN_X());
      break;
    case CIEC_ANY::e_BYTE:
      mHandle->get(IN_B());
      break;
    case CIEC_ANY::e_WORD:
      mHandle->get(IN_W());
      break;
    case CIEC_ANY::e_DWORD:
      mHandle->get(IN_D());
      break;
    case CIEC_ANY::e_LWORD:
      mHandle->get(IN_L());
      break;
    case CIEC_ANY::e_Max:
      // we are an event only IO FB
      return true; //it has no "IN" ...
    default:
      return false;
  }

  return true;
}

bool ProcessInterface::write() {
  CCriticalRegion criticalRegion(mSyncMutex);
  if(!mIsReady) {
    return false;
  }

  switch(mHandle->getIOHandleDataType()){
    case CIEC_ANY::e_BOOL:
      mHandle->set(OUT_X());
      break;
    case CIEC_ANY::e_BYTE:
    mHandle->set(OUT_B());
      break;
    case CIEC_ANY::e_WORD:
    mHandle->set(OUT_W());
      break;
    case CIEC_ANY::e_DWORD:
    mHandle->set(OUT_D());
      break;
    case CIEC_ANY::e_LWORD:
    mHandle->set(OUT_L());
      break;
    case CIEC_ANY::e_Max:
    mHandle->set(QI()); //DUMMY, TODO what is right here ??!!??
    break;
    default:
      return false;
  }

  return true;
}

bool ProcessInterface::onChange() {
  return read();
}

void ProcessInterface::onHandle(IOHandle* paHandle) {
  {
    CCriticalRegion criticalRegion(mSyncMutex);

    IOObserver::onHandle(paHandle);

    if(paHandle->getIOHandleDataType() != mType) {
      STATUS() = scmMappedWrongDataType;
      return;
    }

    if(paHandle->getDirection() != mDirection) {
      STATUS() = mDirection == IOMapper::In ? scmMappedWrongDirectionInput : scmMappedWrongDirectionOutput;
      return;
    }

    STATUS() = scmOK;
    mIsReady = true;
  }

  // Read & write current state
  if(mDirection == IOMapper::In) {
    QO() = CIEC_BOOL(read());
  } else {
    QO() = CIEC_BOOL(write());
  }
}

void ProcessInterface::dropHandle() {
  CCriticalRegion criticalRegion(mSyncMutex);

  IOObserver::dropHandle();

  QO() = CIEC_BOOL(false);
  STATUS() = scmWaitingForHandle;
  mIsReady = CIEC_BOOL(false);
}

