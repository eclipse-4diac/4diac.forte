/*******************************************************************************
 * Copyright (c) 2014 Profactor GmbH, fortiss GmbH
 *                      2018 Johannes Kepler University
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Matthias Plasch, Alois Zoitl
 *   - initial API and implementation and/or initial documentation
 *    Alois Zoitl - introduced new CGenFB class for better handling generic FBs
 *   Martin Jobst
 *     - refactor for ANY variant
 *     - add generic readInputData and writeOutputData
 *******************************************************************************/
#include "GEN_ARRAY2VALUES_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GEN_ARRAY2VALUES_fbt_gen.cpp"
#endif

#include <stdio.h>
#include "forte_printer.h"
#include "resource.h"
#include "criticalregion.h"

DEFINE_GENERIC_FIRMWARE_FB(GEN_ARRAY2VALUES, g_nStringIdGEN_ARRAY2VALUES)

const CStringDictionary::TStringId GEN_ARRAY2VALUES::scmDataInputNames[] = { g_nStringIdIN };

const CStringDictionary::TStringId GEN_ARRAY2VALUES::scmEventInputNames[] = { g_nStringIdREQ };
const CStringDictionary::TStringId GEN_ARRAY2VALUES::scmEventInputTypeIds[] = {g_nStringIdEvent};

const CStringDictionary::TStringId GEN_ARRAY2VALUES::scmEventOutputNames[] = { g_nStringIdCNF };
const CStringDictionary::TStringId GEN_ARRAY2VALUES::scmEventOutputTypeIds[] = {g_nStringIdEvent};

GEN_ARRAY2VALUES::GEN_ARRAY2VALUES(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CGenFunctionBlock<CFunctionBlock>(paContainer, paInstanceNameId), mDataOutputNames(nullptr), mDataOutputTypeIds(nullptr), mDataInputTypeIds(nullptr), mDOutputs(0), mValueTypeID(CStringDictionary::scmInvalidStringId){
}

GEN_ARRAY2VALUES::~GEN_ARRAY2VALUES(){
  delete[] mDataOutputNames;
  delete[] mDataInputTypeIds;
  delete[] mDataOutputTypeIds;
}

void GEN_ARRAY2VALUES::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch (paEIID){
    case scmEventREQID:

      for(size_t output_index = 0; output_index < mDOutputs; output_index++) {
        //copy input values to array
        getDO(static_cast<unsigned int>(output_index))->setValue((IN_Array()[output_index]));
      }

      sendOutputEvent(scmEventCNFID, paECET);

      break;
  }
}

void GEN_ARRAY2VALUES::readInputData(TEventID) {
  readData(0, *mDIs[0], mDIConns[0]);
}

void GEN_ARRAY2VALUES::writeOutputData(TEventID) {
  for(TPortId i = 0; i < getFBInterfaceSpec().mNumDOs; ++i) {
    writeData(i, *mDOs[i], mDOConns[i]);
  }
}

bool GEN_ARRAY2VALUES::createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec){
  const char *dNumberPos = strchr(paConfigString, '_');

  if(nullptr != dNumberPos){
    ++dNumberPos;
    //get position of a second underscore
    const char *dTypePos = strchr(dNumberPos, '_');

    if(nullptr != dTypePos){
      //there is a number and a data type of inputs within the typename
      mDOutputs = static_cast<size_t>(forte::core::util::strtoul(dNumberPos, nullptr, 10));
      mValueTypeID = CStringDictionary::getInstance().getId(++dTypePos);
    }
    else{
      mValueTypeID = CStringDictionary::scmInvalidStringId;
      mDOutputs = 0;
    }
  }
  else{
    return false;
  }

  if(mValueTypeID != CStringDictionary::scmInvalidStringId && mDOutputs >= 2){
    //create the data outputs
    mDataOutputNames = new CStringDictionary::TStringId[mDOutputs];
    mDataOutputTypeIds = new CStringDictionary::TStringId[mDOutputs];

    char doNames[cgIdentifierLength] = { "OUT_" };
    for(size_t doIndex = 0; doIndex < mDOutputs; ++doIndex){
      forte_snprintf(&(doNames[4]), 8 - 4, "%i", doIndex + 1);
      mDataOutputNames[doIndex] = CStringDictionary::getInstance().insert(doNames);
      mDataOutputTypeIds[doIndex] = mValueTypeID;
    }

    //create data input type
    mDataInputTypeIds = new CStringDictionary::TStringId[3];
    mDataInputTypeIds[0] = g_nStringIdARRAY;
    mDataInputTypeIds[1] = static_cast<CStringDictionary::TStringId>(mDOutputs);
    mDataInputTypeIds[2] = mValueTypeID;

    //create the interface Specification
    paInterfaceSpec.mNumEIs = 1;
    paInterfaceSpec.mEINames = scmEventInputNames;
    paInterfaceSpec.mNumEOs = 1;
    paInterfaceSpec.mEONames = scmEventOutputNames;
    paInterfaceSpec.mNumDIs = 1;
    paInterfaceSpec.mDINames = scmDataInputNames;
    paInterfaceSpec.mDIDataTypeNames = mDataInputTypeIds;
    paInterfaceSpec.mNumDOs = mDOutputs;
    paInterfaceSpec.mDONames = mDataOutputNames;
    paInterfaceSpec.mDODataTypeNames = mDataOutputTypeIds;
    return true;
  }

  return false;
}

