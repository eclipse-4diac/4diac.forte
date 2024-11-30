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

#include <example_interfaces/srv/AddTwoInts/ROS2_example_interfaces__srv__AddTwoInts__Response_dtp.h>

#include "AddTwoIntsResponsePubSub.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "AddTwoIntsResponsePubSub_gen.cpp"
#endif

using namespace example_interfaces;

std::string
AddTwoIntsResponsePubSub::registerType(DomainParticipant *participant) {
  this->type.register_type(participant);
  return this->type.get_type_name();
}

bool AddTwoIntsResponsePubSub::validateType(
    const CStringDictionary::TStringId typeId) {
  return typeId ==
         g_nStringIdROS2_example_interfaces__srv__AddTwoInts__Response;
}

bool AddTwoIntsResponsePubSub::publish(CIEC_STRUCT *data) {
  CIEC_ROS2_example_interfaces__srv__AddTwoInts__Response *casted =
      (CIEC_ROS2_example_interfaces__srv__AddTwoInts__Response *)data;
  int64_t sum = (int64_t)casted->var_sum;

  AddTwoInts_Response addTwoIntsResponse;
  addTwoIntsResponse.sum(sum);

  return this->write(&addTwoIntsResponse);
}

std::optional<std::unique_ptr<CIEC_STRUCT>>
AddTwoIntsResponsePubSub::receive() {
  AddTwoInts_Response addTwoIntsResponse;
  bool taken;
  this->take(&taken, &addTwoIntsResponse);
  if (!taken)
    return std::nullopt;

  CIEC_LINT ciecSum = CIEC_LINT(addTwoIntsResponse.sum());

  auto ciecStruct = std::make_unique<
      CIEC_ROS2_example_interfaces__srv__AddTwoInts__Response>();

  ciecStruct->var_sum = ciecSum;

  std::unique_ptr<CIEC_STRUCT> ptr = std::move(ciecStruct);

  return std::make_optional(std::move(ptr));
}
