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

#include <turtlesim/srv/Spawn/ROS2_turtlesim__srv__Spawn__Response_dtp.h>

#include "SpawnResponsePubSub.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SpawnResponsePubSub_gen.cpp"
#endif

using namespace turtlesim;

std::string SpawnResponsePubSub::registerType(DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool SpawnResponsePubSub::validateType(
    const CStringDictionary::TStringId typeId) {
  return typeId == g_nStringIdROS2_turtlesim__srv__Spawn__Response;
}

bool SpawnResponsePubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_turtlesim__srv__Spawn__Response *casted =
      (CIEC_ROS2_turtlesim__srv__Spawn__Response *)data;
  std::string name = casted->var_name.getStorage();

  Spawn_Response spawnResponse;
  spawnResponse.name(name);

  return this->write(&spawnResponse);
}

std::optional<std::unique_ptr<CIEC_STRUCT>> SpawnResponsePubSub::receive() {
  Spawn_Response spawnResponse;
  bool taken;
  this->take(&taken, &spawnResponse);
  if (!taken)
    return std::nullopt;

  CIEC_STRING ciecName = CIEC_STRING(spawnResponse.name().c_str());
  auto ciecStruct =
      std::make_unique<CIEC_ROS2_turtlesim__srv__Spawn__Response>();

  ciecStruct->var_name = ciecName;

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
