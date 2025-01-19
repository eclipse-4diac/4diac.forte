/*******************************************************************************
 * Copyright (c) 2018 - 2024 fortiss GmbH, Jose Cabral
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *  Jose Cabral - initial API and implementation and/or initial documentation
 *  Tarik Terzimehic - make OPC UA server port setable from the command line
 *******************************************************************************/

#include "forte_c.h"

#include "../utils/mainparam_utils.h"
#include "forte_architecture.h"
#include "forte_printer.h"
#include "forteinstance.h"

namespace {
  const unsigned int defaultPort = 61499;
  const unsigned int maxPortValue = 65535;
}

/**
* @brief Check if the correct endianess has been configured.
*/
bool checkEndianess();

int forteGlobalInitialize(int argc, char *argv[]){
  return CForteArchitecture::initialize(argc, argv);
}

int forteGlobalDeinitialize(){
  return CForteArchitecture::deinitialize();
}

FORTE_STATUS forteStartInstance(unsigned int paPort, TForteInstance* paResultInstance){

  if(maxPortValue < paPort){
    DEVLOG_ERROR("Provided port %d is not valid\n", paPort);
    return FORTE_WRONG_PARAMETERS;
  }

  if(0 == paPort){
    paPort = defaultPort;
  }

  char progName[] = "forte";
  char flag[] = "-c";
  char address[17] = "localhost:";
  char port[6];
  forte_snprintf(port, 6, "%u", paPort);
  strcat(address, port);

  char* arguments[] = { progName, flag, address };
  return forteStartInstanceGeneric(3, arguments, paResultInstance);
}

FORTE_STATUS forteStartInstanceGeneric(int argc, char *argv[], TForteInstance* paResultInstance){

  if(nullptr == paResultInstance){
    DEVLOG_ERROR("Provided result instance parameter is not valid\n");
    return FORTE_WRONG_PARAMETERS;
  }

  if(nullptr != *paResultInstance){
    DEVLOG_ERROR("Provided result instance already started\n");
    return FORTE_DEVICE_ALREADY_STARTED;
  }

  if(!checkEndianess()){
    // logged already in the function
    return FORTE_WRONG_ENDIANESS;
  }

  if(!CForteArchitecture::isInitialized()){
    DEVLOG_ERROR("The low level platform should be initialized before starting a forte instance\n");
    return FORTE_ARCHITECTURE_NOT_READY;
  }

  const auto ipPort = parseCommandLineArguments(argc, argv);
  if((ipPort == nullptr) || (0 == strlen(ipPort)) || (nullptr == strchr(ipPort, ':'))){
    listHelp();
    return FORTE_WRONG_PARAMETERS;
  }
  
  C4diacFORTEInstance *instance = new C4diacFORTEInstance();
  if(!instance->startupNewDevice(ipPort)) {
    delete instance;
    return FORTE_COULD_NOT_CREATE_DEVICE;
  }
  *paResultInstance = instance;

  return FORTE_OK;
}

void forteRequestStopInstance(TForteInstance paInstance){
  if(!CForteArchitecture::isInitialized() || paInstance == nullptr){
    return;
  }
  auto *instance = static_cast<C4diacFORTEInstance *>(paInstance);
  instance->triggerDeviceShutdown();
}

void forteWaitForInstanceToStop(TForteInstance paInstance) {
   if(!CForteArchitecture::isInitialized() || paInstance == nullptr){
    return;
  }
  auto *instance = static_cast<C4diacFORTEInstance *>(paInstance);
  instance->awaitDeviceShutdown();
  delete instance;
}

bool checkEndianess(){
  volatile TForteInt16 i = 1;
  char *p = (char *) &i;
  if(p[0] == 1){
    //we are on a little endian platform
#ifdef FORTE_BIG_ENDIAN
    DEVLOG_ERROR("Wrong endianess configured! You are on a little endian platform and have configured big endian!\n");
    return false;
#endif
  }
  else{
    //we are on a big endian platform
#ifdef FORTE_LITTLE_ENDIAN
    DEVLOG_ERROR("Wrong endianess configured! You are on a big endian platform and have configured little endian!\n");
    return false;
#endif
  }

  return true;
}
