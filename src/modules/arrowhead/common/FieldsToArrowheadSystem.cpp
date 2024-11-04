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

#include "FieldsToArrowheadSystem.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FieldsToArrowheadSystem_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_FieldsToArrowheadSystem, g_nStringIdFieldsToArrowheadSystem)

const CStringDictionary::TStringId FORTE_FieldsToArrowheadSystem::scmDataInputNames[] = {g_nStringIdsystemName, g_nStringIdaddress, g_nStringIdport, g_nStringIdauthenticationInfo};

const CStringDictionary::TStringId FORTE_FieldsToArrowheadSystem::scmDataInputTypeIds[] = {g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdDINT, g_nStringIdWSTRING};

const CStringDictionary::TStringId FORTE_FieldsToArrowheadSystem::scmDataOutputNames[] = {g_nStringIdarrowheadSystem};

const CStringDictionary::TStringId FORTE_FieldsToArrowheadSystem::scmDataOutputTypeIds[] = {g_nStringIdArrowheadSystem};

const TForteInt16 FORTE_FieldsToArrowheadSystem::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_FieldsToArrowheadSystem::scmEIWith[] = {3, 2, 1, 0, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_FieldsToArrowheadSystem::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_FieldsToArrowheadSystem::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_FieldsToArrowheadSystem::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FieldsToArrowheadSystem::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_FieldsToArrowheadSystem::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_FieldsToArrowheadSystem::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_FieldsToArrowheadSystem::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  4,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};

void FORTE_FieldsToArrowheadSystem::alg_REQ(){
arrowheadSystem().systemName() = systemName();
arrowheadSystem().address() = address();
arrowheadSystem().port() = port();
arrowheadSystem().authenticationInfo() = authenticationInfo();

}


void FORTE_FieldsToArrowheadSystem::enterStateSTART(CEventChainExecutionThread *const paECET){
  mECCState = scmStateSTART;
}

void FORTE_FieldsToArrowheadSystem::enterStateREQ(CEventChainExecutionThread *const paECET){
  mECCState = scmStateREQ;
  alg_REQ();
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FieldsToArrowheadSystem::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
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


