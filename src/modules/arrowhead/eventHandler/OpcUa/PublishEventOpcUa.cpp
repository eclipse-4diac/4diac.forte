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

#include "PublishEventOpcUa.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "PublishEventOpcUa_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_PublishEventOpcUa, g_nStringIdPublishEventOpcUa)

const TForteInt16 FORTE_PublishEventOpcUa::scmEOWithIndexes[] = {-1};
const SAdapterInstanceDef FORTE_PublishEventOpcUa::scmAdapterInstances[] = {
{g_nStringIdArrowheadPublishAdp, g_nStringIdpublishEvent, false }};

const SFBInterfaceSpec FORTE_PublishEventOpcUa::scmFBInterfaceSpec = {
  0,  0, nullptr,  0,  0,
  0,  0, nullptr,   0, 0,  0,  0, 0, 
  0,  0, 0,
  1,scmAdapterInstances};


const SCFB_FBInstanceData FORTE_PublishEventOpcUa::scmInternalFBs[] = {
  {g_nStringIdANYToJSON, g_nStringIdANYToJSON},
  {g_nStringIdInitFlag, g_nStringIdE_SR},
  {g_nStringIdAPPEND_STRING_3, g_nStringIdAPPEND_STRING_3},
  {g_nStringIdF_STRING_TO_WSTRING, g_nStringIdF_STRING_TO_WSTRING},
  {g_nStringIdE_PERMIT, g_nStringIdE_PERMIT},
  {g_nStringIdE_SWITCH_2, g_nStringIdE_SWITCH},
  {g_nStringIdE_SWITCH_1_1, g_nStringIdE_SWITCH},
  {g_nStringIdE_CTU_1, g_nStringIdE_CTU},
  {g_nStringIdE_DELAY_1, g_nStringIdE_DELAY},
  {g_nStringIdQuery, g_nStringIdCLIENT_1_0},
};

const SCFB_FBParameter FORTE_PublishEventOpcUa::scmParamters[] = {
  {2, g_nStringIdIN_1, "STRING#opc_ua[CALL_METHOD; "},
  {2, g_nStringIdIN_3, "STRING##; /Objects/2:EventHandler/2:publish]"},
  {7, g_nStringIdPV, "UINT#3"},
  {8, g_nStringIdDT, "T#250ms"},
};

const SCFB_FBConnectionData FORTE_PublishEventOpcUa::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdCNF), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdREQ), 3},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdCNF), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdREQ), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdCNF), 3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdS), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdpublishEvent, g_nStringIdpublish), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdREQ), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_2, g_nStringIdEO1), 5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU_1, g_nStringIdR), 7},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1_1, g_nStringIdEO1), 6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU_1, g_nStringIdR), 7},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_2, g_nStringIdEO0), 5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU_1, g_nStringIdCU), 7},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU_1, g_nStringIdCUO), 7, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1_1, g_nStringIdEI), 6},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1_1, g_nStringIdEO0), 6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY_1, g_nStringIdSTART), 8},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdEO), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdINIT), 9},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdEO), 4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdREQ), 9},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY_1, g_nStringIdEO), 8, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdREQ), 9},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdINITO), 9, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdEI), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdCNF), 9, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_2, g_nStringIdEI), 5},
};

const SCFB_FBFannedOutConnectionData FORTE_PublishEventOpcUa::scmFannedOutEventConnections[] = {
  {4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdpublishEvent, g_nStringIdpublished), CCompositeFB::scmAdapterMarker |0},
  {4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdR), 1},
  {5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdR), 1},
  {5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdpublishEvent, g_nStringIdpublished), CCompositeFB::scmAdapterMarker |0},
};

const SCFB_FBConnectionData FORTE_PublishEventOpcUa::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdOUT), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdIN), 3},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdQ), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdPERMIT), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdpublishEvent, g_nStringIdpublishEvent), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdinput), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdpublishEvent, g_nStringIdendpoint), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdIN_2), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU_1, g_nStringIdQ), 7, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1_1, g_nStringIdG), 6},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdOUT), 3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdID), 9},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdoutput), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdSD_1), 9},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdQO), 9, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_2, g_nStringIdG), 5},
};

const SCFB_FBFannedOutConnectionData FORTE_PublishEventOpcUa::scmFannedOutDataConnections[] = {
  {1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdQI), 9},
};

const SCFB_FBNData FORTE_PublishEventOpcUa::scmFBNData = {
  10, scmInternalFBs,
  14, scmEventConnections,
  4, scmFannedOutEventConnections,
  8, scmDataConnections,
  1, scmFannedOutDataConnections,
  0, nullptr,
  4, scmParamters
};


