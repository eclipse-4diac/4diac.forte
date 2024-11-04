/*******************************************************************************
 * Copyright (c) 2018, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral - initial implementation
 *******************************************************************************/

#include "RegisterServiceHTTP.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RegisterServiceHTTP_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_RegisterServiceHTTP, g_nStringIdRegisterServiceHTTP)

const TForteInt16 FORTE_RegisterServiceHTTP::scmEOWithIndexes[] = {-1};
const SAdapterInstanceDef FORTE_RegisterServiceHTTP::scmAdapterInstances[] = {
{g_nStringIdRegisterServiceAdp, g_nStringIdregisterService, false }};

const SFBInterfaceSpec FORTE_RegisterServiceHTTP::scmFBInterfaceSpec = {
  0,  0, nullptr,  0,  0,
  0,  0, nullptr,   0, 0,  0,  0, 0, 
  0,  0, 0,
  1,scmAdapterInstances};


const SCFB_FBInstanceData FORTE_RegisterServiceHTTP::scmInternalFBs[] = {
  {g_nStringIdRegister, g_nStringIdCLIENT_1_2},
  {g_nStringIdUnregister, g_nStringIdCLIENT_1_2},
  {g_nStringIdInitFlagReg, g_nStringIdE_SR},
  {g_nStringIdE_PERMIT, g_nStringIdE_PERMIT},
  {g_nStringIdCreateRegisterID, g_nStringIdAPPEND_STRING_3},
  {g_nStringIdF_STRING_TO_WSTRING, g_nStringIdF_STRING_TO_WSTRING},
  {g_nStringIdE_PERMIT_1, g_nStringIdE_PERMIT},
  {g_nStringIdInitFlagUnReg, g_nStringIdE_SR},
  {g_nStringIdCreateUnRegisterID, g_nStringIdAPPEND_STRING_3},
  {g_nStringIdF_STRING_TO_WSTRING_1, g_nStringIdF_STRING_TO_WSTRING},
  {g_nStringIdANYToJSON, g_nStringIdANYToJSON},
};

const SCFB_FBParameter FORTE_RegisterServiceHTTP::scmParamters[] = {
  {4, g_nStringIdIN_1, "STRING#http["},
  {4, g_nStringIdIN_3, "STRING#/register; POST; application/json]"},
  {8, g_nStringIdIN_1, "STRING#http["},
  {8, g_nStringIdIN_3, "STRING#/remove; PUT; application/json]"},
};

const SCFB_FBConnectionData FORTE_RegisterServiceHTTP::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID, g_nStringIdCNF), 4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdREQ), 5},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdCNF), 5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagReg, g_nStringIdS), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateUnRegisterID, g_nStringIdCNF), 8, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING_1, g_nStringIdREQ), 9},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING_1, g_nStringIdCNF), 9, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagUnReg, g_nStringIdS), 7},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagUnReg, g_nStringIdEO), 7, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdINIT), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdINITO), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT_1, g_nStringIdEI), 6},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT_1, g_nStringIdEO), 6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdREQ), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdCNF), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagUnReg, g_nStringIdR), 7},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagReg, g_nStringIdEO), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdINIT), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdEO), 3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdREQ), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdINITO), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdEI), 3},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdCNF), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagReg, g_nStringIdR), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIdregisterService), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID, g_nStringIdREQ), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIdunregisterService), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateUnRegisterID, g_nStringIdREQ), 8},
};

const SCFB_FBFannedOutConnectionData FORTE_RegisterServiceHTTP::scmFannedOutEventConnections[] = {
  {1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdREQ), 10},
  {3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdREQ), 10},
  {7, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIddoneUnregister), CCompositeFB::scmAdapterMarker |0},
  {11, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIddoneRegister), CCompositeFB::scmAdapterMarker |0},
};

const SCFB_FBConnectionData FORTE_RegisterServiceHTTP::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagReg, g_nStringIdQ), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdPERMIT), 3},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID, g_nStringIdOUT), 4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdIN), 5},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateUnRegisterID, g_nStringIdOUT), 8, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING_1, g_nStringIdIN), 9},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING_1, g_nStringIdOUT), 9, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdID), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagUnReg, g_nStringIdQ), 7, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdQI), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdOUT), 5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdID), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdoutput), 10, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdSD_1), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIdserviceRegistryEntry), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdinput), 10},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIdendpoint), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID, g_nStringIdIN_2), 4},
};

const SCFB_FBFannedOutConnectionData FORTE_RegisterServiceHTTP::scmFannedOutDataConnections[] = {
  {0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdQI), 0},
  {4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT_1, g_nStringIdPERMIT), 6},
  {6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdSD_1), 1},
  {8, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateUnRegisterID, g_nStringIdIN_2), 8},
};

const SCFB_FBNData FORTE_RegisterServiceHTTP::scmFBNData = {
  11, scmInternalFBs,
  14, scmEventConnections,
  4, scmFannedOutEventConnections,
  9, scmDataConnections,
  4, scmFannedOutDataConnections,
  0, nullptr,
  4, scmParamters
};


