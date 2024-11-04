/*******************************************************************************
 * Copyright (c) 2013 fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "ATimeOut_adp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ATimeOut_adp_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_ADAPTER_TYPE(FORTE_ATimeOut, g_nStringIdATimeOut)

const CStringDictionary::TStringId FORTE_ATimeOut::scmDataOutputNames[] = {g_nStringIdDT};
const CStringDictionary::TStringId FORTE_ATimeOut::scmDataOutputTypeIds[] = {g_nStringIdTIME};
const TForteInt16 FORTE_ATimeOut::scmEIWithIndexes[] = {-1};
const CStringDictionary::TStringId FORTE_ATimeOut::scmEventInputNames[] = {g_nStringIdTimeOut};
const CStringDictionary::TStringId FORTE_ATimeOut::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_ATimeOut::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_ATimeOut::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_ATimeOut::scmEventOutputNames[] = {g_nStringIdSTART, g_nStringIdSTOP};
const CStringDictionary::TStringId FORTE_ATimeOut::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};

const SFBInterfaceSpec FORTE_ATimeOut::scmFBInterfaceSpecSocket = {
  1, scmEventInputNames,scmEventInputTypeIds,nullptr, scmEIWithIndexes,
  2, scmEventOutputNames, scmEventOutputTypeIds,scmEOWith, scmEOWithIndexes,
  0, nullptr, nullptr,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

const SFBInterfaceSpec FORTE_ATimeOut::scmFBInterfaceSpecPlug = {
  2, scmEventOutputNames, scmEventOutputTypeIds,scmEOWith, scmEOWithIndexes,
  1, scmEventInputNames, scmEventInputTypeIds,nullptr, scmEIWithIndexes,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

void FORTE_ATimeOut::readInputData(const TEventID paEIID) {
  if(isSocket()) {
    // nothing to do
  } else {
    switch(paEIID) {
      case scmEventSTARTID: {
          readData(0, *mDIs[0], mDIConns[0]);
        break;
      }
      default:
        break;
    }
  }
}

void FORTE_ATimeOut::writeOutputData(const TEventID paEIID) {
  if(isSocket()) {
    switch(paEIID) {
      case scmEventSTARTID: {
          writeData(0, *mDOs[0], mDOConns[0]);
        break;
      }
      default:
        break;
    }
  } else {
    // nothing to do
  }
}
