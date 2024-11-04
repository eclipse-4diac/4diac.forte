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

#include "QueryService.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "QueryService_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_QueryService, g_nStringIdQueryService)

const CStringDictionary::TStringId FORTE_QueryService::scmDataInputNames[] = {g_nStringIdserviceQueryForm, g_nStringIdaddress};

const CStringDictionary::TStringId FORTE_QueryService::scmDataInputTypeIds[] = {g_nStringIdServiceQueryForm, g_nStringIdWSTRING};

const CStringDictionary::TStringId FORTE_QueryService::scmDataOutputNames[] = {g_nStringIdserviceEntries};

const CStringDictionary::TStringId FORTE_QueryService::scmDataOutputTypeIds[] = {g_nStringIdARRAY, 10, g_nStringIdServiceRegistryEntry};

const TForteInt16 FORTE_QueryService::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_QueryService::scmEIWith[] = {0, 1, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_QueryService::scmEventInputNames[] = {g_nStringIdquery};
const CStringDictionary::TStringId FORTE_QueryService::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_QueryService::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_QueryService::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_QueryService::scmEventOutputNames[] = {g_nStringIdqueried};
const CStringDictionary::TStringId FORTE_QueryService::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SAdapterInstanceDef FORTE_QueryService::scmAdapterInstances[] = {
{g_nStringIdQueryServicesAdp, g_nStringIdqueryServices, true }};

const SFBInterfaceSpec FORTE_QueryService::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  2,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  1,scmAdapterInstances};


const SCFB_FBConnectionData FORTE_QueryService::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdquery), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdqueryServices, g_nStringIdquery), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdqueryServices, g_nStringIdqueried), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdqueried), -1},
};

const SCFB_FBConnectionData FORTE_QueryService::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdserviceQueryForm), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdqueryServices, g_nStringIdserviceQueryForm), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdqueryServices, g_nStringIdserviceEntries), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdserviceEntries), -1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdaddress), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdqueryServices, g_nStringIdendpoint), CCompositeFB::scmAdapterMarker |0},
};

const SCFB_FBNData FORTE_QueryService::scmFBNData = {
  0, 0,
  2, scmEventConnections,
  0, 0,
  3, scmDataConnections,
  0, 0,
  0, nullptr,
  0, 0
};


