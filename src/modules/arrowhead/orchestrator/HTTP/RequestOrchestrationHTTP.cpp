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

#include "RequestOrchestrationHTTP.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RequestOrchestrationHTTP_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_RequestOrchestrationHTTP, g_nStringIdRequestOrchestrationHTTP)

const TForteInt16 FORTE_RequestOrchestrationHTTP::scmEOWithIndexes[] = {-1};
const SAdapterInstanceDef FORTE_RequestOrchestrationHTTP::scmAdapterInstances[] = {
{g_nStringIdOrchestratorRequestAdp, g_nStringIdrequestOrchestration, false }};

const SFBInterfaceSpec FORTE_RequestOrchestrationHTTP::scmFBInterfaceSpec = {
  0,  0, nullptr,  0,  0,
  0,  0, nullptr,   0, 0,  0,  0, 0, 
  0,  0, 0,
  1,scmAdapterInstances};


const SCFB_FBInstanceData FORTE_RequestOrchestrationHTTP::scmInternalFBs[] = {
  {g_nStringIdAPPEND_STRING_3, g_nStringIdAPPEND_STRING_3},
  {g_nStringIdRequest, g_nStringIdCLIENT_1_2},
  {g_nStringIdInitFlag, g_nStringIdE_SR},
  {g_nStringIdE_PERMIT, g_nStringIdE_PERMIT},
  {g_nStringIdF_STRING_TO_WSTRING, g_nStringIdF_STRING_TO_WSTRING},
  {g_nStringIdANYToJSON, g_nStringIdANYToJSON},
  {g_nStringIdGetHTTPOrchestrationForm, g_nStringIdGetArrayResponseFromJSON},
};

const SCFB_FBParameter FORTE_RequestOrchestrationHTTP::scmParamters[] = {
  {0, g_nStringIdIN_1, "STRING#http["},
  {0, g_nStringIdIN_3, "STRING#/orchestration; POST; application/json]"},
};

const SCFB_FBConnectionData FORTE_RequestOrchestrationHTTP::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdCNF), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdREQ), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdCNF), 4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdS), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdEO), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRequest, g_nStringIdINIT), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdEO), 3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRequest, g_nStringIdREQ), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdCNF), 5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdREQ), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRequest, g_nStringIdCNF), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdR), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRequest, g_nStringIdINITO), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdEI), 3},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdrequestOrchestration, g_nStringIdrequestOrchestator), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdREQ), 5},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdGetHTTPOrchestrationForm, g_nStringIdCNF), 6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdrequestOrchestration, g_nStringIdresponseReceived), CCompositeFB::scmAdapterMarker |0},
};

const SCFB_FBFannedOutConnectionData FORTE_RequestOrchestrationHTTP::scmFannedOutEventConnections[] = {
  {5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdGetHTTPOrchestrationForm, g_nStringIdREQ), 6},
};

const SCFB_FBConnectionData FORTE_RequestOrchestrationHTTP::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdOUT), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdIN), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdOUT), 4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRequest, g_nStringIdID), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdQ), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdPERMIT), 3},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdoutput), 5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRequest, g_nStringIdSD_1), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdrequestOrchestration, g_nStringIdserviceRequestForm), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdinput), 5},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdrequestOrchestration, g_nStringIdendpoint), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdIN_2), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRequest, g_nStringIdRD_2), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdGetHTTPOrchestrationForm, g_nStringIdresponse), 6},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdGetHTTPOrchestrationForm, g_nStringIdoutput), 6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdrequestOrchestration, g_nStringIdorchestrationResponse), CCompositeFB::scmAdapterMarker |0},
};

const SCFB_FBFannedOutConnectionData FORTE_RequestOrchestrationHTTP::scmFannedOutDataConnections[] = {
  {2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRequest, g_nStringIdQI), 1},
};

const SCFB_FBNData FORTE_RequestOrchestrationHTTP::scmFBNData = {
  7, scmInternalFBs,
  9, scmEventConnections,
  1, scmFannedOutEventConnections,
  8, scmDataConnections,
  1, scmFannedOutDataConnections,
  0, nullptr,
  2, scmParamters
};


