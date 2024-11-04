/*******************************************************************************
 * Copyright (c) 2017, 2024 fortiss GmbH, Monika Wenger, Johannes Kepler University Linz
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Johannes Messmer - initial API and implementation and/or initial documentation
 *   Monika Wenger, Alois Zoitl - migration to current runtime
 *******************************************************************************/

#include "IORevPiBusAdapter.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "IORevPiBusAdapter_gen.cpp"
#endif

DEFINE_ADAPTER_TYPE(FORTE_IORevPiBusAdapter, g_nStringIdIORevPiBusAdapter)

const CStringDictionary::TStringId FORTE_IORevPiBusAdapter::scmDataInputNames[] = {g_nStringIdQO};
const CStringDictionary::TStringId FORTE_IORevPiBusAdapter::scmDataInputTypeIds[] = {g_nStringIdBOOL};
const CStringDictionary::TStringId FORTE_IORevPiBusAdapter::scmDataOutputNames[] = {g_nStringIdQI, g_nStringIdMasterId, g_nStringIdIndex};
const CStringDictionary::TStringId FORTE_IORevPiBusAdapter::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdUINT, g_nStringIdUINT};
const TDataIOID FORTE_IORevPiBusAdapter::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_IORevPiBusAdapter::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_IORevPiBusAdapter::scmEventInputNames[] = {g_nStringIdINITO};
const CStringDictionary::TStringId FORTE_IORevPiBusAdapter::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_IORevPiBusAdapter::scmEOWith[] = {2, 1, 0, scmWithListDelimiter};
const TForteInt16 FORTE_IORevPiBusAdapter::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_IORevPiBusAdapter::scmEventOutputNames[] = {g_nStringIdINIT};
const CStringDictionary::TStringId FORTE_IORevPiBusAdapter::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};

const SFBInterfaceSpec FORTE_IORevPiBusAdapter::scmFBInterfaceSpecSocket = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  3, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

const SFBInterfaceSpec FORTE_IORevPiBusAdapter::scmFBInterfaceSpecPlug = {
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  3, scmDataOutputNames, scmDataOutputTypeIds,
  1, scmDataInputNames, scmDataInputTypeIds,
  0, nullptr,
  0, nullptr
};

void FORTE_IORevPiBusAdapter::readInputData(const TEventID paEIID) {
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
        readData(1, *mDIs[1], mDIConns[1]);
        readData(0, *mDIs[0], mDIConns[0]);
        break;
      }
      default:
        break;
    }
  }
}

void FORTE_IORevPiBusAdapter::writeOutputData(const TEventID paEIID) {
  if(isSocket()) {
    switch(paEIID) {
      case scmEventINITID: {
        writeData(2, *mDOs[2], mDOConns[2]);
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

const TForteUInt8 FORTE_IORevPiBusAdapter::scmSlaveConfigurationIO[] = { };
const TForteUInt8 FORTE_IORevPiBusAdapter::scmSlaveConfigurationIONum = 0;
