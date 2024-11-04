/*******************************************************************************
 * Copyright (c) 2019, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral - initial implementation
 *******************************************************************************/

#include "SubscribeEventAdp_adp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SubscribeEventAdp_adp_gen.cpp"
#endif

DEFINE_ADAPTER_TYPE(FORTE_SubscribeEventAdp, g_nStringIdSubscribeEventAdp)

const CStringDictionary::TStringId FORTE_SubscribeEventAdp::scmDataOutputNames[] = {g_nStringIdeventFilter, g_nStringIdendpoint};

const CStringDictionary::TStringId FORTE_SubscribeEventAdp::scmDataOutputTypeIds[] = {g_nStringIdEventFilter, g_nStringIdWSTRING};

const TForteInt16 FORTE_SubscribeEventAdp::scmEIWithIndexes[] = {-1, -1, -1};
const CStringDictionary::TStringId FORTE_SubscribeEventAdp::scmEventInputNames[] = {g_nStringIdSubscribed, g_nStringIdUnsubscribed};

const TDataIOID FORTE_SubscribeEventAdp::scmEOWith[] = {0, 1, scmWithListDelimiter, 1, 0, scmWithListDelimiter};
const TForteInt16 FORTE_SubscribeEventAdp::scmEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_SubscribeEventAdp::scmEventOutputNames[] = {g_nStringIdSubscribe, g_nStringIdUnsubscribe};

const SFBInterfaceSpec FORTE_SubscribeEventAdp::scmFBInterfaceSpecSocket = {
  2,  scmEventInputNames, scmEventInputTypeIds, 0,  scmEIWithIndexes,
  2,  scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,  0,  0, 0,
  2,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};

const SFBInterfaceSpec FORTE_SubscribeEventAdp::scmFBInterfaceSpecPlug = {
  2,  scmEventOutputNames,  scmEventOutputTypeIds,  scmEOWith,  scmEOWithIndexes,
  2,  scmEventInputNames,  scmEventInputTypeIds,  0, 0,  2,  scmDataOutputNames, scmDataOutputTypeIds,
  0,  0, 0,
  0, 0
};



