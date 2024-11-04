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

#include "RequestOrchestrationForm.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RequestOrchestrationForm_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_RequestOrchestrationForm, g_nStringIdRequestOrchestrationForm)

const CStringDictionary::TStringId FORTE_RequestOrchestrationForm::scmDataInputNames[] = {g_nStringIdserviceRequestForm, g_nStringIdendpoint};

const CStringDictionary::TStringId FORTE_RequestOrchestrationForm::scmDataInputTypeIds[] = {g_nStringIdServiceRequestForm, g_nStringIdWSTRING};

const CStringDictionary::TStringId FORTE_RequestOrchestrationForm::scmDataOutputNames[] = {g_nStringIdorchestrationResponse};

const CStringDictionary::TStringId FORTE_RequestOrchestrationForm::scmDataOutputTypeIds[] = {g_nStringIdARRAY, 10, g_nStringIdOrchestrationForm};

const TForteInt16 FORTE_RequestOrchestrationForm::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_RequestOrchestrationForm::scmEIWith[] = {0, 1, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_RequestOrchestrationForm::scmEventInputNames[] = {g_nStringIdrequestOrchestator};
const CStringDictionary::TStringId FORTE_RequestOrchestrationForm::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_RequestOrchestrationForm::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_RequestOrchestrationForm::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_RequestOrchestrationForm::scmEventOutputNames[] = {g_nStringIdresponseReceived};
const CStringDictionary::TStringId FORTE_RequestOrchestrationForm::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SAdapterInstanceDef FORTE_RequestOrchestrationForm::scmAdapterInstances[] = {
{g_nStringIdOrchestratorRequestAdp, g_nStringIdrequestOrchestration, true }};

const SFBInterfaceSpec FORTE_RequestOrchestrationForm::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  2,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  1,scmAdapterInstances};


const SCFB_FBConnectionData FORTE_RequestOrchestrationForm::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdrequestOrchestator), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdrequestOrchestration, g_nStringIdrequestOrchestator), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdrequestOrchestration, g_nStringIdresponseReceived), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdresponseReceived), -1},
};

const SCFB_FBConnectionData FORTE_RequestOrchestrationForm::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdserviceRequestForm), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdrequestOrchestration, g_nStringIdserviceRequestForm), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdrequestOrchestration, g_nStringIdorchestrationResponse), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdorchestrationResponse), -1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdendpoint), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdrequestOrchestration, g_nStringIdendpoint), CCompositeFB::scmAdapterMarker |0},
};

const SCFB_FBNData FORTE_RequestOrchestrationForm::scmFBNData = {
  0, 0,
  2, scmEventConnections,
  0, 0,
  3, scmDataConnections,
  0, 0,
  0, nullptr,
  0, 0
};


