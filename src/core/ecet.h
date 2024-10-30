/*******************************************************************************
 * Copyright (c) 2005 - 2014 ACIN, Profactor GmbH, fortiss GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Alois Zoitl, Gunnar Grabmaier, Thomas Strasser, Rene Smodic, Ingo Hegny
 *      - initial implementation and rework communication infrastructure
 *******************************************************************************/
#ifndef _ECET_H_
#define _ECET_H_

#include "event.h"
#include "datatypes/forte_time.h"
#include "utils/ringbuf.h"
#include <forte_thread.h>
#include <forte_sync.h>
#include <forte_sem.h>

/*! \ingroup CORE\brief Class for executing one event chain.
 *
 */
class CEventChainExecutionThread : public CThread{
  public:
    CEventChainExecutionThread();
    ~CEventChainExecutionThread() override;

    /*!\brief Start the a new event chain with the given event.
     *
     *
     * \param paEventToAdd event of the EC to start
     */
    virtual void startEventChain(TEventEntry paEventToAdd);

    /*!\brief Add an new event entry to the event chain
     *
     * \param paEventToAdd new event entry
     */
    void addEventEntry(TEventEntry paEventToAdd){
      if(!mEventList.push(paEventToAdd)){
        DEVLOG_ERROR("Event queue is full, event dropped!\n");
      }
    }

    /*!\brief allow to start, stop, and kill the execution of the event chain execution thread
     *
     * @param paCommand the management command to be executed
     */
    void changeExecutionState(EMGMCommandType paCommand);

    void joinEventChainExecutionThread(){
      CThread::join();
    }

    bool isProcessingEvents() const {
      return mProcessingEvents;
    }

    void resumeSelfSuspend(){
      mSuspendSemaphore.inc();
    }

  protected:
    /*! \brief List of input events to deliver.
     *
     * This list stores the necessary information for all events to deliver that occurred within this event chain.
     */
    forte::core::util::CRingBuffer<TEventEntry, cgEventChainEventListSize> mEventList;

    void selfSuspend(){
      mSuspendSemaphore.waitIndefinitely();
    }

    void mainRun();

  private:
    /*! \brief The thread run()-method where the events are sent to the FBs and the FBs are executed in.
     *
     * If there is an entry in the Event List the event will be delivered and the FB executed.
     * If there is no entry in this list the CEventChainExecutionThread will suspend itself and remove itself from the
     * active EventChainExecutionlist in CFBNExecution.
     * \return true if thread execution ended successfully
     */
    void run() override;

    void onAliveChanged(bool paNewValue) override;

    /*! \brief Clear the event chain.
     */
    void clear();

    bool externalEventOccured() const {
      /* we should not need a protection here as we are just comparing the both
       * the only value that could change during the compare is mExternalEventListEnd. In the worst case
       * this results in a to early or to late detection. However as the transfer is protected this should be no
       * big issue.
       * TODO perform test to verify this assumption
       */
      return !mExternalEventList.isEmpty();
    }

    //! Transfer elements stored in the external event list to the main event list
    void transferExternalEvents();

    /*! \brief List of external events that occurred during one FB's execution
     *
     * This list stores external events that may have occurred during the execution of a FB or during when the
     * Event-Chain execution was sleeping. with this second list we omit the need for a mutex protection of the event
     * list. This is a great performance gain.
     */
    forte::core::util::CRingBuffer<TEventEntry, cgEventChainExternalEventListSize> mExternalEventList;

    //! SyncObject for protecting the list in regard to several accesses
    CSyncObject mExternalEventListSync;

    forte::arch::CSemaphore mSuspendSemaphore;

    /*! \brief Flag indicating if this event chain execution thread is currently processing any events
     *
     * Initially this flag is false.
     * This flag is activated when a new event chain is started and deactivated when the event queue is empty.
     *
     * Currently this flag is only needed for the FB tester.
     * TODO consider surrounding the usage points of this flag with #defines such that it is only used for testing.
     */
    bool mProcessingEvents{false};
};

#endif /*ECET_H_*/
