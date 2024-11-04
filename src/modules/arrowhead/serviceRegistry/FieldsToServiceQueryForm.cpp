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

#include "FieldsToServiceQueryForm.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "FieldsToServiceQueryForm_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_FieldsToServiceQueryForm, g_nStringIdFieldsToServiceQueryForm)

const CStringDictionary::TStringId FORTE_FieldsToServiceQueryForm::scmDataInputNames[] = {g_nStringIdservice, g_nStringIdmetadataSearch, g_nStringIdpingProviders, g_nStringIdversion};

const CStringDictionary::TStringId FORTE_FieldsToServiceQueryForm::scmDataInputTypeIds[] = {g_nStringIdArrowheadService, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdDINT};

const CStringDictionary::TStringId FORTE_FieldsToServiceQueryForm::scmDataOutputNames[] = {g_nStringIdserviceQueryForm};

const CStringDictionary::TStringId FORTE_FieldsToServiceQueryForm::scmDataOutputTypeIds[] = {g_nStringIdServiceQueryForm};

const TForteInt16 FORTE_FieldsToServiceQueryForm::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_FieldsToServiceQueryForm::scmEIWith[] = {0, 3, 2, 1, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_FieldsToServiceQueryForm::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_FieldsToServiceQueryForm::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_FieldsToServiceQueryForm::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_FieldsToServiceQueryForm::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_FieldsToServiceQueryForm::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_FieldsToServiceQueryForm::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_FieldsToServiceQueryForm::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  4,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};

void FORTE_FieldsToServiceQueryForm::alg_REQ(){
serviceQueryForm().service() = service();
serviceQueryForm().metadataSearch() = metadataSearch();
serviceQueryForm().pingProviders() = pingProviders();
serviceQueryForm().version() = version();

}


void FORTE_FieldsToServiceQueryForm::enterStateSTART(CEventChainExecutionThread *const paECET){
  mECCState = scmStateSTART;
}

void FORTE_FieldsToServiceQueryForm::enterStateREQ(CEventChainExecutionThread * const paECET){
  mECCState = scmStateREQ;
  alg_REQ();
  sendOutputEvent(scmEventCNFID, paECET);
}

void FORTE_FieldsToServiceQueryForm::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
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


