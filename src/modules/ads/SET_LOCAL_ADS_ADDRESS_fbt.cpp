/*******************************************************************************
 * Copyright (c) 2018 TU Wien/ACIN
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Martin Melik-Merkumians - initial contribution
 *******************************************************************************/

#include "SET_LOCAL_ADS_ADDRESS_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SET_LOCAL_ADS_ADDRESS_fbt_gen.cpp"
#endif

#include <sstream>

#include <AdsLib.h>

DEFINE_FIRMWARE_FB(FORTE_SET_LOCAL_ADS_ADDRESS, g_nStringIdSET_LOCAL_ADS_ADDRESS)

const CStringDictionary::TStringId FORTE_SET_LOCAL_ADS_ADDRESS::scmDataInputNames[] ={g_nStringIdQI, g_nStringIdPARAMS};

const CStringDictionary::TStringId FORTE_SET_LOCAL_ADS_ADDRESS::scmDataInputTypeIds[] = { g_nStringIdBOOL, g_nStringIdSTRING };

const CStringDictionary::TStringId FORTE_SET_LOCAL_ADS_ADDRESS::scmDataOutputNames[] = { g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdLOCAL_ADS_ADDRESS };

const CStringDictionary::TStringId FORTE_SET_LOCAL_ADS_ADDRESS::scmDataOutputTypeIds[] = { g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdSTRING };

const TForteInt16 FORTE_SET_LOCAL_ADS_ADDRESS::scmEIWithIndexes[] = { 0 };
const TDataIOID FORTE_SET_LOCAL_ADS_ADDRESS::scmEIWith[] = { 0, scmWithListDelimiter };
const CStringDictionary::TStringId FORTE_SET_LOCAL_ADS_ADDRESS::scmEventInputNames[] = { g_nStringIdINIT };
const CStringDictionary::TStringId FORTE_SET_LOCAL_ADS_ADDRESS::scmEventInputTypeIds[] = {g_nStringIdEInit};

const TDataIOID FORTE_SET_LOCAL_ADS_ADDRESS::scmEOWith[] = { 0, 1, 2, scmWithListDelimiter };
const TForteInt16 FORTE_SET_LOCAL_ADS_ADDRESS::scmEOWithIndexes[] = { 0, -1 };
const CStringDictionary::TStringId FORTE_SET_LOCAL_ADS_ADDRESS::scmEventOutputNames[] = { g_nStringIdINITO };
const CStringDictionary::TStringId FORTE_SET_LOCAL_ADS_ADDRESS::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_SET_LOCAL_ADS_ADDRESS::scmFBInterfaceSpec = { 1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes, 1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes, 2, scmDataInputNames, scmDataInputTypeIds, 3, scmDataOutputNames, scmDataOutputTypeIds, 0, 0 };

void FORTE_SET_LOCAL_ADS_ADDRESS::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch (paEIID){
    case scmEventINITID:
      AmsNetId desiredAddress(std::string(PARAMS().getStorage().c_str()));
      if(QI()){
        AdsSetLocalAddress(desiredAddress);
        AmsAddr actualAddress = { 0 };
        long port = AdsPortOpenEx();
        AdsGetLocalAddressEx(port, &actualAddress);
        if(actualAddress.netId == desiredAddress){
          STATUS() = CIEC_WSTRING("OK");
          QO() = CIEC_BOOL(true);
          std::stringstream amsNetId;
          amsNetId << std::to_string(actualAddress.netId.b[0]) << "." + std::to_string(actualAddress.netId.b[1]) << "." << std::to_string(actualAddress.netId.b[2]) << "." << std::to_string(actualAddress.netId.b[3]) << "." << std::to_string(actualAddress.netId.b[4]) << "." << std::to_string(actualAddress.netId.b[5]);
          LOCAL_ADS_ADDRESS() = CIEC_STRING(amsNetId.str().c_str());
        }
        else{
          STATUS() = CIEC_WSTRING("NOT OK");
          QO() = CIEC_BOOL(false);
        }
      }
      else{
        QO() = CIEC_BOOL(false);
      }

      sendOutputEvent(scmEventINITOID, paECET);
      break;
  }
}

