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

#include <turtlesim/action/RotateAbsolute/ROS2_turtlesim__action__RotateAbsolute__Result_dtp.h>

#include "RotateAbsoluteResultPubSub.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RotateAbsoluteResultPubSub_gen.cpp"
#endif

using namespace turtlesim;

std::string
RotateAbsoluteResultPubSub::registerType(DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool RotateAbsoluteResultPubSub::validateType(
    const CStringDictionary::TStringId typeId) {
  return typeId == g_nStringIdROS2_turtlesim__action__RotateAbsolute__Result;
}

bool RotateAbsoluteResultPubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_turtlesim__action__RotateAbsolute__Result *casted =
      (CIEC_ROS2_turtlesim__action__RotateAbsolute__Result *)data;
  float delta = casted->var_delta;

  RotateAbsolute_Result result;
  result.delta(delta);

  return this->write(&result);
}

std::optional<std::unique_ptr<CIEC_STRUCT>>
RotateAbsoluteResultPubSub::receive() {
  RotateAbsolute_Result result;
  bool taken;
  this->take(&taken, &result);
  if (!taken)
    return std::nullopt;

  CIEC_REAL ciecDelta = CIEC_REAL(result.delta());

  auto ciecStruct =
      std::make_unique<CIEC_ROS2_turtlesim__action__RotateAbsolute__Result>();

  ciecStruct->var_delta = ciecDelta;

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
