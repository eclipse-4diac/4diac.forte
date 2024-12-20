/*******************************************************************************
 * Copyright (c) 2015-2023 Florian Froschermeier <florian.froschermeier@tum.de>,
 *               fortiss GmbH, Primetals Technologies Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Florian Froschermeier
 *      - initial integration of the OPC-UA protocol
 *    Stefan Profanter
 *      - refactoring and adaption to new concept
 *    Jose Cabral:
 *      - refactoring to cleaner architecture
 *    Markus Meingast:
 *      - add support for Object Structs
 *******************************************************************************/

#include "opcua_layer.h"
#include "opcua_helper.h"
#include "opcua_local_handler.h"
#include "../../core/cominfra/basecommfb.h"
#include "../../arch/devlog.h"
#include <forte_string.h>
#include <criticalregion.h>
#include "opcua_action_info.h"
#include "opcua_remote_handler.h"
#include "struct_action_info.h"
#include "opcua_objectstruct_helper.h"

using namespace forte::com_infra;

COPC_UA_Layer::COPC_UA_Layer(CComLayer *paUpperLayer, CBaseCommFB *paComFB) :
    CComLayer(paUpperLayer, paComFB), mInterruptResp(e_Nothing), mHandler(nullptr), mDataAlreadyPresent(false), mIsObjectNodeStruct(false) {
}

COPC_UA_Layer::~COPC_UA_Layer() = default;

EComResponse COPC_UA_Layer::openConnection(char *paLayerParameter) {
  EComResponse response = e_InitTerminated;
  mActionInfo = CActionInfo::getActionInfoFromParams(paLayerParameter, *this);
  if(mActionInfo) {
      mHandler =
          (mActionInfo->isRemote()) ? static_cast<COPC_UA_HandlerAbstract*>(&getExtEvHandler<COPC_UA_Remote_Handler>()) :
            static_cast<COPC_UA_HandlerAbstract*>(&getExtEvHandler<COPC_UA_Local_Handler>());
    if(checkTypesFromInterface()) {
      if(UA_STATUSCODE_GOOD == mHandler->initializeAction(*mActionInfo)) {
        CCriticalRegion criticalRegion(mRDBufferMutex);
        response = e_InitOk;
        for(size_t i = 0; i < getCommFB()->getNumRD(); ++i) {
          mRDBuffer.emplace_back(getCommFB()->getRDs()[i]->clone(nullptr));
        }
      }
    } else {
      bool isPublisher;
      if(getCommFB()->getComServiceType() == EComServiceType::e_Publisher) {
        isPublisher = true;
      } else if(getCommFB()->getComServiceType() == EComServiceType::e_Subscriber) {
        isPublisher = false;
      } else {
        return response;
      }
      CActionInfo::UA_ActionType action = mActionInfo->getAction();
      mStructObjectHelper = std::make_unique<COPC_UA_ObjectStruct_Helper>(*this, mHandler);
      if(COPC_UA_ObjectStruct_Helper::isStructType(*this, isPublisher) && (CActionInfo::eWrite == action || CActionInfo::eRead == action) ) {
        mIsObjectNodeStruct = true;
        CIEC_ANY** apoDataPorts = isPublisher ? getCommFB()->getSDs() : getCommFB()->getRDs();
        CIEC_STRUCT& structType = static_cast<CIEC_STRUCT&>(apoDataPorts[0]->unwrap());
        if(!mStructObjectHelper->checkStructTypeConnection(*mActionInfo, structType)) {
          return response;
        }
        response = mStructObjectHelper->createObjectNode(*mActionInfo, structType);
        if(!isPublisher && (response == e_InitOk)) {
          CCriticalRegion criticalRegion(mRDBufferMutex);
          mRDBuffer = mStructObjectHelper->initializeRDBuffer();
        }
      }
    }   
  }
  return response;
}

void COPC_UA_Layer::closeConnection() {
  if(mHandler) {
    CCriticalRegion criticalRegion(mRDBufferMutex);
    mHandler->uninitializeAction(*mActionInfo);
    mActionInfo.reset();

    if(mIsObjectNodeStruct) {
      mStructObjectHelper->uninitializeStruct();
    }
    mHandler = nullptr;
    if(mIsObjectNodeStruct) {
      COPC_UA_ObjectStruct_Helper::deleteRDBufferEntries(*getCommFB(), mRDBuffer);
    } else {
      mRDBuffer.clear();
    }
  }
}

EComResponse COPC_UA_Layer::recvData(const void *paData, unsigned int) {
  mInterruptResp = e_ProcessDataOk;
  auto handleRecv = static_cast<const COPC_UA_Helper::UA_RecvVariable_handle *>(paData);

  if(!handleRecv->mFailed) {
    if(handleRecv->mData.size() != 0) {
      if(handleRecv->mData.size() + handleRecv->mOffset <= getCommFB()->getNumRD()) {
        CCriticalRegion criticalRegion(mRDBufferMutex);
        for(size_t i = 0; i < handleRecv->mData.size(); i++) {
          long long bufferIndex = mIsObjectNodeStruct ? mStructObjectHelper->getRDBufferIndexFromNodeId(handleRecv->mNodeId) : handleRecv->mOffset + i;
          if(bufferIndex == -1) {
            DEVLOG_ERROR("[OPC UA LAYER]: Received Node ID %d does not match with any registered Node ID for FB %s\n", handleRecv->mNodeId, getCommFB()->getInstanceName());
            mInterruptResp = e_ProcessDataRecvFaild;
            break;
          }
          if(UA_Variant_isScalar(handleRecv->mData[i]) && handleRecv->mData[i]->data
            && handleRecv->mData[i]->type == COPC_UA_Helper::getOPCUATypeFromAny(*mRDBuffer[bufferIndex])) {
            COPC_UA_Helper::convertFromOPCUAType(handleRecv->mData[i]->data, *mRDBuffer[bufferIndex]);
          } else {
            DEVLOG_ERROR("[OPC UA LAYER]: RD_%d of FB %s has no data, is not a scalar or there is a type mismatch\n", bufferIndex,
              getCommFB()->getInstanceName());
            mInterruptResp = e_ProcessDataRecvFaild;
            break;
          }
        }
      } else {
        DEVLOG_ERROR("[OPC UA LAYER]: Receiving data for FB %s failed because the response size is %u with an offset of %u but the FB has %u RDs\n",
          getCommFB()->getInstanceName(), handleRecv->mData.size(), handleRecv->mOffset, getCommFB()->getNumRD());
        mInterruptResp = e_ProcessDataRecvFaild;
      }
    } else { //no data received. When remote writing this will happen
      mInterruptResp = e_ProcessDataOk;
    }
  } else { //this fail is logged in the handler
    mInterruptResp = e_ProcessDataRecvFaild;
  }

  if(e_ProcessDataOk == mInterruptResp) {
    if(getDataAlreadyPresentRead()) {
      return e_Nothing; //won't trigger another external event on subscription
    } else {
      setDataAlreadyPresentRead(true);
      return e_ProcessDataOk; //will trigger an external event on subscription
    }
  }

  return mInterruptResp;
}

EComResponse COPC_UA_Layer::sendData(void *, unsigned int) {
  if(mIsObjectNodeStruct) {
    return mStructObjectHelper->executeStructAction();
  }
  return (UA_STATUSCODE_GOOD == mHandler->executeAction(*mActionInfo) ? e_ProcessDataOk : e_ProcessDataDataTypeError);
}


EComResponse COPC_UA_Layer::processInterrupt() {
  CCriticalRegion criticalRegion(mRDBufferMutex);
  if(mIsObjectNodeStruct) { 
    COPC_UA_ObjectStruct_Helper::setMemberValues(getCommFB()->getRDs(), mRDBuffer);
  } else {
    for(size_t i = 0; i < getCommFB()->getNumRD(); ++i) {
      getCommFB()->getRDs()[i]->setValue(*mRDBuffer[i]);
    }
  }
  setDataAlreadyPresentRead(false);
  return mInterruptResp;
}

void COPC_UA_Layer::triggerNewEvent() {
  mHandler->triggerNewEvent(*this->getCommFB());
}

bool COPC_UA_Layer::checkTypesFromInterface() const {
  bool somethingFailed = false;
  for(unsigned int i = 0; i < getCommFB()->getNumSD(); i++) {
    if(!checkPortConnectionInfo(i + 2, true)) {
      somethingFailed = true;
      break;
    }
  }
  if(!somethingFailed) {
    for(unsigned int i = 0; i < getCommFB()->getNumRD(); i++) {
      if(!checkPortConnectionInfo(i + 2, false)) {
        somethingFailed = true;
        break;
      }
    }
  }

  return !somethingFailed;
}

bool COPC_UA_Layer::checkPortConnectionInfo(unsigned int paPortIndex, bool paIsSD) const {
  const CStringDictionary::TStringId localPortNameId = getLocalPortNameId(paPortIndex, paIsSD);
  const CDataConnection *localPortConnection = getLocalPortConnection(paPortIndex, paIsSD);
  if(!localPortConnection) {
    DEVLOG_ERROR("[OPC UA LAYER]: Got invalid port connection on FB %s at port %s. It must be connected to another FB.\n", getCommFB()->getInstanceName(),
      CStringDictionary::getInstance().get(localPortNameId));
    return false;
  }

  if(!localPortConnection->isConnected()) {
    DEVLOG_ERROR("[OPC UA LAYER]: Connection %s of FB %s is not connected to anything.\n", CStringDictionary::getInstance().get(localPortNameId),
      getCommFB()->getInstanceName());
    return false;
  }

  CIEC_ANY &remoteType = (paIsSD) ? getCommFB()->getDI(paPortIndex)->unwrap() : getCommFB()->getDO(paPortIndex)->unwrap();

  if(!COPC_UA_Helper::getOPCUATypeFromAny(remoteType)) {
    if(!COPC_UA_ObjectStruct_Helper::isStructType(*this, paIsSD)) {
      DEVLOG_ERROR("[OPC UA LAYER]: Invalid  type %d in FB %s at connection %s\n", remoteType.getDataTypeID(), getCommFB()->getInstanceName(),
      CStringDictionary::getInstance().get(localPortNameId));
    }
    return false;
  }
  return true;
}

bool COPC_UA_Layer::getDataAlreadyPresentRead() {
  CCriticalRegion dataReadRegion(mDataAlreadyPresentMutex);
  return mDataAlreadyPresent;
}
void COPC_UA_Layer::setDataAlreadyPresentRead(bool paDataRead) {
  CCriticalRegion dataReadRegion(mDataAlreadyPresentMutex);
  mDataAlreadyPresent = paDataRead;
}

const CDataConnection* COPC_UA_Layer::getLocalPortConnection(int paPortIndex, bool paIsSD) const {
  const CStringDictionary::TStringId localPortNameId = getLocalPortNameId(paPortIndex, paIsSD);
  const CDataConnection *localPortConnection = paIsSD ? getCommFB()->getDIConnection(localPortNameId) : getCommFB()->getDOConnection(localPortNameId);
  return localPortConnection;
}

CStringDictionary::TStringId COPC_UA_Layer::getLocalPortNameId(int paPortIndex, bool paIsSD) const {
  const SFBInterfaceSpec& localInterfaceSpec(getCommFB()->getFBInterfaceSpec());
  return paIsSD ? localInterfaceSpec.mDINames[paPortIndex] : localInterfaceSpec.mDONames[paPortIndex];
}
