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

#ifndef _FIELDSTOARROWHEADEVENT_H_
#define _FIELDSTOARROWHEADEVENT_H_

#include <basicfb.h>
#include <forte_date_and_time.h>
#include <forte_arrowheadevent.h>
#include <forte_wstring.h>
#include <forte_array.h>

class FORTE_FieldsToArrowheadEvent: public CBasicFB{
  DECLARE_FIRMWARE_FB(FORTE_FieldsToArrowheadEvent)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  CIEC_WSTRING &type() {
    return *static_cast<CIEC_WSTRING*>(getDI(0));
  };

  CIEC_WSTRING &payload() {
    return *static_cast<CIEC_WSTRING*>(getDI(1));
  };

  CIEC_DATE_AND_TIME &timestamp() {
    return *static_cast<CIEC_DATE_AND_TIME*>(getDI(2));
  };

  CIEC_WSTRING *eventMetadata() {
    return (CIEC_WSTRING*)(*static_cast<CIEC_ARRAY<> *>(getDI(3)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY<> &eventMetadata_Array() {
    return *static_cast<CIEC_ARRAY<>*>(getDI(3));
  };

  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  CIEC_ArrowheadEvent &arrowheadEvent() {
    return *static_cast<CIEC_ArrowheadEvent*>(getDO(0));
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
  FORTE_FieldsToArrowheadEvent(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) : 
       CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId,
              0){
  };

  ~FORTE_FieldsToArrowheadEvent() override = default;

};

#endif //close the ifdef sequence from the beginning of the file

