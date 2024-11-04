/*******************************************************************************
 * Copyright (c) 2013, 2024 ACIN, Martin Erich Jobst,
 *                          Primetals Technologies Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - refactored from F_MOVE
 *******************************************************************************/

#include "GEN_FORTE_F_MOVE_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GEN_FORTE_F_MOVE_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_GENERIC_FIRMWARE_FB(GEN_FORTE_F_MOVE, g_nStringIdGEN_F_MOVE)

const CStringDictionary::TStringId GEN_FORTE_F_MOVE::scmDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId GEN_FORTE_F_MOVE::scmDataOutputNames[] = {g_nStringIdOUT};

const TDataIOID GEN_FORTE_F_MOVE::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 GEN_FORTE_F_MOVE::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId GEN_FORTE_F_MOVE::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId GEN_FORTE_F_MOVE::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID GEN_FORTE_F_MOVE::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 GEN_FORTE_F_MOVE::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId GEN_FORTE_F_MOVE::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId GEN_FORTE_F_MOVE::scmEventOutputTypeIds[] = {g_nStringIdEvent};


GEN_FORTE_F_MOVE::GEN_FORTE_F_MOVE(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CGenFunctionBlock<CFunctionBlock>(paContainer, paInstanceNameId) {
}

GEN_FORTE_F_MOVE::~GEN_FORTE_F_MOVE(){
    delete[](getGenInterfaceSpec().mDIDataTypeNames);
    delete[](getGenInterfaceSpec().mDODataTypeNames);
}

void GEN_FORTE_F_MOVE::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      var_OUT().setValue(var_IN());
      sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

void GEN_FORTE_F_MOVE::readInputData(TEventID paEIID) {
  if(paEIID == scmEventREQID) {
    readData(0, *mDIs[0], mDIConns[0]);
  }
}

void GEN_FORTE_F_MOVE::writeOutputData(TEventID paEOID) {
  if(paEOID == scmEventCNFID){
    writeData(0, *mDOs[0], mDOConns[0]);
  }
}

bool GEN_FORTE_F_MOVE::createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec) {
  const CTypeLib::CTypeEntry *poToCreate;
  if(strcmp(paConfigString, "F_MOVE") == 0) {
    poToCreate = &CIEC_ANY_VARIANT::csmFirmwareDataTypeEntry_ANY_VARIANT;
  } else {
    poToCreate = CTypeLib::findType(getDataTypeNameId(paConfigString), CTypeLib::getDTLibStart());
    if (nullptr == poToCreate) {
      return false;
    }
  }

  CStringDictionary::TStringId *diDataTypeNames = new CStringDictionary::TStringId[1];
  diDataTypeNames[0] = poToCreate->getTypeNameId();
  CStringDictionary::TStringId *doDataTypeNames = new CStringDictionary::TStringId[1];
  doDataTypeNames[0] = poToCreate->getTypeNameId();

  paInterfaceSpec.mNumEIs = 1;
  paInterfaceSpec.mEINames = scmEventInputNames;
  paInterfaceSpec.mEIWith = scmEIWith;
  paInterfaceSpec.mEIWithIndexes = scmEIWithIndexes;
  paInterfaceSpec.mNumEOs = 1;
  paInterfaceSpec.mEONames = scmEventOutputNames;
  paInterfaceSpec.mEOWith = scmEOWith;
  paInterfaceSpec.mEOWithIndexes = scmEOWithIndexes;
  paInterfaceSpec.mNumDIs = 1;
  paInterfaceSpec.mDINames = scmDataInputNames;
  paInterfaceSpec.mDIDataTypeNames = diDataTypeNames;
  paInterfaceSpec.mNumDOs = 1;
  paInterfaceSpec.mDONames = scmDataOutputNames;
  paInterfaceSpec.mDODataTypeNames = doDataTypeNames;

  return true;
}

CStringDictionary::TStringId GEN_FORTE_F_MOVE::getDataTypeNameId(const char *paConfigString) {
  const char *acPos = strchr(paConfigString, '_');
  if(nullptr != acPos){
    acPos++;
    acPos = strchr(acPos, '_');
    if(nullptr != acPos){
      acPos += 2;  //put the position one after the separating number
      return CStringDictionary::getInstance().getId(acPos);
    }
  }
  return CStringDictionary::scmInvalidStringId;
}

