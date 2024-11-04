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

#ifndef _FIELDSTOARROWHEADSERVICE_H_
#define _FIELDSTOARROWHEADSERVICE_H_

#include <basicfb.h>
#include <forte_arrowheadservice.h>
#include <forte_wstring.h>
#include <forte_array.h>

class FORTE_FieldsToArrowheadService: public CBasicFB{
  DECLARE_FIRMWARE_FB(FORTE_FieldsToArrowheadService)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  CIEC_WSTRING &serviceDefinition() {
    return *static_cast<CIEC_WSTRING*>(getDI(0));
  };

  CIEC_WSTRING *interfaces() {
    return (CIEC_WSTRING*)(*static_cast<CIEC_ARRAY<> *>(getDI(1)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY<> &interfaces_Array() {
    return *static_cast<CIEC_ARRAY<>*>(getDI(1));
  };

  CIEC_WSTRING *serviceMetadata() {
    return (CIEC_WSTRING*)(*static_cast<CIEC_ARRAY<> *>(getDI(2)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY<> &serviceMetadata_Array() {
    return *static_cast<CIEC_ARRAY<>*>(getDI(2));
  };

  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  CIEC_ArrowheadService &arrowheadService() {
    return *static_cast<CIEC_ArrowheadService*>(getDO(0));
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
  FORTE_FieldsToArrowheadService(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) : 
       CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId,
              0){
  };

  ~FORTE_FieldsToArrowheadService() override = default;

};

#endif //close the ifdef sequence from the beginning of the file

