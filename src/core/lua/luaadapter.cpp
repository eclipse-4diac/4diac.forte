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

#include "luaadapter.h"
#include "resource.h"
#include "criticalregion.h"

CLuaAdapter::CLuaAdapter(CStringDictionary::TStringId paInstanceNameId, const CLuaAdapterTypeEntry* paTypeEntry, bool paIsPlug, forte::core::CFBContainer &paContainer) :
    CAdapter(paContainer, paTypeEntry->getSocketInterfaceSpec(), paInstanceNameId, paTypeEntry->getPlugInterfaceSpec(), paIsPlug),
        mTypeEntry(paTypeEntry) {
}

CLuaAdapter::~CLuaAdapter() = default;

void CLuaAdapter::readInputData(TEventID paEIID) {
  if(nullptr != getFBInterfaceSpec().mEIWithIndexes && scmNoDataAssociated != getFBInterfaceSpec().mEIWithIndexes[paEIID]) {
    const TDataIOID *eiWithStart = &(getFBInterfaceSpec().mEIWith[getFBInterfaceSpec().mEIWithIndexes[paEIID]]);
    for(size_t i = 0; eiWithStart[i] != scmWithListDelimiter; ++i) {
      TDataIOID diNum = eiWithStart[i];
      readData(diNum, *getDI(diNum), *getDIConUnchecked(diNum));
    }
  }
}

void CLuaAdapter::writeOutputData(TEventID paEO) {
  if (nullptr != getFBInterfaceSpec().mEOWithIndexes && -1 != getFBInterfaceSpec().mEOWithIndexes[paEO]) {
    const TDataIOID *eiWithStart = &(getFBInterfaceSpec().mEOWith[getFBInterfaceSpec().mEOWithIndexes[paEO]]);
    for (size_t i = 0; eiWithStart[i] != scmWithListDelimiter; ++i) {
      TDataIOID doNum = eiWithStart[i];
      writeData(doNum, *getDO(doNum), *getDOConUnchecked(doNum));
    }
  }
}
