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

#ifndef _EXECUTE_ACTION_CLIENT_H_
#define _EXECUTE_ACTION_CLIENT_H_

#include <esfb.h>
#include <forte_bool.h>
#include <forte_string.h>
#include <forte_dint.h>

#include <actionlib/client/simple_action_client.h>
#include <reapp_msgs/ExecuteAction.h>
#include <reapp_msgs/ExecuteResult.h>

typedef boost::shared_ptr<reapp_msgs::ExecuteResult const> ExecuteResultConstPtr;
typedef boost::shared_ptr<reapp_msgs::ExecuteFeedback const> ExecuteFeedbackConstPtr;

typedef actionlib::SimpleActionClient<reapp_msgs::ExecuteAction> actionClient;

// cppcheck-suppress noConstructor
class FORTE_EXECUTE_ACTION_CLIENT : public CEventSourceFB{
  DECLARE_FIRMWARE_FB(FORTE_EXECUTE_ACTION_CLIENT)

  private:

    bool m_Initiated;
    bool m_GoalActive;
    actionClient* m_ActionClient;
    ExecuteResultConstPtr m_ExecuteResultConstPtr;
    ExecuteFeedbackConstPtr m_ExecuteFeedbackConstPtr;
    bool mResultReady;

    ros::NodeHandle* nh;
    std::string m_RosNamespace;
    std::string m_RosMsgName;

    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    CIEC_BOOL &QI(){
      return *static_cast<CIEC_BOOL*>(getDI(0));
    }
    ;

    CIEC_STRING &ACTIONNAMESPACE(){
      return *static_cast<CIEC_STRING*>(getDI(1));
    }
    ;

    CIEC_STRING &ACTIONMSGNAME(){
      return *static_cast<CIEC_STRING*>(getDI(2));
    }
    ;

    CIEC_STRING &COMMAND(){
      return *static_cast<CIEC_STRING*>(getDI(3));
    }
    ;

    CIEC_DINT &ID1(){
      return *static_cast<CIEC_DINT*>(getDI(4));
    }
    ;

    CIEC_DINT &ID2(){
      return *static_cast<CIEC_DINT*>(getDI(5));
    }
    ;

    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    CIEC_BOOL &QO(){
      return *static_cast<CIEC_BOOL*>(getDO(0));
    }
    ;

    CIEC_STRING &FBSTATUS(){
      return *static_cast<CIEC_STRING*>(getDO(1));
    }
    ;

    CIEC_STRING &ACTIONSTATUS(){
      return *static_cast<CIEC_STRING*>(getDO(2));
    }
    ;

    CIEC_STRING &RESULT(){
      return *static_cast<CIEC_STRING*>(getDO(3));
    }
    ;

    CIEC_DINT &ID(){
      return *static_cast<CIEC_DINT*>(getDO(4));
    }
    ;

    CIEC_STRING &STATE(){
      return *static_cast<CIEC_STRING*>(getDO(5));
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

    void doneCallback(const actionlib::SimpleClientGoalState& state, const ExecuteResultConstPtr& result);
    void activeCallback();
    void feedbackCallback(const ExecuteFeedbackConstPtr &feedback);

    std::string getCurrentActionState();

    void connectToActionServer();

  public:
    EVENT_SOURCE_FUNCTION_BLOCK_CTOR(FORTE_EXECUTE_ACTION_CLIENT), m_Initiated(false), m_GoalActive(false), m_ActionClient(0), mResultReady(false), nh(0), m_RosNamespace(""), m_RosMsgName(""){
    };

    ~FORTE_EXECUTE_ACTION_CLIENT() override = default;

  };

#endif //close the ifdef sequence from the beginning of the file
