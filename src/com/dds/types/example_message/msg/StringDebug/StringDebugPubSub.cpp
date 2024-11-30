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

#include <memory>
#include <example_message/msg/ROS2_example_message__msg__DebugString_dtp.h>
#include <string>

#include "StringDebugPubSub.h"
#include "devlog.h"
#include "forte_struct.h"
#include "stringlist.h"
#include "types/example_message/msg/StringDebug/StringDebug.h"

#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "StringPubSub_gen.cpp"
#endif

std::string example_message::StringDebugPubSub::registerType(DomainParticipant* paParticipant) {

  this->m_type.register_type(paParticipant);
  return this->m_type.get_type_name();
}

bool example_message::StringDebugPubSub::validateType(const CStringDictionary::TStringId typeId) {
  return typeId == g_nStringIdROS2_example_message__msg__DebugString;
}

bool example_message::StringDebugPubSub::publish(CIEC_STRUCT* data) {
  const auto casted = static_cast<CIEC_ROS2_example_message__msg__DebugString*> (data);

  const std::string value = casted->var_data.getStorage();
  
  DEVLOG_DEBUG(("[DDS Publisher/std_msgs/String] Sent message '" + value + "'.\n").c_str());

  example_message::msg::StringDebug string;
  string.data(value.c_str());

  return this->write(&string);
}

std::optional<std::unique_ptr<CIEC_STRUCT>> example_message::StringDebugPubSub::receive() {
  example_message::msg::StringDebug string;
  bool taken;
  this->take(&taken, &string);
  if (!taken) return std::nullopt;

  CIEC_STRING ciecString = CIEC_STRING(string.data());

  auto ciecStruct = std::make_unique<CIEC_ROS2_example_message__msg__DebugString>();

  ciecStruct->var_data = ciecString;

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
