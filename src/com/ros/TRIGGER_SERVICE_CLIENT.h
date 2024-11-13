/*******************************************************************************
 * Copyright (c) 2016 - 2017 fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Ben Schneider
 *      - initial implementation and documentation
 *******************************************************************************/

#ifndef _TRIGGER_SERVICE_CLIENT_H_
#define _TRIGGER_SERVICE_CLIENT_H_

#include <esfb.h>
#include <forte_bool.h>
#include <forte_string.h>
#include <ros/ros.h>
#include <std_srvs/Trigger.h>

class CServiceCallManager;

// cppcheck-suppress noConstructor
class FORTE_TRIGGER_SERVICE_CLIENT : public CEventSourceFB{
  DECLARE_FIRMWARE_FB(FORTE_TRIGGER_SERVICE_CLIENT)

  private:

    bool m_Initiated;
    ros::NodeHandle* m_nh;
    std::string m_RosNamespace;
    std::string m_RosMsgName;

    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    CIEC_BOOL &QI(){
      return *static_cast<CIEC_BOOL*>(getDI(0));
    }
    ;

    CIEC_STRING &NAMESPACE(){
      return *static_cast<CIEC_STRING*>(getDI(1));
    }
    ;

    CIEC_STRING &SRVNAME(){
      return *static_cast<CIEC_STRING*>(getDI(2));
    }
    ;

    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    CIEC_BOOL &QO(){
      return *static_cast<CIEC_BOOL*>(getDO(0));
    }
    ;

    CIEC_STRING &STATUS(){
      return *static_cast<CIEC_STRING*>(getDO(1));
    }
    ;

    CIEC_BOOL &SUCCESS(){
      return *static_cast<CIEC_BOOL*>(getDO(2));
    }
    ;

    CIEC_STRING &MESSAGE(){
      return *static_cast<CIEC_STRING*>(getDO(3));
    }
    ;

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
    ros::ServiceClient m_triggerClient;
    std_srvs::Trigger m_srv;

    void callService();
    void waitForServer();

    // cppcheck-suppress noConstructor
    EVENT_SOURCE_FUNCTION_BLOCK_CTOR(FORTE_TRIGGER_SERVICE_CLIENT), m_Initiated(false) , m_RosNamespace(""), m_RosMsgName(""){
    };

    ~FORTE_TRIGGER_SERVICE_CLIENT() override = default;

  };

#endif //close the ifdef sequence from the beginning of the file
