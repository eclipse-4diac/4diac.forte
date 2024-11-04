/*******************************************************************************
 * Copyright (c) 2015, 2024 fortiss GmbH, Johannes Kepler University Linz
 *                          Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Martin Jobst - initial API and implementation and/or initial documentation
 *   Alois Zoitl  - upgraded to new FB memory layout
 *   Martin Jobst - add dynamic internal variable setup from CBasicFB
 *******************************************************************************/

#include "luabfb.h"
#include "resource.h"
#include "luaengine.h"
#include "../adapter.h"
#include "criticalregion.h"

extern "C" {
#include <lualib.h>
}

// write variable to lua engine
int CLuaFB_index(lua_State *paLuaState) {
  CLuaBFB* luaFB = CLuaEngine::luaGetObject<CLuaBFB>(paLuaState, 1);
  TForteUInt32 id = static_cast<TForteUInt32>(luaL_checkinteger(paLuaState, 2));
  CIEC_ANY* var = luaFB->getVariable(id);
  CLuaEngine::luaPushAny(paLuaState, *var);
  return 1;
}

// get variables from lua engine
int CLuaFB_newindex(lua_State *paLuaState) {
  CLuaBFB* luaFB = CLuaEngine::luaGetObject<CLuaBFB>(paLuaState, 1);
  TForteUInt32 id = static_cast<TForteUInt32>(luaL_checkinteger(paLuaState, 2));
  CIEC_ANY* var = luaFB->getVariable(id);
  CLuaEngine::luaGetAny(paLuaState, *var, 3);
  return 0;
}

int CLuaFB_call(lua_State *paLuaState) {
  CLuaBFB* luaFB = CLuaEngine::luaGetObject<CLuaBFB>(paLuaState, 1);
  TForteUInt32 id = static_cast<TForteUInt32>(luaL_checkinteger(paLuaState, 2));
  if((id & CLuaBFB::scmLuaFBAdpFlag) != 0) {
    luaFB->sendAdapterEvent((id >> 16) & CLuaBFB::scmLuaAdpVarMax, id & CLuaBFB::scmLuaFBVarMax, luaFB->mInvokingExecEnv);
  } else {
    luaFB->sendOutputEvent(id, luaFB->mInvokingExecEnv);
  }
  return 0;
}

const char CLuaBFB::LUA_NAME[] = "FORTE_CLuaFB";
const luaL_Reg CLuaBFB::LUA_FUNCS[] = { { "__index", CLuaFB_index }, { "__newindex", CLuaFB_newindex }, { "__call", CLuaFB_call }, { nullptr, nullptr } };

CLuaBFB::CLuaBFB(CStringDictionary::TStringId paInstanceNameId, const CLuaBFBTypeEntry* paTypeEntry, forte::core::CFBContainer &paContainer) :
    CGenFunctionBlock<CBasicFB>(paContainer, paTypeEntry->getInterfaceSpec(), paInstanceNameId, paTypeEntry->getInternalVarsInformation()),
        mTypeEntry(paTypeEntry) {
  CLuaEngine *luaEngine = getResource()->getLuaEngine();
  luaEngine->registerType<CLuaBFB>();
  luaEngine->pushObject<CLuaBFB>(this);
  luaEngine->store(this);
}

bool CLuaBFB::initialize() {
  //before calling super we need to configure the interface of the FB
  createVarInternals();
  return CGenFunctionBlock<CBasicFB>::initialize();
}

CLuaBFB::~CLuaBFB() {
  if(mInternals) {
    for(TPortId i = 0; i < cmVarInternals->mNumIntVars; ++i) {
      if(CIEC_ANY* value = mInternals[i]; nullptr != value) {
        std::destroy_at(value);
      }
    }
  }
  operator delete(mInternalVarsData);
  mInternalVarsData = nullptr;
}

void CLuaBFB::createVarInternals() {
  if(cmVarInternals && cmVarInternals->mNumIntVars) {
    size_t internalVarsDataSize = calculateInternalVarsDataSize(*cmVarInternals);
    mInternalVarsData = internalVarsDataSize ? operator new(internalVarsDataSize) : nullptr;

    auto *internalVarsData = reinterpret_cast<TForteByte *>(mInternalVarsData);
    mInternals = reinterpret_cast<CIEC_ANY**>(internalVarsData);
    internalVarsData += cmVarInternals->mNumIntVars * sizeof(CIEC_ANY *);
    const CStringDictionary::TStringId *pnDataIds = cmVarInternals->mIntVarsDataTypeNames;
    for(TPortId i = 0; i < cmVarInternals->mNumIntVars; ++i) {
      mInternals[i] = createDataPoint(pnDataIds, internalVarsData);
    }
  }
}

void CLuaBFB::executeEvent(TEventID paEIID, CEventChainExecutionThread *paECET) {
  mInvokingExecEnv = paECET;
  CLuaEngine *luaEngine = getResource()->getLuaEngine();
  luaEngine->load(mTypeEntry);
  luaEngine->load(this);
  luaEngine->pushInteger(paEIID > 255 ? recalculateID(paEIID) : paEIID);
  if(!luaEngine->call(2, 0)) {
    DEVLOG_ERROR("Error calling function executeEvent for instance %s\n", getInstanceName());
  }
}

CIEC_ANY* CLuaBFB::getVariable(TForteUInt32 paId) {
  if(CLuaBFB::scmLuaFBState == paId) {
    return &mECCState;
  }
  if((paId & CLuaBFB::scmLuaFBInFlag) != 0) {
    return getVarInternal(paId & CLuaBFB::scmLuaFBVarMax);
  }
  if((paId & CLuaBFB::scmLuaFBAdpFlag) != 0) {
    if((paId & CLuaBFB::scmLuaFBDoFlag) != 0) {
      return mAdapters[(paId >> 16) & CLuaBFB::scmLuaAdpVarMax]->getDO(paId & CLuaBFB::scmLuaFBVarMax);
    }
    if((paId & CLuaBFB::scmLuaFBDiFlag) != 0) {
      return mAdapters[(paId >> 16) & CLuaBFB::scmLuaAdpVarMax]->getDI(paId & CLuaBFB::scmLuaFBVarMax);
    }
    return nullptr;
  }
  if((paId & CLuaBFB::scmLuaFBDiFlag) != 0) {
    return getDI(paId & CLuaBFB::scmLuaFBVarMax);
  }
  if((paId & CLuaBFB::scmLuaFBDoFlag) != 0) {
    return getDO(paId & CLuaBFB::scmLuaFBVarMax);
  }
  return nullptr;
}

void CLuaBFB::readInputData(TEventID paEIID) {
  if(nullptr != getFBInterfaceSpec().mEIWithIndexes && scmNoDataAssociated != getFBInterfaceSpec().mEIWithIndexes[paEIID]) {
    const TDataIOID *eiWithStart = &(getFBInterfaceSpec().mEIWith[getFBInterfaceSpec().mEIWithIndexes[paEIID]]);
    for(size_t i = 0; eiWithStart[i] != scmWithListDelimiter; ++i) {
      TDataIOID diNum = eiWithStart[i];
      readData(diNum, *getDI(diNum), *getDIConUnchecked(diNum));
    }
  }
}

void CLuaBFB::writeOutputData(TEventID paEO) {
  if (nullptr != getFBInterfaceSpec().mEOWithIndexes && -1 != getFBInterfaceSpec().mEOWithIndexes[paEO]) {
    const TDataIOID *eiWithStart = &(getFBInterfaceSpec().mEOWith[getFBInterfaceSpec().mEOWithIndexes[paEO]]);
    for (size_t i = 0; eiWithStart[i] != scmWithListDelimiter; ++i) {
      TDataIOID doNum = eiWithStart[i];
      writeData(doNum, *getDO(doNum), *getDOConUnchecked(doNum));
    }
  }
}

size_t CLuaBFB::calculateInternalVarsDataSize(const SInternalVarsInformation &paVarInternals) {
  size_t result = 0;
  const CStringDictionary::TStringId *pnDataIds;

  result += paVarInternals.mNumIntVars * sizeof(CIEC_ANY *);
  pnDataIds = paVarInternals.mIntVarsDataTypeNames;
  for (TPortId i = 0; i < paVarInternals.mNumIntVars; ++i) {
    result += getDataPointSize(pnDataIds);
  }

  return result;
}

