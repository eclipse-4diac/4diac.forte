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

#include "GetArrayResponseFromJSON_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GetArrayResponseFromJSON_fbt_gen.cpp"
#endif

#include "ArrowheadJSONHelper.h"

DEFINE_FIRMWARE_FB(FORTE_GetArrayResponseFromJSON, g_nStringIdGetArrayResponseFromJSON)

const CStringDictionary::TStringId FORTE_GetArrayResponseFromJSON::scmDataInputNames[] = {g_nStringIdresponse};

const CStringDictionary::TStringId FORTE_GetArrayResponseFromJSON::scmDataInputTypeIds[] = {g_nStringIdSTRING};

const CStringDictionary::TStringId FORTE_GetArrayResponseFromJSON::scmDataOutputNames[] = {g_nStringIdoutput};

const CStringDictionary::TStringId FORTE_GetArrayResponseFromJSON::scmDataOutputTypeIds[] = {g_nStringIdANY};

const TForteInt16 FORTE_GetArrayResponseFromJSON::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_GetArrayResponseFromJSON::scmEIWith[] = {0, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_GetArrayResponseFromJSON::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_GetArrayResponseFromJSON::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_GetArrayResponseFromJSON::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_GetArrayResponseFromJSON::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_GetArrayResponseFromJSON::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_GetArrayResponseFromJSON::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_GetArrayResponseFromJSON::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  1,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};


bool FORTE_GetArrayResponseFromJSON::isResponseEmpty(char* paText) {
  while(']' != *paText) {
    if(' ' != *paText) {
      return false;
    }
    paText++;
  }
  return true;
}

void FORTE_GetArrayResponseFromJSON::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  if(scmEventREQID == paEIID && CIEC_ANY::e_ARRAY == output().getDataTypeID() && CIEC_ANY::e_STRUCT == output_Array()[0]->getDataTypeID()) {
    //clean the output first
    output_Array().setup(output_Array().size(), static_cast<CIEC_STRUCT*>(output_Array()[0])->getStructTypeNameID());

    DEVLOG_DEBUG("[Arrowhead GetArrayResponseFromJSON]: Response received: %s\n", response().getValue());
    char* helper = strrchr(response().getValue(), ']');
    if(0 != helper) {

      *(helper + 1) = '\0';

      helper = strchr(response().getValue(), '[');
      if(0 != helper) {
        if(!isResponseEmpty(helper + 1)) {
          ArrowheadJSONHelper::transformJSONToStruct(helper);
          output().fromString(helper);
        } //if response is empty, don't do anything.
      } else {
        DEVLOG_ERROR("[Arrowhead GetArrayResponseFromJSON]: Invalid response, ] was found but not [: \n", response().getValue());
      }
    } else {
      DEVLOG_ERROR("[Arrowhead GetArrayResponseFromJSON]: Invalid response, no ] was found: %s\n", response().getValue());
    }
    sendOutputEvent(scmEventCNFID, paECET);
  }
}




