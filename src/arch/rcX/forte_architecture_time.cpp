/*******************************************************************************
 * Copyright (c) 2019 TU Wien/ACIN
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *  Martin Melik Merkumians - Adds getNanoSecondsMonotonic
 *  Martin Jobst - add high-resolution realtime clock fallback
 *******************************************************************************/

#include <stdint.h>
#include <AP_Sys.h>

#include "forte_architecture_time.h"

uint_fast64_t getNanoSecondsMonotonicArch() {
  return rX_SysGetSystemTicks() * rX_SysGetSystemCycletime() *
      (forte::core::constants::cNanosecondsPerSecond / forte::core::constants::cMicrosecondsPerSecond);
}

uint_fast64_t getNanoSecondsRealtimeArch() {
  return static_cast<uint_fast64_t>(forte_time())*1000000000LL;
}

time_t forte_timegm(struct tm *pa_tm) {
  return timegm(pa_tm);
}

struct tm* forte_localtime(const time_t* paTime, struct tm* const paResult) {
  return localtime_r(paTime, paResult);
}

struct tm* forte_gmtime(const time_t* const paTime, struct tm* const paResult){
  return gmtime_r(paTime, paResult);
}
