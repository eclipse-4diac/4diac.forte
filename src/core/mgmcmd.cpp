/*******************************************************************************
 * Copyright (c) 2024 Jose Cabral
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Jose Cabral:
 *      - initial implementation and rework communication infrastructure
 *******************************************************************************/

#include "mgmcmd.h"

#include <type_traits>

namespace forte::mgm_cmd {

  /*!\brief Type for the response of MGM command messages
  *
  * TODO fully define all responses as defined in IEC 61499 inc. numbers.
  */
  const std::string scmMGMResponseTexts[] = {
    "RDY",
    "BAD_PARAMS",
    "LOCAL_TERMINATION",
    "SYSTEM_TERMINATION",
    "NOT_READY",
    "UNSUPPORTED_CMD",
    "UNSUPPORTED_TYPE",
    "NO_SUCH_OBJECT",
    "INVALID_OBJECT",
    "INVALID_OPERATION",
    "INVALID_STATE",
    "OVERFLOW",
    "INVALID_DST"
  };

  const std::string& getResponseText(EMGMResponse paResp) {
    return scmMGMResponseTexts[static_cast<std::underlying_type_t<EMGMResponse>>(paResp)];
  }

} // namespace forte::mgm_cmd