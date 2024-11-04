/*******************************************************************************
 * Copyright (c) 2013, 2024 ACIN, Martin Erich Jobst,
 *                          Primetals Technologies Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - refactored from F_MOVE
 *******************************************************************************/

#pragma once

#include <genfb.h>
#include "forte_any_variant.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class GEN_FORTE_F_MOVE : public CGenFunctionBlock<CFunctionBlock>  {
    DECLARE_GENERIC_FIRMWARE_FB(GEN_FORTE_F_MOVE)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  
  static const CStringDictionary::TStringId scmDataOutputNames[];
  
  static const TEventID scmEventREQID = 0;
  
  static const TDataIOID scmEIWith[];
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];
  
  static const TEventID scmEventCNFID = 0;
  
  static const TDataIOID scmEOWith[]; 
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];
  

  bool createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec) override;

  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;

  static CStringDictionary::TStringId getDataTypeNameId(const char *paConfigString);

public:
  GEN_FORTE_F_MOVE(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);
  ~GEN_FORTE_F_MOVE() override;

  CIEC_ANY& var_IN() {
    return *static_cast<CIEC_ANY*>(getDI(0));
  }

  CIEC_ANY& var_OUT() {
    return *static_cast<CIEC_ANY*>(getDO(0));
  }

};



