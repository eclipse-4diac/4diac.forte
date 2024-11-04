/*******************************************************************************
 * Copyright (c) 2018 TU Wien/ACIN
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Martin Melik-Merkumians - initial contribution
 *******************************************************************************/

#ifndef _ADS_SERVER_CONFIG_H_
#define _ADS_SERVER_CONFIG_H_

#include <funcbloc.h>
#include <forte_bool.h>
#include <forte_string.h>
#include <forte_uint.h>
#include <forte_wstring.h>

class FORTE_ADS_SERVER_CONFIG : public CFunctionBlock{
    DECLARE_FIRMWARE_FB (FORTE_ADS_SERVER_CONFIG)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    CIEC_BOOL &QI(){
      return *static_cast<CIEC_BOOL*>(getDI(0));
    };

    CIEC_STRING &FRIENDLY_NAME(){
      return *static_cast<CIEC_STRING*>(getDI(1));
    };

    CIEC_STRING &SERVER_ADS_ADDRESS(){
      return *static_cast<CIEC_STRING*>(getDI(2));
    };

    CIEC_UINT &ADS_PORT(){
      return *static_cast<CIEC_UINT*>(getDI(3));
    };

    CIEC_STRING &SERVER_IPV4_OR_HOSTNAME(){
      return *static_cast<CIEC_STRING*>(getDI(4));
    };

    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    CIEC_BOOL &QO(){
      return *static_cast<CIEC_BOOL*>(getDO(0));
    };

    CIEC_WSTRING &STATUS(){
      return *static_cast<CIEC_WSTRING*>(getDO(1));
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

  public:
    FUNCTION_BLOCK_CTOR (FORTE_ADS_SERVER_CONFIG) { };

    ~FORTE_ADS_SERVER_CONFIG() override = default;

};

#endif //close the ifdef sequence from the beginning of the file

