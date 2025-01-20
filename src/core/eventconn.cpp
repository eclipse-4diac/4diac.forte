/*******************************************************************************
 * Copyright (c) 2005 - 2015 Profactor GmbH, ACIN, fortiss GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Thomas Strasser, Alois Zoitl,
 *      - initial implementation and rework communication infrastructure
 *******************************************************************************/
#include "eventconn.h"
#include "ecet.h"
#include "funcbloc.h"

CEventConnection::CEventConnection(CFunctionBlock *paSrcFB, TPortId paSrcPortId) :
    CConnection(paSrcFB, paSrcPortId){
}

CEventConnection::~CEventConnection() = default;

EMGMResponse CEventConnection::connect(CFunctionBlock *paDstFB, CStringDictionary::TStringId paDstPortNameId){
  EMGMResponse retval = EMGMResponse::NoSuchObject;
  TPortId nEIID = paDstFB->getEIID(paDstPortNameId);

  if(cgInvalidEventID != nEIID){
    retval = CConnection::addDestination(CConnectionPoint(paDstFB, nEIID));
    paDstFB->addInputEventConnection(nEIID);
  }
  return retval;
}

EMGMResponse CEventConnection::connectToCFBInterface(CFunctionBlock *paDstFB, CStringDictionary::TStringId paDstPortNameId){
  EMGMResponse retval = EMGMResponse::NoSuchObject;
  TPortId nEOID = paDstFB->getEOID(paDstPortNameId);

  if(cgInvalidEventID != nEOID){
    nEOID |= cgInternal2InterfaceMarker;
    retval = CConnection::addDestination(CConnectionPoint(paDstFB, nEOID));
  }
  return retval;
}

EMGMResponse CEventConnection::disconnect(CFunctionBlock *paDstFB, CStringDictionary::TStringId paDstPortNameId){
  EMGMResponse retval = EMGMResponse::NoSuchObject;
  TEventID nEIID = paDstFB->getEIID(paDstPortNameId);

  if(cgInvalidEventID != nEIID){
    retval = CConnection::removeDestination(CConnectionPoint(paDstFB, nEIID));
    paDstFB->removeInputEventConnection(nEIID);
  }
  return retval;
}

void CEventConnection::triggerEvent(CEventChainExecutionThread *paExecEnv) const {
  if(paExecEnv != nullptr){
    for(const auto& runner : mDestinationIds){
      paExecEnv->addEventEntry(runner);
    }
  }
}


