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
#include "QueryServiceOpcUa.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "QueryServiceOpcUa_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_QueryServiceOpcUa, g_nStringIdQueryServiceOpcUa)

const TForteInt16 FORTE_QueryServiceOpcUa::scmEOWithIndexes[] = {-1};
const SAdapterInstanceDef FORTE_QueryServiceOpcUa::scmAdapterInstances[] = {
{g_nStringIdQueryServicesAdp, g_nStringIdqueryServices, false }};

const SFBInterfaceSpec FORTE_QueryServiceOpcUa::scmFBInterfaceSpec = {
  0,  0, nullptr,  0,  0,
  0,  0, nullptr,   0, 0,  0,  0, 0, 
  0,  0, 0,
  1,scmAdapterInstances};


const SCFB_FBInstanceData FORTE_QueryServiceOpcUa::scmInternalFBs[] = {
  {g_nStringIdAPPEND_STRING_3, g_nStringIdAPPEND_STRING_3},
  {g_nStringIdF_STRING_TO_WSTRING, g_nStringIdF_STRING_TO_WSTRING},
  {g_nStringIdInitFlag, g_nStringIdE_SR},
  {g_nStringIdE_PERMIT, g_nStringIdE_PERMIT},
  {g_nStringIdANYToJSON, g_nStringIdANYToJSON},
  {g_nStringIdGetHTTPResult, g_nStringIdGetArrayResponseFromJSON},
  {g_nStringIdQuery, g_nStringIdCLIENT_1},
  {g_nStringIdE_SWITCH_1, g_nStringIdE_SWITCH},
  {g_nStringIdE_SWITCH, g_nStringIdE_SWITCH},
  {g_nStringIdE_DELAY, g_nStringIdE_DELAY},
  {g_nStringIdE_CTU, g_nStringIdE_CTU},
};

const SCFB_FBParameter FORTE_QueryServiceOpcUa::scmParamters[] = {
  {0, g_nStringIdIN_1, "STRING#opc_ua[CALL_METHOD; "},
  {0, g_nStringIdIN_3, "STRING##; /Objects/2:ServiceRegistry/2:query]"},
  {9, g_nStringIdDT, "T#250ms"},
  {10, g_nStringIdPV, "UINT#3"},
};

const SCFB_FBConnectionData FORTE_QueryServiceOpcUa::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdCNF), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdREQ), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdCNF), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdS), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdCNF), 4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdREQ), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdqueryServices, g_nStringIdquery), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdREQ), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdGetHTTPResult, g_nStringIdCNF), 5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdqueryServices, g_nStringIdqueried), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdEO), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdINIT), 6},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdEO), 3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdREQ), 6},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdINITO), 6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdEI), 3},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1, g_nStringIdEO0), 7, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY, g_nStringIdSTART), 9},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdCUO), 10, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1, g_nStringIdEI), 7},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdEO0), 8, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdCU), 10},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdEO1), 8, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdGetHTTPResult, g_nStringIdREQ), 5},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdCNF), 6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdEI), 8},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1, g_nStringIdEO1), 7, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdR), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY, g_nStringIdEO), 9, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdREQ), 6},
};

const SCFB_FBFannedOutConnectionData FORTE_QueryServiceOpcUa::scmFannedOutEventConnections[] = {
  {11, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdR), 2},
  {11, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdR), 10},
  {13, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdGetHTTPResult, g_nStringIdREQ), 5},
  {13, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdR), 10},
};

const SCFB_FBConnectionData FORTE_QueryServiceOpcUa::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdOUT), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdIN), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdQ), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdPERMIT), 3},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdqueryServices, g_nStringIdserviceQueryForm), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdinput), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdqueryServices, g_nStringIdendpoint), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdIN_2), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdGetHTTPResult, g_nStringIdoutput), 5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdqueryServices, g_nStringIdserviceEntries), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdOUT), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdID), 6},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdoutput), 4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdSD_1), 6},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdRD_1), 6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdGetHTTPResult, g_nStringIdresponse), 5},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdQ), 10, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1, g_nStringIdG), 7},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdQO), 6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdG), 8},
};

const SCFB_FBFannedOutConnectionData FORTE_QueryServiceOpcUa::scmFannedOutDataConnections[] = {
  {1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdQI), 6},
};

const SCFB_FBNData FORTE_QueryServiceOpcUa::scmFBNData = {
  11, scmInternalFBs,
  15, scmEventConnections,
  4, scmFannedOutEventConnections,
  10, scmDataConnections,
  1, scmFannedOutDataConnections,
  0, nullptr,
  4, scmParamters
};


