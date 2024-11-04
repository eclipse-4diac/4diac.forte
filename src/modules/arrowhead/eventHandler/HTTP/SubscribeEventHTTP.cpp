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

#include "SubscribeEventHTTP.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SubscribeEventHTTP_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_SubscribeEventHTTP, g_nStringIdSubscribeEventHTTP)

const TForteInt16 FORTE_SubscribeEventHTTP::scmEOWithIndexes[] = {-1};
const SAdapterInstanceDef FORTE_SubscribeEventHTTP::scmAdapterInstances[] = {
{g_nStringIdSubscribeEventAdp, g_nStringIdSubscribeEventAdp, false }};

const SFBInterfaceSpec FORTE_SubscribeEventHTTP::scmFBInterfaceSpec = {
  0,  0, nullptr,  0,  0,
  0,  0, nullptr,   0, 0,  0,  0, 0, 
  0,  0, 0,
  1,scmAdapterInstances};


const SCFB_FBInstanceData FORTE_SubscribeEventHTTP::scmInternalFBs[] = {
  {g_nStringIdInitFlagReg, g_nStringIdE_SR},
  {g_nStringIdE_PERMIT, g_nStringIdE_PERMIT},
  {g_nStringIdInitFlagUnReg, g_nStringIdE_SR},
  {g_nStringIdF_STRING_TO_WSTRING, g_nStringIdF_STRING_TO_WSTRING},
  {g_nStringIdCreateRegisterID, g_nStringIdAPPEND_STRING_3},
  {g_nStringIdANYToJSON, g_nStringIdANYToJSON},
  {g_nStringIdE_PERMIT_1, g_nStringIdE_PERMIT},
  {g_nStringIdRegister, g_nStringIdCLIENT_1_2},
  {g_nStringIdUnregister, g_nStringIdCLIENT_1_2},
  {g_nStringIdCreateRegisterID_1, g_nStringIdAPPEND_STRING_3},
  {g_nStringIdF_STRING_TO_WSTRING_2, g_nStringIdF_STRING_TO_WSTRING},
};

const SCFB_FBParameter FORTE_SubscribeEventHTTP::scmParamters[] = {
  {4, g_nStringIdIN_1, "STRING#http["},
  {4, g_nStringIdIN_3, "STRING#/subscription; POST; application/json]"},
  {9, g_nStringIdIN_1, "STRING#http["},
  {9, g_nStringIdIN_3, "STRING#/subscription; PUT; application/json]"},
};

const SCFB_FBConnectionData FORTE_SubscribeEventHTTP::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdINITO), 7, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdEI), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdCNF), 7, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagReg, g_nStringIdR), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagReg, g_nStringIdEO), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdINIT), 7},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID, g_nStringIdCNF), 4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdREQ), 3},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdCNF), 3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdREQ), 5},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdEO), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdREQ), 7},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdSubscribeEventAdp, g_nStringIdSubscribe), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID, g_nStringIdREQ), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagUnReg, g_nStringIdEO), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdINIT), 8},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT_1, g_nStringIdEO), 6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdREQ), 8},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdINITO), 8, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT_1, g_nStringIdEI), 6},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdCNF), 8, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdSubscribeEventAdp, g_nStringIdUnsubscribed), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdSubscribeEventAdp, g_nStringIdUnsubscribe), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID_1, g_nStringIdREQ), 9},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID_1, g_nStringIdCNF), 9, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING_2, g_nStringIdREQ), 10},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING_2, g_nStringIdCNF), 10, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdREQ), 5},
};

const SCFB_FBFannedOutConnectionData FORTE_SubscribeEventHTTP::scmFannedOutEventConnections[] = {
  {1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdSubscribeEventAdp, g_nStringIdSubscribed), CCompositeFB::scmAdapterMarker |0},
  {4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagReg, g_nStringIdS), 0},
  {10, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagUnReg, g_nStringIdR), 2},
  {13, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagUnReg, g_nStringIdS), 2},
};

const SCFB_FBConnectionData FORTE_SubscribeEventHTTP::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagUnReg, g_nStringIdQ), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT_1, g_nStringIdPERMIT), 6},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagReg, g_nStringIdQ), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdQI), 7},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdoutput), 5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdSD_1), 7},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID, g_nStringIdOUT), 4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdIN), 3},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdOUT), 3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdID), 7},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdSubscribeEventAdp, g_nStringIdendpoint), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID, g_nStringIdIN_2), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdSubscribeEventAdp, g_nStringIdeventFilter), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdinput), 5},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID_1, g_nStringIdOUT), 9, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING_2, g_nStringIdIN), 10},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING_2, g_nStringIdOUT), 10, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdID), 8},
};

const SCFB_FBFannedOutConnectionData FORTE_SubscribeEventHTTP::scmFannedOutDataConnections[] = {
  {0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdQI), 8},
  {1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdPERMIT), 1},
  {2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdSD_1), 8},
  {5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID_1, g_nStringIdIN_2), 9},
};

const SCFB_FBNData FORTE_SubscribeEventHTTP::scmFBNData = {
  11, scmInternalFBs,
  14, scmEventConnections,
  4, scmFannedOutEventConnections,
  9, scmDataConnections,
  4, scmFannedOutDataConnections,
  0, nullptr,
  4, scmParamters
};


