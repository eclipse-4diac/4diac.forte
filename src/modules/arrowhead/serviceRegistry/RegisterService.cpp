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

#include "RegisterService.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RegisterService_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_RegisterService, g_nStringIdRegisterService)

const CStringDictionary::TStringId FORTE_RegisterService::scmDataInputNames[] = {g_nStringIdserviceRegistryEntry, g_nStringIdendpoint};

const CStringDictionary::TStringId FORTE_RegisterService::scmDataInputTypeIds[] = {g_nStringIdServiceRegistryEntry, g_nStringIdWSTRING};

const TForteInt16 FORTE_RegisterService::scmEIWithIndexes[] = {0, 3};
const TDataIOID FORTE_RegisterService::scmEIWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_RegisterService::scmEventInputNames[] = {g_nStringIdregister, g_nStringIdunregister};
const CStringDictionary::TStringId FORTE_RegisterService::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};

const TForteInt16 FORTE_RegisterService::scmEOWithIndexes[] = {-1, -1, -1};
const CStringDictionary::TStringId FORTE_RegisterService::scmEventOutputNames[] = {g_nStringIddoneRegister, g_nStringIddoneUnregister};
const CStringDictionary::TStringId FORTE_RegisterService::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};

const SAdapterInstanceDef FORTE_RegisterService::scmAdapterInstances[] = {
{g_nStringIdRegisterServiceAdp, g_nStringIdregisterService, true }};

const SFBInterfaceSpec FORTE_RegisterService::scmFBInterfaceSpec = {
  2,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  2,  scmEventOutputNames, scmEventOutputTypeIds,  0, 0,  2,  scmDataInputNames, scmDataInputTypeIds,
  0,  0, 0,
  1,scmAdapterInstances};


const SCFB_FBConnectionData FORTE_RegisterService::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdregister), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIdregisterService), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdunregister), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIdunregisterService), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIddoneRegister), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIddoneRegister), -1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIddoneUnregister), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIddoneUnregister), -1},
};

const SCFB_FBConnectionData FORTE_RegisterService::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdserviceRegistryEntry), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIdserviceRegistryEntry), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdendpoint), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdregisterService, g_nStringIdendpoint), CCompositeFB::scmAdapterMarker |0},
};

const SCFB_FBNData FORTE_RegisterService::scmFBNData = {
  0, 0,
  4, scmEventConnections,
  0, 0,
  2, scmDataConnections,
  0, 0,
  0, nullptr,
  0, 0
};


