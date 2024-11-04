/*******************************************************************************
 * Copyright (c) 2013, 2014 fortiss GmbH, 2018 TU Vienna/ACIN
 *                      2018 Johannes Kepler University
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Alois Zoitl
 *      - initial implementation and rework communication infrastructure
 *    Martin Melik Merkumians - fixes event chain initialisation, adds typifyAnyAdapter
 *    Alois Zoitl - introduced new CGenFB class for better handling generic FBs
 *******************************************************************************/
#include "anyadapter.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "anyadapter_gen.cpp"
#endif

DEFINE_GENERIC_ADAPTER_TYPE(CAnyAdapter, g_nStringIdANY_ADAPTER)

const SFBInterfaceSpec CAnyAdapter::scmFBInterfaceSpec = {
  0, nullptr, nullptr, nullptr, nullptr,
  0, nullptr, nullptr, nullptr, nullptr,
  0, nullptr, nullptr,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

CAnyAdapter::CAnyAdapter(CStringDictionary::TStringId paAdapterInstanceName, forte::core::CFBContainer &paContainer, bool paIsPlug) :
    CAdapter(paContainer, scmFBInterfaceSpec, paAdapterInstanceName, scmFBInterfaceSpec, paIsPlug), m_ParentFB(nullptr),
    mParentAdapterlistID(0){
}

CAnyAdapter::~CAnyAdapter() = default;

void CAnyAdapter::typifyAnyAdapter(CAdapter *paPeer){
  getGenInterfaceSpec().mNumEIs = paPeer->getFBInterfaceSpec().mNumEOs;
  getGenInterfaceSpec().mEINames = paPeer->getFBInterfaceSpec().mEONames;
  getGenInterfaceSpec().mEIWith = paPeer->getFBInterfaceSpec().mEOWith;
  getGenInterfaceSpec().mEIWithIndexes = paPeer->getFBInterfaceSpec().mEOWithIndexes;
  getGenInterfaceSpec().mNumEOs = paPeer->getFBInterfaceSpec().mNumEIs;
  getGenInterfaceSpec().mEONames = paPeer->getFBInterfaceSpec().mEINames;
  getGenInterfaceSpec().mEOWith = paPeer->getFBInterfaceSpec().mEIWith;
  getGenInterfaceSpec().mEOWithIndexes = paPeer->getFBInterfaceSpec().mEIWithIndexes;
  getGenInterfaceSpec().mNumDIs = paPeer->getFBInterfaceSpec().mNumDOs;
  getGenInterfaceSpec().mDINames = paPeer->getFBInterfaceSpec().mDONames;
  getGenInterfaceSpec().mDIDataTypeNames = paPeer->getFBInterfaceSpec().mDODataTypeNames;
  getGenInterfaceSpec().mNumDOs = paPeer->getFBInterfaceSpec().mNumDIs;
  getGenInterfaceSpec().mDONames = paPeer->getFBInterfaceSpec().mDINames;
  getGenInterfaceSpec().mDODataTypeNames = paPeer->getFBInterfaceSpec().mDIDataTypeNames;
  getGenInterfaceSpec().mNumDIOs = paPeer->getFBInterfaceSpec().mNumDIOs;
  getGenInterfaceSpec().mDIONames = paPeer->getFBInterfaceSpec().mDIONames;
  setupFBInterface();
  fillEventEntryList(m_ParentFB);
}

bool CAnyAdapter::disconnect(CAdapterConnection *paAdConn){
  bool bRetVal = CAdapter::disconnect(paAdConn);

  //clean interface data and reset to empty interface
  getGenInterfaceSpec() = scmFBInterfaceSpec;
  setupFBInterface();

  return bRetVal;
}

// Saves parentFB for later use
void CAnyAdapter::setParentFB(CFunctionBlock *paParentFB, TForteUInt8 paParentAdapterlistID){
  if(nullptr == m_ParentFB){
    m_ParentFB = paParentFB;
  }
  if(0 == mParentAdapterlistID){
    mParentAdapterlistID = paParentAdapterlistID;
  }

  CAdapter::setParentFB(m_ParentFB, mParentAdapterlistID);
}
