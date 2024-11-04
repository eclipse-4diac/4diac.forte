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

#ifndef SRC_CORE_LUACFBTYPEENTRY_H_
#define SRC_CORE_LUACFBTYPEENTRY_H_

#include "typelib.h"
#include "cfb.h"
#include <string>

class CResource;
class CLuaEngine;

class CLuaCFBTypeEntry: public CTypeLib::CFBTypeEntry {
private:
  const std::string cmLuaScriptAsString;
  SFBInterfaceSpec m_interfaceSpec;
  SCFB_FBNData mSpec;

  CLuaCFBTypeEntry(CStringDictionary::TStringId typeNameId, const std::string & paLuaScriptAsString,  SFBInterfaceSpec& interfaceSpec, SCFB_FBNData& fbnSpec);

  ~CLuaCFBTypeEntry() override;

  static bool initInterfaceSpec(SFBInterfaceSpec& interfaceSpec, CLuaEngine* luaEngine, int index);
  static void deleteInterfaceSpec(SFBInterfaceSpec& interfaceSpec);
  static bool initFbnSpec(SCFB_FBNData& fbnSpec, CLuaEngine* luaEngine, int index);
  static void deleteFbnSpec(SCFB_FBNData& fbnSpec);

public:
  static CLuaCFBTypeEntry* createLuaFBTypeEntry(CStringDictionary::TStringId typeNameId, const std::string& paLuaScriptAsString);

  CFunctionBlock* createFBInstance(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) override;

  const SFBInterfaceSpec& getInterfaceSpec() const {
    return m_interfaceSpec;
  }

  SCFB_FBNData& getFbnSpec(){
    return mSpec;
  }
};

#endif /* SRC_CORE_LUACFBTYPEENTRY_H_ */
