/*******************************************************************************
 * Copyright (c) 2020, 2023 Johannes Kepler University
 *                          Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - initial API and implementation and/or initial documentation
 *   Martin Jobst - add generic readInputData and writeOutputData
 *******************************************************************************/
#include "GEN_STRUCT_DEMUX_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GEN_STRUCT_DEMUX_fbt_gen.cpp"
#endif
#include "GEN_STRUCT_MUX_fbt.h"
#include <stdio.h>
#include "GEN_STRUCT_DEMUX_fbt.h"

#include "resource.h"
#include "criticalregion.h"

DEFINE_GENERIC_FIRMWARE_FB(GEN_STRUCT_DEMUX, g_nStringIdGEN_STRUCT_DEMUX);

const CStringDictionary::TStringId GEN_STRUCT_DEMUX::scmEventInputNames[] = { g_nStringIdREQ };
const CStringDictionary::TStringId GEN_STRUCT_DEMUX::scmEventInputTypeIds[] = {g_nStringIdEvent};
const CStringDictionary::TStringId GEN_STRUCT_DEMUX::scmEventOutputNames[] = { g_nStringIdCNF };
const CStringDictionary::TStringId GEN_STRUCT_DEMUX::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const CStringDictionary::TStringId GEN_STRUCT_DEMUX::scmDataInputNames[] = { g_nStringIdIN };

void GEN_STRUCT_DEMUX::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  if(scmEventREQID == paEIID) {
    for (TPortId i = 0; i < st_IN().getStructSize(); i++){
      getDO(i)->setValue(*st_IN().getMember(i));
    }
    sendOutputEvent(scmEventCNFID, paECET);
  }
}

GEN_STRUCT_DEMUX::GEN_STRUCT_DEMUX(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CGenFunctionBlock<CFunctionBlock>(paContainer, paInstanceNameId){
}

GEN_STRUCT_DEMUX::~GEN_STRUCT_DEMUX() {
  delete[] (getGenInterfaceSpec().mDIDataTypeNames);
  delete[] (getGenInterfaceSpec().mDONames);
  delete[] (getGenInterfaceSpec().mDODataTypeNames);
}

void GEN_STRUCT_DEMUX::readInputData(TEventID) {
  readData(0, *mDIs[0], mDIConns[0]);
}

void GEN_STRUCT_DEMUX::writeOutputData(TEventID) {
  for(TPortId i = 0; i < getFBInterfaceSpec().mNumDOs; ++i) {
    writeData(i, *mDOs[i], mDOConns[i]);
  }
}

bool GEN_STRUCT_DEMUX::initialize() {
  if(CGenFunctionBlock::initialize()) {
    copyStructValuesToOutputs();
    return true;
  }
  return false;
}

void GEN_STRUCT_DEMUX::setInitialValues() {
  CFunctionBlock::setInitialValues();
  copyStructValuesToOutputs();
}

void GEN_STRUCT_DEMUX::copyStructValuesToOutputs() {
  for (TPortId i = 0; i < st_IN().getStructSize(); i++) {
    getDO(i)->setValue(st_IN().getMember(i)->unwrap());
  }
}

bool GEN_STRUCT_DEMUX::createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec) {
  bool retval = false;
  CStringDictionary::TStringId structTypeNameId = GEN_STRUCT_MUX::getStructNameId(paConfigString);

  CIEC_ANY *data = CTypeLib::createDataTypeInstance(structTypeNameId, nullptr);

  if(nullptr != data) {
    if(data->getDataTypeID() == CIEC_ANY::e_STRUCT) {
      // we could find the struct
      CIEC_STRUCT *structInstance = static_cast<CIEC_STRUCT*>(data);

      size_t structSize = structInstance->getStructSize();
      if(structSize != 0 && structSize < cgInvalidPortId) { //the structure size must be non zero and less than cgInvalidPortId (maximum number of data outputs)
        CStringDictionary::TStringId *doDataTypeNames = new CStringDictionary::TStringId[GEN_STRUCT_MUX::calcStructTypeNameSize(*structInstance)];
        CStringDictionary::TStringId *doNames = new CStringDictionary::TStringId[structSize];
        CStringDictionary::TStringId *diDataTypeNames = new CStringDictionary::TStringId[1];

        paInterfaceSpec.mNumEIs = 1;
        paInterfaceSpec.mEINames = scmEventInputNames;
        paInterfaceSpec.mEITypeNames = scmEventInputTypeIds;
        paInterfaceSpec.mNumEOs = 1;
        paInterfaceSpec.mEONames = scmEventOutputNames;
        paInterfaceSpec.mEOTypeNames = scmEventOutputTypeIds;
        paInterfaceSpec.mNumDIs = 1;
        paInterfaceSpec.mDINames = scmDataInputNames;
        paInterfaceSpec.mDIDataTypeNames = diDataTypeNames;
        paInterfaceSpec.mNumDOs = structSize;
        paInterfaceSpec.mDONames = doNames;
        paInterfaceSpec.mDODataTypeNames = doDataTypeNames;
        diDataTypeNames[0] = structTypeNameId;

        for(size_t i = 0; i < structSize; ++i) {
          const CIEC_ANY &member = *structInstance->getMember(i);
          doNames[i] = structInstance->elementNames()[i];
          fillDataPointSpec(member, doDataTypeNames);
        }
        retval = true;
      } else {
        DEVLOG_ERROR("[GEN_STRUCT_DEMUX]: The structure %s has a size is not within range > 0 and < %u\n",
                     CStringDictionary::getInstance().get(structTypeNameId), cgInvalidPortId);
      }
    } else {
      DEVLOG_ERROR("[GEN_STRUCT_DEMUX]: data type is not a structure: %s\n", CStringDictionary::getInstance().get(structTypeNameId));
    }
    delete data;
  } else {
    DEVLOG_ERROR("[GEN_STRUCT_DEMUX]: Couldn't create structure of type: %s\n", CStringDictionary::getInstance().get(structTypeNameId));
  }
  return retval;
}




