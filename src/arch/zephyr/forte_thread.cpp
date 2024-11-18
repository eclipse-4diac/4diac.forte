/************************************************************************************
 Copyright (c) 2023 KT Elektronik GmbH
 This program and the accompanying materials are made available under the
 terms of the Eclipse Public License 2.0 which is available at
 http://www.eclipse.org/legal/epl-2.0.

 SPDX-License-Identifier: EPL-2.0
 
 Contributors:
  Dirk Kaar - initial API and implementation and/or initial documentation
 ************************************************************************************/

#include <criticalregion.h>
#include <fortealloc.h>

#include "forte_thread.h"

#ifndef K_FP_REGS
#define K_FP_REGS 0
#endif // K_FP_REGS

CZephyrThread::CZephyrThread(long paStackSize) : CThreadBase(paStackSize) {
  stack = k_thread_stack_alloc(paStackSize, 0);
  if (stack == nullptr) return;
  thread = static_cast<k_thread*>(k_malloc(sizeof(struct k_thread)));
}

CZephyrThread::~CZephyrThread() {
  if (thread) {
    k_thread_abort(thread);
    k_free(thread);
  }
  if (stack) k_thread_stack_free(stack);
}

void CZephyrThread::threadFunction(void* arg1, void* arg2, void* arg3) {
  CThreadBase::runThread(static_cast<CZephyrThread *>(arg1));
}

forte::arch::CThreadBase<k_tid_t, nullptr, CZephyrThread>::TThreadHandleType CZephyrThread::createThread(long paStackSize) {
  if (thread == nullptr) return nullptr;
  auto thread_id = k_thread_create(thread, stack, paStackSize, threadFunction, this, NULL, NULL, 10, K_FP_REGS, K_NO_WAIT);
  if (thread_id) k_thread_name_set(thread_id, "forte_thread");
  return thread_id;
}

void CZephyrThread::sleepThread(unsigned int paMilliSeconds) {
  k_msleep(paMilliSeconds);
}
void CZephyrThread::setDeadline(const CIEC_TIME &paVal) {
  CThreadBase::setDeadline(paVal);
}
