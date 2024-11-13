/*******************************************************************************
 * Copyright (c) 2024 Jose Cabral
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Jose Cabral
 *      - initial integration of the OPC-UA protocol
 *******************************************************************************/

#ifndef SRC_COM_OPC_UA_DETAIL_LDSMEHANDLER_H_
#define SRC_COM_OPC_UA_DETAIL_LDSMEHANDLER_H_

#include <open62541.h>

#include <string>
#include <vector>

namespace forte::com::opc_ua::detail {

/**
 * @brief Handles all things related to LDS-ME
 * 
 * Configures the server to accept LDS-ME messages and handles them accordingly.
 */
class LdsMeHandler {
  public:

    /**
     * @brief Register this instance as handler for incoming discovery message
     * 
     * @param paUaServer OpcUa server to handle
     */
    LdsMeHandler(UA_Server& paUaServer);

    /**
     * @brief Un-register this instance as handler incoming discovery message
     * 
     */
    ~LdsMeHandler();


    /**
     * @brief Sets the proper values to the server configuration so it accepts LDS-ME messages
     * 
     * @param paUaServerConfig configuration to be set
     * @param paServerName server name to be used when registering to the discovery server 
     */
    static void configureServer(UA_ServerConfig& paUaServerConfig, const std::string& paServerName);
  
  private:

    bool registerDiscoveryServer(const UA_String& paDiscoveryUrl);
    void deregisterDiscoveryServer(const UA_String& paDiscoveryUrl);

    static void serverOnNetworkCallback(const UA_ServerOnNetwork* paServerOnNetwork, UA_Boolean paIsServerAnnounce, UA_Boolean paIsTxtReceived, void* paData);

    UA_Server& mUaServer;

    // Handle the lifetime of a UA_String nicely
    class UA_StringRAII {
      public:
        UA_StringRAII(const UA_String& paString) {
          UA_String_copy(&paString, &mString);
        }

        UA_StringRAII(const char* paString) {
          mString = UA_String_fromChars(paString);
        }

        ~UA_StringRAII() {
          UA_String_clear(&mString);
        }

        UA_StringRAII(UA_StringRAII&& paOther) {
          *this = std::move(paOther);
        }
        
        UA_StringRAII& operator=(UA_StringRAII&& paOther) {
          mString = paOther.mString;
          UA_String_init(&paOther.mString);  
          return *this; 
        };


        UA_StringRAII(const UA_StringRAII&) = delete;
        UA_StringRAII& operator=(const UA_StringRAII&) = delete;
      
        UA_String mString;
    };

    /// List of discovery servers where this instance is already registered
    std::vector<UA_StringRAII> mRegisteredServers;
};
}

#endif // SRC_COM_OPC_UA_DETAIL_LDSMEHANDLER_H_
