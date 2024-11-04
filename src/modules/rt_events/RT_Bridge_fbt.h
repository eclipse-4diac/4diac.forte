/*******************************************************************************
 * Copyright (c) 2023 Johannes Kepler University Linz
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - initial API and implementation and/or initial documentation
 *******************************************************************************/

#pragma once

#include "genfb.h"
#include "mixedStorage.h"
#include "forte_any_variant.h"
#include "criticalregion.h"


class FORTE_GEN_RT_Bridge final : public CGenFunctionBlock<CFunctionBlock>  {
    DECLARE_GENERIC_FIRMWARE_FB(FORTE_GEN_RT_Bridge)

  public:
    FORTE_GEN_RT_Bridge(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);
    ~FORTE_GEN_RT_Bridge() override = default;

  private:
    static const TEventID scmEventRDID = 0;
    static const TEventID scmEventWRID = 1;
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];

    static const TEventID scmEventRDOID = 0;
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

    bool createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec) override;

    forte::core::util::CMixedStorage mIfSpecStorage;
    CSyncObject mSyncObject;
};


