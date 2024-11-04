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
#ifndef _GET_CHAN_INFO_H_
#define _GET_CHAN_INFO_H_

#include <mtypes.h>
#include <funcbloc.h>
#include <forte_int.h>
#include <forte_string.h>

class FORTE_GET_CHAN_INFO: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_GET_CHAN_INFO)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  CIEC_STRING &SYMB_NAME() {
    return *static_cast<CIEC_STRING*>(getDI(0));
  };

  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  CIEC_INT &RET_CODE() {
    return *static_cast<CIEC_INT*>(getDO(0));
  };

  CIEC_INT &MOD_NB() {
    return *static_cast<CIEC_INT*>(getDO(1));
  };

  CIEC_INT &CHAN_NB() {
    return *static_cast<CIEC_INT*>(getDO(2));
  };

  static const TEventID scmEventINITID = 0;
  static const TForteInt16 scmEIWithIndexes[];
  static const TDataIOID scmEIWith[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];

  static const TEventID scmEventINITOID = 0;
  static const TForteInt16 scmEOWithIndexes[];
  static const TDataIOID scmEOWith[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;


  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

  bool init();
  SINT32 getChannelInfo();

public:
  FUNCTION_BLOCK_CTOR(FORTE_GET_CHAN_INFO){
  };

  ~FORTE_GET_CHAN_INFO() override = default;
};

#endif //close the ifdef sequence from the beginning of the file

