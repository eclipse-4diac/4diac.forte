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

#include "ArrowheadPublishAdp_adp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ArrowheadPublishAdp_adp_gen.cpp"
#endif

DEFINE_ADAPTER_TYPE(FORTE_ArrowheadPublishAdp, g_nStringIdArrowheadPublishAdp)

const CStringDictionary::TStringId FORTE_ArrowheadPublishAdp::scmDataOutputNames[] = {g_nStringIdpublishEvent, g_nStringIdendpoint};

const CStringDictionary::TStringId FORTE_ArrowheadPublishAdp::scmDataOutputTypeIds[] = {g_nStringIdPublishEvent, g_nStringIdWSTRING};

const TForteInt16 FORTE_ArrowheadPublishAdp::scmEIWithIndexes[] = {-1, -1};
const CStringDictionary::TStringId FORTE_ArrowheadPublishAdp::scmEventInputNames[] = {g_nStringIdpublished};

const TDataIOID FORTE_ArrowheadPublishAdp::scmEOWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_ArrowheadPublishAdp::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_ArrowheadPublishAdp::scmEventOutputNames[] = {g_nStringIdpublish};

const SFBInterfaceSpec FORTE_ArrowheadPublishAdp::scmFBInterfaceSpecSocket = {
  1,  scmEventInputNames, scmEventInputTypeIds, 0,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmDataOutputTypeIds, scmEOWith, scmEOWithIndexes,  0,  0, 0,
  2,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};

const SFBInterfaceSpec FORTE_ArrowheadPublishAdp::scmFBInterfaceSpecPlug = {
  1,  scmEventOutputNames, scmDataOutputTypeIds,  scmEOWith,  scmEOWithIndexes,
  1,  scmEventInputNames, scmEventInputTypeIds, 0, 0,  2,  scmDataOutputNames, scmDataOutputTypeIds,
  0,  0, 0,
  0, 0
};



