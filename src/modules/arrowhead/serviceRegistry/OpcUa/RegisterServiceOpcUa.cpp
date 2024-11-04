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

#include "RegisterServiceOpcUa.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RegisterServiceOpcUa_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_RegisterServiceOpcUa, g_nStringIdRegisterServiceOpcUa)

const TForteInt16 FORTE_RegisterServiceOpcUa::scmEOWithIndexes[] = {-1};
const SAdapterInstanceDef FORTE_RegisterServiceOpcUa::scmAdapterInstances[] = {
{g_nStringIdRegisterServiceAdp, g_nStringIdregisterService, false }};

const SFBInterfaceSpec FORTE_RegisterServiceOpcUa::scmFBInterfaceSpec = {
  0,  0, nullptr,  0,  0,
  0,  0, nullptr,   0, 0,  0,  0, 0, 
  0,  0, 0,
  1,scmAdapterInstances};


const SCFB_FBInstanceData FORTE_RegisterServiceOpcUa::scmInternalFBs[] = {
  {g_nStringIdInitFlagReg, g_nStringIdE_SR},
  {g_nStringIdE_PERMIT, g_nStringIdE_PERMIT},
  {g_nStringIdCreateRegisterID, g_nStringIdAPPEND_STRING_3},
  {g_nStringIdF_STRING_TO_WSTRING, g_nStringIdF_STRING_TO_WSTRING},
  {g_nStringIdE_PERMIT_1, g_nStringIdE_PERMIT},
  {g_nStringIdInitFlagUnReg, g_nStringIdE_SR},
  {g_nStringIdCreateUnRegisterID, g_nStringIdAPPEND_STRING_3},
  {g_nStringIdF_STRING_TO_WSTRING_1, g_nStringIdF_STRING_TO_WSTRING},
  {g_nStringIdANYToJSON, g_nStringIdANYToJSON},
  {g_nStringIdRegister, g_nStringIdCLIENT_1_0},
  {g_nStringIdUnregister, g_nStringIdCLIENT_1_0},
  {g_nStringIdE_SWITCH, g_nStringIdE_SWITCH},
  {g_nStringIdE_SWITCH_1, g_nStringIdE_SWITCH},
  {g_nStringIdE_DELAY, g_nStringIdE_DELAY},
  {g_nStringIdE_CTU, g_nStringIdE_CTU},
  {g_nStringIdE_SWITCH_1_1, g_nStringIdE_SWITCH},
  {g_nStringIdE_SWITCH_2, g_nStringIdE_SWITCH},
  {g_nStringIdE_DELAY_1, g_nStringIdE_DELAY},
  {g_nStringIdE_CTU_1, g_nStringIdE_CTU},
};

const SCFB_FBParameter FORTE_RegisterServiceOpcUa::scmParamters[] = {
  {2, g_nStringIdIN_1, "STRING#opc_ua[CALL_METHOD; "},
  {2, g_nStringIdIN_3, "STRING##; /Objects/2:ServiceRegistry/2:register]"},
  {6, g_nStringIdIN_1, "STRING#opc_ua[CALL_METHOD; "},
  {6, g_nStringIdIN_3, "STRING##; /Objects/2:ServiceRegistry/2:remove]"},
  {13, g_nStringIdDT, "T#250ms"},
  {14, g_nStringIdPV, "UINT#3"},
  {17, g_nStringIdDT, "T#250ms"},
  {18, g_nStringIdPV, "UINT#3"},
};

const SCFB_FBConnectionData FORTE_RegisterServiceOpcUa::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID, g_nStringIdCNF), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdREQ), 3},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdCNF), 3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagReg, g_nStringIdS), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateUnRegisterID, g_nStringIdCNF), 6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING_1, g_nStringIdREQ), 7},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING_1, g_nStringIdCNF), 7, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagUnReg, g_nStringIdS), 5},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIdregisterService), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID, g_nStringIdREQ), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIdunregisterService), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateUnRegisterID, g_nStringIdREQ), 6},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagReg, g_nStringIdEO), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdINIT), 9},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdEO), 1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdREQ), 9},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdINITO), 9, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdEI), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagUnReg, g_nStringIdEO), 5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdINIT), 10},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT_1, g_nStringIdEO), 4, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdREQ), 10},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdINITO), 10, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT_1, g_nStringIdEI), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdCUO), 14, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1, g_nStringIdEI), 12},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1, g_nStringIdEO0), 12, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY, g_nStringIdSTART), 13},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdEO0), 11, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdCU), 14},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdEO1), 11, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagReg, g_nStringIdR), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdCNF), 9, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdEI), 11},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY, g_nStringIdEO), 13, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdREQ), 9},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1_1, g_nStringIdEO0), 15, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY_1, g_nStringIdSTART), 17},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU_1, g_nStringIdCUO), 18, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1_1, g_nStringIdEI), 15},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_2, g_nStringIdEO0), 16, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU_1, g_nStringIdCU), 18},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_2, g_nStringIdEO1), 16, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagUnReg, g_nStringIdR), 5},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdCNF), 10, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_2, g_nStringIdEI), 16},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_DELAY_1, g_nStringIdEO), 17, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdREQ), 10},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1_1, g_nStringIdEO1), 15, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagUnReg, g_nStringIdR), 5},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1, g_nStringIdEO1), 12, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagReg, g_nStringIdR), 0},
};

const SCFB_FBFannedOutConnectionData FORTE_RegisterServiceOpcUa::scmFannedOutEventConnections[] = {
  {1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdREQ), 8},
  {3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdREQ), 8},
  {15, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIddoneRegister), CCompositeFB::scmAdapterMarker |0},
  {15, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdR), 14},
  {21, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIddoneUnregister), CCompositeFB::scmAdapterMarker |0},
  {21, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU_1, g_nStringIdR), 18},
  {24, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIddoneUnregister), CCompositeFB::scmAdapterMarker |0},
  {24, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU_1, g_nStringIdR), 18},
  {25, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIddoneRegister), CCompositeFB::scmAdapterMarker |0},
  {25, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdR), 14},
};

const SCFB_FBConnectionData FORTE_RegisterServiceOpcUa::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagReg, g_nStringIdQ), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT, g_nStringIdPERMIT), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID, g_nStringIdOUT), 2, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdIN), 3},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateUnRegisterID, g_nStringIdOUT), 6, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING_1, g_nStringIdIN), 7},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdInitFlagUnReg, g_nStringIdQ), 5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_PERMIT_1, g_nStringIdPERMIT), 4},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIdserviceRegistryEntry), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdinput), 8},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIdendpoint), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateRegisterID, g_nStringIdIN_2), 2},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING, g_nStringIdOUT), 3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdID), 9},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdANYToJSON, g_nStringIdoutput), 8, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdSD_1), 9},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdF_STRING_TO_WSTRING_1, g_nStringIdOUT), 7, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdID), 10},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU, g_nStringIdQ), 14, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1, g_nStringIdG), 12},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdQO), 9, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH, g_nStringIdG), 11},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CTU_1, g_nStringIdQ), 18, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_1_1, g_nStringIdG), 15},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdQO), 10, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_SWITCH_2, g_nStringIdG), 16},
};

const SCFB_FBFannedOutConnectionData FORTE_RegisterServiceOpcUa::scmFannedOutDataConnections[] = {
  {0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdRegister, g_nStringIdQI), 9},
  {3, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdQI), 10},
  {5, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdCreateUnRegisterID, g_nStringIdIN_2), 6},
  {7, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdUnregister, g_nStringIdSD_1), 10},
};

const SCFB_FBNData FORTE_RegisterServiceOpcUa::scmFBNData = {
  19, scmInternalFBs,
  26, scmEventConnections,
  10, scmFannedOutEventConnections,
  13, scmDataConnections,
  4, scmFannedOutDataConnections,
  0, nullptr,
  8, scmParamters
};


