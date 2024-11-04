/*******************************************************************************
 * Copyright (c) 2014 - 2015 Profactor GmbH, fortiss GmbH
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
#include "GEN_VALUES2ARRAY_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GEN_VALUES2ARRAY_fbt_gen.cpp"
#endif

#include <stdio.h>
#include "forte_printer.h"
#include "resource.h"
#include "criticalregion.h"

DEFINE_GENERIC_FIRMWARE_FB(GEN_VALUES2ARRAY, g_nStringIdGEN_VALUES2ARRAY)

const CStringDictionary::TStringId GEN_VALUES2ARRAY::scmDataOutputNames[] = { g_nStringIdOUT };

const CStringDictionary::TStringId GEN_VALUES2ARRAY::scmEventInputNames[] = { g_nStringIdREQ };
const CStringDictionary::TStringId GEN_VALUES2ARRAY::scmEventInputTypeIds[] = {g_nStringIdEvent};

const CStringDictionary::TStringId GEN_VALUES2ARRAY::scmEventOutputNames[] = { g_nStringIdCNF };
const CStringDictionary::TStringId GEN_VALUES2ARRAY::scmEventOutputTypeIds[] = {g_nStringIdEvent};

GEN_VALUES2ARRAY::GEN_VALUES2ARRAY(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CGenFunctionBlock<CFunctionBlock>(paContainer, paInstanceNameId), mDataInputNames(nullptr), mDataInputTypeIds(nullptr), mDataOutputTypeIds(nullptr), mDInputs(0), m_ValueTypeID(CStringDictionary::CStringDictionary::scmInvalidStringId){
}

GEN_VALUES2ARRAY::~GEN_VALUES2ARRAY(){
  delete[] mDataInputNames;
  delete[] mDataInputTypeIds;
  delete[] mDataOutputTypeIds;
}

void GEN_VALUES2ARRAY::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch (paEIID){
    case scmEventREQID:

      for(unsigned int input_index = 0; input_index < mDInputs; input_index++){
        //copy input values to array
        OUT_Array()[input_index].setValue(*getDI(input_index));
      }

      sendOutputEvent(scmEventCNFID, paECET);

      break;
  }
}

void GEN_VALUES2ARRAY::readInputData(TEventID) {
  for(TPortId i = 0; i < getFBInterfaceSpec().mNumDIs; ++i) {
    readData(i, *mDIs[i], mDIConns[i]);
  }
}

void GEN_VALUES2ARRAY::writeOutputData(TEventID) {
  writeData(0, *mDOs[0], mDOConns[0]);
}

bool GEN_VALUES2ARRAY::createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec){
  const char *dNumberPos = strchr(paConfigString, '_');

  if(nullptr != dNumberPos){
    ++dNumberPos;
    //get position of a second underscore
    const char *dTypePos = strchr(dNumberPos, '_');

    if(nullptr != dTypePos){
      //there is a number and a data type of inputs within the typename
      mDInputs = static_cast<unsigned int>(forte::core::util::strtoul(dNumberPos, nullptr, 10));
      m_ValueTypeID = CStringDictionary::getInstance().getId(++dTypePos);
    }
    else{
      m_ValueTypeID = CStringDictionary::scmInvalidStringId;
      mDInputs = 0;
    }
  }
  else{
    return false;
  }

  if(m_ValueTypeID != CStringDictionary::scmInvalidStringId && mDInputs >= 2){
    //create the data inputs
    mDataInputNames = new CStringDictionary::TStringId[mDInputs];
    mDataInputTypeIds = new CStringDictionary::TStringId[mDInputs];

    char diNames[cgIdentifierLength] = { "IN_" };
    for(unsigned int di = 0; di < mDInputs; di = di + 1){
      forte_snprintf(&(diNames[3]), 7 - 3, "%u", di + 1);
      mDataInputNames[di] = CStringDictionary::getInstance().insert(diNames);
      mDataInputTypeIds[di] = m_ValueTypeID;
    }

    //create data output type
    mDataOutputTypeIds = new CStringDictionary::TStringId[3];
    mDataOutputTypeIds[0] = g_nStringIdARRAY;
    mDataOutputTypeIds[1] = mDInputs;
    mDataOutputTypeIds[2] = m_ValueTypeID;

    //create the interface Specification
    paInterfaceSpec.mNumEIs = 1;
    paInterfaceSpec.mEINames = scmEventInputNames;
    paInterfaceSpec.mNumEOs = 1;
    paInterfaceSpec.mEONames = scmEventOutputNames;
    paInterfaceSpec.mNumDIs = mDInputs;
    paInterfaceSpec.mDINames = mDataInputNames;
    paInterfaceSpec.mDIDataTypeNames = mDataInputTypeIds;
    paInterfaceSpec.mNumDOs = 1;
    paInterfaceSpec.mDONames = scmDataOutputNames;
    paInterfaceSpec.mDODataTypeNames = mDataOutputTypeIds;
    return true;
  }
  return false;
}

