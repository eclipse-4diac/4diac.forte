
#include "lds_me_handler.h"

#include "devlog.h"

using namespace forte::com::opc_ua::detail;

LdsMeHandler::LdsMeHandler(UA_Server& paUaServer) : mUaServer{paUaServer}  {
  UA_Server_setServerOnNetworkCallback(&mUaServer, serverOnNetworkCallback, this);
}

LdsMeHandler::~LdsMeHandler() {
  for(const auto& registeredServer : mRegisteredServers){
    deregisterDiscoveryServer(registeredServer.mString);
  }
  UA_Server_setServerOnNetworkCallback(&mUaServer, nullptr, nullptr);
}

void LdsMeHandler::configureServer(UA_ServerConfig& paUaServerConfig, const std::string& paServerName) {
  UA_String_clear(&paUaServerConfig.mdnsConfig.mdnsServerName);
  paUaServerConfig.mdnsConfig.mdnsServerName = UA_String_fromChars(paServerName.c_str());
  // Enable the mDNS announce and response functionality
  paUaServerConfig.mdnsEnabled = true;
}

void LdsMeHandler::serverOnNetworkCallback(const UA_ServerOnNetwork* paServerOnNetwork, UA_Boolean paIsServerAnnounce, UA_Boolean paIsTxtReceived, void* paData) { 

  if(!paIsTxtReceived) {
    return; // we wait until the corresponding TXT record is announced.
  }

  DEVLOG_DEBUG("[OPC UA LDS ME]: mDNS %s '%.*s' with url '%.*s'\n", paIsServerAnnounce ? "announce" : "remove", paServerOnNetwork->serverName.length,
      paServerOnNetwork->serverName.data, paServerOnNetwork->discoveryUrl.length, paServerOnNetwork->discoveryUrl.data);

  // check if server is LDS
  bool isServerLDS = false;

  UA_StringRAII ldsStr("LDS");
  for(unsigned int i = 0; i < paServerOnNetwork->serverCapabilitiesSize; i++) {
    if(UA_String_equal(&paServerOnNetwork->serverCapabilities[i], &ldsStr.mString)) {
      isServerLDS = true;
      break;
    }
  }

  // skip non-LDS servers
  if(!isServerLDS) {
    return;
  }

  auto handler = static_cast<LdsMeHandler*>(paData);

  auto foundDiscoveryUrl = handler->mRegisteredServers.end();
  for(auto iter = handler->mRegisteredServers.begin(); iter != handler->mRegisteredServers.end(); iter++) {
    if(UA_String_equal(&paServerOnNetwork->discoveryUrl, &iter->mString)) {
      foundDiscoveryUrl = iter;
      break;
    }
  }

  // if a new server is being announced
  if(paIsServerAnnounce && foundDiscoveryUrl == handler->mRegisteredServers.end()) {
    if(handler->registerDiscoveryServer(paServerOnNetwork->discoveryUrl)){
        handler->mRegisteredServers.emplace_back(paServerOnNetwork->discoveryUrl);
    }
  // if a known server is being un-announced
  } else if(!paIsServerAnnounce && foundDiscoveryUrl != handler->mRegisteredServers.end()) {
    handler->deregisterDiscoveryServer(foundDiscoveryUrl->mString);
    handler->mRegisteredServers.erase(foundDiscoveryUrl);
  }
}

bool LdsMeHandler::registerDiscoveryServer(const UA_String& paDiscoveryUrl) {
  
  UA_ClientConfig clientConfig;
  memset(&clientConfig, 0, sizeof(UA_ClientConfig));
  UA_ClientConfig_setDefault(&clientConfig);
  auto retVal = UA_Server_registerDiscovery(&mUaServer, &clientConfig, paDiscoveryUrl, UA_STRING_NULL);
  if( UA_STATUSCODE_GOOD != retVal) {
    DEVLOG_ERROR("[OPC UA LDSME]: Could not register with LDS. Error: %s\n", UA_StatusCode_name(retVal));
    return false;
  }
  DEVLOG_INFO("[OPC UA LDSME]: Registered to LDS '%.*s'\n", paDiscoveryUrl.length, paDiscoveryUrl.data);
  return true;
}

void LdsMeHandler::deregisterDiscoveryServer(const UA_String& paDiscoveryUrl) {
  UA_ClientConfig clientConfig;
  memset(&clientConfig, 0, sizeof(UA_ClientConfig));
  UA_ClientConfig_setDefault(&clientConfig);

  auto retVal = UA_Server_deregisterDiscovery(&mUaServer, &clientConfig, paDiscoveryUrl);
  // if unregister fails, we don't do anything else
  if( UA_STATUSCODE_GOOD != retVal) {
    DEVLOG_ERROR("[OPC UA LDSME]: Could not deregister with LDS. Error: %s\n", UA_StatusCode_name(retVal));
    return;
  }

  DEVLOG_INFO("[OPC UA LDSME]: Unregistered from LDS '%.*s'\n", paDiscoveryUrl.length, paDiscoveryUrl.data);
}