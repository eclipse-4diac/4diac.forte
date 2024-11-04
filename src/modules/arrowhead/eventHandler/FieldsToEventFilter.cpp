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

#include "FieldsToEventFilter.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FieldsToEventFilter_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_FieldsToEventFilter, g_nStringIdFieldsToEventFilter)

const CStringDictionary::TStringId FORTE_FieldsToEventFilter::scmDataInputNames[] = {g_nStringIdeventType, g_nStringIdconsumer, g_nStringIdsources, g_nStringIdstartDate, g_nStringIdendDate, g_nStringIdfilterMetadata, g_nStringIdnotifyUri, g_nStringIdmatchMetadata};

const CStringDictionary::TStringId FORTE_FieldsToEventFilter::scmDataInputTypeIds[] = {g_nStringIdWSTRING, g_nStringIdArrowheadSystem, g_nStringIdARRAY, 10, g_nStringIdArrowheadSystem, g_nStringIdDATE_AND_TIME, g_nStringIdDATE_AND_TIME, g_nStringIdARRAY, 10, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdBOOL};

const CStringDictionary::TStringId FORTE_FieldsToEventFilter::scmDataOutputNames[] = {g_nStringIdeventFilter};

const CStringDictionary::TStringId FORTE_FieldsToEventFilter::scmDataOutputTypeIds[] = {g_nStringIdEventFilter};

const TForteInt16 FORTE_FieldsToEventFilter::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_FieldsToEventFilter::scmEIWith[] = {0, 1, 3, 6, 2, 4, 5, 7, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_FieldsToEventFilter::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_FieldsToEventFilter::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_FieldsToEventFilter::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FieldsToEventFilter::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_FieldsToEventFilter::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_FieldsToEventFilter::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_FieldsToEventFilter::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  8,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};

void FORTE_FieldsToEventFilter::alg_REQ(){
CIEC_INT i;
;

i = 0;
eventFilter().eventType() = eventType();
eventFilter().consumer() = consumer();
eventFilter().startDate() = startDate();
eventFilter().endDate() = endDate();
eventFilter().notifyUri() = notifyUri();
eventFilter().matchMetadata() = matchMetadata();

while((i < 10)){
// looks like while is faster than FOR when exporting to cpp

eventFilter().sources()[i] = sources()[i];
eventFilter().filterMetadata()[i] = filterMetadata()[i];
i = i+1;
}
}


void FORTE_FieldsToEventFilter::enterStateSTART(CEventChainExecutionThread *const paECET){
  mECCState = scmStateSTART;
}

void FORTE_FieldsToEventFilter::enterStateREQ(CEventChainExecutionThread *const paECET){
  mECCState = scmStateREQ;
  alg_REQ();
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FieldsToEventFilter::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
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


