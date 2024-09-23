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
     * @brief Constructor
     * 
     * @param paUaServer OpcUa server to handle
     */
    LdsMeHandler(UA_Server& paUaServer);

    /**
     * @brief Sets the proper values to the server configuration so it accepts LDS-ME messages
     * 
     * @param paUaServerConfig configuration to be set
     * @param paServerName server name to be used when registering to the discovery server 
     */
    static void configureServer(UA_ServerConfig& paUaServerConfig, const std::string& paServerName);
  
  private:
    void registerWithLds(const UA_String& paDiscoveryUrl);
    void removeLdsRegister(const UA_String& paDiscoveryUrl);

    static void serverOnNetworkCallback(const UA_ServerOnNetwork* paServerOnNetwork, UA_Boolean paIsServerAnnounce, UA_Boolean paIsTxtReceived, void* paData);

    UA_Server& mUaServer;

    /**
     * @brief For each discovery server, this class handles the opcua client connectig to it
     * and the memory for the string holding the discovery url.
     * 
     */
    class ClientWithLds {
      public:
        ClientWithLds(const UA_String& paDiscoveryUrl);
        ~ClientWithLds();

        ClientWithLds(ClientWithLds&& other);
        ClientWithLds& operator=(ClientWithLds&& other);

        ClientWithLds(ClientWithLds&) = delete;
        ClientWithLds& operator=(ClientWithLds&) = delete;

        UA_String mDiscoveryUrl;
        UA_Client *mClient;
    };

    /// List of discovery servers where this instance is already registered
    std::vector<ClientWithLds> mRegisteredWithLds;
};
}

#endif // SRC_COM_OPC_UA_DETAIL_LDSMEHANDLER_H_
