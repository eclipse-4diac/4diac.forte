/*******************************************************************************
 * Copyright (c) 2006-2014 ACIN, Profactor GmbH, fortiss GmbH
 *     2018 Johannes Kepler University, 2018 TU Wien/ACIN
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Rene Smodic, Alois Zoitl, Michael Hofmann, Martin Melik Merkumians,
 *    Patrick Smejkal
 *      - initial implementation and rework communication infrastructure
 *    Alois Zoitl - introduced new CGenFB class for better handling generic FBs
 *    Martin Melik Merkumians - removes usage of unsecure function
 *******************************************************************************/

#include "basecommfb.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "basecommfb_gen.cpp"
#endif
#include "comlayer.h"
#include "comlayersmanager.h"
#include "../resource.h"
#include "../../arch/fortenew.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <devlog.h>
#include "core/utils/string_utils.h"

using namespace forte::com_infra;

const CStringDictionary::TStringId CBaseCommFB::scmRequesterEventInputNameIds[2] = { g_nStringIdINIT, g_nStringIdREQ };
const CStringDictionary::TStringId CBaseCommFB::scmRequesterEventOutputNameIds[2] = { g_nStringIdINITO, g_nStringIdCNF };

const CStringDictionary::TStringId CBaseCommFB::scmResponderEventInputNameIds[2] = { g_nStringIdINIT, g_nStringIdRSP };
const CStringDictionary::TStringId CBaseCommFB::scmResponderEventOutputNameIds[2] = { g_nStringIdINITO, g_nStringIdIND };

const CStringDictionary::TStringId CBaseCommFB::scmEventInputTypeIds[2] = {g_nStringIdEInit, g_nStringIdEvent};
const CStringDictionary::TStringId CBaseCommFB::scmEventOutputTypeIds[2] = {g_nStringIdEvent, g_nStringIdEvent};

const char * const CBaseCommFB::scmResponseTexts[] = { "OK", "INVALID_ID", "TERMINATED", "INVALID_OBJECT", "DATA_TYPE_ERROR", "INHIBITED", "NO_SOCKET", "SEND_FAILED", "RECV_FAILED" };

CBaseCommFB::CBaseCommFB(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer, forte::com_infra::EComServiceType paCommServiceType) :
    CGenFunctionBlock<CEventSourceFB>(paContainer, paInstanceNameId), mCommServiceType(paCommServiceType), mTopOfComStack(nullptr) {
  memset(mInterruptQueue, 0, sizeof(mInterruptQueue)); //TODO change this to  mInterruptQueue{0} in the extended list when fully switching to C++11
  setEventChainExecutor(getResource()->getResourceEventExecution());
  mComInterruptQueueCount = 0;
}

CBaseCommFB::~CBaseCommFB() {
  closeConnection();
}

EMGMResponse CBaseCommFB::changeExecutionState(EMGMCommandType paCommand) {
  EMGMResponse retVal = CEventSourceFB::changeExecutionState(paCommand);
  if ((EMGMResponse::Ready == retVal) && (EMGMCommandType::Kill == paCommand)) {
    //when we are killed we'll close the connection so that it can safely be opened again after an reset
    closeConnection();
  }
  return retVal;
}

EComResponse CBaseCommFB::openConnection() {
  EComResponse retVal;
  if (nullptr == mTopOfComStack) {
    // Get the ID
    char *commID;
    if (nullptr == strchr(ID().getValue(), ']')) {
      commID = getDefaultIDString(ID().getValue());
    }
    else {
      size_t commIdLength = strlen(ID().getValue()) + 1;
      commID = new char[commIdLength];
      memcpy(commID, ID().getValue(), commIdLength);
      commID[commIdLength - 1] = '\0';
    }

    // If the ID is empty return an error
    if ('\0' == *commID) {
      retVal = e_InitInvalidId;
    }
    else {
      retVal = createComstack(commID);
      // If any error is going to be returned, delete the layers that were created
      if (e_InitOk != retVal) {
        closeConnection();
      }
    }
    delete[] commID;
  }
  else {
    // If the connection was already opened return ok
    retVal = e_InitOk;
  }
  return retVal;
}

EComResponse CBaseCommFB::createComstack(char *commID) {
  EComResponse retVal = e_InitInvalidId;
  CComLayer *newLayer = nullptr;
  CComLayer *previousLayer = nullptr; // Reference to the previous layer as it needs to set the bottom layer
  char *layerParams = nullptr;
  while('\0' != *commID) { // Loop until reaching the end of the ID
    retVal = e_InitInvalidId;
    char * layerID = extractLayerIdAndParams(&commID, &layerParams); // Get the next layer's ID and parameters

    if(nullptr != layerID && '\0' != *layerID) { // If well formated ID, keep going
    // Create the new layer
      newLayer = CComLayersManager::createCommunicationLayer(layerID, previousLayer, this);
      if(nullptr != newLayer) { // If the layer could be created, keep going
        if(nullptr == mTopOfComStack) {
          mTopOfComStack = newLayer; // Assign the newly created layer to the FB
        }

        previousLayer = newLayer; // Update the previous layer reference
        retVal = newLayer->openConnection(layerParams); // Open the layer connection
      }
    }

    if(e_InitOk != retVal) {  // If it was not opened correctly return the error
      break;
    }
  }
  return retVal;
}


void CBaseCommFB::closeConnection() {
  if (mTopOfComStack != nullptr) {
    mTopOfComStack->closeConnection();
    delete mTopOfComStack; // this will close the whole communication stack
    mTopOfComStack = nullptr;
  }
}

void CBaseCommFB::interruptCommFB(CComLayer *paComLayer) {
  if (cgCommunicationInterruptQueueSize > mComInterruptQueueCount) {
    mInterruptQueue[mComInterruptQueueCount] = paComLayer;
    mComInterruptQueueCount++;
  }
  else {
    //TODO to many interrupts received issue error msg
  }
}

char *CBaseCommFB::extractLayerIdAndParams(char **paRemainingID, char **paLayerParams) {
  if ('\0' != **paRemainingID) {
    char *const layerID = *paRemainingID;
    *paRemainingID = strchr(*paRemainingID, '[');
    if (nullptr != *paRemainingID) {
      int bracketCount = 0;
      char * const paramsStart = *paRemainingID;
      char *currentChar = *paRemainingID;
      while ('\0' != *currentChar) {
        if (*currentChar == '[') {
          bracketCount++;
        }
        if (*currentChar == ']') {
          bracketCount--;

          if (bracketCount == 0){
            *paramsStart = '\0';
            *currentChar = '\0';
            *paRemainingID = currentChar + 1;  //let the paRemainingID point to the char after the closing bracket
            *paLayerParams = paramsStart + 1;  //let the paLayerParams point to the char after the opening bracket

            if('\0' != **paRemainingID) {
              ++(*paRemainingID);
             }
            return layerID;
          }
        }
        currentChar++;
      }
      DEVLOG_ERROR("[CBaseCommFB] ID is not valid!\n");
    } else {
      DEVLOG_ERROR("[CBaseCommFB]: No valid opening bracket was found\n");
    }
  } else {
    DEVLOG_ERROR("[CBaseCommFB]: The id of the layer is empty\n");
  }
  return nullptr;
}

char *CBaseCommFB::buildIDString(const char *paPrefix, const char *paIDRoot, const char *paSuffix) {
  size_t idStringLength = strlen(paPrefix) + strlen(paIDRoot) + strlen(paSuffix) + 1;
  char *RetVal = new char[idStringLength];
  snprintf(RetVal, idStringLength, "%s%s%s", paPrefix, paIDRoot, paSuffix);
  return RetVal;
}

bool CBaseCommFB::createInterfaceSpec(const char* paConfigString, SFBInterfaceSpec& paInterfaceSpec) {
  TIdentifier tempstring;
  const char *sParamA = nullptr;
  const char *sParamB = nullptr;

  paInterfaceSpec.mNumEIs = 2;
  paInterfaceSpec.mNumEOs = 2;

  memcpy(tempstring, paConfigString, (strlen(paConfigString) > cgIdentifierLength) ? cgIdentifierLength : strlen(paConfigString) + 1); //plus 1 for the null character
  tempstring[cgIdentifierLength] = '\0';

  size_t inlength = strlen(tempstring);

  size_t i;
  for (i = 0; i < inlength - 1; i++) { // search first underscore
    if (tempstring[i] == '_') {
      sParamA = sParamB = &(tempstring[i + 1]);
      break;
    }
  }
  if(nullptr != sParamA) { // search for 2nd underscore
    for (i = i + 1; i < inlength - 1; i++) {
      if (tempstring[i] == '_') {
        tempstring[i] = '\0';
        sParamB = &(tempstring[i + 1]);
        break;
      }
    }
  }
  if (nullptr == sParamB){ // no underscore found
    return false;
  }

  configureDIs(sParamA, paInterfaceSpec);
  configureDOs(sParamB, paInterfaceSpec);

  if (forte::com_infra::e_Requester == (forte::com_infra::e_Requester & mCommServiceType)) {
    paInterfaceSpec.mEINames = scmRequesterEventInputNameIds;
    paInterfaceSpec.mEONames = scmRequesterEventOutputNameIds;
  }
  else {
    if (forte::com_infra::e_Responder == (forte::com_infra::e_Responder & mCommServiceType)) {
      paInterfaceSpec.mEINames = scmResponderEventInputNameIds;
      paInterfaceSpec.mEONames = scmResponderEventOutputNameIds;
    }
  }
  paInterfaceSpec.mEITypeNames = scmEventInputTypeIds;
  paInterfaceSpec.mEOTypeNames = scmEventOutputTypeIds;

  return true;
}

void CBaseCommFB::configureDIs(const char* paDIConfigString, SFBInterfaceSpec& paInterfaceSpec) {
  paInterfaceSpec.mNumDIs = 2;

  if (forte::com_infra::e_DataInputs == (forte::com_infra::e_DataInputs & mCommServiceType)) {
      //TODO: Check range of sParamA
      paInterfaceSpec.mNumDIs = paInterfaceSpec.mNumDIs +
                                  static_cast<TPortId>(forte::core::util::strtol(paDIConfigString, nullptr, 10));
      mDiDataTypeNames.reset(new CStringDictionary::TStringId[paInterfaceSpec.mNumDIs]);
      mDiNames.reset(new CStringDictionary::TStringId[paInterfaceSpec.mNumDIs]);

      generateGenericDataPointArrays("SD_", &(mDiDataTypeNames[2]), &(mDiNames[2]), paInterfaceSpec.mNumDIs - 2);
    }
    else {
      mDiDataTypeNames.reset(new CStringDictionary::TStringId[paInterfaceSpec.mNumDIs]);
      mDiNames.reset(new CStringDictionary::TStringId[paInterfaceSpec.mNumDIs]);
    }
    paInterfaceSpec.mDIDataTypeNames = mDiDataTypeNames.get();
    paInterfaceSpec.mDINames = mDiNames.get();

    mDiDataTypeNames[0] = g_nStringIdBOOL;
    mDiNames[0] = g_nStringIdQI;
#ifdef FORTE_USE_WSTRING_DATATYPE
    mDiDataTypeNames[1] = g_nStringIdWSTRING;
#else //FORTE_USE_WSTRING_DATATYPE
    mDiDataTypeNames[1] = g_nStringIdSTRING;
#endif //FORTE_USE_WSTRING_DATATYPE
    mDiNames[1] = g_nStringIdID;
}

void CBaseCommFB::configureDOs(const char* paDOConfigString, SFBInterfaceSpec& paInterfaceSpec) {
  paInterfaceSpec.mNumDOs = 2;

  if(forte::com_infra::e_DataOutputs == (forte::com_infra::e_DataOutputs & mCommServiceType)){
    //TODO: Check range of sParamA
    paInterfaceSpec.mNumDOs = paInterfaceSpec.mNumDOs +
                                static_cast<TPortId>(forte::core::util::strtol(paDOConfigString, nullptr, 10));
    mDoDataTypeNames.reset(new CStringDictionary::TStringId[paInterfaceSpec.mNumDOs]);
    mDoNames.reset(new CStringDictionary::TStringId[paInterfaceSpec.mNumDOs]);

    generateGenericDataPointArrays("RD_", &(mDoDataTypeNames[2]), &(mDoNames[2]), paInterfaceSpec.mNumDOs - 2);
  }
  else{
    mDoDataTypeNames.reset(new CStringDictionary::TStringId[paInterfaceSpec.mNumDOs]);
    mDoNames.reset(new CStringDictionary::TStringId[paInterfaceSpec.mNumDOs]);
  }

  paInterfaceSpec.mDONames = mDoNames.get();
  paInterfaceSpec.mDODataTypeNames = mDoDataTypeNames.get();

  mDoDataTypeNames[0] = g_nStringIdBOOL;
  mDoNames[0] = g_nStringIdQO;
#ifdef FORTE_USE_WSTRING_DATATYPE
  mDoDataTypeNames[1] = g_nStringIdWSTRING;
#else
  mDoDataTypeNames[1] = g_nStringIdSTRING;
#endif
  mDoNames[1] = g_nStringIdSTATUS;

}