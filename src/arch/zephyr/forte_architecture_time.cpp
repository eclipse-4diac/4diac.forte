/*******************************************************************************
 * Copyright (c) 2019 TU Wien/ACIN
 *               2023 Martin Erich Jobst
 *               2023 KT Elektronik GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *  Martin Melik Merkumians - Adds getNanoSecondsMonotonic
 *  Martin Jobst - add high-resolution realtime clock
 *  Dirk Kaar - Zephyr OS initial API and implementation
 *******************************************************************************/

#include "forte_architecture_time.h"
#include "forte_constants.h"
#include <zephyr/kernel.h>

uint_fast64_t getNanoSecondsMonotonicArch() {
  return static_cast<uint_fast64_t>(k_uptime_ticks() * (forte::core::constants::cNanosecondsPerSecond / static_cast<uint_fast64_t>(CONFIG_SYS_CLOCK_TICKS_PER_SEC)));
}

uint_fast64_t getNanoSecondsRealtimeArch() {
  return static_cast<uint_fast64_t>(k_uptime_ticks() * (forte::core::constants::cNanosecondsPerSecond / static_cast<uint_fast64_t>(CONFIG_SYS_CLOCK_TICKS_PER_SEC)));
}

time_t forte_timegm(struct tm *pa_tm) {
  time_t tm = mktime(pa_tm);
  return mktime(gmtime(&tm));
}

struct tm* forte_localtime(const time_t* paTime, struct tm* const paResult) {
  return localtime_r(paTime, paResult);
}

struct tm* forte_gmtime(const time_t* const paTime, struct tm* const paResult){
  return gmtime_r(paTime, paResult);
}

