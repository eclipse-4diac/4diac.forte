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

#include <turtlesim/action/RotateAbsolute/ROS2_turtlesim__action__RotateAbsolute__Feedback_dtp.h>

#include "RotateAbsoluteFeedbackPubSub.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RotateAbsoluteFeedbackPubSub_gen.cpp"
#endif

using namespace turtlesim;

std::string
RotateAbsoluteFeedbackPubSub::registerType(DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool RotateAbsoluteFeedbackPubSub::validateType(
    const CStringDictionary::TStringId typeId) {
  return typeId == g_nStringIdROS2_turtlesim__action__RotateAbsolute__Feedback;
}

bool RotateAbsoluteFeedbackPubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback *casted =
      (CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback *)data;
  float remaining = casted->var_remaining;

  RotateAbsolute_Feedback feedback;
  feedback.remaining(remaining);

  return this->write(&feedback);
}

std::optional<std::unique_ptr<CIEC_STRUCT>>
RotateAbsoluteFeedbackPubSub::receive() {
  RotateAbsolute_Feedback feedback;
  bool taken;
  this->take(&taken, &feedback);
  if (!taken)
    return std::nullopt;

  CIEC_REAL ciecRemaining = CIEC_REAL(feedback.remaining());
  auto ciecStruct =
      std::make_unique<CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback>();

  ciecStruct->var_remaining = ciecRemaining;

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
