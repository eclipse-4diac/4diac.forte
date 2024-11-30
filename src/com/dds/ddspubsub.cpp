/*******************************************************************************
 * Copyright (c) 2024 OFFIS e.V.
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Malte Grave - initial implementation
 ********************************************************************************/

#include "ddspubsub.h"
#include "ddshandler.h"

#include "devlog.h"
#include "types/action_msgs/msg/GoalInfo/GoalInfoPubSub.h"
#include "types/action_msgs/msg/GoalStatusArray/GoalStatusArrayPubSub.h"
#include "types/action_msgs/srv/CancelGoal/CancelGoalRequestPubSub.h"
#include "types/action_msgs/srv/CancelGoal/CancelGoalResponsePubSub.h"

#include "types/example_message/msg/StringDebug/StringDebugPubSub.h"

#include "types/turtlesim/action/RotateAbsolute/RotateAbsoluteFeedbackMessagePubSub.h"
#include "types/turtlesim/action/RotateAbsolute/RotateAbsoluteFeedbackPubSub.h"
#include "types/turtlesim/action/RotateAbsolute/RotateAbsoluteGetResultRequestPubSub.h"
#include "types/turtlesim/action/RotateAbsolute/RotateAbsoluteGetResultResponsePubSub.h"
#include "types/turtlesim/action/RotateAbsolute/RotateAbsoluteGoalPubSub.h"
#include "types/turtlesim/action/RotateAbsolute/RotateAbsoluteResultPubSub.h"
#include "types/turtlesim/action/RotateAbsolute/RotateAbsoluteSendGoalRequestPubSub.h"
#include "types/turtlesim/action/RotateAbsolute/RotateAbsoluteSendGoalResponsePubSub.h"
#include "types/turtlesim/srv/Spawn/SpawnRequestPubSub.h"
#include "types/turtlesim/srv/Spawn/SpawnResponsePubSub.h"

#include "types/example_interfaces/srv/AddTwoInts/AddTwoIntsRequestPubSub.h"
#include "types/example_interfaces/srv/AddTwoInts/AddTwoIntsResponsePubSub.h"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/qos/DomainParticipantQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>

#include "basecommfb.h"

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastrtps::types;
using namespace forte::com_infra;

CDDSPubSub::~CDDSPubSub() {
  if (this->m_pWriter != nullptr)
    this->m_pPublisher->delete_datawriter(this->m_pWriter);
  if (this->m_pPublisher != nullptr)
    this->m_pParticipant->delete_publisher(this->m_pPublisher);

  if (this->m_pReader != nullptr)
    this->m_pSubscriber->delete_datareader(this->m_pReader);
  if (this->m_pSubscriber != nullptr)
    this->m_pParticipant->delete_subscriber(this->m_pSubscriber);

  if (this->m_pTopic != nullptr)
    this->m_pParticipant->delete_topic(this->m_pTopic);
  DomainParticipantFactory::get_instance()->delete_participant(
      this->m_pParticipant);
}

bool CDDSPubSub::initCommon() {
  DomainParticipantQos participantQos;
  participantQos.name("4diac PubSub");

  this->m_pParticipant =
      DomainParticipantFactory::get_instance()->create_participant(
          0, participantQos);
  if (this->m_pParticipant == nullptr)
    return false;

  this->m_sTopicType = this->registerType(this->m_pParticipant);
  DEVLOG_DEBUG(
      ("[DDS PubSub] Registered type '" + this->m_sTopicType + "'.\n").c_str());

  this->m_pTopic = this->m_pParticipant->create_topic(
      this->m_sTopicName, this->m_sTopicType, TOPIC_QOS_DEFAULT);
  if (this->m_pTopic == nullptr)
    return false;

  return true;
}

bool CDDSPubSub::initPublisher() {
  if (!this->initCommon())
    return false;

  this->m_pPublisher =
      this->m_pParticipant->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
  if (this->m_pPublisher == nullptr)
    return false;

  this->m_pWriter = this->m_pPublisher->create_datawriter(
      this->m_pTopic, DATAWRITER_QOS_DEFAULT, nullptr);
  if (this->m_pWriter == nullptr)
    return false;

  DEVLOG_DEBUG("[DDS PubSub] Initialized Publisher.\n");
  return true;
}

bool CDDSPubSub::initSubscriber(CDDSHandler *handler) {
  if (!this->initCommon())
    return false;

  this->mReaderListener.m_pHandler = handler;

  this->m_pSubscriber =
      this->m_pParticipant->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);
  if (this->m_pSubscriber == nullptr)
    return false;

  this->m_pReader = this->m_pSubscriber->create_datareader(
      this->m_pTopic, DATAREADER_QOS_DEFAULT, &(this->mReaderListener));
  if (this->m_pReader == nullptr)
    return false;

  DEVLOG_DEBUG("[DDS PubSub] Initialized Subscriber.\n");
  return true;
}

void CDDSPubSub::setIdentityQueue(std::queue<SRequestInfo> *paRequestInfos) {
  this->m_pRequestInfos = paRequestInfos;
}

std::optional<GUID_t> CDDSPubSub::getReaderGUID() {
  if (this->m_pSubscriber != nullptr)
    return this->m_pReader->guid();
  return std::nullopt;
}

inline void CDDSPubSub::CSubListener::on_data_available(DataReader *m_pReader) {
  this->m_pHandler->onDataAvailable(m_pReader);
}

CDDSPubSub *CDDSPubSub::selectPubSub(std::string pa_sTopicName,
                                     std::string pa_sTopicType,
                                     EPubSubRole pa_enPubSubRole) {
  if (pa_sTopicType == "action_msgs::srv::dds_::CancelGoal_Response_")
    return new action_msgs::CancelGoalResponsePubSub(pa_sTopicName,
                                                     pa_enPubSubRole);
  if (pa_sTopicType == "action_msgs::srv::dds_::CancelGoal_Request_")
    return new action_msgs::CancelGoalRequestPubSub(pa_sTopicName,
                                                    pa_enPubSubRole);

  if (pa_sTopicType == "action_msgs::msg::dds_::GoalInfo_")
    return new action_msgs::GoalInfoPubSub(pa_sTopicName, pa_enPubSubRole);
  if (pa_sTopicType == "action_msgs::msg::dds_::GoalStatusArray_")
    return new action_msgs::GoalStatusArrayPubSub(pa_sTopicName,
                                                  pa_enPubSubRole);

  if (pa_sTopicType == "example_message::msg::StringDebug")
    return new example_message::StringDebugPubSub(pa_sTopicName,
                                                  pa_enPubSubRole);

  if (pa_sTopicType == "turtlesim::srv::dds_::Spawn_Request")
    return new turtlesim::SpawnRequestPubSub(pa_sTopicName, pa_enPubSubRole);
  if (pa_sTopicType == "turtlesim::srv::dds_::Spawn_Response")
    return new turtlesim::SpawnResponsePubSub(pa_sTopicName, pa_enPubSubRole);

  if (pa_sTopicType ==
      "turtlesim::action::dds_::RotateAbsolute_FeedbackMessage_")
    return new turtlesim::RotateAbsoluteFeedbackMessagePubSub(pa_sTopicName,
                                                              pa_enPubSubRole);
  if (pa_sTopicType == "turtlesim::action::dds_::RotateAbsolute_Feedback_")
    return new turtlesim::RotateAbsoluteFeedbackPubSub(pa_sTopicName,
                                                       pa_enPubSubRole);
  if (pa_sTopicType ==
      "turtlesim::action::dds_::RotateAbsolute_GetResult_Request_")
    return new turtlesim::RotateAbsoluteGetResultRequestPubSub(pa_sTopicName,
                                                               pa_enPubSubRole);
  if (pa_sTopicType ==
      "turtlesim::action::dds_::RotateAbsolute_GetResult_Response_")
    return new turtlesim::RotateAbsoluteGetResultResponsePubSub(
        pa_sTopicName, pa_enPubSubRole);
  if (pa_sTopicType == "turtlesim::action::dds_::RotateAbsolute_Goal_")
    return new turtlesim::RotateAbsoluteGoalPubSub(pa_sTopicName,
                                                   pa_enPubSubRole);
  if (pa_sTopicType == "turtlesim::action::dds_::RotateAbsolute_Result_")
    return new turtlesim::RotateAbsoluteResultPubSub(pa_sTopicName,
                                                     pa_enPubSubRole);
  if (pa_sTopicType ==
      "turtlesim::action::dds_::RotateAbsolute_SendGoal_Request_")
    return new turtlesim::RotateAbsoluteSendGoalRequestPubSub(pa_sTopicName,
                                                              pa_enPubSubRole);
  if (pa_sTopicType ==
      "turtlesim::action::dds_::RotateAbsolute_SendGoal_Response_")
    return new turtlesim::RotateAbsoluteSendGoalResponsePubSub(pa_sTopicName,
                                                               pa_enPubSubRole);

  if (pa_sTopicType == "example_interfaces::srv::dds_::AddTwoInts_Request_")
    return new example_interfaces::AddTwoIntsRequestPubSub(pa_sTopicName,
                                                           pa_enPubSubRole);
  if (pa_sTopicType == "example_interfaces::srv::dds_::AddTwoInts_Response_")
    return new example_interfaces::AddTwoIntsResponsePubSub(pa_sTopicName,
                                                            pa_enPubSubRole);

  // add other topic types here

  return nullptr;
}

bool CDDSPubSub::write(void *pa_pData) {

  auto writeParams = WriteParams();
  SRequestInfo reqInfo;

  switch (this->m_enRole) {

  // simply publish
  case EPubSubRole::NONE:
    return this->m_pWriter->write(pa_pData);

  // take data from the request queueue and update the response with it
  case EPubSubRole::SERVER:
    if (this->m_pRequestInfos == nullptr || this->m_pRequestInfos->empty())
      return false;
    reqInfo = this->m_pRequestInfos->front();
    this->m_pRequestInfos->pop();
    writeParams.related_sample_identity().writer_guid(reqInfo.guid);
    writeParams.related_sample_identity().sequence_number() = reqInfo.sequence;
    return this->m_pWriter->write(pa_pData, writeParams);

  // when sending a request, make sure it uses the correct writer guid and
  // sequence number, also update the queue
  case EPubSubRole::CLIENT:
    if (this->m_pRequestInfos == nullptr)
      return false;
    SequenceNumber_t sequenceNumber = ++this->mSequenceNumber;
    writeParams.related_sample_identity().writer_guid(this->m_pWriter->guid());
    writeParams.related_sample_identity().sequence_number() = sequenceNumber;
    reqInfo.guid = this->m_pWriter->guid();
    reqInfo.sequence = sequenceNumber;
    this->m_pRequestInfos->push(reqInfo);
    return this->m_pWriter->write(pa_pData, writeParams);
  }
};

ReturnCode_t CDDSPubSub::take(bool *pa_pTaken, void *pa_pData) {

  *pa_pTaken = false;
  SampleInfo info;
  SRequestInfo reqInfo;
  auto ret = this->m_pReader->take_next_sample(pa_pData, &info);

  switch (this->m_enRole) {

  // do nothing special
  case EPubSubRole::NONE:
    *pa_pTaken = true;
    break;

  // store the request info in the queue
  case EPubSubRole::SERVER:
    if (this->m_pRequestInfos == nullptr)
      break;
    *pa_pTaken = true;
    reqInfo.guid = info.related_sample_identity.writer_guid();
    reqInfo.sequence = info.sample_identity.sequence_number();
    this->m_pRequestInfos->push(reqInfo);
    break;

  // compare if the sample info matches the prepared request
  case EPubSubRole::CLIENT:
    if (this->m_pRequestInfos == nullptr || this->m_pRequestInfos->empty())
      break;
    reqInfo = this->m_pRequestInfos->front();

    // TODO: handle sequence number in some way

    if (info.related_sample_identity.writer_guid() == reqInfo.guid) {
      *pa_pTaken = true;
      this->m_pRequestInfos->pop();
    }
    break;
  }

  return ret;
};