/*******************************************************************************
 * Copyright (c) 2014 fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "ARTimeOut_adp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ARTimeOut_adp_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_ADAPTER_TYPE(FORTE_ARTimeOut, g_nStringIdARTimeOut)

const CStringDictionary::TStringId FORTE_ARTimeOut::scmDataOutputNames[] = {g_nStringIdDT};
const CStringDictionary::TStringId FORTE_ARTimeOut::scmDataOutputTypeIds[] = {g_nStringIdTIME};
const TForteInt16 FORTE_ARTimeOut::scmEIWithIndexes[] = {-1};
const CStringDictionary::TStringId FORTE_ARTimeOut::scmEventInputNames[] = {g_nStringIdTimeOut};
const CStringDictionary::TStringId FORTE_ARTimeOut::scmEventInputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};
const TDataIOID FORTE_ARTimeOut::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_ARTimeOut::scmEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_ARTimeOut::scmEventOutputNames[] = {g_nStringIdSTART, g_nStringIdSTOP};
const CStringDictionary::TStringId FORTE_ARTimeOut::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};

const SFBInterfaceSpec FORTE_ARTimeOut::scmFBInterfaceSpecSocket = {
  1, scmEventInputNames, scmEventInputTypeIds, nullptr, scmEIWithIndexes,
  2, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  0, nullptr, nullptr,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

const SFBInterfaceSpec FORTE_ARTimeOut::scmFBInterfaceSpecPlug = {
  2, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmEventInputNames, scmEventInputTypeIds, nullptr, scmEIWithIndexes,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

void FORTE_ARTimeOut::readInputData(const TEventID paEIID) {
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

void FORTE_ARTimeOut::writeOutputData(const TEventID paEIID) {
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
