/*******************************************************************************
 * Copyright (c) 2006, 2023 ACIN, Profactor GmbH, fortiss GmbH
 *                          Johannes Kepler University
 *                          Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Rene Smodic, Alois Zoitl, Michael Hofmann, Martin Melik Merkumians,
 *    Patrick Smejkal
 *      - initial implementation and rework communication infrastructure
 *    Alois Zoitl - introduced new CGenFB class for better handling generic FBs
 *    Martin Jobst - add generic readInputData and writeOutputData
 *******************************************************************************/
#include <fortenew.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "commfb.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "commfb_gen.cpp"
#endif
#include "../resource.h"
#include "comlayer.h"
#include "comlayersmanager.h"
#include "criticalregion.h"

using namespace forte::com_infra;

CCommFB::CCommFB(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer, forte::com_infra::EComServiceType paCommServiceType) :
  CBaseCommFB(paInstanceNameId, paContainer, paCommServiceType) {
}

CCommFB::~CCommFB() = default;

EMGMResponse CCommFB::changeExecutionState(EMGMCommandType paCommand) {
  EMGMResponse retVal = CEventSourceFB::changeExecutionState(paCommand);
  if ((EMGMResponse::Ready == retVal) && (EMGMCommandType::Kill == paCommand)) {
    //when we are killed we'll close the connection so that it can safely be opened again after an reset
    closeConnection();
  }
  return retVal;
}

void CCommFB::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  EComResponse resp = e_Nothing;

  switch (paEIID) {
  case scmEventINITID:
    if (true == QI()) {
      resp = openConnection();
    }
    else {
      closeConnection();
      resp = e_InitTerminated;
    }
    break;
  case scmSendNotificationEventID:
    resp = sendData();
    break;
  case cgExternalEventID:
    resp = receiveData();
    break;
  default:
    break;
  }

  if(resp & e_Terminated) {
    if(mCommServiceType == e_Server && scmEventINITID != paEIID) { //if e_Terminated happened in INIT event, server shouldn't be silent
      //servers will not send information on client termination and should silently start to listen again
      resp = e_Nothing;
    } else {
      //subscribers and clients will close the connection and inform the user
      closeConnection();
    }
  }

  if (e_Nothing != resp) {
    STATUS() = CIEC_WSTRING(scmResponseTexts[resp & 0xF]);
    QO() = CIEC_BOOL(!(resp & scg_unComNegative));

    if (scg_unINIT & resp) {
      sendOutputEvent(scmEventINITOID, paECET);
    }
    else {
      sendOutputEvent(scmReceiveNotificationEventID, paECET);
    }
  }
}

void CCommFB::readInputData(TEventID paEI) {
  switch(paEI) {
    case scmEventINITID: {
      readData(0, *mDIs[0], mDIConns[0]);
      readData(1, *mDIs[1], mDIConns[1]);
      break;
    }
    case scmSendNotificationEventID: {
      for(TPortId i = 0; i < getFBInterfaceSpec().mNumDIs; ++i) {
        readData(i, *mDIs[i], mDIConns[i]);
      }
      break;
    }
    default:
      break;
  }
}

void CCommFB::writeOutputData(TEventID paEO) {
  switch(paEO) {
    case scmEventINITOID: {
      writeData(0, *mDOs[0], mDOConns[0]);
      writeData(1, *mDOs[1], mDOConns[1]);
      break;
    }
    case scmReceiveNotificationEventID: {
      CCriticalRegion lock(getFBLock());
      for(TPortId i = 0; i < getFBInterfaceSpec().mNumDOs; ++i) {
        writeData(i, *mDOs[i], mDOConns[i]);
      }
      break;
    }
    default:
      break;
  }
}

EComResponse CCommFB::sendData() {
  EComResponse resp = e_Nothing;
  if (true == QI()) {
    if (mCommServiceType != e_Subscriber) {
      if (nullptr != mTopOfComStack) {
        resp = mTopOfComStack->sendData(static_cast<void*>(getSDs()), static_cast<unsigned int>(getFBInterfaceSpec().mNumDIs - 2));
        if ((resp == e_ProcessDataOk) && (mCommServiceType != e_Publisher)) {
          // client and server will not directly send a cnf/ind event
          resp = e_Nothing;
        }
      }
      else {
        resp = e_ProcessDataNoSocket;
      }
    }
  }
  else {
    resp = e_ProcessDataInhibited; // we are not allowed to send data
  }
  return resp;
}

EComResponse CCommFB::receiveData() {
  EComResponse eResp;
  EComResponse eRetVal = e_Nothing;

  const unsigned int comInterruptQueueCountCopy = mComInterruptQueueCount;
  for (size_t i = 0; i < comInterruptQueueCountCopy; ++i) {
    if(mInterruptQueue[i] == nullptr) {
      DEVLOG_ERROR("Attempt to process nullptr in CommFB::receiveData");
      eResp = e_Nothing;
    } else {
      eResp = mInterruptQueue[i]->processInterrupt();
    }
    if (eResp > eRetVal) {
      eRetVal = eResp;
    }
  }
  mComInterruptQueueCount -= comInterruptQueueCountCopy;
  for (unsigned int i = 0; i < mComInterruptQueueCount; ++i) {
    mInterruptQueue[i] = mInterruptQueue[i + comInterruptQueueCountCopy];
  }

  return eRetVal;
}

char *CCommFB::getDefaultIDString(const char *paID) {
  return buildIDString("fbdk[].ip[", paID, "]");
}
