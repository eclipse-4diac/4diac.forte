/*******************************************************************************
 * Copyright (c) 2019, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral - initial implementation
 *******************************************************************************/

#include "FieldsToPublishEvent.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FieldsToPublishEvent_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_FieldsToPublishEvent, g_nStringIdFieldsToPublishEvent)

const CStringDictionary::TStringId FORTE_FieldsToPublishEvent::scmDataInputNames[] = {g_nStringIdsource, g_nStringIdevent, g_nStringIddeliveryCompleteUri};

const CStringDictionary::TStringId FORTE_FieldsToPublishEvent::scmDataInputTypeIds[] = {g_nStringIdArrowheadSystem, g_nStringIdArrowheadEvent, g_nStringIdWSTRING};

const CStringDictionary::TStringId FORTE_FieldsToPublishEvent::scmDataOutputNames[] = {g_nStringIdpublishEvent};

const CStringDictionary::TStringId FORTE_FieldsToPublishEvent::scmDataOutputTypeIds[] = {g_nStringIdPublishEvent};

const TForteInt16 FORTE_FieldsToPublishEvent::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_FieldsToPublishEvent::scmEIWith[] = {0, 1, 2, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_FieldsToPublishEvent::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_FieldsToPublishEvent::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_FieldsToPublishEvent::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FieldsToPublishEvent::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_FieldsToPublishEvent::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_FieldsToPublishEvent::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_FieldsToPublishEvent::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  3,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};

void FORTE_FieldsToPublishEvent::alg_REQ(){
publishEvent().source() = source();
publishEvent().event() = event();
publishEvent().deliveryCompleteUri() = deliveryCompleteUri();


}


void FORTE_FieldsToPublishEvent::enterStateSTART(CEventChainExecutionThread *const paECET){
  mECCState = scmStateSTART;
}

void FORTE_FieldsToPublishEvent::enterStateREQ(CEventChainExecutionThread *const paECET){
  mECCState = scmStateREQ;
  alg_REQ();
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FieldsToPublishEvent::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
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
        if((1))
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


