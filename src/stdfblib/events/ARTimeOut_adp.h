/*******************************************************************************
 * Copyright (c) 2014 fortiss GmbH
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

#include "adapter.h"
#include "typelib.h"
#include "forte_time.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_ARTimeOut final : public CAdapter {
  DECLARE_ADAPTER_TYPE(FORTE_ARTimeOut)

private:
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  public:
    static const TEventID scmEventTimeOutID = 0;
  private:
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];
  public:
    static const TEventID scmEventSTARTID = 0;
    static const TEventID scmEventSTOPID = 1;
  private:
  static const TDataIOID scmEOWith[];
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpecSocket;

  static const SFBInterfaceSpec scmFBInterfaceSpecPlug;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
public:
  CIEC_TIME &var_DT() {
    return *static_cast<CIEC_TIME*>((isSocket()) ? getDO(0) : getDI(0));
  }

  TEventID evt_TimeOut() {
    return mParentAdapterListEventID + scmEventTimeOutID;
  }

  TEventID evt_START() {
    return mParentAdapterListEventID + scmEventSTARTID;
  }

  TEventID evt_STOP() {
    return mParentAdapterListEventID + scmEventSTOPID;
  }

public:
  FORTE_ARTimeOut(CStringDictionary::TStringId paAdapterInstanceName, forte::core::CFBContainer &paContainer, bool paIsPlug) :
      CAdapter(paContainer, scmFBInterfaceSpecSocket, paAdapterInstanceName, scmFBInterfaceSpecPlug, paIsPlug) {
   };

  virtual ~FORTE_ARTimeOut() = default;
};


