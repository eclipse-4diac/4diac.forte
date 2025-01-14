/*******************************************************************************
 * Copyright (c) 2025 Primetals Technologies Austria GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Markus Meingast - initial implementation
 *******************************************************************************/

#pragma once

#include "struct_member_action_info.h"
#include "opcua_layer.h"
#include "opcua_objectstruct_helper.h"

class CStructActionInfo : public CStructMemberActionInfo {
  public:

    explicit CStructActionInfo(COPC_UA_ObjectStruct_Helper &paStructHelper, COPC_UA_Layer &paLayer, UA_ActionType paAction, const std::string &paEndpoint):
        CStructMemberActionInfo(paStructHelper, paLayer, paAction, paEndpoint) {
    }

    void addMemberActionInfos(std::vector<std::shared_ptr<CActionInfo>> paActionInfos) {
      mStructMemberActionInfos.insert(mStructMemberActionInfos.end(), paActionInfos.begin(), paActionInfos.end());
    }

  private:

  std::vector<std::shared_ptr<CActionInfo>> mStructMemberActionInfos;

};
