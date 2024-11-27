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

#include "luacfbtypeentry.h"

#include "resource.h"
#include "luaengine.h"
#include "luacfb.h"
#include "luatype.h"

namespace luatype {
  bool getFBInstanceData(SCFB_FBInstanceData& paDef, CLuaEngine* paLuaEngine, int paIndex) {
    paDef.mFBInstanceNameId = paLuaEngine->getField<CStringDictionary::TStringId, &CLuaEngine::getStringId>(paIndex, "fbNameID");
    paDef.mFBTypeNameId = paLuaEngine->getField<CStringDictionary::TStringId, &CLuaEngine::getStringId>(paIndex, "fbTypeID");
    if(paDef.mFBInstanceNameId == CStringDictionary::scmInvalidStringId || paDef.mFBTypeNameId == CStringDictionary::scmInvalidStringId) {
      return false;
    }
    return true;
  }

  bool getFBConnectionData(SCFB_FBConnectionData& paDef, CLuaEngine* paLuaEngine, int paIndex) {
    paDef.mDstFBNum = paLuaEngine->getField<int, &CLuaEngine::getInteger<int> >(paIndex, "dstFBNum");
    paDef.mDstId = paLuaEngine->getField<CStringDictionary::TStringId, &CLuaEngine::getStringId>(paIndex, "dstID");
    paDef.mSrcFBNum = paLuaEngine->getField<int, &CLuaEngine::getInteger<int> >(paIndex, "srcFBNum");
    paDef.mSrcId = paLuaEngine->getField<CStringDictionary::TStringId, &CLuaEngine::getStringId>(paIndex, "srcID");
    if(paDef.mDstId == CStringDictionary::scmInvalidStringId || paDef.mSrcId == CStringDictionary::scmInvalidStringId) {
      return false;
    }
    return true;
  }

  bool getFBFannedOutConnectionData(SCFB_FBFannedOutConnectionData& paDef, CLuaEngine* paLuaEngine, int paIndex) {
    paDef.mConnectionNum = paLuaEngine->getField<int, &CLuaEngine::getInteger<int> >(paIndex, "connectionNum");
    paDef.mDstFBNum = paLuaEngine->getField<int, &CLuaEngine::getInteger<int> >(paIndex, "dstFBNum");
    paDef.mDstId = paLuaEngine->getField<CStringDictionary::TStringId, &CLuaEngine::getStringId>(paIndex, "dstID");
    if(paDef.mDstId == CStringDictionary::scmInvalidStringId) {
      return false;
    }
    return true;
  }

  bool getFBParameter(SCFB_FBParameter& paDef, CLuaEngine* paLuaEngine, int paIndex) {
    paDef.mParamValue = paLuaEngine->getField<const char *, &CLuaEngine::getString>(paIndex, "paramValue");
    paDef.mDINameID = paLuaEngine->getField<CStringDictionary::TStringId, &CLuaEngine::getStringId>(paIndex, "diNameID");
    paDef.mFBNum = paLuaEngine->getField<int, &CLuaEngine::getInteger<int> >(paIndex, "fbNum");
    if(paDef.mDINameID == CStringDictionary::scmInvalidStringId) {
      return false;
    }
    return true;
  }
}

CLuaCFBTypeEntry::CLuaCFBTypeEntry(CStringDictionary::TStringId paTypeNameId, const std::string & paLuaScriptAsString, SFBInterfaceSpec& paInterfaceSpec,
    SCFB_FBNData& paFbnSpec) :
    CTypeLib::CFBTypeEntry(paTypeNameId, nullptr, &m_interfaceSpec), cmLuaScriptAsString(paLuaScriptAsString), m_interfaceSpec(paInterfaceSpec), mSpec(paFbnSpec) {
}

CLuaCFBTypeEntry::~CLuaCFBTypeEntry() {
  deleteInterfaceSpec(m_interfaceSpec);
  deleteFbnSpec(mSpec);
}

CLuaCFBTypeEntry* CLuaCFBTypeEntry::createLuaFBTypeEntry(CStringDictionary::TStringId paTypeNameId, const std::string & paLuaScriptAsString) {
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
  //fbnSpec
  SCFB_FBNData fbnSpec = { 0, nullptr, 0, nullptr, 0, nullptr, 0, nullptr, 0, nullptr, 0, nullptr, 0, nullptr };
  if(!luaEngine.pushField(-1, "fbnSpec", LUA_TTABLE)) {
    deleteInterfaceSpec(interfaceSpec);
    return nullptr;
  }
  if(!initFbnSpec(fbnSpec, &luaEngine, -1)) {
    deleteInterfaceSpec(interfaceSpec);
    deleteFbnSpec(fbnSpec);
    return nullptr;
  }
  luaEngine.pop(); //pop fbnSpec
  luaEngine.pop(); //pop loaded defs
  return new CLuaCFBTypeEntry(paTypeNameId, paLuaScriptAsString, interfaceSpec, fbnSpec);
}

CFunctionBlock* CLuaCFBTypeEntry::createFBInstance(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) {
  CLuaEngine* luaEngine = paContainer.getResource()->getLuaEngine();
  if(!luaEngine->load(this) && (!luaEngine->loadString(cmLuaScriptAsString))) {
    return nullptr;
  }
  return new CLuaCFB(paInstanceNameId, this, getFbnSpec(), paContainer);
}

bool CLuaCFBTypeEntry::initInterfaceSpec(SFBInterfaceSpec& paInterfaceSpec, CLuaEngine* paLuaEngine, int paIndex) {
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

void CLuaCFBTypeEntry::deleteInterfaceSpec(SFBInterfaceSpec& paInterfaceSpec) {
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

bool CLuaCFBTypeEntry::initFbnSpec(SCFB_FBNData& paFbnSpec, CLuaEngine* paLuaEngine, int paIndex) {
  //internalFBs
  paFbnSpec.mNumFBs = paLuaEngine->getField<TForteUInt8, &CLuaEngine::getInteger<TForteUInt8> >(paIndex, "numFBs");
  size_t numFBs = paFbnSpec.mNumFBs;
  paFbnSpec.mFBInstances = paLuaEngine->getCustomArrayField<SCFB_FBInstanceData, luatype::getFBInstanceData>(paIndex, "internalFBs", numFBs);
  //eventConnections
  paFbnSpec.mNumEventConnections = paLuaEngine->getField<TForteUInt8, &CLuaEngine::getInteger<TForteUInt8> >(paIndex, "numECons");
  size_t numECons = paFbnSpec.mNumEventConnections;
  paFbnSpec.mEventConnections = paLuaEngine->getCustomArrayField<SCFB_FBConnectionData, luatype::getFBConnectionData>(paIndex, "eventConnections",
    numECons);
  //fannedOutEventConnections
  paFbnSpec.mNumFannedOutEventConnections = paLuaEngine->getField<TForteUInt8, &CLuaEngine::getInteger<TForteUInt8> >(paIndex, "numFECons");
  size_t numFECons = paFbnSpec.mNumFannedOutEventConnections;
  paFbnSpec.mFannedOutEventConnections = paLuaEngine->getCustomArrayField<SCFB_FBFannedOutConnectionData, luatype::getFBFannedOutConnectionData>(paIndex,
    "fannedOutEventConnections", numFECons);
  //dataConnections
  paFbnSpec.mNumDataConnections = paLuaEngine->getField<TForteUInt8, &CLuaEngine::getInteger<TForteUInt8> >(paIndex, "numDCons");
  size_t numDCons = paFbnSpec.mNumDataConnections;
  paFbnSpec.mDataConnections = paLuaEngine->getCustomArrayField<SCFB_FBConnectionData, luatype::getFBConnectionData>(paIndex, "dataConnections", numDCons);
  //fannedOutDataConnections
  paFbnSpec.mNumFannedOutDataConnections = paLuaEngine->getField<TForteUInt8, &CLuaEngine::getInteger<TForteUInt8> >(paIndex, "numFDCons");
  size_t numFDCons = paFbnSpec.mNumFannedOutDataConnections;
  paFbnSpec.mFannedOutDataConnections = paLuaEngine->getCustomArrayField<SCFB_FBFannedOutConnectionData, luatype::getFBFannedOutConnectionData>(paIndex,
    "fannedOutDataConnections", numFDCons);
  //dataConnections
  paFbnSpec.mNumAdapterConnections = paLuaEngine->getField<TForteUInt8, &CLuaEngine::getInteger<TForteUInt8> >(paIndex, "numAdpCons");
  size_t numAdpCons = paFbnSpec.mNumAdapterConnections;
  paFbnSpec.mAdapterConnections = paLuaEngine->getCustomArrayField<SCFB_FBConnectionData, luatype::getFBConnectionData>(paIndex, "adapterConnections", numAdpCons);
  //parameters
  paFbnSpec.mNumParams = paLuaEngine->getField<TForteUInt8, &CLuaEngine::getInteger<TForteUInt8> >(paIndex, "numParams");
  size_t numParams = paFbnSpec.mNumParams;
  paFbnSpec.mParams = paLuaEngine->getCustomArrayField<SCFB_FBParameter, luatype::getFBParameter>(paIndex, "parameters", numParams);
  //checks
  if(paFbnSpec.mFBInstances == nullptr) {
    return false;
  }
  return true;
}

void CLuaCFBTypeEntry::deleteFbnSpec(SCFB_FBNData& paFbnSpec) {
  delete[] paFbnSpec.mFBInstances;
  delete[] paFbnSpec.mEventConnections;
  delete[] paFbnSpec.mFannedOutEventConnections;
  delete[] paFbnSpec.mDataConnections;
  delete[] paFbnSpec.mFannedOutDataConnections;
  delete[] paFbnSpec.mParams;
}
