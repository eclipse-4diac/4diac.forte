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

#include "OrchestrationForm2OrchestrationForm_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "OrchestrationForm2OrchestrationForm_fbt_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_OrchestrationForm2OrchestrationForm, g_nStringIdOrchestrationForm2OrchestrationForm)

const CStringDictionary::TStringId FORTE_OrchestrationForm2OrchestrationForm::scmDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId FORTE_OrchestrationForm2OrchestrationForm::scmDataInputTypeIds[] = {g_nStringIdOrchestrationForm};

const CStringDictionary::TStringId FORTE_OrchestrationForm2OrchestrationForm::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_OrchestrationForm2OrchestrationForm::scmDataOutputTypeIds[] = {g_nStringIdOrchestrationForm};

const TForteInt16 FORTE_OrchestrationForm2OrchestrationForm::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_OrchestrationForm2OrchestrationForm::scmEIWith[] = {0, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_OrchestrationForm2OrchestrationForm::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_OrchestrationForm2OrchestrationForm::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_OrchestrationForm2OrchestrationForm::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_OrchestrationForm2OrchestrationForm::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_OrchestrationForm2OrchestrationForm::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_OrchestrationForm2OrchestrationForm::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_OrchestrationForm2OrchestrationForm::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  1,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};


void FORTE_OrchestrationForm2OrchestrationForm::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  if(scmEventREQID == paEIID) {
    st_OUT() = st_IN();
    sendOutputEvent(scmEventCNFID, paECET);
  }
}



