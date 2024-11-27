/*******************************************************************************
 * Copyright (c) 2017, 2023 fortiss GmbH, Johannes Kepler University Linz
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger - initial API and implementation and/or initial documentation
 *   Alois Zoitl   - upgraded to new FB memory layout
 *******************************************************************************/

#include "luaadaptertypeentry.h"
#include "luaengine.h"
#include "luatype.h"
#include "luaadapter.h"
#include "resource.h"
#include "adapter.h"

CLuaAdapterTypeEntry::CLuaAdapterTypeEntry(CStringDictionary::TStringId paTypeNameId, const std::string &  paLuaScriptAsString, SFBInterfaceSpec& paInterfaceSpec) :
    CTypeLib::CAdapterTypeEntry(paTypeNameId, nullptr, &mSocketInterfaceSpec), cmLuaScriptAsString(paLuaScriptAsString), mSocketInterfaceSpec(paInterfaceSpec) {
  initPlugInterfaceSpec(mSocketInterfaceSpec);
}

CLuaAdapterTypeEntry::~CLuaAdapterTypeEntry() {
  deleteInterfaceSpec(mSocketInterfaceSpec);
}

CLuaAdapterTypeEntry* CLuaAdapterTypeEntry::createLuaAdapterTypeEntry(CStringDictionary::TStringId paTypeNameId, const std::string & paLuaScriptAsString) {
  CLuaEngine luaEngine;
  if(!luaEngine.loadString(paLuaScriptAsString)) {
    return nullptr;
  }
  //interfaceSpec
  SFBInterfaceSpec interfaceSpec{};
  if(!luaEngine.pushField(-1, "interfaceSpec", LUA_TTABLE)) {
    return nullptr;
  }
  if(!initInterfaceSpec(interfaceSpec, &luaEngine, -1)) {
    deleteInterfaceSpec(interfaceSpec);
    return nullptr;
  }
  luaEngine.pop(); //pop interfaceSpec
  luaEngine.pop(); //pop loaded defs
  return new CLuaAdapterTypeEntry(paTypeNameId, paLuaScriptAsString, interfaceSpec);
}

CAdapter* CLuaAdapterTypeEntry::createAdapterInstance(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer, bool paIsPlug) {
  CLuaEngine* luaEngine = paContainer.getResource()->getLuaEngine();
  if(!luaEngine->load(this) && (!luaEngine->loadString(cmLuaScriptAsString))) {
    return nullptr;
  }
  return new CLuaAdapter(paInstanceNameId, this, paIsPlug, paContainer);
}

bool CLuaAdapterTypeEntry::initInterfaceSpec(SFBInterfaceSpec& paInterfaceSpec, CLuaEngine* paLuaEngine, int paIndex) {
  //EI
  paInterfaceSpec.mNumEIs = paLuaEngine->getField<TForteUInt8, &CLuaEngine::getInteger<TForteUInt8> >(paIndex, "numEIs");
  size_t numEIs = paInterfaceSpec.mNumEIs;
  paInterfaceSpec.mEINames = paLuaEngine->getArrayField<CStringDictionary::TStringId, &CLuaEngine::getStringId>(paIndex, "EINames", numEIs);
  size_t numEIWith = SIZE_MAX;
  paInterfaceSpec.mEIWith = paLuaEngine->getArrayField<TDataIOID, &CLuaEngine::getInteger<TDataIOID> >(paIndex, "EIWith", numEIWith);
  paInterfaceSpec.mEIWithIndexes = paLuaEngine->getArrayField<TForteInt16, &CLuaEngine::getInteger<TForteInt16> >(paIndex, "EIWithIndexes", numEIs);
  //EO
  paInterfaceSpec.mNumEOs = paLuaEngine->getField<TForteUInt8, &CLuaEngine::getInteger<TForteUInt8> >(paIndex, "numEOs");
  size_t numEOs = paInterfaceSpec.mNumEOs;
  paInterfaceSpec.mEONames = paLuaEngine->getArrayField<CStringDictionary::TStringId, &CLuaEngine::getStringId>(paIndex, "EONames", numEOs);
  size_t numEOWith = SIZE_MAX;
  paInterfaceSpec.mEOWith = paLuaEngine->getArrayField<TDataIOID, &CLuaEngine::getInteger<TDataIOID> >(paIndex, "EOWith", numEOWith);
  paInterfaceSpec.mEOWithIndexes = paLuaEngine->getArrayField<TForteInt16, &CLuaEngine::getInteger<TForteInt16> >(paIndex, "EOWithIndexes", numEOs);
  //DI
  paInterfaceSpec.mNumDIs = paLuaEngine->getField<TForteUInt8, &CLuaEngine::getInteger<TForteUInt8> >(paIndex, "numDIs");
  size_t numDIs = paInterfaceSpec.mNumDIs;
  paInterfaceSpec.mDINames = paLuaEngine->getArrayField<CStringDictionary::TStringId, &CLuaEngine::getStringId>(paIndex, "DINames", numDIs);
  size_t numDIDataTypeNames = SIZE_MAX;
  paInterfaceSpec.mDIDataTypeNames = paLuaEngine->getCustomArrayField<CStringDictionary::TStringId, luatype::getTypeNameId>(paIndex, "DIDataTypeNames",
    numDIDataTypeNames);
  //DO
  paInterfaceSpec.mNumDOs = paLuaEngine->getField<TForteUInt8, &CLuaEngine::getInteger<TForteUInt8> >(paIndex, "numDOs");
  size_t numDOs = paInterfaceSpec.mNumDOs;
  paInterfaceSpec.mDONames = paLuaEngine->getArrayField<CStringDictionary::TStringId, &CLuaEngine::getStringId>(paIndex, "DONames", numDOs);
  size_t numDODataTypeNames = SIZE_MAX;
  paInterfaceSpec.mDODataTypeNames = paLuaEngine->getCustomArrayField<CStringDictionary::TStringId, luatype::getTypeNameId>(paIndex, "DODataTypeNames",
    numDODataTypeNames);
  paInterfaceSpec.mNumAdapters = 0;
  paInterfaceSpec.mAdapterInstanceDefinition = nullptr;
  //checks
  if(paInterfaceSpec.mEINames == nullptr || paInterfaceSpec.mEIWith == nullptr || paInterfaceSpec.mEIWithIndexes == nullptr
    || paInterfaceSpec.mEONames == nullptr || paInterfaceSpec.mEOWith == nullptr || paInterfaceSpec.mEOWithIndexes == nullptr
    || paInterfaceSpec.mDINames == nullptr || paInterfaceSpec.mDIDataTypeNames == nullptr || paInterfaceSpec.mDONames == nullptr
    || paInterfaceSpec.mDODataTypeNames == nullptr) {
    return false;
  }
  for(size_t i = 0; i < numEIs; i++) {
    if(paInterfaceSpec.mEIWithIndexes[i] >= (TForteInt16) numEIWith) {
      return false;
    }
  }
  for(size_t i = 0; i < numEOs; i++) {
    if(paInterfaceSpec.mEOWithIndexes[i] >= (TForteInt16) numEOWith) {
      return false;
    }
  }
  return true;
}

bool CLuaAdapterTypeEntry::initPlugInterfaceSpec(SFBInterfaceSpec& paInterfaceSpec) {
  //EI
  mPlugInterfaceSpec.mNumEIs = paInterfaceSpec.mNumEOs;
  mPlugInterfaceSpec.mEINames = paInterfaceSpec.mEONames;
  mPlugInterfaceSpec.mEIWith = paInterfaceSpec.mEOWith;
  mPlugInterfaceSpec.mEIWithIndexes = paInterfaceSpec.mEOWithIndexes;
  //EO
  mPlugInterfaceSpec.mNumEOs = paInterfaceSpec.mNumEIs;
  mPlugInterfaceSpec.mEONames = paInterfaceSpec.mEINames;
  mPlugInterfaceSpec.mEOWith = paInterfaceSpec.mEIWith;
  mPlugInterfaceSpec.mEOWithIndexes = paInterfaceSpec.mEIWithIndexes;
  //DI
  mPlugInterfaceSpec.mNumDIs = paInterfaceSpec.mNumDOs;
  mPlugInterfaceSpec.mDINames = paInterfaceSpec.mDONames;
  mPlugInterfaceSpec.mDIDataTypeNames = paInterfaceSpec.mDODataTypeNames;
  //DO
  mPlugInterfaceSpec.mNumDOs = paInterfaceSpec.mNumDIs;
  mPlugInterfaceSpec.mDONames = paInterfaceSpec.mDINames;
  mPlugInterfaceSpec.mDODataTypeNames = paInterfaceSpec.mDIDataTypeNames;
  mPlugInterfaceSpec.mNumAdapters = 0;
  mPlugInterfaceSpec.mAdapterInstanceDefinition = nullptr;
  return true;
}

void CLuaAdapterTypeEntry::deleteInterfaceSpec(SFBInterfaceSpec& paInterfaceSpec) {
  delete[] paInterfaceSpec.mEINames;
  delete[] paInterfaceSpec.mEIWith;
  delete[] paInterfaceSpec.mEIWithIndexes;
  delete[] paInterfaceSpec.mEONames;
  delete[] paInterfaceSpec.mEOWith;
  delete[] paInterfaceSpec.mEOWithIndexes;
  delete[] paInterfaceSpec.mDINames;
  delete[] paInterfaceSpec.mDIDataTypeNames;
  delete[] paInterfaceSpec.mDONames;
  delete[] paInterfaceSpec.mDODataTypeNames;
}
