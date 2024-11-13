/*******************************************************************************
 * Copyright (c) 2018 - fortiss GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Jose Cabral - initial implementation and rework communication infrastructure
 *******************************************************************************/

#include "ecetFake.h"
#include "funcbloc.h"

CFakeEventExecutionThread::CFakeEventExecutionThread() :
    CEventChainExecutionThread(){
  setDefaultCallbackForNewEventChain();
  setDefaultCallbackForEventTrigger();
}

void CFakeEventExecutionThread::triggerNextEvent(){
  auto event = mEventList.pop();
  if(nullptr == event){
    return;
  }

  if(!mProcessEventCallback.has_value()){
    return;
  }
  mProcessEventCallback.value()(*event);
}

void CFakeEventExecutionThread::setCallbackForEventTriggering(std::optional<HandleEvent> paCallback) {
  mProcessEventCallback = paCallback;
}

void CFakeEventExecutionThread::setDefaultCallbackForEventTrigger() {
  mProcessEventCallback = [this](TEventEntry paEvent){
    paEvent.mFB->receiveInputEvent(paEvent.mPortId, this);
  };
}

void CFakeEventExecutionThread::startEventChain(TEventEntry paEvent) {
  if(!mNewEventChainCallback.has_value()){
    return;
  }
  mNewEventChainCallback.value()(paEvent);
}

void CFakeEventExecutionThread::setCallbackForNewEventChain(std::optional<HandleEvent> paCallback) {
  mNewEventChainCallback = paCallback;
}

void CFakeEventExecutionThread::setDefaultCallbackForNewEventChain(){
  mNewEventChainCallback = [this](TEventEntry paEvent){
    CEventChainExecutionThread::startEventChain(paEvent);
  };
}

void CFakeEventExecutionThread::removeExternalControl() {
  setDefaultCallbackForNewEventChain();
  setDefaultCallbackForEventTrigger();
  mIsControlledFromOutside = false;      
  resumeSelfSuspend();
}

void CFakeEventExecutionThread::insertFront(TEventEntry paEvent){
  // the ring buffer does not have a way to insert in the front,
  // so we create a new one and push the event first there and then the rest
  // and then copy the events back to the original list
  decltype(mEventList) temp;
  temp.push(paEvent);
  while(!mEventList.isEmpty()){
    temp.push(*mEventList.pop());
  }

  while(!temp.isEmpty()){
    mEventList.push(*temp.pop());
  }
}

void CFakeEventExecutionThread::removeFromBack(size_t paNumberOfItemsToRemove){
  std::vector<TEventEntry> temp;
  while(!mEventList.isEmpty()){
    temp.push_back(*mEventList.pop());
  }

  while(paNumberOfItemsToRemove-- != 0){
    temp.pop_back();
  }

  for(auto& event : temp){
    mEventList.push(event);
  }
}

std::optional<TEventEntry> CFakeEventExecutionThread::getNextEvent(){
  auto nextEvent = mEventList.pop(); // get a copy, but need to pop for it
  if(nextEvent == nullptr){
    return std::nullopt;
  }

  insertFront(*nextEvent);
  return *nextEvent;
}

// we don't need the complexities of a separate thread, so 
// the funtion just set to sleep when is controlled from outside
void CFakeEventExecutionThread::run(){
  while(isAlive()){
    if(mIsControlledFromOutside){
      selfSuspend();
    } 
    CEventChainExecutionThread::mainRun();
  }
}