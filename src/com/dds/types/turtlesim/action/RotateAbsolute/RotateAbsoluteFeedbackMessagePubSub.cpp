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

#include <turtlesim/action/RotateAbsolute/ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage_dtp.h>

#include "RotateAbsoluteFeedbackMessagePubSub.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RotateAbsoluteFeedbackMessagePubSub_gen.cpp"
#endif

using namespace turtlesim;
using namespace unique_identifier_msgs::msg;

std::string RotateAbsoluteFeedbackMessagePubSub::registerType(
    DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool RotateAbsoluteFeedbackMessagePubSub::validateType(
    const CStringDictionary::TStringId typeId) {
  return typeId ==
         g_nStringIdROS2_turtlesim__action__RotateAbsolute__FeedbackMessage;
}

bool RotateAbsoluteFeedbackMessagePubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage *casted =
      (CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage *)data;

  UUID uuid = ciec2dds(casted->var_goal_id);

  RotateAbsolute_Feedback feedback;
  float remaining = casted->var_feedback.var_remaining;
  feedback.remaining(remaining);

  RotateAbsolute_FeedbackMessage feedbackMessage;
  feedbackMessage.goal_id(uuid);
  feedbackMessage.feedback(feedback);

  return this->write(&feedbackMessage);
}

std::optional<std::unique_ptr<CIEC_STRUCT>>
RotateAbsoluteFeedbackMessagePubSub::receive() {
  RotateAbsolute_FeedbackMessage feedbackMessage;
  bool taken;
  this->take(&taken, &feedbackMessage);
  if (!taken)
    return std::nullopt;

  auto ciecStruct = std::make_unique<
      CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage>();

  CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback ciecFeedback;
  ciecFeedback.var_remaining =
      CIEC_REAL(feedbackMessage.feedback().remaining());
  ciecStruct->var_feedback = ciecFeedback;

  CIEC_ROS2_unique_identifier_msgs__msg__UUID ciecUUID =
      dds2ciec(feedbackMessage.goal_id());
  ciecStruct->var_goal_id = ciecUUID;

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
