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

#include <cstdint>
#include <optional>
#include <system_error>
#include <turtlesim/action/RotateAbsolute/ROS2_turtlesim__action__RotateAbsolute__GetResult__Response_dtp.h>
#include <turtlesim/action/RotateAbsolute/ROS2_turtlesim__action__RotateAbsolute__Result_dtp.h>
#include <utility>

#include "RotateAbsoluteGetResultResponsePubSub.h"
#include "forte_struct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RotateAbsoluteGetResultResponsePubSub_gen.cpp"
#endif

using namespace turtlesim;

std::string RotateAbsoluteGetResultResponsePubSub::registerType(
    DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool RotateAbsoluteGetResultResponsePubSub::validateType(
    const CStringDictionary::TStringId typeId) {
  return typeId ==
         g_nStringIdROS2_turtlesim__action__RotateAbsolute__GetResult__Response;
}

bool RotateAbsoluteGetResultResponsePubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response *casted =
      (CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response *)data;

  int8_t status = (int8_t)casted->var_status;
  float delta = casted->var_result.var_delta;

  RotateAbsolute_GetResult_Response response;
  response.status(status);
  response.result().delta(delta);

  return this->write(&response);
}

std::optional<std::unique_ptr<CIEC_STRUCT>>
RotateAbsoluteGetResultResponsePubSub::receive() {
  RotateAbsolute_GetResult_Response response;
  bool taken;
  this->take(&taken, &response);
  if (!taken)
    return std::nullopt;

  auto ciecStruct = std::make_unique<
      CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response>();

  CIEC_ROS2_turtlesim__action__RotateAbsolute__Result ciecResult;
  ciecResult.var_delta = CIEC_REAL(response.result().delta());

  ciecStruct->var_result = ciecResult;

  ciecStruct->var_status = CIEC_SINT(response.status());

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
