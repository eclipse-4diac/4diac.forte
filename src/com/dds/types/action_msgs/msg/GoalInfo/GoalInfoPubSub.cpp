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

#include "../../../../util/convert.h"

#include <action_msgs/msg/GoalInfo/ROS2_action_msgs__msg__GoalInfo_dtp.h>
#include <exception>
#include <memory>
#include <optional>

#include "GoalInfoPubSub.h"
#include "forte_uint.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GoalInfoPubSub_gen.cpp"
#endif

#include "TimePubSubTypes.h"
#include "UUIDPubSubTypes.h"

using namespace action_msgs;
using namespace builtin_interfaces::msg;
using namespace unique_identifier_msgs::msg;

std::string GoalInfoPubSub::registerType(DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool GoalInfoPubSub::validateType(const CStringDictionary::TStringId typeId) {
  return typeId == g_nStringIdROS2_action_msgs__msg__GoalInfo;
}

bool GoalInfoPubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_action_msgs__msg__GoalInfo *casted =
      (CIEC_ROS2_action_msgs__msg__GoalInfo *)data;

  unique_identifier_msgs::msg::uint8__16 uuidArray = {};
  for (size_t i = 0; i < 16; i++)
    uuidArray[i] = static_cast<unsigned char>(CIEC_USINT(
        static_cast<unsigned char>(casted->var_goal_id.var_uuid[i])));
  int sec = static_cast<int>(casted->var_stamp.var_sec.getSignedValue());
  unsigned int nanosec = static_cast<unsigned int>(
      casted->var_stamp.var_nanosec.getUnsignedValue());

  UUID uuid;
  uuid.uuid(uuidArray);

  Time time;
  time.sec(sec);
  time.nanosec(nanosec);

  GoalInfo goalInfo;
  goalInfo.goal_id(uuid);
  goalInfo.stamp(time);

  return this->write(&goalInfo);
}

std::optional<std::unique_ptr<CIEC_STRUCT>> GoalInfoPubSub::receive() {
  GoalInfo goalInfo;
  bool taken;
  this->take(&taken, &goalInfo);
  if (!taken)
    return std::nullopt;

  unique_identifier_msgs::msg::uint8__16 uuid = goalInfo.goal_id().uuid();
  int sec = goalInfo.stamp().sec();
  unsigned int nanosec = goalInfo.stamp().nanosec();

  CIEC_ROS2_unique_identifier_msgs__msg__UUID ciecUUID =
      dds2ciec(goalInfo.goal_id());
  CIEC_ROS2_builtin_interfaces__msg__Time ciecTime;
  ciecTime.var_nanosec = CIEC_UINT(goalInfo.stamp().nanosec());
  ciecTime.var_sec = CIEC_INT(goalInfo.stamp().sec());

  auto ciecStruct = std::make_unique<CIEC_ROS2_action_msgs__msg__GoalInfo>();
  ciecStruct->var_stamp = ciecTime;
  ciecStruct->var_goal_id = ciecUUID;

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
