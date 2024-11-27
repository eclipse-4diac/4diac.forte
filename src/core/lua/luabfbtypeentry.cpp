/*******************************************************************************
 * Copyright (c) 2015, 2023 fortiss GmbH, Johannes Kepler University Linz
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Martin Jobst - initial API and implementation and/or initial documentation
 *   Alois Zoitl  - upgraded to new FB memory layout
 *******************************************************************************/

#include "luabfbtypeentry.h"

#include "luaengine.h"
#include "luabfb.h"
#include "luatype.h"
#include "resource.h"

CLuaBFBTypeEntry::CLuaBFBTypeEntry(CStringDictionary::TStringId paTypeNameId, const std::string& paLuaScriptAsString, SFBInterfaceSpec& paInterfaceSpec,
    SInternalVarsInformation& paInternalVarsInformation) :
    CFBTypeEntry(paTypeNameId, nullptr, &m_interfaceSpec), cmLuaScriptAsString(paLuaScriptAsString), m_interfaceSpec(paInterfaceSpec),
        m_internalVarsInformation(paInternalVarsInformation) {
}

CLuaBFBTypeEntry::~CLuaBFBTypeEntry() {
  deleteInterfaceSpec(m_interfaceSpec);
  deleteInternalVarsInformation(m_internalVarsInformation);
}

CLuaBFBTypeEntry* CLuaBFBTypeEntry::createLuaFBTypeEntry(CStringDictionary::TStringId paTypeNameId, const std::string& paLuaScriptAsString) {
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
  //internalVarsInformation
  SInternalVarsInformation internalVarsInformation = { 0, nullptr, nullptr };
  if(!luaEngine.pushField(-1, "internalVarsInformation", LUA_TTABLE)) {
    deleteInterfaceSpec(interfaceSpec);
    return nullptr;
  }
  if(!initInternalVarsInformation(internalVarsInformation, &luaEngine, -1)) {
    deleteInterfaceSpec(interfaceSpec);
    deleteInternalVarsInformation(internalVarsInformation);
    return nullptr;
  }
  luaEngine.pop(); //pop internalVarsInformation
  luaEngine.pop(); //pop loaded defs
  return new CLuaBFBTypeEntry(paTypeNameId, paLuaScriptAsString, interfaceSpec, internalVarsInformation);
}

CFunctionBlock* CLuaBFBTypeEntry::createFBInstance(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) {
  CLuaEngine* luaEngine = paContainer.getResource()->getLuaEngine();
  if(!luaEngine->load(this)) {
    if(!luaEngine->loadString(cmLuaScriptAsString)) {
      return nullptr;
    }
    luaEngine->pushField(-1, "ECC", LUA_TFUNCTION);
    luaEngine->store(this); //store ECC
  }
  luaEngine->pop(); //pop ECC / loaded defs
  return new CLuaBFB(paInstanceNameId, this, paContainer);
}

bool CLuaBFBTypeEntry::initInterfaceSpec(SFBInterfaceSpec& paInterfaceSpec, CLuaEngine* paLuaEngine, int paIndex) {
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
  //Adapters
  paInterfaceSpec.mNumAdapters = paLuaEngine->getField<TForteUInt8, &CLuaEngine::getInteger<TForteUInt8> >(paIndex, "numAdapters");
  size_t numAdapters = paInterfaceSpec.mNumAdapters;
  paInterfaceSpec.mAdapterInstanceDefinition = paLuaEngine->getCustomArrayField<SAdapterInstanceDef, luatype::getAdapterInstanceDefinition>(paIndex,
    "adapterInstanceDefinition", numAdapters);
  //checks
  if(paInterfaceSpec.mEINames == nullptr || paInterfaceSpec.mEIWith == nullptr || paInterfaceSpec.mEIWithIndexes == nullptr
    || paInterfaceSpec.mEONames == nullptr || paInterfaceSpec.mEOWith == nullptr || paInterfaceSpec.mEOWithIndexes == nullptr
    || paInterfaceSpec.mDINames == nullptr || paInterfaceSpec.mDIDataTypeNames == nullptr || paInterfaceSpec.mDONames == nullptr
    || paInterfaceSpec.mDODataTypeNames == nullptr || paInterfaceSpec.mAdapterInstanceDefinition == nullptr) {
    return false;
  }
  return true;
}

void CLuaBFBTypeEntry::deleteInterfaceSpec(SFBInterfaceSpec& paInterfaceSpec) {
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
  delete[] paInterfaceSpec.mAdapterInstanceDefinition;
}

bool CLuaBFBTypeEntry::initInternalVarsInformation(SInternalVarsInformation& paInternalVarsInformation, CLuaEngine* paLuaEngine, int paIndex) {
  paInternalVarsInformation.mNumIntVars = paLuaEngine->getField<TPortId, &CLuaEngine::getInteger<TPortId> >(paIndex, "numIntVars");
  size_t numIntVars = paInternalVarsInformation.mNumIntVars;
  paInternalVarsInformation.mIntVarsNames = paLuaEngine->getArrayField<CStringDictionary::TStringId, &CLuaEngine::getStringId>(paIndex, "intVarsNames",
    numIntVars);
  size_t numIntVarTypes = SIZE_MAX;
  paInternalVarsInformation.mIntVarsDataTypeNames = paLuaEngine->getCustomArrayField<CStringDictionary::TStringId, luatype::getTypeNameId>(paIndex,
    "intVarsDataTypeNames", numIntVarTypes);
  if(paInternalVarsInformation.mIntVarsNames == nullptr || paInternalVarsInformation.mIntVarsDataTypeNames == nullptr) {
    return false;
  }
  return true;
}

void CLuaBFBTypeEntry::deleteInternalVarsInformation(SInternalVarsInformation& paInternalVarsInformation) {
  delete[] paInternalVarsInformation.mIntVarsNames;
  delete[] paInternalVarsInformation.mIntVarsDataTypeNames;
}
