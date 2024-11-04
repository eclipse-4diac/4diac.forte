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

#include "FieldsToPreferredProvider.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FieldsToPreferredProvider_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_FieldsToPreferredProvider, g_nStringIdFieldsToPreferredProvider)

const CStringDictionary::TStringId FORTE_FieldsToPreferredProvider::scmDataInputNames[] = {g_nStringIdproviderSystem, g_nStringIdproviderCloud};

const CStringDictionary::TStringId FORTE_FieldsToPreferredProvider::scmDataInputTypeIds[] = {g_nStringIdArrowheadSystem, g_nStringIdArrowheadCloud};

const CStringDictionary::TStringId FORTE_FieldsToPreferredProvider::scmDataOutputNames[] = {g_nStringIdpreferredProvider};

const CStringDictionary::TStringId FORTE_FieldsToPreferredProvider::scmDataOutputTypeIds[] = {g_nStringIdPreferredProvider};

const TForteInt16 FORTE_FieldsToPreferredProvider::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_FieldsToPreferredProvider::scmEIWith[] = {0, 1, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_FieldsToPreferredProvider::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_FieldsToPreferredProvider::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_FieldsToPreferredProvider::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FieldsToPreferredProvider::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_FieldsToPreferredProvider::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_FieldsToPreferredProvider::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_FieldsToPreferredProvider::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  2,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};

void FORTE_FieldsToPreferredProvider::alg_REQ(){
preferredProvider().providerSystem() = providerSystem();
preferredProvider().providerCloud() = providerCloud();





}


void FORTE_FieldsToPreferredProvider::enterStateSTART(CEventChainExecutionThread *const paECET){
  mECCState = scmStateSTART;
}

void FORTE_FieldsToPreferredProvider::enterStateREQ(CEventChainExecutionThread * const paECET){
  mECCState = scmStateREQ;
  alg_REQ();
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FieldsToPreferredProvider::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
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


