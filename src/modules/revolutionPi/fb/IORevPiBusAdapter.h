/*******************************************************************************
 * Copyright (c) 2017, 2024 fortiss GmbH, Monika Wenger, Johannes Kepler University Linz
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Johannes Messmer - initial API and implementation and/or initial documentation
 *   Monika Wenger, Alois Zoitl - migration to current runtime
 *******************************************************************************/

#pragma once

#include <io/configFB/io_adapter_multi.h>
#include "adapter.h"
#include "typelib.h"
#include "forte_bool.h"
#include "forte_uint.h"

class FORTE_IORevPiBusAdapter: public forte::core::io::IOConfigFBMultiAdapter {
  DECLARE_ADAPTER_TYPE(FORTE_IORevPiBusAdapter)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];

    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];

    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];

    static const SFBInterfaceSpec scmFBInterfaceSpecSocket;

    static const SFBInterfaceSpec scmFBInterfaceSpecPlug;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;

  public:
    ADAPTER_CTOR_FOR_IO_MULTI (FORTE_IORevPiBusAdapter) {
    };
    virtual ~FORTE_IORevPiBusAdapter(){};

    static const TEventID scmEventINITOID = 0;
    static const TEventID scmEventINITID = 0;

    static const TForteUInt8 scmSlaveConfigurationIO[];
    static const TForteUInt8 scmSlaveConfigurationIONum;

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

    TEventID evt_INITO() {
      return mParentAdapterListEventID + scmEventINITOID;
    }

    TEventID evt_INIT() {
      return mParentAdapterListEventID + scmEventINITID;
    }
};
