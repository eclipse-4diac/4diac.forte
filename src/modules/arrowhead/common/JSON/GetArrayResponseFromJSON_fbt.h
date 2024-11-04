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

#ifndef _GETARRAYRESPONSEFROMJSON_H_
#define _GETARRAYRESPONSEFROMJSON_H_

#include <funcbloc.h>
#include <forte_string.h>
#include <forte_any.h>

class FORTE_GetArrayResponseFromJSON: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_GetArrayResponseFromJSON)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  CIEC_STRING &response() {
    return *static_cast<CIEC_STRING*>(getDI(0));
  };

  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  CIEC_ANY &output() {
    return *static_cast<CIEC_ANY*>(getDO(0));
  };

  CIEC_ARRAY<> &output_Array() {
    return *static_cast<CIEC_ARRAY<>*>(getDO(0));
  }

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

  bool isResponseEmpty(char* paText);


public:
  FUNCTION_BLOCK_CTOR(FORTE_GetArrayResponseFromJSON){
  };

  ~FORTE_GetArrayResponseFromJSON() override = default;

};

#endif //close the ifdef sequence from the beginning of the file

