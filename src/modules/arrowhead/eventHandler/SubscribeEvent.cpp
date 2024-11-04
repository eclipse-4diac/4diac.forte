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

#include "SubscribeEvent.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SubscribeEvent_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_SubscribeEvent, g_nStringIdSubscribeEvent)

const CStringDictionary::TStringId FORTE_SubscribeEvent::scmDataInputNames[] = {g_nStringIdeventFilter, g_nStringIdendpoint};

const CStringDictionary::TStringId FORTE_SubscribeEvent::scmDataInputTypeIds[] = {g_nStringIdEventFilter, g_nStringIdWSTRING};

const TForteInt16 FORTE_SubscribeEvent::scmEIWithIndexes[] = {0, 3};
const TDataIOID FORTE_SubscribeEvent::scmEIWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_SubscribeEvent::scmEventInputNames[] = {g_nStringIdSubscribe, g_nStringIdUnsubscribe};
const CStringDictionary::TStringId FORTE_SubscribeEvent::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};

const TForteInt16 FORTE_SubscribeEvent::scmEOWithIndexes[] = {-1, -1, -1};
const CStringDictionary::TStringId FORTE_SubscribeEvent::scmEventOutputNames[] = {g_nStringIdSubscribed, g_nStringIdUnsubscribed};
const CStringDictionary::TStringId FORTE_SubscribeEvent::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};

const SAdapterInstanceDef FORTE_SubscribeEvent::scmAdapterInstances[] = {
{g_nStringIdSubscribeEventAdp, g_nStringIdSubscribeEventAdp, true }};

const SFBInterfaceSpec FORTE_SubscribeEvent::scmFBInterfaceSpec = {
  2,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  2,  scmEventOutputNames, scmEventOutputTypeIds,  0, 0,  2,  scmDataInputNames, scmDataInputTypeIds,
  0,  0, 0,
  1,scmAdapterInstances};


const SCFB_FBConnectionData FORTE_SubscribeEvent::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdUnsubscribe), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdSubscribeEventAdp, g_nStringIdUnsubscribe), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdSubscribe), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdSubscribeEventAdp, g_nStringIdSubscribe), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdSubscribeEventAdp, g_nStringIdSubscribed), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdSubscribed), -1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdSubscribeEventAdp, g_nStringIdUnsubscribed), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdUnsubscribed), -1},
};

const SCFB_FBConnectionData FORTE_SubscribeEvent::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdeventFilter), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdSubscribeEventAdp, g_nStringIdeventFilter), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdendpoint), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdSubscribeEventAdp, g_nStringIdendpoint), CCompositeFB::scmAdapterMarker |0},
};

const SCFB_FBNData FORTE_SubscribeEvent::scmFBNData = {
  0, 0,
  4, scmEventConnections,
  0, 0,
  2, scmDataConnections,
  0, 0,
  0, nullptr,
  0, 0
};


