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

#include <action_msgs/srv/CancelGoal/ROS2_action_msgs__srv__CancelGoal__Request_dtp.h>

#include "CancelGoalRequestPubSub.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "CancelGoalRequestPubSub_gen.cpp"
#endif

#include "GoalInfoPubSubTypes.h"
#include "TimePubSubTypes.h"
#include "UUIDPubSubTypes.h"

#include <boost/format.hpp>

using namespace action_msgs;
using namespace action_msgs::msg;
using namespace unique_identifier_msgs::msg;
using namespace builtin_interfaces::msg;

std::string
CancelGoalRequestPubSub::registerType(DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool CancelGoalRequestPubSub::validateType(
    const CStringDictionary::TStringId typeId) {
  return typeId == g_nStringIdROS2_action_msgs__srv__CancelGoal__Request;
}

bool CancelGoalRequestPubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_action_msgs__srv__CancelGoal__Request *casted =
      (CIEC_ROS2_action_msgs__srv__CancelGoal__Request *)data;

  unique_identifier_msgs::msg::uint8__16 uuidArray = {};
  for (size_t i = 0; i < 16; i++)
    uuidArray[i] = static_cast<unsigned char>(
        casted->var_goal_info.var_goal_id.var_uuid[i]);
  int sec = static_cast<int>(
      casted->var_goal_info.var_stamp.var_sec.getSignedValue());
  unsigned int nanosec = static_cast<unsigned int>(
      casted->var_goal_info.var_stamp.var_nanosec.getUnsignedValue());

  UUID uuid;
  uuid.uuid(uuidArray);

  Time time;
  time.sec(sec);
  time.nanosec(nanosec);

  GoalInfo goalInfo;
  goalInfo.goal_id(uuid);
  goalInfo.stamp(time);

  CancelGoal_Request request;
  request.goal_info() = goalInfo;

  return this->write(&request);
}

std::optional<std::unique_ptr<CIEC_STRUCT>> CancelGoalRequestPubSub::receive() {
  CancelGoal_Request request;
  bool taken;
  this->take(&taken, &request);
  if (!taken)
    return std::nullopt;

  unique_identifier_msgs::msg::uint8__16 uuid =
      request.goal_info().goal_id().uuid();
  int sec = request.goal_info().stamp().sec();
  unsigned int nanosec = request.goal_info().stamp().nanosec();

  boost::format fmt("(goal_info:=(goal_id:=(uuid:=[%d,%d,%d,%d,%d,%d,%d,%d,%d,%"
                    "d,%d,%d,%d,%d,%d,%d]),stamp:=(sec:=%d,nanosec:=%d)))");
  for (const auto &value : uuid)
    fmt % value;
  fmt % sec % nanosec;

  auto ciecStruct =
      std::make_unique<CIEC_ROS2_action_msgs__srv__CancelGoal__Request>();

  ciecStruct->fromString(fmt.str().c_str());

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
