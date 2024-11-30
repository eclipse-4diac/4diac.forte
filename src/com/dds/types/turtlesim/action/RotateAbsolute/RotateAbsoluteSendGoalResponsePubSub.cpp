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

#include <builtin_interfaces/msg/Time/ROS2_builtin_interfaces__msg__Time_dtp.h>
#include <cstdint>
#include <turtlesim/action/RotateAbsolute/ROS2_turtlesim__action__RotateAbsolute__SendGoal__Response_dtp.h>

#include "RotateAbsoluteSendGoalResponsePubSub.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RotateAbsoluteSendGoalResponsePubSub_gen.cpp"
#endif
#include "TimePubSubTypes.h"

using namespace turtlesim;
using namespace unique_identifier_msgs::msg;
using namespace builtin_interfaces::msg;

std::string RotateAbsoluteSendGoalResponsePubSub::registerType(
    DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool RotateAbsoluteSendGoalResponsePubSub::validateType(
    const CStringDictionary::TStringId typeId) {
  return typeId ==
         g_nStringIdROS2_turtlesim__action__RotateAbsolute__SendGoal__Response;
}

bool RotateAbsoluteSendGoalResponsePubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Response *casted =
      (CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Response *)data;

  bool accepted = casted->var_accepted;

  Time time;
  int32_t sec =
      static_cast<int32_t>(casted->var_stamp.var_sec.getSignedValue());
  uint32_t nanosec =
      static_cast<uint32_t>(casted->var_stamp.var_nanosec.getUnsignedValue());
  time.sec() = sec;
  time.nanosec() = nanosec;

  RotateAbsolute_SendGoal_Response response;
  response.accepted(accepted);
  response.stamp(time);

  return this->write(&response);
}

std::optional<std::unique_ptr<CIEC_STRUCT>>
RotateAbsoluteSendGoalResponsePubSub::receive() {
  RotateAbsolute_SendGoal_Response response;
  bool taken;
  this->take(&taken, &response);
  if (!taken)
    return std::nullopt;

  auto ciecStruct = std::make_unique<
      CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Response>();

  CIEC_BOOL ciecAccepted = CIEC_BOOL(response.accepted());
  ciecStruct->var_accepted = ciecAccepted;

  CIEC_ROS2_builtin_interfaces__msg__Time ciecStamp;
  ciecStamp.var_sec = CIEC_INT(response.stamp().sec());
  ciecStamp.var_nanosec = CIEC_UINT(response.stamp().nanosec());
  ciecStruct->var_stamp = ciecStamp;

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
