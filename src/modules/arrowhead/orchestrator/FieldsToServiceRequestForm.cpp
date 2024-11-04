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

#include "FieldsToServiceRequestForm.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FieldsToServiceRequestForm_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_FieldsToServiceRequestForm, g_nStringIdFieldsToServiceRequestForm)

const CStringDictionary::TStringId FORTE_FieldsToServiceRequestForm::scmDataInputNames[] = {g_nStringIdrequesterSystem, g_nStringIdrequesterCloud, g_nStringIdrequestedService, g_nStringIdorchestrationFlags, g_nStringIdpreferredProviders, g_nStringIdrequestedQoS};

const CStringDictionary::TStringId FORTE_FieldsToServiceRequestForm::scmDataInputTypeIds[] = {g_nStringIdArrowheadSystem, g_nStringIdArrowheadCloud, g_nStringIdArrowheadService, g_nStringIdARRAY, 10, g_nStringIdWSTRING, g_nStringIdARRAY, 10, g_nStringIdPreferredProvider, g_nStringIdARRAY, 10, g_nStringIdWSTRING};

const CStringDictionary::TStringId FORTE_FieldsToServiceRequestForm::scmDataOutputNames[] = {g_nStringIdserviceRequestForm};

const CStringDictionary::TStringId FORTE_FieldsToServiceRequestForm::scmDataOutputTypeIds[] = {g_nStringIdServiceRequestForm};

const TForteInt16 FORTE_FieldsToServiceRequestForm::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_FieldsToServiceRequestForm::scmEIWith[] = {0, 1, 5, 4, 3, 2, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_FieldsToServiceRequestForm::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_FieldsToServiceRequestForm::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_FieldsToServiceRequestForm::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FieldsToServiceRequestForm::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_FieldsToServiceRequestForm::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_FieldsToServiceRequestForm::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_FieldsToServiceRequestForm::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  6,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};

void FORTE_FieldsToServiceRequestForm::alg_REQ(){
CIEC_INT i;
;

serviceRequestForm().requesterSystem() = requesterSystem();
serviceRequestForm().requesterCloud() = requesterCloud();
serviceRequestForm().requestedService() = requestedService();


i = 0;
while((i < 10)){
// looks like while is faster than FOR when exporting to cpp

serviceRequestForm().orchestrationFlags()[i] = orchestrationFlags()[i];
serviceRequestForm().preferredProviders()[i] = preferredProviders()[i];
serviceRequestForm().requestedQoS()[i] = requestedQoS()[i];
i = i+1;
}






}


void FORTE_FieldsToServiceRequestForm::enterStateSTART(CEventChainExecutionThread *const paECET){
  mECCState = scmStateSTART;
}

void FORTE_FieldsToServiceRequestForm::enterStateREQ(, CEventChainExecutionThread * const paECET){
  mECCState = scmStateREQ;
  alg_REQ();
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FieldsToServiceRequestForm::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
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


