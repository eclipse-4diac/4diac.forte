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

#ifndef SRC_CORE_LUAADAPTERTYPEENTRY_H_
#define SRC_CORE_LUAADAPTERTYPEENTRY_H_

#include "typelib.h"
#include "../funcbloc.h"
#include <string>

class CResource;
class CAdapter;
class CLuaEngine;

class CLuaAdapterTypeEntry: public CTypeLib::CAdapterTypeEntry {
private:

  const std::string cmLuaScriptAsString;
  SFBInterfaceSpec mSocketInterfaceSpec;
  SFBInterfaceSpec mPlugInterfaceSpec;

  CLuaAdapterTypeEntry(CStringDictionary::TStringId typeNameId, const std::string& paLuaScriptAsString,  SFBInterfaceSpec& interfaceSpec);

  ~CLuaAdapterTypeEntry() override;

  static bool initInterfaceSpec(SFBInterfaceSpec& interfaceSpec, CLuaEngine* luaEngine, int index);
  bool initPlugInterfaceSpec(SFBInterfaceSpec& interfaceSpec);
  static void deleteInterfaceSpec(SFBInterfaceSpec& interfaceSpec);

public:
  static CLuaAdapterTypeEntry* createLuaAdapterTypeEntry(CStringDictionary::TStringId typeNameId, const std::string& paLuaScriptAsString);

  CAdapter* createAdapterInstance(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer, bool paIsPlug) override;

  const SFBInterfaceSpec & getSocketInterfaceSpec() const {
    return mSocketInterfaceSpec;
  }

  const SFBInterfaceSpec & getPlugInterfaceSpec() const {
      return mPlugInterfaceSpec;
  }
};

#endif /* SRC_CORE_LUAADAPTERTYPEENTRY_H_ */
