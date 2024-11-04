/*******************************************************************************
 * Copyright (c) 2018, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral - initial implementation
 *******************************************************************************/

#include "FieldsToServiceRegistryEntry.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FieldsToServiceRegistryEntry_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_FieldsToServiceRegistryEntry, g_nStringIdFieldsToServiceRegistryEntry)

const CStringDictionary::TStringId FORTE_FieldsToServiceRegistryEntry::scmDataInputNames[] = {g_nStringIdprovidedService, g_nStringIdprovider, g_nStringIdserviceURI, g_nStringIdversion, g_nStringIdudp, g_nStringIdttl, g_nStringIdmetadata};

const CStringDictionary::TStringId FORTE_FieldsToServiceRegistryEntry::scmDataInputTypeIds[] = {g_nStringIdArrowheadService, g_nStringIdArrowheadSystem, g_nStringIdWSTRING, g_nStringIdDINT, g_nStringIdBOOL, g_nStringIdDINT, g_nStringIdWSTRING};

const CStringDictionary::TStringId FORTE_FieldsToServiceRegistryEntry::scmDataOutputNames[] = {g_nStringIdserviceRegistryEntry};

const CStringDictionary::TStringId FORTE_FieldsToServiceRegistryEntry::scmDataOutputTypeIds[] = {g_nStringIdServiceRegistryEntry};

const TForteInt16 FORTE_FieldsToServiceRegistryEntry::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_FieldsToServiceRegistryEntry::scmEIWith[] = {6, 5, 4, 3, 2, 1, 0, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_FieldsToServiceRegistryEntry::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_FieldsToServiceRegistryEntry::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_FieldsToServiceRegistryEntry::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FieldsToServiceRegistryEntry::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_FieldsToServiceRegistryEntry::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_FieldsToServiceRegistryEntry::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_FieldsToServiceRegistryEntry::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  7,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};

void FORTE_FieldsToServiceRegistryEntry::alg_REQ(){
serviceRegistryEntry().providedService() = providedService();
serviceRegistryEntry().provider() = provider();
serviceRegistryEntry().serviceURI() = serviceURI();
serviceRegistryEntry().version() = version();
serviceRegistryEntry().udp() = udp();
serviceRegistryEntry().ttl() = ttl();
serviceRegistryEntry().metadata() = metadata();

}


void FORTE_FieldsToServiceRegistryEntry::enterStateSTART(CEventChainExecutionThread *const paECET){
  mECCState = scmStateSTART;
}

void FORTE_FieldsToServiceRegistryEntry::enterStateREQ(CEventChainExecutionThread * const paECET){
  mECCState = scmStateREQ;
  alg_REQ();
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FieldsToServiceRegistryEntry::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  bool bTransitionCleared;
  do{
    bTransitionCleared = true;
    switch(mECCState){
      case scmStateSTART:
        if(scmEventREQID == paEIID)
          enterStateREQ(paECET);
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      case scmStateREQ:
        if(1)
          enterStateSTART(paECET);
        else
          bTransitionCleared  = false; //no transition cleared
        break;
      default:
      DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 1.", mECCState.operator TForteUInt16 ());
        mECCState = 0; //0 is always the initial state
        break;
    }
    paEIID = cgInvalidEventID;  // we have to clear the event after the first check in order to ensure correct behavior
  }while(bTransitionCleared);
}


