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

#include "ArrowheadPublish.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ArrowheadPublish_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_ArrowheadPublish, g_nStringIdArrowheadPublish)

const CStringDictionary::TStringId FORTE_ArrowheadPublish::scmDataInputNames[] = {g_nStringIdpublishEvent, g_nStringIdendpoint};

const CStringDictionary::TStringId FORTE_ArrowheadPublish::scmDataInputTypeIds[] = {g_nStringIdPublishEvent, g_nStringIdWSTRING};

const TForteInt16 FORTE_ArrowheadPublish::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_ArrowheadPublish::scmEIWith[] = {0, 1, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_ArrowheadPublish::scmEventInputNames[] = {g_nStringIdpublish};
const CStringDictionary::TStringId FORTE_ArrowheadPublish::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TForteInt16 FORTE_ArrowheadPublish::scmEOWithIndexes[] = {-1, -1};
const CStringDictionary::TStringId FORTE_ArrowheadPublish::scmEventOutputNames[] = {g_nStringIdpublished};
const CStringDictionary::TStringId FORTE_ArrowheadPublish::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SAdapterInstanceDef FORTE_ArrowheadPublish::scmAdapterInstances[] = {
{g_nStringIdArrowheadPublishAdp, g_nStringIdArrowheadPublishAdp, true }};

const SFBInterfaceSpec FORTE_ArrowheadPublish::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  0, 0,  2,  scmDataInputNames, scmDataInputTypeIds,
  0,  0, 0,
  1,scmAdapterInstances};


const SCFB_FBConnectionData FORTE_ArrowheadPublish::scmEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdpublish), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdArrowheadPublishAdp, g_nStringIdpublish), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdArrowheadPublishAdp, g_nStringIdpublished), CCompositeFB::scmAdapterMarker |0, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdpublished), -1},
};

const SCFB_FBConnectionData FORTE_ArrowheadPublish::scmDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdpublishEvent), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdArrowheadPublishAdp, g_nStringIdpublishEvent), CCompositeFB::scmAdapterMarker |0},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdendpoint), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdArrowheadPublishAdp, g_nStringIdendpoint), CCompositeFB::scmAdapterMarker |0},
};

const SCFB_FBNData FORTE_ArrowheadPublish::scmFBNData = {
  0, 0,
  2, scmEventConnections,
  0, 0,
  2, scmDataConnections,
  0, 0,
  0, nullptr,
  0, 0
};


