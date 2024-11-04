/*******************************************************************************
 * Copyright (c) 2017, 2024 fortiss GmbH, Johannes Kepler University Linz
 *                          Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger - initial API and implementation and/or initial documentation
 *   Alois Zoitl   - upgraded to new FB memory layout
 *   Martin Jobst  - added dynamic internal FB creation from CCompositeFB
 *******************************************************************************/

#include "luacfb.h"
#include "resource.h"
#include "criticalregion.h"

CLuaCFB::CLuaCFB(CStringDictionary::TStringId paInstanceNameId, const CLuaCFBTypeEntry* paTypeEntry, SCFB_FBNData &paFbnData, forte::core::CFBContainer &paContainer) :
    CGenFunctionBlock<CCompositeFB>(paContainer, paTypeEntry->getInterfaceSpec(), paInstanceNameId, paFbnData), mTypeEntry(paTypeEntry) {
}

CLuaCFB::~CLuaCFB() = default;

bool CLuaCFB::createInternalFBs(){
  const SCFB_FBNData &fbnData = getFBNData();
  if(fbnData.mNumFBs){
    for(size_t i = 0; i < fbnData.mNumFBs; ++i){
      const SCFB_FBInstanceData &cfbInstanceData(fbnData.mFBInstances[i]);
      if(createFB(cfbInstanceData.mFBInstanceNameId, cfbInstanceData.mFBTypeNameId) != EMGMResponse::Ready){
        DEVLOG_ERROR("Cannot create internal FB (name: %s, type: %s) in CFB (type: %s)!\n",
                     CStringDictionary::getInstance().get(cfbInstanceData.mFBInstanceNameId),
                     CStringDictionary::getInstance().get(cfbInstanceData.mFBTypeNameId),
                     getFBTypeName());
        return false;
      }
    }
  }
  return true;
}

void CLuaCFB::readInputData(TEventID paEIID) {
  if(getFBInterfaceSpec().mEIWithIndexes != nullptr && getFBInterfaceSpec().mEIWithIndexes[paEIID] != scmNoDataAssociated) {
    const TDataIOID *eiWithStart = &(getFBInterfaceSpec().mEIWith[getFBInterfaceSpec().mEIWithIndexes[paEIID]]);
    for(size_t i = 0; eiWithStart[i] != scmWithListDelimiter; ++i) {
      TDataIOID diNum = eiWithStart[i];
      readData(diNum, *getDI(diNum), *getDIConUnchecked(diNum));
    }
  }
}

void CLuaCFB::writeOutputData(TEventID paEO) {
  if (getFBInterfaceSpec().mEOWithIndexes != nullptr && getFBInterfaceSpec().mEOWithIndexes[paEO] != -1) {
    const TDataIOID *eiWithStart = &(getFBInterfaceSpec().mEOWith[getFBInterfaceSpec().mEOWithIndexes[paEO]]);
    for (size_t i = 0; eiWithStart[i] != scmWithListDelimiter; ++i) {
      TDataIOID doNum = eiWithStart[i];
      writeData(doNum, *getDO(doNum), *getDOConUnchecked(doNum));
    }
  }
}

void CLuaCFB::readInternal2InterfaceOutputData(TEventID paEOID){
  //handle sampling of internal 2 interface data connections
  if((paEOID < getFBInterfaceSpec().mNumEOs) && (getFBInterfaceSpec().mEOWithIndexes != nullptr) &&
      (getFBInterfaceSpec().mEOWithIndexes[paEOID]) != -1){
    const TDataIOID *poEOWithStart = &(getFBInterfaceSpec().mEOWith[getFBInterfaceSpec().mEOWithIndexes[paEOID]]);
    for(size_t i = 0; poEOWithStart[i] != scmWithListDelimiter; ++i){
      if(getIn2IfConUnchecked(poEOWithStart[i]) != nullptr){
        getIn2IfConUnchecked(poEOWithStart[i])->readData(*getDO(poEOWithStart[i]));
      }
    }
  }
}
