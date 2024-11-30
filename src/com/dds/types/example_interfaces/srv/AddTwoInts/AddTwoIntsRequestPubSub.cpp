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

#include <example_interfaces/srv/AddTwoInts/ROS2_example_interfaces__srv__AddTwoInts__Request_dtp.h>
#include <memory>

#include "AddTwoIntsRequestPubSub.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "AddTwoIntsRequestPubSub_gen.cpp"
#endif

using namespace example_interfaces;

std::string
AddTwoIntsRequestPubSub::registerType(DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool AddTwoIntsRequestPubSub::validateType(
    const CStringDictionary::TStringId typeId) {
  return typeId == g_nStringIdROS2_example_interfaces__srv__AddTwoInts__Request;
}

bool AddTwoIntsRequestPubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_example_interfaces__srv__AddTwoInts__Request *casted =
      (CIEC_ROS2_example_interfaces__srv__AddTwoInts__Request *)data;

  int64_t a = (int64_t)casted->var_a;
  int64_t b = (int64_t)casted->var_b;

  AddTwoInts_Request addTwoIntsRequest;
  addTwoIntsRequest.a(a);
  addTwoIntsRequest.b(b);

  return this->write(&addTwoIntsRequest);
}

std::optional<std::unique_ptr<CIEC_STRUCT>> AddTwoIntsRequestPubSub::receive() {
  AddTwoInts_Request addTwoIntsRequest;
  bool taken;
  this->take(&taken, &addTwoIntsRequest);
  if (!taken)
    return std::nullopt;

  CIEC_LINT ciecA = CIEC_LINT(addTwoIntsRequest.a());
  CIEC_LINT ciecB = CIEC_LINT(addTwoIntsRequest.b());

  auto ciecStruct = std::make_unique<
      CIEC_ROS2_example_interfaces__srv__AddTwoInts__Request>();

  ciecStruct->var_a = ciecA;
  ciecStruct->var_b = ciecB;

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
