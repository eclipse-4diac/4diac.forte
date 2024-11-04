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

#include "FieldsPreferredProvider.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FieldsPreferredProvider_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_FieldsPreferredProvider, g_nStringIdFieldsPreferredProvider)

const CStringDictionary::TStringId FORTE_FieldsPreferredProvider::scmDataInputNames[] = {g_nStringIdproviderSystem, g_nStringIdproviderCloud};

const CStringDictionary::TStringId FORTE_FieldsPreferredProvider::scmDataInputTypeIds[] = {g_nStringIdArrowheadSystem, g_nStringIdArrowheadCloud};

const CStringDictionary::TStringId FORTE_FieldsPreferredProvider::scmDataOutputNames[] = {g_nStringIdpreferredProvider};

const CStringDictionary::TStringId FORTE_FieldsPreferredProvider::scmDataOutputTypeIds[] = {g_nStringIdPreferredProvider};

const TForteInt16 FORTE_FieldsPreferredProvider::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_FieldsPreferredProvider::scmEIWith[] = {0, 1, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_FieldsPreferredProvider::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_FieldsPreferredProvider::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_FieldsPreferredProvider::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FieldsPreferredProvider::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_FieldsPreferredProvider::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_FieldsPreferredProvider::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_FieldsPreferredProvider::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  2,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};

void FORTE_FieldsPreferredProvider::alg_REQ(){
preferredProvider().providerSystem() = providerSystem();
preferredProvider().providerCloud() = providerCloud();

}


void FORTE_FieldsPreferredProvider::enterStateSTART(CEventChainExecutionThread *const paECET){
  mECCState = scmStateSTART;
}

void FORTE_FieldsPreferredProvider::enterStateREQ(CEventChainExecutionThread * const paECET){
  mECCState = scmStateREQ;
  alg_REQ();
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FieldsPreferredProvider::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
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


