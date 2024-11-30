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

#ifndef _COM_DDS_TYPES_ACTION_MSGS_MSG_GOAL_STATUS_ARRAY_PUB_SUB_H_
#define _COM_DDS_TYPES_ACTION_MSGS_MSG_GOAL_STATUS_ARRAY_PUB_SUB_H_

#include "ddspubsub.h"

#include "GoalStatusArrayPubSubTypes.h"
using namespace action_msgs::msg;

namespace action_msgs {

class GoalStatusArrayPubSub : public CDDSPubSub {
public:
  GoalStatusArrayPubSub(std::string topicName, EPubSubRole role)
      : CDDSPubSub(topicName, role), type(new GoalStatusArrayPubSubType()) {}

  std::string registerType(DomainParticipant *paParticipant) override;
  bool validateType(const CStringDictionary::TStringId typeId) override;
  bool publish(CIEC_STRUCT *data) override;
  std::optional<std::unique_ptr<CIEC_STRUCT>> receive() override;

private:
  TypeSupport type;
};

} // namespace action_msgs

#endif
