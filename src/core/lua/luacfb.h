/*******************************************************************************
 * Copyright (c) 2017, 2024 fortiss GmbH, Johannes Kepler University Linz
 *                          Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger - initial API and implementation and/or initial documentation
 *   Alois Zoitl   - upgraded to new FB memory layout
 *   Martin Jobst  - added dynamic internal FB creation from CCompositeFB
 *******************************************************************************/

#ifndef SRC_CORE_LUACFB_H_
#define SRC_CORE_LUACFB_H_

#include "genfb.h"
#include "cfb.h"
#include "luacfbtypeentry.h"

class CLuaCFB : public CGenFunctionBlock<CCompositeFB> {
  public:
    CLuaCFB(CStringDictionary::TStringId paInstanceNameId, const CLuaCFBTypeEntry* paTypeEntry, SCFB_FBNData &paFbnData, forte::core::CFBContainer &paContainer);
    ~CLuaCFB() override;

    CStringDictionary::TStringId getFBTypeId() const override {
      return mTypeEntry->getTypeNameId();
    }

    bool createInterfaceSpec(const char *, SFBInterfaceSpec &) override {
      return true;
    }

  protected:
    void readInternal2InterfaceOutputData(TEventID paEOID) override;

  private:
    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEO) override;

    bool createInternalFBs() override;

    const CLuaCFBTypeEntry* mTypeEntry;
};

#endif /* SRC_CORE_LUACFB_H_ */
