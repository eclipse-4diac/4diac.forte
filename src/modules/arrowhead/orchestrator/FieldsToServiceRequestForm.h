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

#ifndef _FIELDSTOSERVICEREQUESTFORM_H_
#define _FIELDSTOSERVICEREQUESTFORM_H_

#include <basicfb.h>
#include <forte_preferredprovider.h>
#include <forte_arrowheadservice.h>
#include <forte_arrowheadcloud.h>
#include <forte_arrowheadsystem.h>
#include <forte_servicerequestform.h>
#include <forte_wstring.h>
#include <forte_array.h>

class FORTE_FieldsToServiceRequestForm: public CBasicFB{
  DECLARE_FIRMWARE_FB(FORTE_FieldsToServiceRequestForm)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  CIEC_ArrowheadSystem &requesterSystem() {
    return *static_cast<CIEC_ArrowheadSystem*>(getDI(0));
  };

  CIEC_ArrowheadCloud &requesterCloud() {
    return *static_cast<CIEC_ArrowheadCloud*>(getDI(1));
  };

  CIEC_ArrowheadService &requestedService() {
    return *static_cast<CIEC_ArrowheadService*>(getDI(2));
  };

  CIEC_WSTRING *orchestrationFlags() {
    return (CIEC_WSTRING*)(*static_cast<CIEC_ARRAY<> *>(getDI(3)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY<> &orchestrationFlags_Array() {
    return *static_cast<CIEC_ARRAY<>*>(getDI(3));
  };

  CIEC_PreferredProvider *preferredProviders() {
    return (CIEC_PreferredProvider*)(*static_cast<CIEC_ARRAY<> *>(getDI(4)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY<> &preferredProviders_Array() {
    return *static_cast<CIEC_ARRAY<>*>(getDI(4));
  };

  CIEC_WSTRING *requestedQoS() {
    return (CIEC_WSTRING*)(*static_cast<CIEC_ARRAY<> *>(getDI(5)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY<> &requestedQoS_Array() {
    return *static_cast<CIEC_ARRAY<>*>(getDI(5));
  };

  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  CIEC_ServiceRequestForm &serviceRequestForm() {
    return *static_cast<CIEC_ServiceRequestForm*>(getDO(0));
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
  FORTE_FieldsToServiceRequestForm(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) : 
       CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId,
              0){
  };

  ~FORTE_FieldsToServiceRequestForm() override = default;

};

#endif //close the ifdef sequence from the beginning of the file

