/*******************************************************************************
 * Copyright (c) 2017 fortiss GmbH, 2019 TU Wien/ACIN
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *  Jose Cabral - initial API and implementation and/or initial documentation
 *  Martin Melik-Merkumians - adds function for getting monotonic time in nanoseconds
 *  Christoph Binder - add possibility to configure simulated time
 *  Martin Jobst - add high-resolution realtime clock
 *******************************************************************************/

#ifndef SRC_ARCH_FORTE_ARCHITECTURE_TIME_H_
#define SRC_ARCH_FORTE_ARCHITECTURE_TIME_H_

#include <time.h>

#include "forte_constants.h"

time_t forte_time_arch();
uint_fast64_t getNanoSecondsMonotonicArch();
uint_fast64_t getNanoSecondsRealtimeArch();

#ifdef FORTE_FAKE_TIME

  time_t forte_time_fake();
  uint_fast64_t getNanoSecondsMonotonicFake();
  uint_fast64_t getNanoSecondsRealtimeFake();

  constexpr auto forte_time = forte_time_fake;
  constexpr auto getNanoSecondsMonotonic = getNanoSecondsMonotonicFake;
  constexpr auto  getNanoSecondsRealtime = getNanoSecondsRealtimeFake;

#else // FORTE_FAKE_TIME

  constexpr auto forte_time = forte_time_arch;
  constexpr auto getNanoSecondsMonotonic = getNanoSecondsMonotonicArch;
  constexpr auto  getNanoSecondsRealtime = getNanoSecondsRealtimeArch;
#endif // FORTE_FAKE_TIME

#if defined(WINCE)
#include <wce_time.h>

inline
struct tm* forte_localtime(const time_t* pa_time){
  return wceex_localtime(pa_time);
}

inline
time_t forte_mktime(struct tm* pa_tm){
  return wceex_mktime(pa_tm);
}

inline
struct tm* forte_gmtime(const time_t* pa_time){
  return wceex_gmtime(pa_time);
}

inline
time_t forte_time_arch(){
  return wceex_time(0);
}

#else // defined(WINCE)

struct tm* forte_localtime(const time_t* paTime, struct tm* const paResult);

inline
time_t forte_mktime(struct tm* pa_tm){
  return mktime(pa_tm);
}

time_t forte_timegm(struct tm* pa_tm);

struct tm* forte_gmtime(const time_t* const paTime, struct tm* const paResult);

inline
time_t forte_time_arch(){
  return time(nullptr);
}

#endif // defined(WINCE)

#endif /* SRC_ARCH_FORTE_ARCHITECTURE_TIME_H_ */
