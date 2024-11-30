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

#include <action_msgs/srv/CancelGoal/ROS2_action_msgs__srv__CancelGoal__Response_dtp.h>

#include "CancelGoalResponsePubSub.h"
#include "forte_usint.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "CancelGoalResponsePubSub_gen.cpp"
#endif

#include "GoalInfoPubSubTypes.h"
#include "TimePubSubTypes.h"
#include "UUIDPubSubTypes.h"

#include <boost/format.hpp>
#include <memory>
#include <optional>

using namespace action_msgs;
using namespace action_msgs::msg;
using namespace unique_identifier_msgs::msg;
using namespace builtin_interfaces::msg;

std::string
CancelGoalResponsePubSub::registerType(DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool CancelGoalResponsePubSub::validateType(
    const CStringDictionary::TStringId typeId) {
  return typeId == g_nStringIdROS2_action_msgs__srv__CancelGoal__Response;
}

bool CancelGoalResponsePubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_action_msgs__srv__CancelGoal__Response *casted =
      (CIEC_ROS2_action_msgs__srv__CancelGoal__Response *)data;

  std::vector<GoalInfo> goalsCanceling = std::vector<GoalInfo>();
  for (int i = 0; i < 16; i++) {
    CIEC_ROS2_action_msgs__msg__GoalInfo goalCanceling =
        casted->var_goals_canceling[i];
    unique_identifier_msgs::msg::uint8__16 uuidArray = {};
    bool allZero = true;
    for (size_t j = 0; j < 16; j++) {
      auto entry = goalCanceling.var_goal_id.var_uuid[j];
      if (static_cast<int>(entry.getSignedValue()) != 0)
        allZero = false;
      uuidArray[i] = static_cast<unsigned char>(entry);
    }
    if (allZero)
      break;
    int sec =
        static_cast<int>(goalCanceling.var_stamp.var_sec.getSignedValue());
    unsigned int nanosec = static_cast<unsigned int>(
        goalCanceling.var_stamp.var_nanosec.getUnsignedValue());

    UUID uuid;
    uuid.uuid(uuidArray);

    Time time;
    time.sec(sec);
    time.nanosec(nanosec);

    GoalInfo goalInfo;
    goalInfo.goal_id(uuid);
    goalInfo.stamp(time);

    goalsCanceling.push_back(goalInfo);
  }

  uint8_t returnCode = (int8_t)casted->var_return_code;

  CancelGoal_Response response;
  response.goals_canceling(goalsCanceling);
  response.return_code(returnCode);

  return this->write(&response);
}

std::optional<std::unique_ptr<CIEC_STRUCT>>
CancelGoalResponsePubSub::receive() {
  CancelGoal_Response response;
  bool taken;
  this->take(&taken, &response);
  if (!taken)
    return std::nullopt;

  std::string constructor;
  constructor.reserve(4096);

  constructor += "(goals_canceling:=[";
  int counter = 0;
  for (GoalInfo goalInfo : response.goals_canceling()) {
    unique_identifier_msgs::msg::uint8__16 uuid = goalInfo.goal_id().uuid();
    int sec = goalInfo.stamp().sec();
    unsigned int nanosec = goalInfo.stamp().nanosec();

    boost::format fmt("(goal_id:=(uuid:=[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%"
                      "d,%d,%d,%d]),stamp:=(sec:=%d,nanosec:=%d)),");
    for (const auto &value : uuid)
      fmt % value;
    fmt % sec % nanosec;

    constructor += fmt.str();

    if (counter++ >= 16)
      break;
  }

  for (; counter < 16; counter++) {
    constructor += "(goal_id:=(uuid:=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]),stamp:="
                   "(sec:=0,nanosec:=0)),";
  }

  constructor.pop_back();
  constructor +=
      "],return_code:=" + std::to_string(response.return_code()) + ")";

  CIEC_SINT returnCode = CIEC_SINT(response.return_code());

  auto ciecStruct =
      std::make_unique<CIEC_ROS2_action_msgs__srv__CancelGoal__Response>();
  ciecStruct->fromString(constructor.c_str());

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
