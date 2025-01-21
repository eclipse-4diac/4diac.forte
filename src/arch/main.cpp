/*******************************************************************************
 * Copyright (c) 2006, 2024 ACIN, Profactor GmbH, AIT, fortiss GmbH,
 *                          Primetals Technologies Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *  Alois Zoitl, Gerhard Ebenhofer, Thomas Strasser, Rene Smodic,
 *  Martin Melik Merkumians, Ingo Hegny, Filip Andren - initial API and implementation and/or initial documentation
 *  Tarik Terzimehic - make OPC UA server port setable from the command line
 *******************************************************************************/

#include <stdio.h>
#include <signal.h>
#include "../core/forteinstance.h"
#include "forte_architecture.h"

#include "../utils/mainparam_utils.h"

/*!\brief Check if the correct endianess has been configured.
 *
 * If the right endianess is not set this function will end FORTE.
 */
void checkEndianess();

void hookSignals();

C4diacFORTEInstance g4diacForteInstance;

void endForte(int ){
  g4diacForteInstance.triggerDeviceShutdown();
}

void callOnExit(){
  CForteArchitecture::deinitialize();
}

int main(int argc, char *arg[]){

  checkEndianess();

  if(auto result = CForteArchitecture::initialize(argc, arg); result != 0){
     return result;
  }

  std::atexit(callOnExit);

  hookSignals();

  const char *ipPort = parseCommandLineArguments(argc, arg);
  if((ipPort == nullptr) || (0 == strlen(ipPort)) || (nullptr == strchr(ipPort, ':'))) {
    //! Lists the help for FORTE
    listHelp();
    return -1;
  }

  if(!g4diacForteInstance.startupNewDevice(ipPort)) {
    DEVLOG_INFO("Could not start a new device\n");
    return -1;
  }

  DEVLOG_INFO("FORTE is up and running\n");
  g4diacForteInstance.awaitDeviceShutdown();
  DEVLOG_INFO("FORTE finished\n");

  return 0;
}

void checkEndianess(){
  int i = 1;
  char *p = (char *) &i;
  if(p[0] == 1){
    //we are on a little endian platform
#ifdef FORTE_BIG_ENDIAN
    DEVLOG_ERROR("Wrong endianess configured! You are on a little endian platform and have configured big endian!\n");
    exit(-1);
#endif
  }
  else{
    //we are on a big endian platform
#ifdef FORTE_LITTLE_ENDIAN
    DEVLOG_ERROR("Wrong endianess configured! You are on a big endian platform and have configured little endian!\n");
    exit(-1);
#endif
  }
}

void hookSignals() {
  signal(SIGINT, endForte);
  signal(SIGTERM, endForte);
#ifndef WIN32
  signal(SIGHUP, endForte);
#endif
}