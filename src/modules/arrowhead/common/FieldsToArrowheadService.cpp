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

#include "FieldsToArrowheadService.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FieldsToArrowheadService_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_FieldsToArrowheadService, g_nStringIdFieldsToArrowheadService)

const CStringDictionary::TStringId FORTE_FieldsToArrowheadService::scmDataInputNames[] = {g_nStringIdserviceDefinition, g_nStringIdinterfaces, g_nStringIdserviceMetadata};

const CStringDictionary::TStringId FORTE_FieldsToArrowheadService::scmDataInputTypeIds[] = {g_nStringIdWSTRING, g_nStringIdARRAY, 10, g_nStringIdWSTRING, g_nStringIdARRAY, 10, g_nStringIdWSTRING};

const CStringDictionary::TStringId FORTE_FieldsToArrowheadService::scmDataOutputNames[] = {g_nStringIdarrowheadService};

const CStringDictionary::TStringId FORTE_FieldsToArrowheadService::scmDataOutputTypeIds[] = {g_nStringIdArrowheadService};

const TForteInt16 FORTE_FieldsToArrowheadService::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_FieldsToArrowheadService::scmEIWith[] = {0, 1, 2, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_FieldsToArrowheadService::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_FieldsToArrowheadService::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_FieldsToArrowheadService::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FieldsToArrowheadService::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_FieldsToArrowheadService::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_FieldsToArrowheadService::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_FieldsToArrowheadService::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  3,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};

void FORTE_FieldsToArrowheadService::alg_REQ(){
CIEC_INT i;
;

i = 0;
arrowheadService().serviceDefinition() = serviceDefinition();

while((i < 10)){
// looks like while is faster than FOR when exporting to cpp

arrowheadService().interfaces()[i] = interfaces()[i];
arrowheadService().serviceMetadata()[i] = serviceMetadata()[i];
i = i+1;
}

}


void FORTE_FieldsToArrowheadService::enterStateSTART(CEventChainExecutionThread *const paECET){
  mECCState = scmStateSTART;
}

void FORTE_FieldsToArrowheadService::enterStateREQ(CEventChainExecutionThread *const paECET){
  mECCState = scmStateREQ;
  alg_REQ();
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FieldsToArrowheadService::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
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


