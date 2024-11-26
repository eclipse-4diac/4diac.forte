/*******************************************************************************
 * Copyright (c) 2024 Primetals Technologies Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Markus Meingast
 *    - initial API and implementation and/or initial documentation
 *******************************************************************************/
#pragma once

#include "EMB_RES.h"

class Config_EMB_RES : public CResource {
  DECLARE_FIRMWARE_FB(Config_EMB_RES);

  public:
    Config_EMB_RES(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paDevice);
    ~Config_EMB_RES() override;

    bool initialize() override;

    CIEC_ANY *getDI(size_t) override;
    CDataConnection **getDIConUnchecked(TPortId) override;

  private:
    forte::core::CInternalFB<FORTE_E_RESTART> fb_START;

    CIEC_WSTRING var_OPCUA_Namespace;

    CDataConnection *conn_opcua_namespace;

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    static const CStringDictionary::TStringId scmVarInputNameIds[];
    static const CStringDictionary::TStringId scmDIDataTypeIds[];
};
