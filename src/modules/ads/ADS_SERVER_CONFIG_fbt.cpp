/*******************************************************************************
 * Copyright (c) 2018 TU Wien/ACIN
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Martin Melik-Merkumians - initial contribution
 *******************************************************************************/

#include "ADS_SERVER_CONFIG_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ADS_SERVER_CONFIG_fbt_gen.cpp"
#endif

#include "CAdsConnectionManager.h"

DEFINE_FIRMWARE_FB(FORTE_ADS_SERVER_CONFIG, g_nStringIdADS_SERVER_CONFIG)

const CStringDictionary::TStringId FORTE_ADS_SERVER_CONFIG::scmDataInputNames[] = { g_nStringIdQI, g_nStringIdFRIENDLY_NAME, g_nStringIdSERVER_ADS_ADDRESS, g_nStringIdADS_PORT, g_nStringIdSERVER_IPV4_OR_HOSTNAME };

const CStringDictionary::TStringId FORTE_ADS_SERVER_CONFIG::scmDataInputTypeIds[] = { g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdUINT, g_nStringIdSTRING };

const CStringDictionary::TStringId FORTE_ADS_SERVER_CONFIG::scmDataOutputNames[] = { g_nStringIdQO, g_nStringIdSTATUS };

const CStringDictionary::TStringId FORTE_ADS_SERVER_CONFIG::scmDataOutputTypeIds[] = { g_nStringIdBOOL, g_nStringIdWSTRING };

const TForteInt16 FORTE_ADS_SERVER_CONFIG::scmEIWithIndexes[] = { 0 };
const TDataIOID FORTE_ADS_SERVER_CONFIG::scmEIWith[] = { 0, scmWithListDelimiter };
const CStringDictionary::TStringId FORTE_ADS_SERVER_CONFIG::scmEventInputNames[] = { g_nStringIdINIT };
const CStringDictionary::TStringId FORTE_ADS_SERVER_CONFIG::scmEventInputTypeIds[] = {g_nStringIdEInit};

const TDataIOID FORTE_ADS_SERVER_CONFIG::scmEOWith[] = { 0, 1, scmWithListDelimiter };
const TForteInt16 FORTE_ADS_SERVER_CONFIG::scmEOWithIndexes[] = { 0, -1 };
const CStringDictionary::TStringId FORTE_ADS_SERVER_CONFIG::scmEventOutputNames[] = { g_nStringIdINITO };
const CStringDictionary::TStringId FORTE_ADS_SERVER_CONFIG::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_ADS_SERVER_CONFIG::scmFBInterfaceSpec = { 1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes, 1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes, 5, scmDataInputNames, scmDataInputTypeIds, 2, scmDataOutputNames, scmDataOutputTypeIds, 0, 0 };

void FORTE_ADS_SERVER_CONFIG::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch (paEIID){
    case scmEventINITID:
      if(QI()) {
        QO() = CIEC_BOOL(forte::ads::CAdsConnectionManager::getInstance().addConnection(FRIENDLY_NAME().getStorage().c_str(), SERVER_ADS_ADDRESS().getStorage().c_str(), static_cast<CIEC_UDINT::TValueType>(ADS_PORT()), SERVER_IPV4_OR_HOSTNAME().getStorage().c_str()));
      } else {
        forte::ads::CAdsConnectionManager::getInstance().removeConnection(FRIENDLY_NAME().getStorage().c_str());
        QO() = CIEC_BOOL(false);
      }
      sendOutputEvent(scmEventINITOID, paECET);
      break;
  }
}

