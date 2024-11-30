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

#include <turtlesim/srv/Spawn/ROS2_turtlesim__srv__Spawn__Request_dtp.h>

#include "SpawnRequestPubSub.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SpawnRequestPubSub_gen.cpp"
#endif

using namespace turtlesim;

std::string SpawnRequestPubSub::registerType(DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool SpawnRequestPubSub::validateType(
    const CStringDictionary::TStringId typeId) {
  return typeId == g_nStringIdROS2_turtlesim__srv__Spawn__Request;
}

bool SpawnRequestPubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_turtlesim__srv__Spawn__Request *casted =
      (CIEC_ROS2_turtlesim__srv__Spawn__Request *)data;
  float x = casted->var_x;
  float y = casted->var_y;
  float theta = casted->var_theta;
  std::string name = casted->var_name.getValue();

  Spawn_Request spawnRequest;
  spawnRequest.x(x);
  spawnRequest.y(y);
  spawnRequest.theta(theta);
  spawnRequest.name(name);

  return this->write(&spawnRequest);
}

std::optional<std::unique_ptr<CIEC_STRUCT>> SpawnRequestPubSub::receive() {
  Spawn_Request spawnRequest;
  bool taken;
  this->take(&taken, &spawnRequest);
  if (!taken)
    return std::nullopt;

  CIEC_REAL ciecX = CIEC_REAL(spawnRequest.x());
  CIEC_REAL ciecY = CIEC_REAL(spawnRequest.y());
  CIEC_REAL ciecTheta = CIEC_REAL(spawnRequest.theta());
  CIEC_STRING ciecName = CIEC_STRING(spawnRequest.name().c_str());

  auto ciecStruct =
      std::make_unique<CIEC_ROS2_turtlesim__srv__Spawn__Request>();

  ciecStruct->var_x = ciecX;
  ciecStruct->var_y = ciecY;
  ciecStruct->var_theta = ciecTheta;
  ciecStruct->var_name = ciecName;

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
