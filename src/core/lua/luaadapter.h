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

#ifndef SRC_CORE_LUAADAPTER_H_
#define SRC_CORE_LUAADAPTER_H_

#include "adapter.h"
#include "luaadaptertypeentry.h"

class CLuaAdapter : public CAdapter {
  public:
    CLuaAdapter(CStringDictionary::TStringId paInstanceNameId, const CLuaAdapterTypeEntry* paTypeEntry, bool paIsPlug, forte::core::CFBContainer &paContainer);
    ~CLuaAdapter() override;

    CStringDictionary::TStringId getFBTypeId() const override {
      return mTypeEntry->getTypeNameId();
    }

  private:
    virtual void readInputData(TEventID paEIID);
    virtual void writeOutputData(TEventID paEO);

    const CLuaAdapterTypeEntry* mTypeEntry;
};

#endif /* SRC_CORE_LUAADAPTER_H_ */
