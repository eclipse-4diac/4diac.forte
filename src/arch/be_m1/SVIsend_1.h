/*******************************************************************************
 * Copyright (c) 2011 ACIN
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *  Alois Zoitl - initial API and implementation and/or initial documentation
 *******************************************************************************/
#ifndef _SVISEND_1_H_
#define _SVISEND_1_H_

#include "BE_SVIFB.h"
#include <forte_any.h>
#include <forte_string.h>
#include <forte_bool.h>

class FORTE_SVIsend_1: public BE_SVIFB{
  DECLARE_FIRMWARE_FB(FORTE_SVIsend_1)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  CIEC_BOOL &QI() {
    return *static_cast<CIEC_BOOL*>(getDI(0));
  };

  CIEC_STRING &ID() {
    return *static_cast<CIEC_STRING*>(getDI(1));
  };

  CIEC_ANY &SD_1() {
    return *static_cast<CIEC_ANY*>(getDI(2));
  };

  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  CIEC_BOOL &QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  };

  static const TEventID scmEventINITID = 0;
  static const TEventID scmEventREQID = 1;
  static const TForteInt16 scmEIWithIndexes[];
  static const TDataIOID scmEIWith[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];

  static const TEventID scmEventINITOID = 0;
  static const TEventID scmEventCNFID = 1;
  static const TForteInt16 scmEOWithIndexes[];
  static const TDataIOID scmEOWith[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;


  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

public:
  FORTE_SVIsend_1(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
       BE_SVIFB(paContainer, scmFBInterfaceSpec, paInstanceNameId){
  };

  ~FORTE_SVIsend_1() override = default;

};

#endif //close the ifdef sequence from the beginning of the file

