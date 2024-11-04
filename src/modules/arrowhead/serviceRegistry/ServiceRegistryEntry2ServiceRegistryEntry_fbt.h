/*******************************************************************************
 * Copyright (c) 2019, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral - initial implementation
 *******************************************************************************/

#ifndef _SERVICEREGISTRYENTRY2SERVICEREGISTRYENTRY_H_
#define _SERVICEREGISTRYENTRY2SERVICEREGISTRYENTRY_H_

#include <funcbloc.h>
#include <forte_serviceregistryentry.h>

class FORTE_ServiceRegistryEntry2ServiceRegistryEntry: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_ServiceRegistryEntry2ServiceRegistryEntry)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  CIEC_ServiceRegistryEntry &st_IN() {
    return *static_cast<CIEC_ServiceRegistryEntry*>(getDI(0));
  };

  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  CIEC_ServiceRegistryEntry &st_OUT() {
    return *static_cast<CIEC_ServiceRegistryEntry*>(getDO(0));
  };

  static const TEventID scmEventREQID = 0;
  static const TForteInt16 scmEIWithIndexes[];
  static const TDataIOID scmEIWith[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];

  static const TEventID scmEventCNFID = 0;
  static const TForteInt16 scmEOWithIndexes[];
  static const TDataIOID scmEOWith[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;


  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

public:
  FUNCTION_BLOCK_CTOR(FORTE_ServiceRegistryEntry2ServiceRegistryEntry){
  };

  ~FORTE_ServiceRegistryEntry2ServiceRegistryEntry() override = default;

};

#endif //close the ifdef sequence from the beginning of the file

