/************************************************************************************
 Copyright (c) 2023 KT Elektronik GmbH
 This program and the accompanying materials are made available under the
 terms of the Eclipse Public License 2.0 which is available at
 http://www.eclipse.org/legal/epl-2.0.

 SPDX-License-Identifier: EPL-2.0
 
 Contributors:
  Dirk Kaar - initial API and implementation and/or initial documentation
 ************************************************************************************/

#include "../../core/devexec.h"
#include "fortenew.h"
#include "zephyrtiha.h"
#include "forte_constants.h"

#ifndef K_FP_REGS
#define K_FP_REGS 0
#endif // K_FP_REGS


CZephyrTimerHandler::CZephyrTimerHandler(CDeviceExecution& paDeviceExecution) :
  CTimerHandler(paDeviceExecution) {
  k_timer_init(&timer, NULL, NULL);
  constexpr size_t stackSize = 1024;
  stack = k_thread_stack_alloc(stackSize, 0);
  if (stack == nullptr) {
    return;
  }
  thread = static_cast<k_thread*>(k_malloc(sizeof(struct k_thread)));
  if (thread == nullptr) {
    return;
  }
  thread_id = k_thread_create(thread, stack, stackSize, thread_fn, this, NULL, NULL, 1, K_FP_REGS, K_FOREVER);
  if (thread_id) k_thread_name_set(thread_id, "forte_tiha");
}

CZephyrTimerHandler::~CZephyrTimerHandler() {
  disableHandler();
  if (thread) {
    k_thread_abort(thread_id);
    k_free(thread);
  }
  if (stack) {
    k_thread_stack_free(stack);
  }
}

void CZephyrTimerHandler::enableHandler() {
  if (thread == nullptr) {
    return;
  }
  const auto period = K_NSEC(forte::core::constants::cNanosecondsPerSecond / getTicksPerSecond());
  k_timer_start(&timer, period, period);
  k_thread_start(thread_id);
}

void CZephyrTimerHandler::disableHandler() {
  k_timer_stop(&timer);
}

void CZephyrTimerHandler::setPriority(int paPriority) {
  (void)paPriority;
}

int CZephyrTimerHandler::getPriority() const {
  return 1;
}

void CZephyrTimerHandler::thread_fn(void* arg1, void* arg2, void* arg3) {
  auto self = static_cast<CZephyrTimerHandler*>(arg1);
  while (true) {
    for (auto status = k_timer_status_sync(&self->timer); status > 0; --status) {
      self->nextTick();
    }
  }
}
