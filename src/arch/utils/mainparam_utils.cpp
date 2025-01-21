/*******************************************************************************
 * Copyright (c) 2018 fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Tarik Terzimehic
 *    - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include <forte_config.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef FORTE_MULTIPLE_DEVICES
#include "deviceFactory.h"
#endif // FORTE_MULTIPLE_DEVICES

#ifdef FORTE_TRACE_CTF
#include <string>
#endif

/*!\brief Lists the help for FORTE
 *
 */
void listHelp(){
  printf("Usage: forte [options]\n");
  printf("Options:\n");
  printf("%-20s Display this information\n", "  -h");
  printf("%-20s Set the listening IP and port for the incoming connections\n", "  -c <IP>:<port>");
#ifdef FORTE_MULTIPLE_DEVICES
  printf("%-20s Set the device to be used\n", "  -d DEVICE_NAME");
#endif // FORTE_MULTIPLE_DEVICES
#ifdef FORTE_SUPPORT_BOOT_FILE
  printf("%-20s Set the boot-file where to read from to load the applications\n", "  -f <file>");
#endif
#ifdef FORTE_COM_OPC_UA
  printf("%-20s Set the listening port for the OPC UA connection\n", "  -op <port>");
  printf("%-20s Set the configuration file for the OPC UA clients\n", "  -oc <file>");
#endif //FORTE_COM_OPC_UA
#ifdef FORTE_COM_PAHOMQTT
  printf("%-20s Set the configuration file for the MQTT clients\n", "  -mc <file>");
#endif //FORTE_COM_PAHOMQTT
#ifdef FORTE_COM_HTTP
  printf("%-20s Set the listening port for the HTTP server\n", "  -Hp <port>");
#endif //FORTE_COM_HTTP
#ifdef FORTE_TRACE_CTF
  printf("%-20s Set the output directory for TRACE_CTF\n", "  -t <directory>");
#endif //FORTE_TRACE_CTF
}

/*!\brief Parses the command line arguments passed to the main function
 *
 */
const char *parseCommandLineArguments(int argc, char *arg[]){

  const char *pIpPort = "localhost:61499"; //! Default Value (localhost:61499)

  if(argc > 1) {
    for(size_t i = 1; i < static_cast<size_t>(argc); i += 2) {
      if('-' == arg[i][0]) {
        switch(arg[i][1]){
          case 'c': //! sets the destination for the connection
            pIpPort = arg[i + 1];
            break;
#ifdef FORTE_MULTIPLE_DEVICES
          case 'd': //! sets the device to be used
            if(!DeviceFactory::setDeviceToCreate(arg[i + 1])){
              printf("The selected device '%s' is not valid. Select one of the following: %s\n", arg[i + 1], DeviceFactory::getAvailableDevices().c_str());
              return nullptr;
            }
            break;
#endif // FORTE_MULTIPLE_DEVICES
#ifdef FORTE_SUPPORT_BOOT_FILE
          case 'f': //! sets the boot-file to be used
            gCommandLineBootFile = arg[i + 1];
            break;
#endif //FORTE_SUPPORT_BOOT_FILE
#ifdef FORTE_COM_OPC_UA
          case 'o':
            if('p' == arg[i][2]) { //! Retrieves OPCUA server port number entered from the command line
              gOpcuaServerPort = static_cast<TForteUInt16>(atoi(arg[i + 1]));
            } else if('c' == arg[i][2]) { //! Retrieves OPCUA configuration file for clients entered from the command line
              gOpcuaClientConfigFile = arg[i + 1];
            }
            break;
#endif //FORTE_COM_OPC_UA
#ifdef FORTE_COM_PAHOMQTT
          case 'm':
            if('c' == arg[i][2]) { //! Retrieves MQTT configuration file for clients entered from the command line
              gMqttClientConfigFile = arg[i + 1];
            }
            break;
#endif //FORTE_COM_PAHOMQTT
#ifdef FORTE_COM_HTTP
          case 'H':
            if('p' == arg[i][2]) { //! Retrieves HTTP server port number entered from the command line
              gHTTPServerPort = static_cast<TForteUInt16>(atoi(arg[i + 1]));
            }
            break;
#endif //FORTE_COM_HTTP
#ifdef FORTE_TRACE_CTF
          case 't':
            void barectfSetup(std::string directory);
            barectfSetup(arg[i + 1] ?: "");
            break;
#endif //FORTE_TRACE_CTF
          default: //! Unknown parameter or -h -> Lists the help for FORTE
            return "";
        }
      } else { //! Unknown parameter -> Lists the help for FORTE
        return "";
      }
    }
  }

  return pIpPort;
}
