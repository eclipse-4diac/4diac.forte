/************************************************************************************
 * Copyright (c) 2016, 2024 fortiss GmbH, Jose Cabral
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 * Milan Vathoopan, Guru Chandrasekhara - initial API and implementation and/or initial documentation
 ************************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#include "devlog.h"
#include "../c_interface/forte_c.h"

static const unsigned scForteTaskPriority = tskIDLE_PRIORITY + 1;

static const unsigned int scDesiredFortePort = 61499;

static const configSTACK_DEPTH_TYPE scStackDepth = 2000,

void vForteTask(void* ) {
  TForteInstance forteInstance;

  if(auto result = CForteArchitecture::initialize(0, NULL); result != 0){
    vTaskDelete(nullptr);
  }

  if(auto result = forteStartInstance(scDesiredFortePort, &forteInstance); result != FORTE_OK){
    vTaskDelete(nullptr);
  }

  forteWaitForInstanceToStop(forteInstance);

  vTaskDelete(nullptr);
}

int main() {

  if(auto result = forteGlobalInitialize(0, nullptr); result != FORTE_OK){
    return result;
  }

  xTaskCreate(vForteTask, "forte", scStackDepth, nullptr, scForteTaskPriority, nullptr);

  vTaskStartScheduler();

  // Will not get here unless there is insufficient RAM.
}

