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

#ifndef _COM_DDS_UTIL_CONVERT_H_
#define _COM_DDS_UTIL_CONVERT_H_

#include "../types/unique_identifier_msgs/msg/UUID/UUID.h"
#include <unique_identifier_msgs/msg/UUID/ROS2_unique_identifier_msgs__msg__UUID_dtp.h>

namespace unique_identifier_msgs {
namespace msg {

UUID ciec2dds(CIEC_ROS2_unique_identifier_msgs__msg__UUID paCIEC);
CIEC_ROS2_unique_identifier_msgs__msg__UUID dds2ciec(UUID paDDS);

} // namespace msg
} // namespace unique_identifier_msgs

#endif