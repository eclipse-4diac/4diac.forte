/*******************************************************************************
 * Copyright (c) 2023 Johannes Kepler University Linz
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include <modules/rt_events/RT_Bridge_fbt.h>
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RT_Bridge_fbt_gen.cpp"
#endif

#include "ifSpecBuilder.h"
#include "resource.h"

DEFINE_GENERIC_FIRMWARE_FB(FORTE_GEN_RT_Bridge, g_nStringIdGEN_RT_Bridge)

const CStringDictionary::TStringId FORTE_GEN_RT_Bridge::scmEventInputNames[] = {g_nStringIdRD, g_nStringIdWR};
const CStringDictionary::TStringId FORTE_GEN_RT_Bridge::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const CStringDictionary::TStringId FORTE_GEN_RT_Bridge::scmEventOutputNames[] = {g_nStringIdRDO};
const CStringDictionary::TStringId FORTE_GEN_RT_Bridge::scmEventOutputTypeIds[] = {g_nStringIdEvent};


FORTE_GEN_RT_Bridge::FORTE_GEN_RT_Bridge(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CGenFunctionBlock<CFunctionBlock>(paContainer, paInstanceNameId) {
};

void FORTE_GEN_RT_Bridge::setInitialValues() {
}

void FORTE_GEN_RT_Bridge::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  CCriticalRegion criticalRegion(mSyncObject); // protect the processing of the data independent of the calling event
  switch(paEIID){
    case scmEventRDID:
      sendOutputEvent(scmEventRDOID, paECET);
      break;
    case scmEventWRID:
      for(size_t i = 0; i < getFBInterfaceSpec().mNumDIs; i++) {
        getDO(i)->setValue(getDI(i)->unwrap());
      }
      break;
  }
}

void FORTE_GEN_RT_Bridge::readInputData(const TEventID paEIID) {
  if(paEIID == scmEventWRID) {
    for(size_t i = 0; i < getFBInterfaceSpec().mNumDIs; i++){
      readData(i, *getDI(i), *getDIConUnchecked(i));
    }
  }
}

void FORTE_GEN_RT_Bridge::writeOutputData(const TEventID paEIID) {
  if(paEIID == scmEventRDOID){
    for(size_t i = 0; i < getFBInterfaceSpec().mNumDOs; i++){
      writeData(i, *getDO(i), *getDOConUnchecked(i));
    }
  }
}

bool FORTE_GEN_RT_Bridge::createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec){
  size_t numPorts = 0;

  const char *pos = strrchr(paConfigString, '_');
  if(nullptr != pos){
    pos++;  // move after underscore
    numPorts = static_cast<size_t>(forte::core::util::strtoul(pos, nullptr, 10));
  } else{
    return false;
  }

  if(numPorts < 1){
    return false;
  }

  static const std::array<CStringDictionary::TStringId, 2>anEventInputNames = { g_nStringIdRD, g_nStringIdWR};
  static const std::array<CStringDictionary::TStringId, 1>anEventOutputNames = { g_nStringIdRDO};

  forte::core::util::CIfSpecBuilder isb;
  isb.mEI.setStaticEvents(anEventInputNames);
  isb.mEO.setStaticEvents(anEventOutputNames);
  isb.mDI.addDataRange("SD_", static_cast<int>(numPorts), g_nStringIdANY);
  isb.mDO.addDataRange("RD_", static_cast<int>(numPorts), g_nStringIdANY);

  return isb.build(mIfSpecStorage, paInterfaceSpec);
}



