/*******************************************************************************
 * Copyright (c) 2016 - 2018 Johannes Messmer (admin@jomess.com), fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Johannes Messmer - initial API and implementation and/or initial documentation
 *   Jose Cabral - Cleaning of namespaces
 *******************************************************************************/

#pragma once

#include <io/configFB/io_adapter_multi.h>
#include "adapter.h"
#include "typelib.h"
#include "forte_bool.h"
#include "forte_uint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_EBBusAdapter final : public forte::core::io::IOConfigFBMultiAdapter {
  DECLARE_ADAPTER_TYPE(FORTE_EBBusAdapter)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  public:
    static const TEventID scmEventINITOID = 0;

  private:
  static const TDataIOID scmEIWith[];
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];
  public:
    static const TEventID scmEventINITID = 0;

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
  CIEC_BOOL &var_QO() {
    return *static_cast<CIEC_BOOL*>((isSocket()) ? getDI(0) : getDO(0));
  }

  CIEC_BOOL &var_QI() {
    return *static_cast<CIEC_BOOL*>((isSocket()) ? getDO(0) : getDI(0));
  }

  CIEC_UINT &var_MasterId() {
    return *static_cast<CIEC_UINT*>((isSocket()) ? getDO(1) : getDI(1));
  }

  CIEC_UINT &var_Index() {
    return *static_cast<CIEC_UINT*>((isSocket()) ? getDO(2) : getDI(2));
  }

  CIEC_UINT &var_UpdateInterval() {
    return *static_cast<CIEC_UINT*>((isSocket()) ? getDO(3) : getDI(3));
  }

  TEventID evt_INITO() {
    return mParentAdapterListEventID + scmEventINITOID;
  }

  TEventID evt_INIT() {
    return mParentAdapterListEventID + scmEventINITID;
  }

  ADAPTER_CTOR_FOR_IO_MULTI(FORTE_EBBusAdapter){
  };

  virtual ~FORTE_EBBusAdapter() = default;
  
  private:
    static const TForteUInt8 scmSlaveConfigurationIO[];
    static const TForteUInt8 scmSlaveConfigurationIONum;
};
