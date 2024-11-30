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
#include "action_msgs/msg/GoalStatus/ROS2_action_msgs__msg__GoalStatus_dtp.h"

#include <action_msgs/msg/GoalStatusArray/ROS2_action_msgs__msg__GoalStatusArray_dtp.h>

#include <cstdint>
#include <memory>
#include <optional>

#include "GoalStatusArrayPubSub.h"
#include "forte_sint.h"
#include "forte_uint.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GoalStatusArrayPubSub_gen.cpp"
#endif;

using namespace action_msgs;
using namespace action_msgs::msg;
using namespace unique_identifier_msgs::msg;

std::string
GoalStatusArrayPubSub::registerType(DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool GoalStatusArrayPubSub::validateType(
    const CStringDictionary::TStringId typeId) {
  return typeId == g_nStringIdROS2_action_msgs__msg__GoalStatusArray;
}

bool GoalStatusArrayPubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_action_msgs__msg__GoalStatusArray *casted =
      (CIEC_ROS2_action_msgs__msg__GoalStatusArray *)data;

  std::vector<GoalStatus> statusList;
  for (int i = 0; i < 16; i++) {
    CIEC_ROS2_action_msgs__msg__GoalStatus status = casted->var_status_list[i];
    GoalStatus goalStatus;
    goalStatus.goal_info().goal_id(ciec2dds(status.var_goal_info.var_goal_id));
    goalStatus.goal_info().stamp().sec() = static_cast<uint32_t>(
        status.var_goal_info.var_stamp.var_sec.getSignedValue());
    goalStatus.goal_info().stamp().nanosec() = static_cast<uint32_t>(
        status.var_goal_info.var_stamp.var_nanosec.getUnsignedValue());
    goalStatus.status(static_cast<int8_t>(status.var_status.getSignedValue()));
    statusList.push_back(goalStatus);
  }

  GoalStatusArray statusArray;
  statusArray.status_list(statusList);

  return this->write(&statusArray);
}

std::optional<std::unique_ptr<CIEC_STRUCT>> GoalStatusArrayPubSub::receive() {
  GoalStatusArray goalStatusArray;
  bool taken;
  this->take(&taken, &goalStatusArray);
  if (!taken)
    return std::nullopt;

  auto ciecGoalStatusArray =
      std::make_unique<CIEC_ROS2_action_msgs__msg__GoalStatusArray>();
  for (size_t i = 0; i < goalStatusArray.status_list().size(); i++) {
    ciecGoalStatusArray->var_status_list[i].var_status =
        CIEC_SINT(goalStatusArray.status_list()[i].status());

    ciecGoalStatusArray->var_status_list[i].var_goal_info.var_goal_id =
        dds2ciec(goalStatusArray.status_list()[i].goal_info().goal_id());

    ciecGoalStatusArray->var_status_list[i].var_goal_info.var_stamp.var_sec =
        CIEC_INT(goalStatusArray.status_list()[i].goal_info().stamp().sec());

    ciecGoalStatusArray->var_status_list[i]
        .var_goal_info.var_stamp.var_nanosec = CIEC_UINT(
        goalStatusArray.status_list()[i].goal_info().stamp().nanosec());
  }

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecGoalStatusArray);

  return std::make_optional(std::move(ptr));
}
