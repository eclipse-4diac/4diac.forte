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

#ifndef _FIELDSTOEVENTFILTER_H_
#define _FIELDSTOEVENTFILTER_H_

#include <basicfb.h>
#include <forte_date_and_time.h>
#include <forte_bool.h>
#include <forte_arrowheadsystem.h>
#include <forte_eventfilter.h>
#include <forte_wstring.h>
#include <forte_array.h>

class FORTE_FieldsToEventFilter: public CBasicFB{
  DECLARE_FIRMWARE_FB(FORTE_FieldsToEventFilter)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  CIEC_WSTRING &eventType() {
    return *static_cast<CIEC_WSTRING*>(getDI(0));
  };

  CIEC_ArrowheadSystem &consumer() {
    return *static_cast<CIEC_ArrowheadSystem*>(getDI(1));
  };

  CIEC_ArrowheadSystem *sources() {
    return (CIEC_ArrowheadSystem*)(*static_cast<CIEC_ARRAY<> *>(getDI(2)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY<> &sources_Array() {
    return *static_cast<CIEC_ARRAY<>*>(getDI(2));
  };

  CIEC_DATE_AND_TIME &startDate() {
    return *static_cast<CIEC_DATE_AND_TIME*>(getDI(3));
  };

  CIEC_DATE_AND_TIME &endDate() {
    return *static_cast<CIEC_DATE_AND_TIME*>(getDI(4));
  };

  CIEC_WSTRING *filterMetadata() {
    return (CIEC_WSTRING*)(*static_cast<CIEC_ARRAY<> *>(getDI(5)))[0]; //the first element marks the start of the array
  };

  CIEC_ARRAY<> &filterMetadata_Array() {
    return *static_cast<CIEC_ARRAY<>*>(getDI(5));
  };

  CIEC_WSTRING &notifyUri() {
    return *static_cast<CIEC_WSTRING*>(getDI(6));
  };

  CIEC_BOOL &matchMetadata() {
    return *static_cast<CIEC_BOOL*>(getDI(7));
  };

  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  CIEC_EventFilter &eventFilter() {
    return *static_cast<CIEC_EventFilter*>(getDO(0));
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
  FORTE_FieldsToEventFilter(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) : 
       CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId,
              0){
  };

  ~FORTE_FieldsToEventFilter() override = default;

};

#endif //close the ifdef sequence from the beginning of the file

