
#include "lds_me_handler.h"

#include "devlog.h"

using namespace forte::com::opc_ua::detail;

LdsMeHandler::ClientWithLds::ClientWithLds(const UA_String& paDiscoveryUrl) {
  mClient = UA_Client_new();
  UA_ClientConfig_setDefault(UA_Client_getConfig(mClient));
  UA_String_copy(&paDiscoveryUrl, &mDiscoveryUrl);
}

LdsMeHandler::ClientWithLds::ClientWithLds(LdsMeHandler::ClientWithLds&& other) {
  *this = std::move(other);
}

LdsMeHandler::ClientWithLds& LdsMeHandler::ClientWithLds::operator=(LdsMeHandler::ClientWithLds&& other ) {
  mDiscoveryUrl = other.mDiscoveryUrl;
  UA_String_init(&other.mDiscoveryUrl);
  mClient = other.mClient;
  other.mClient = nullptr;
  return *this;
} 

LdsMeHandler::ClientWithLds::~ClientWithLds() {
  if(mClient){
    UA_Client_disconnect(mClient);
    UA_Client_delete(mClient);
  }
  if(mDiscoveryUrl.data){
    UA_String_clear(&mDiscoveryUrl);
  }
}

LdsMeHandler::LdsMeHandler(UA_Server& paUaServer) : mUaServer{paUaServer}  {
  UA_Server_setServerOnNetworkCallback(&mUaServer, serverOnNetworkCallback, this);
}      

void LdsMeHandler::configureServer(UA_ServerConfig& paUaServerConfig, const std::string& paServerName) {
  // hostname will be added by mdns library
  UA_String_clear(&paUaServerConfig.mdnsConfig.mdnsServerName);
  paUaServerConfig.mdnsConfig.mdnsServerName = UA_String_fromChars(paServerName.c_str());
  // Enable the mDNS announce and response functionality
  paUaServerConfig.mdnsEnabled = true;
}

void LdsMeHandler::serverOnNetworkCallback(const UA_ServerOnNetwork* paServerOnNetwork, UA_Boolean paIsServerAnnounce, UA_Boolean paIsTxtReceived, void* paData) { 

  auto handler = static_cast<LdsMeHandler*>(paData);

  if(!paIsTxtReceived) {
    return; // we wait until the corresponding TXT record is announced.
  }

  DEVLOG_DEBUG("[OPC UA LDS ME]: mDNS %s '%.*s' with url '%.*s'\n", paIsServerAnnounce ? "announce" : "remove", paServerOnNetwork->serverName.length,
      paServerOnNetwork->serverName.data, paServerOnNetwork->discoveryUrl.length, paServerOnNetwork->discoveryUrl.data);

  // check if server is LDS, and then register
  UA_String ldsStr = UA_String_fromChars("LDS");
  for(unsigned int i = 0; i < paServerOnNetwork->serverCapabilitiesSize; i++) {
    if(UA_String_equal(&paServerOnNetwork->serverCapabilities[i], &ldsStr)) {
      if(paIsServerAnnounce) {
        handler->registerWithLds(paServerOnNetwork->discoveryUrl);
      } else {
        handler->removeLdsRegister(paServerOnNetwork->discoveryUrl);
      }
      break;
    }
  }
  UA_String_clear(&ldsStr);
}

void LdsMeHandler::registerWithLds(const UA_String& paDiscoveryUrl) {
  // check if already registered with the given LDS
  for(const auto& clientWithLds : mRegisteredWithLds) {
    if(UA_String_equal(&paDiscoveryUrl, &clientWithLds.mDiscoveryUrl)) {
      return;
    }
  }

  ClientWithLds clienWithLDS(paDiscoveryUrl);
  UA_StatusCode retVal = UA_Server_addPeriodicServerRegisterCallback(&mUaServer, clienWithLDS.mClient, reinterpret_cast<const char*>(clienWithLDS.mDiscoveryUrl.data), 10 * 60 * 1000, 500, nullptr);
  if( UA_STATUSCODE_GOOD != retVal) {
    DEVLOG_ERROR("[OPC UA LDSME]: Could not register with LDS. Error: %s\n", UA_StatusCode_name(retVal));
    return;
  }
  mRegisteredWithLds.emplace_back(std::move(clienWithLDS));
  DEVLOG_INFO("[OPC UA LDSME]: Registered to LDS '%.*s'\n", paDiscoveryUrl.length, paDiscoveryUrl.data);
}

void LdsMeHandler::removeLdsRegister(const UA_String& paDiscoveryUrl) {
  for(auto iter = mRegisteredWithLds.begin(); iter != mRegisteredWithLds.end(); iter++) {
    if(UA_String_equal(&paDiscoveryUrl, &iter->mDiscoveryUrl)) {
      DEVLOG_INFO("[OPC UA LDSME]: Unregistered from LDS '%.*s'\n", paDiscoveryUrl.length, paDiscoveryUrl.data);
      mRegisteredWithLds.erase(iter);
      break;
    }
  }
}