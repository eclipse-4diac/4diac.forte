/*******************************************************************************
 * Copyright (c) 2018, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral - initial implementation
 *******************************************************************************/

#ifndef _FIELDSPREFERREDPROVIDER_H_
#define _FIELDSPREFERREDPROVIDER_H_

#include <basicfb.h>
#include <forte_preferredprovider.h>
#include <forte_arrowheadcloud.h>
#include <forte_arrowheadsystem.h>

class FORTE_FieldsPreferredProvider: public CBasicFB{
  DECLARE_FIRMWARE_FB(FORTE_FieldsPreferredProvider)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  CIEC_ArrowheadSystem &providerSystem() {
    return *static_cast<CIEC_ArrowheadSystem*>(getDI(0));
  };

  CIEC_ArrowheadCloud &providerCloud() {
    return *static_cast<CIEC_ArrowheadCloud*>(getDI(1));
  };

  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  CIEC_PreferredProvider &preferredProvider() {
    return *static_cast<CIEC_PreferredProvider*>(getDO(0));
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


  void alg_REQ();
  static const TForteInt16 scmStateSTART = 0;
  static const TForteInt16 scmStateREQ = 1;

  void enterStateSTART(CEventChainExecutionThread *const paECET);
  void enterStateREQ(CEventChainExecutionThread *const paECET);

  virtual void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

public:
  FORTE_FieldsPreferredProvider(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) : 
       CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId,
              0){
  };

  ~FORTE_FieldsPreferredProvider() override = default;

};

#endif //close the ifdef sequence from the beginning of the file

