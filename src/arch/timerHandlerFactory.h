/*******************************************************************************
 * Copyright (c) 2024 
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Jose Cabral - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include <string>

class CTimerHandler;
class CDeviceExecution;

namespace TimerHandlerFactory {

    /*!\brief create the timer handler
      *
      * The selection of the timer to be created depends on the value set using the method setTimeHandlerNameToCreate
      * and it is usually set to default to the one from the selected architecture.
      */
    CTimerHandler* createTimerHandler(CDeviceExecution &paDeviceExecution);

    void setTimeHandlerNameToCreate(std::string paName);

    const std::string& getTImerHandlerName();
};