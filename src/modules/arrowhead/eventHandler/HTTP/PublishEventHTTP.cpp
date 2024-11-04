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

#include "PublishEventHTTP.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "PublishEventHTTP_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_PublishEventHTTP, g_nStringIdPublishEventHTTP)

const TForteInt16 FORTE_PublishEventHTTP::scmEOWithIndexes[] = {-1};
const SAdapterInstanceDef FORTE_PublishEventHTTP::scmAdapterInstances[] = {
{g_nStringIdArrowheadPublishAdp, g_nStringIdpublishEvent, false }};

const SFBInterfaceSpec FORTE_PublishEventHTTP::scmFBInterfaceSpec = {
  0,  0, nullptr,  0,  0,
  0,  0, nullptr,   0, 0,  0,  0, 0, 
  0,  0, 0,
  1,scmAdapterInstances};


const SCFB_FBInstanceData FORTE_PublishEventHTTP::scmInternalFBs[] = {
  {g_nStringIdANYToJSON, g_nStringIdANYToJSON},
  {g_nStringIdInitFlag, g_nStringIdE_SR},
  {g_nStringIdAPPEND_STRING_3, g_nStringIdAPPEND_STRING_3},
  {g_nStringIdF_STRING_TO_WSTRING, g_nStringIdF_STRING_TO_WSTRING},
  {g_nStringIdQuery, g_nStringIdCLIENT_1_2},
  {g_nStringIdE_PERMIT, g_nStringIdE_PERMIT},
};

const SCFB_FBParameter FORTE_PublishEventHTTP::scmParamters[] = {
  {2, g_nStringIdIN_1, "STRING#http["},
  {2, g_nStringIdIN_3, "STRING#/publish; POST; application/json]"},
};

const SCFB_FBConnectionData FORTE_PublishEventHTTP::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdEO), 5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdREQ), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdCNF), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdREQ), 3},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdEO), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdINIT), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdCNF), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdREQ), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdCNF), 3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdS), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdINITO), 4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdEI), 5},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdCNF), 4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdR), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdpublishEvent, g_nStringIdpublish), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdREQ), 0},
};

const SCFB_FBFannedOutConnectionData FORTE_PublishEventHTTP::scmFannedOutEventConnections[] = {
  {6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdpublishEvent, g_nStringIdpublished), CCompositeFB::scmAdapterMarker |0},
};

const SCFB_FBConnectionData FORTE_PublishEventHTTP::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdoutput), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdSD_1), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlag, g_nStringIdQ), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdQI), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdOUT), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdIN), 3},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdOUT), 3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdQuery, g_nStringIdID), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdpublishEvent, g_nStringIdpublishEvent), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdinput), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdpublishEvent, g_nStringIdendpoint), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAPPEND_STRING_3, g_nStringIdIN_2), 2},
};

const SCFB_FBFannedOutConnectionData FORTE_PublishEventHTTP::scmFannedOutDataConnections[] = {
  {1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdPERMIT), 5},
};

const SCFB_FBNData FORTE_PublishEventHTTP::scmFBNData = {
  6, scmInternalFBs,
  8, scmEventConnections,
  1, scmFannedOutEventConnections,
  6, scmDataConnections,
  1, scmFannedOutDataConnections,
  0, nullptr,
  2, scmParamters
};


