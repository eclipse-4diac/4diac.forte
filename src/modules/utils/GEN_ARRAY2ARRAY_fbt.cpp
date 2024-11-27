/*******************************************************************************
 * Copyright (c) 2014, 2023 Profactor GmbH, fortiss GmbH
 *                          Johannes Kepler University
 *                          Martin Erich Jobst
 *
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
 *    Martin Jobst - add generic readInputData and writeOutputData
 *******************************************************************************/
#include "GEN_ARRAY2ARRAY_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GEN_ARRAY2ARRAY_fbt_gen.cpp"
#endif

#include "resource.h"
#include "criticalregion.h"

DEFINE_GENERIC_FIRMWARE_FB(GEN_ARRAY2ARRAY, g_nStringIdGEN_ARRAY2ARRAY)

const CStringDictionary::TStringId GEN_ARRAY2ARRAY::scmDataInputNames[] = { g_nStringIdIN };
const CStringDictionary::TStringId GEN_ARRAY2ARRAY::scmDataOutputNames[] = { g_nStringIdOUT };

const CStringDictionary::TStringId GEN_ARRAY2ARRAY::scmEventInputNames[] = { g_nStringIdREQ };
const CStringDictionary::TStringId GEN_ARRAY2ARRAY::scmEventInputTypeIds[] = {g_nStringIdEvent};

const CStringDictionary::TStringId GEN_ARRAY2ARRAY::scmEventOutputNames[] = { g_nStringIdCNF };
const CStringDictionary::TStringId GEN_ARRAY2ARRAY::scmEventOutputTypeIds[] = {g_nStringIdEvent};

GEN_ARRAY2ARRAY::GEN_ARRAY2ARRAY(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CGenFunctionBlock<CFunctionBlock>(paContainer, paInstanceNameId) {
}

void GEN_ARRAY2ARRAY::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch (paEIID){
    case scmEventREQID:

      OUT_Array().setValue(IN_Array());

      sendOutputEvent(scmEventCNFID, paECET);

      break;
  }
}

void GEN_ARRAY2ARRAY::readInputData(TEventID) {
  readData(0, *mDIs[0], mDIConns[0]);
}

void GEN_ARRAY2ARRAY::writeOutputData(TEventID) {
  writeData(0, *mDOs[0], mDOConns[0]);
}

bool GEN_ARRAY2ARRAY::createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec){
  const char *dNumberPos = strchr(paConfigString, '_');

  if(nullptr != dNumberPos){
    ++dNumberPos;
    //get position of a second underscore
    const char *dTypePos = strchr(dNumberPos, '_');

    if(nullptr != dTypePos){
      //there is a number and a data type of inputs within the typename
      mArrayLength = static_cast<unsigned int>(forte::core::util::strtoul(dNumberPos, nullptr, 10));
      m_ValueTypeID = CStringDictionary::getInstance().getId(++dTypePos);
    }
    else{
      m_ValueTypeID = CStringDictionary::scmInvalidStringId;
      mArrayLength = 0;
    }
  }
  else{
    return false;
  }

  if(m_ValueTypeID != CStringDictionary::scmInvalidStringId && mArrayLength >= 1){
    //create data input type
    mDataInputTypeIds[0] = g_nStringIdARRAY;
    mDataInputTypeIds[1] = mArrayLength;
    mDataInputTypeIds[2] = m_ValueTypeID;

    //create data output type
    mDataOutputTypeIds[0] = g_nStringIdARRAY;
    mDataOutputTypeIds[1] = mArrayLength;
    mDataOutputTypeIds[2] = m_ValueTypeID;

    //create the interface Specification
    paInterfaceSpec.mNumEIs = 1;
    paInterfaceSpec.mEINames = scmEventInputNames;
    paInterfaceSpec.mNumEOs = 1;
    paInterfaceSpec.mEONames = scmEventOutputNames;
    paInterfaceSpec.mNumDIs = 1;
    paInterfaceSpec.mDINames = scmDataInputNames;
    paInterfaceSpec.mDIDataTypeNames = mDataInputTypeIds.data();
    paInterfaceSpec.mNumDOs = 1;
    paInterfaceSpec.mDONames = scmDataOutputNames;
    paInterfaceSpec.mDODataTypeNames = mDataOutputTypeIds.data();
    return true;
  }

  return false;
}

