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
#ifndef _FMUECET_H_
#define _FMUECET_H_

#include "../ecet.h"

class CFMUEventChainExecutionThread : public CEventChainExecutionThread{
  public:
    CFMUEventChainExecutionThread();
    ~CFMUEventChainExecutionThread() override;

    void setAllowedToRun(bool* paAllowedToRun){
      mAllowedToRun = paAllowedToRun;
    }

    void setStepSemaphore(forte::arch::CSemaphore* paStepSemaphore){
      mStepSemaphore = paStepSemaphore;
    }

    bool hasMoreEvents(){
      return !mEventList.isEmpty();
    }

    bool isInWaitingStepState(){
      return mWaitingStep;
    }

private:
    virtual void run();
    bool* mAllowedToRun;
    forte::arch::CSemaphore* mStepSemaphore;
    bool mWaitingStep;

};

#endif /*_FMUECET_H_*/
