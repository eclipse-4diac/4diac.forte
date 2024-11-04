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

#ifndef SRC_CORE_LUAFBTYPEENTRY_H_
#define SRC_CORE_LUAFBTYPEENTRY_H_

#include "typelib.h"
#include "basicfb.h"

class CLuaEngine;

class CLuaBFBTypeEntry: public CTypeLib::CFBTypeEntry {
private:

  const std::string cmLuaScriptAsString;
  SFBInterfaceSpec m_interfaceSpec;
  SInternalVarsInformation m_internalVarsInformation;

  CLuaBFBTypeEntry(CStringDictionary::TStringId typeNameId, const std::string& paLuaScriptAsString, SFBInterfaceSpec& interfaceSpec,
      SInternalVarsInformation& internalVarsInformation);

  ~CLuaBFBTypeEntry() override;

  static bool initInterfaceSpec(SFBInterfaceSpec& interfaceSpec, CLuaEngine* luaEngine, int index);
  static void deleteInterfaceSpec(SFBInterfaceSpec& interfaceSpec);
  static bool initInternalVarsInformation(SInternalVarsInformation& internalVarsInformation, CLuaEngine* luaEngine, int index);
  static void deleteInternalVarsInformation(SInternalVarsInformation& internalVarsInformation);
public:
  static CLuaBFBTypeEntry* createLuaFBTypeEntry(CStringDictionary::TStringId typeNameId, const std::string& paLuaScriptAsString);

  CFunctionBlock* createFBInstance(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) override;

  const SFBInterfaceSpec& getInterfaceSpec() const {
    return m_interfaceSpec;
  }

  const SInternalVarsInformation* getInternalVarsInformation() const {
    return &m_internalVarsInformation;
  }
};

#endif /* SRC_CORE_LUABFBTYPEENTRY_H_ */
