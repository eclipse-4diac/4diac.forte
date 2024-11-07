/*******************************************************************************
 * Copyright (c) 2022 Peirlberger Juergen
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Peirlberger Juergen - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "PLCnextBusAdapter.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "PLCnextBusAdapter_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_ADAPTER_TYPE(FORTE_PLCnextBusAdapter, g_nStringIdPLCnextBusAdapter)

const CStringDictionary::TStringId FORTE_PLCnextBusAdapter::scmDataInputNames[] = {g_nStringIdQO};
const CStringDictionary::TStringId FORTE_PLCnextBusAdapter::scmDataInputTypeIds[] = {g_nStringIdBOOL};
const CStringDictionary::TStringId FORTE_PLCnextBusAdapter::scmDataOutputNames[] = {g_nStringIdQI, g_nStringIdMasterId, g_nStringIdIndex, g_nStringIdUpdateInterval};
const CStringDictionary::TStringId FORTE_PLCnextBusAdapter::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdUINT, g_nStringIdUINT, g_nStringIdUINT};
const TDataIOID FORTE_PLCnextBusAdapter::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_PLCnextBusAdapter::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_PLCnextBusAdapter::scmEventInputNames[] = {g_nStringIdINITO};
const CStringDictionary::TStringId FORTE_PLCnextBusAdapter::scmEventInputTypeIds[] = {g_nStringIdEInit};
const TDataIOID FORTE_PLCnextBusAdapter::scmEOWith[] = {2, 3, 1, 0, scmWithListDelimiter};
const TForteInt16 FORTE_PLCnextBusAdapter::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_PLCnextBusAdapter::scmEventOutputNames[] = {g_nStringIdINIT};
const CStringDictionary::TStringId FORTE_PLCnextBusAdapter::scmEventOutputTypeIds[] = {g_nStringIdEvent};

const SFBInterfaceSpec FORTE_PLCnextBusAdapter::scmFBInterfaceSpecSocket = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  4, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr
};

const SFBInterfaceSpec FORTE_PLCnextBusAdapter::scmFBInterfaceSpecPlug = {
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  4, scmDataOutputNames, scmDataOutputTypeIds,
  1, scmDataInputNames, scmDataInputTypeIds,
  0, nullptr
};

void FORTE_PLCnextBusAdapter::readInputData(const TEventID paEIID) {
  if(isSocket()) {
    switch(paEIID) {
      case scmEventINITOID: {
          readData(0, *mDIs[0], mDIConns[0]);
        break;
      }
      default:
        break;
    }
  } else {
    switch(paEIID) {
      case scmEventINITID: {
          readData(2, *mDIs[2], mDIConns[2]);
        readData(3, *mDIs[3], mDIConns[3]);
        readData(1, *mDIs[1], mDIConns[1]);
        readData(0, *mDIs[0], mDIConns[0]);
        break;
      }
      default:
        break;
    }
  }
}

void FORTE_PLCnextBusAdapter::writeOutputData(const TEventID paEIID) {
  if(isSocket()) {
    switch(paEIID) {
      case scmEventINITID: {
          writeData(2, *mDOs[2], mDOConns[2]);
        writeData(3, *mDOs[3], mDOConns[3]);
        writeData(1, *mDOs[1], mDOConns[1]);
        writeData(0, *mDOs[0], mDOConns[0]);
        break;
      }
      default:
        break;
    }
  } else {
    switch(paEIID) {
      case scmEventINITOID: {
          writeData(0, *mDOs[0], mDOConns[0]);
        break;
      }
      default:
        break;
    }
  }
}
