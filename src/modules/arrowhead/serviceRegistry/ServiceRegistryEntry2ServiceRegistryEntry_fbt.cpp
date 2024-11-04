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

#include "ServiceRegistryEntry2ServiceRegistryEntry_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ServiceRegistryEntry2ServiceRegistryEntry_fbt_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_ServiceRegistryEntry2ServiceRegistryEntry, g_nStringIdServiceRegistryEntry2ServiceRegistryEntry)

const CStringDictionary::TStringId FORTE_ServiceRegistryEntry2ServiceRegistryEntry::scmDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId FORTE_ServiceRegistryEntry2ServiceRegistryEntry::scmDataInputTypeIds[] = {g_nStringIdServiceRegistryEntry};

const CStringDictionary::TStringId FORTE_ServiceRegistryEntry2ServiceRegistryEntry::scmDataOutputNames[] = {g_nStringIdOUT};

const CStringDictionary::TStringId FORTE_ServiceRegistryEntry2ServiceRegistryEntry::scmDataOutputTypeIds[] = {g_nStringIdServiceRegistryEntry};

const TForteInt16 FORTE_ServiceRegistryEntry2ServiceRegistryEntry::scmEIWithIndexes[] = {0};
const TDataIOID FORTE_ServiceRegistryEntry2ServiceRegistryEntry::scmEIWith[] = {0, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_ServiceRegistryEntry2ServiceRegistryEntry::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_ServiceRegistryEntry2ServiceRegistryEntry::scmEventInputTypeIds[] = {g_nStringIdEvent};

const TDataIOID FORTE_ServiceRegistryEntry2ServiceRegistryEntry::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_ServiceRegistryEntry2ServiceRegistryEntry::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_ServiceRegistryEntry2ServiceRegistryEntry::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_ServiceRegistryEntry2ServiceRegistryEntry::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_ServiceRegistryEntry2ServiceRegistryEntry::scmFBInterfaceSpec = {
  1,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  1,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  1,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};


void FORTE_ServiceRegistryEntry2ServiceRegistryEntry::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  if(scmEventREQID == paEIID) {
    st_OUT() = st_IN();
    sendOutputEvent(scmEventCNFID, paECET);
  }
}



