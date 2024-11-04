/*******************************************************************************
 * Copyright (c) 2005 - 2014 ACIN, Profactor GmbH, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Rene Smodic, Gerhard Ebenhofer, Martin Melik Merkumians,
 *   Matthias Plasch
 *     - initial API and implementation and/or initial documentation
 *******************************************************************************/

#pragma once

#include "../core/esfb.h"
#include "../core/resource.h"
#include "forte_sem.h"

class FORTE_E_RESTART final : public CEventSourceFB {
  DECLARE_FIRMWARE_FB(FORTE_E_RESTART)

  private:
    static const TEventID scmEventCOLDID = 0;
    static const TEventID scmEventWARMID = 1;
    static const TEventID scmEventSTOPID = 2;
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    // semaphore to ensure proper handling of STOP execution state change
    forte::arch::CSemaphore mSuspendSemaphore;

    TEventID mEventToSend;

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;

public:
    FORTE_E_RESTART(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CEventConnection conn_COLD;
    CEventConnection conn_WARM;
    CEventConnection conn_STOP;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    EMGMResponse changeExecutionState(EMGMCommandType paCommand) override;
};

