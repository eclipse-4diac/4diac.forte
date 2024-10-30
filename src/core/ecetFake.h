/*******************************************************************************
 * Copyright (c) 2024 
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
#ifndef _CORE_FAKE_ECET_H_
#define _CORE_FAKE_ECET_H_

#include "ecet.h"

#include <functional>
#include <mutex>
#include <condition_variable>
#include <set>
#include <optional>

/**
 * @brief An ecet which can be fully controlled from outside the class 
 * 
 */
class CFakeEventExecutionThread : public CEventChainExecutionThread{
  public:

    /**
     * @brief Callback type for processing events 
     */
    typedef std::function<void(TEventEntry)> HandleEvent;


    CFakeEventExecutionThread();
    ~CFakeEventExecutionThread() override = default;

    /**
     * @brief Triggers the next event in the list if there's any
     * 
     * How the event trigger is handled can be configured via a callback. 
     */
    void triggerNextEvent();

    /**
     * @brief Set the callback that will be called for each event that is triggered.
     * If set to std::nullopt, the event is supressed
     * 
     * @param paCallback Callback to be used
     */
    void setCallbackForEventTriggering(std::optional<HandleEvent> paCallback = std::nullopt);
    
    /**
     * @brief Set the callback for event trigger to the default one, 
     * which calls receiveInputEvent on the Function Block 
     */
    void setDefaultCallbackForEventTrigger();
    
    /**
     * @brief Starts a new chain event. If a callback was set, it is called. * Initially,
     * the callback is set to call the same function in the parent ecet
     * 
     * @param paEventToAdd event starting the chain 
     */
    void startEventChain(TEventEntry paEventToAdd) override;

    /**
     * @brief Set a new callback that will be called when a new event chain would be started. If set
     * to std::nullopt, the new event chain is supressed
     * 
     * @param paCallback function to be called when a new chain of event starts
     */
    void setCallbackForNewEventChain(std::optional<HandleEvent> paCallback = std::nullopt);

    /**
     * @brief Set the callback for new event chains to the default one which calls the parent startEventChain
     */
    void setDefaultCallbackForNewEventChain();

    /**
     * @brief Let the ecet run freely and not controlled from outside anymore
     */
    void removeExternalControl();

    /**
     * @brief Insert a new event at the front of the list of events
     * 
     * @param paEvent event to be inserted
     */
    void insertFront(TEventEntry paEvent);

    /**
     * @brief Remove events from the back of the list of events
     * 
     * @param paNumberOfItemsToRemove number of events to remove from the back of the list
     */
    void removeFromBack(size_t paNumberOfItemsToRemove);

    /**
     * @brief Get a copy of next event to be triggered if any
     * 
     * @return The next event to be triggered, std::nullopt if there isn't any 
     */
    std::optional<TEventEntry> getNextEvent();

private:

    void run() override;
    bool mIsControlledFromOutside{true};
    std::optional<HandleEvent> mNewEventChainCallback;
    std::optional<HandleEvent> mProcessEventCallback;
};

#endif /*_CORE_FAKE_ECET_H_*/