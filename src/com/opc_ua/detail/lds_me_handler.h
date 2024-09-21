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

#include <vector>
#include <string>

namespace forte::com::opc_ua::detail {

class LdsMeHandler {
  public:
    LdsMeHandler(UA_Server& paUaServer);
    static void configureServer(UA_ServerConfig& paUaServerConfig, const std::string& paServerName);
  
  private:
    void registerWithLds(const UA_String& paDiscoveryUrl);
    void removeLdsRegister(const UA_String& paDiscoveryUrl);

    static void serverOnNetworkCallback(const UA_ServerOnNetwork* paServerOnNetwork, UA_Boolean paIsServerAnnounce, UA_Boolean paIsTxtReceived, void* paData);

    UA_Server& mUaServer;

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

    /**
     * List of LDS servers where this instance is already registered.
     */
    std::vector<ClientWithLds> mRegisteredWithLds;
};
}

#endif // SRC_COM_OPC_UA_DETAIL_LDSMEHANDLER_H_
