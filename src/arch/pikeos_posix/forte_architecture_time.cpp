/*******************************************************************************
 * Copyright (c) 2021 SYSGO GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *  Martin Melik Merkumians - Adds getNanoSecondsMonotonic
 *  Thomas Wagner - copy from "arch/posix": CLOCK_MONOTONIC was replaced by
 *                  CLOCK_REALTIME, which is required by PikeOS Posix.
 *******************************************************************************/

#include <time.h>

#include "forte_architecture_time.h"
#include "forte_constants.h"

uint_fast64_t getNanoSecondsMonotonicArch() {
  struct timespec now;
  clock_gettime(CLOCK_REALTIME, &now);
  return now.tv_nsec + now.tv_sec * forte::core::constants::cNanosecondsPerSecond;
}


