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

#include "ANYToJSON_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ANYToJSON_fbt_gen.cpp"
#endif
#include "ArrowheadJSONHelper.h"

DEFINE_FIRMWARE_FB(FORTE_ANYToJSON, g_nStringIdANYToJSON)

const CStringDictionary::TStringId FORTE_ANYToJSON::scmDataInputNames[] = {g_nStringIdinput};

const CStringDictionary::TStringId FORTE_ANYToJSON::scmDataInputTypeIds[] = {g_nStringIdANY};

const CStringDictionary::TStringId FORTE_ANYToJSON::scmDataOutputNames[] = {g_nStringIdoutput};

const CStringDictionary::TStringId FORTE_ANYToJSON::scmDataOutputTypeIds[] = {g_nStringIdSTRING};

const TForteInt16 FORTE_ANYToJSON::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_ANYToJSON::scmEIWith[] = {0, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_ANYToJSON::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_ANYToJSON::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_ANYToJSON::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_ANYToJSON::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_ANYToJSON::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_ANYToJSON::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_ANYToJSON::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  1,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};


void FORTE_ANYToJSON::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  if(scmEventREQID == paEIID) {
    output() = "";
    ArrowheadJSONHelper::transformANYToJSON(input(), output());
    sendOutputEvent(scmEventCNFID, paECET);
  }
}



