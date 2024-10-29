/*******************************************************************************
 * Copyright (c) 2024 Samator Indo Gas
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *  Ketut Kumajaya - Create a common standard C++ time implementation
 *******************************************************************************/

#include <chrono>

using namespace std::chrono;

#include "forte_architecture_time.h"

uint_fast64_t getNanoSecondsMonotonicArch() {
  return static_cast<uint_fast64_t>(duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count());
}

uint_fast64_t getNanoSecondsRealtimeArch() {
  return static_cast<uint_fast64_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
}
