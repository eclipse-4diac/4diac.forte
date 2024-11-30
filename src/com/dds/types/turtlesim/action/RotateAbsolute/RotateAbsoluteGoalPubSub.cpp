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

#include <turtlesim/action/RotateAbsolute/ROS2_turtlesim__action__RotateAbsolute__Goal_dtp.h>

#include "RotateAbsoluteGoalPubSub.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RotateAbsoluteGoalPubSub_gen.cpp"
#endif

using namespace turtlesim;

std::string
RotateAbsoluteGoalPubSub::registerType(DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool RotateAbsoluteGoalPubSub::validateType(
    const CStringDictionary::TStringId typeId) {
  return typeId == g_nStringIdROS2_turtlesim__action__RotateAbsolute__Goal;
}

bool RotateAbsoluteGoalPubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal *casted =
      (CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal *)data;
  float theta = casted->var_theta;

  RotateAbsolute_Goal goal;
  goal.theta(theta);

  return this->write(&goal);
}

std::optional<std::unique_ptr<CIEC_STRUCT>>
RotateAbsoluteGoalPubSub::receive() {
  RotateAbsolute_Goal goal;
  bool taken;
  this->take(&taken, &goal);
  if (!taken)
    return std::nullopt;

  CIEC_REAL ciecTheta = CIEC_REAL(goal.theta());

  auto ciecStruct =
      std::make_unique<CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal>();

  ciecStruct->var_theta = ciecTheta;

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
