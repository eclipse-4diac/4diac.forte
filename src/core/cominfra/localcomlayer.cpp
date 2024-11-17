/*******************************************************************************
 * Copyright (c) 2011-2014 fortiss and TU Wien ACIN.
 *               2023 Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Alois Zoitl - initial implementation and bug fixes
 *    Patrik Smejkal - rename interrupt in interruptCCommFB
 *    Martin Jobst - account for new FB layout and varying data type size
 *    Mario Kastner - bug fixes
 *******************************************************************************/
#include "localcomlayer.h"
#include "commfb.h"
#include "../resource.h"
#include "../device.h"
#include "../utils/criticalregion.h"


using namespace forte::com_infra;

CLocalComLayer::CLocalCommGroupsManager CLocalComLayer::smLocalCommGroupsManager;

CLocalComLayer::CLocalComLayer(CComLayer* paUpperLayer, CBaseCommFB * paFB) :
  CComLayer(paUpperLayer, paFB){
}

CLocalComLayer::~CLocalComLayer(){
  closeConnection();
}

EComResponse CLocalComLayer::sendData(void *, unsigned int){
  CIEC_ANY **sds = mFb->getSDs();
  TPortId numSDs = mFb->getNumSD();

  CLocalCommGroup* comGroup = getLocalCommGroupsManager().getComGroup(mGroupID);

  if (comGroup == nullptr) {
    return e_ProcessDataSendFailed;
  }

  for(auto runner : comGroup->mSublList){
    forte::com_infra::CBaseCommFB& subFb(*runner->getCommFB());
    CCriticalRegion criticalRegion(subFb.getFBLock());
    setRDs(subFb, sds, numSDs);
    subFb.interruptCommFB(runner);
    subFb.getDevice()->getDeviceExecution().startNewEventChain(&subFb);
  }
  
  return e_ProcessDataOk;
}


void CLocalComLayer::setRDs(forte::com_infra::CBaseCommFB& paSubl, CIEC_ANY **paSDs, TPortId paNumSDs){
  CIEC_ANY **aRDs = paSubl.getRDs();
  for(size_t i = 0; i < paNumSDs; ++i){
      aRDs[i]->setValue(*paSDs[i]);
  }
}

EComResponse CLocalComLayer::openConnection(char *const paLayerParameter){
  mGroupID = CStringDictionary::getInstance().insert(paLayerParameter);

  switch(mFb->getComServiceType()){
    case e_Server:
    case e_Client:
      break;
    case e_Publisher:
      if(!getLocalCommGroupsManager().registerPubl(mGroupID, this)) {
        return e_InitInvalidId;
      }
      break;
    case e_Subscriber:
      if(!getLocalCommGroupsManager().registerSubl(mGroupID, this)) {
        return e_InitInvalidId;
      }
      break;
  }
  return e_InitOk;
}

void CLocalComLayer::closeConnection() {
  if(e_Publisher == mFb->getComServiceType()) {
    getLocalCommGroupsManager().unregisterPubl(mGroupID, this);
  } else {
    getLocalCommGroupsManager().unregisterSubl(mGroupID, this);
  }
}

/********************** CLocalCommGroupsManager *************************************/
bool CLocalComLayer::CLocalCommGroupsManager::registerPubl(const CStringDictionary::TStringId paGroupID, CLocalComLayer *paLayer) {
  forte::com_infra::CBaseCommFB *commFb = paLayer->getCommFB();
  return registerPubl(paGroupID, paLayer, commFb->getSDs(), commFb->getNumSD());
}

CLocalComLayer::CLocalCommGroup* CLocalComLayer::CLocalCommGroupsManager::getComGroup(const CStringDictionary::TStringId paGroupID) {
  auto iterator = getLocalCommGroupIterator(paGroupID);
  if (isGroupIteratorForGroup(iterator, paGroupID)) {
    return &(*iterator);
  }
  return nullptr;
}

bool CLocalComLayer::CLocalCommGroupsManager::registerPubl(const CStringDictionary::TStringId paGroupID, CLocalComLayer *paLayer, CIEC_ANY **paDataPins,
    TPortId paNumDataPins) {
  CCriticalRegion criticalRegion(mSync);
  CLocalCommGroup *const group = findOrCreateLocalCommGroup(paGroupID, paDataPins, paNumDataPins);
  if(group == nullptr) {
    return false;
  }
  group->mPublList.push_back(paLayer);
  return true;
}

void CLocalComLayer::CLocalCommGroupsManager::unregisterPubl(const CStringDictionary::TStringId paGroupID, CLocalComLayer *paLayer){
  CCriticalRegion criticalRegion(mSync);
  auto comGroupIt = getLocalCommGroupIterator(paGroupID);
  if (isGroupIteratorForGroup(comGroupIt, paGroupID)) {
    removeListEntry(comGroupIt->mPublList, paLayer);
    checkForGroupRemoval(comGroupIt);
  }
}

bool CLocalComLayer::CLocalCommGroupsManager::registerSubl(const CStringDictionary::TStringId paGroupID, CLocalComLayer *paLayer){
  CCriticalRegion criticalRegion(mSync);
  forte::com_infra::CBaseCommFB *commFb = paLayer->getCommFB();
  CLocalCommGroup *const group = findOrCreateLocalCommGroup(paGroupID, commFb->getRDs(), commFb->getNumRD());
  if(group == nullptr) {
    return false;
  }
  group->mSublList.push_back(paLayer);
  return true;
}

void CLocalComLayer::CLocalCommGroupsManager::unregisterSubl(const CStringDictionary::TStringId paGroupID, CLocalComLayer *paLayer){
  CCriticalRegion criticalRegion(mSync);
  auto comGroupIt = getLocalCommGroupIterator(paGroupID);
    if (isGroupIteratorForGroup(comGroupIt, paGroupID)) {
      removeListEntry(comGroupIt->mSublList, paLayer);
      checkForGroupRemoval(comGroupIt);
    }
}

CLocalComLayer::CLocalCommGroupsManager::TLocalCommGroupList::iterator CLocalComLayer::CLocalCommGroupsManager::getLocalCommGroupIterator(
    CStringDictionary::TStringId paID){
  return lower_bound(mLocalCommGroups.begin(), mLocalCommGroups.end(), paID,
                                  [](const CLocalCommGroup& locGroup,
                                     CStringDictionary::TStringId groupId) {
                                    return locGroup.mGroupName < groupId;
                                  });
}

CLocalComLayer::CLocalCommGroup* CLocalComLayer::CLocalCommGroupsManager::findOrCreateLocalCommGroup(CStringDictionary::TStringId paID,
    CIEC_ANY **paDataPins, TPortId paNumDataPins){
  auto iter = getLocalCommGroupIterator(paID);
  if(isGroupIteratorForGroup(iter, paID)){
    if(checkDataTypes(*iter, paDataPins, paNumDataPins)){
      return &(*iter);
    }
    return nullptr;
  }
  return &(*mLocalCommGroups.insert(iter, CLocalCommGroup(paID, buildDataTypeList(paDataPins, paNumDataPins))));
}

void CLocalComLayer::CLocalCommGroupsManager::checkForGroupRemoval(TLocalCommGroupList::iterator comGroupIt) {
  if((comGroupIt->mPublList.empty()) && (comGroupIt->mSublList.empty())){
    mLocalCommGroups.erase(comGroupIt);
  }
}

void CLocalComLayer::CLocalCommGroupsManager::removeListEntry(CLocalCommGroup::TLocalComLayerList  &paComLayerList, CLocalComLayer *paLayer){
  auto iter = std::find(paComLayerList.begin(), paComLayerList.end(), paLayer);
  if(iter != paComLayerList.end()){
    paComLayerList.erase(iter);
  }
}

CLocalComLayer::CLocalCommGroup::TLocalComDataTypeList CLocalComLayer::CLocalCommGroupsManager::buildDataTypeList(CIEC_ANY **paDataPins,
    TPortId paNumDataPins){
  CLocalComLayer::CLocalCommGroup::TLocalComDataTypeList dataTypes;

  if(paDataPins != nullptr){
    dataTypes.reserve(paNumDataPins);
    for(size_t i = 0; i < paNumDataPins; i++){
      dataTypes.push_back(paDataPins[i]->unwrap().getTypeNameID());
    }
  }

  return dataTypes;
}

bool CLocalComLayer::CLocalCommGroupsManager::checkDataTypes(const CLocalCommGroup& group, CIEC_ANY **paDataPins, TPortId paNumDataPins){
  if(paNumDataPins != group.mDataTypes.size()){
    return false;
  }

  size_t i = 0;
  for(auto runner : group.mDataTypes){
    if(runner != paDataPins[i]->unwrap().getTypeNameID()){
      return false;
    }
    i++;
  }

  return true;
}
