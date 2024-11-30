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

#include <turtlesim/action/RotateAbsolute/ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request_dtp.h>

#include "RotateAbsoluteSendGoalRequestPubSub.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RotateAbsoluteSendGoalRequestPubSub_gen.cpp"
#endif

using namespace turtlesim;
using namespace unique_identifier_msgs::msg;

std::string RotateAbsoluteSendGoalRequestPubSub::registerType(
    DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool RotateAbsoluteSendGoalRequestPubSub::validateType(
    const CStringDictionary::TStringId typeId) {
  return typeId ==
         g_nStringIdROS2_turtlesim__action__RotateAbsolute__SendGoal__Request;
}

bool RotateAbsoluteSendGoalRequestPubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request *casted =
      (CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request *)data;

  UUID uuid = ciec2dds(casted->var_goal_id);

  RotateAbsolute_Goal goal;
  float theta = casted->var_goal.var_theta;
  goal.theta(theta);

  RotateAbsolute_SendGoal_Request request;
  request.goal_id(uuid);
  request.goal(goal);

  return this->write(&request);
}

std::optional<std::unique_ptr<CIEC_STRUCT>>
RotateAbsoluteSendGoalRequestPubSub::receive() {
  RotateAbsolute_SendGoal_Request request;
  bool taken;
  this->take(&taken, &request);
  if (!taken)
    return std::nullopt;

  auto ciecStruct = std::make_unique<
      CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request>();

  CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal ciecGoal;
  ciecGoal.var_theta = CIEC_REAL(request.goal().theta());
  ciecStruct->var_goal = ciecGoal;

  CIEC_ROS2_unique_identifier_msgs__msg__UUID ciecUUID =
      dds2ciec(request.goal_id());
  ciecStruct->var_goal_id = ciecUUID;

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
