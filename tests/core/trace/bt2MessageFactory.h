#ifndef TRACE_MESSAGE_FACTORY_H
#define TRACE_MESSAGE_FACTORY_H

#include "trace/EventMessage.h"

class bt_message;


namespace Bt2MessageFactory {
    /**
     * @brief babeltrace2 message factory
     * 
     * Creates an EventMessage from the babeltrace type. If any errors occur, the program aborts
     * 
     * @param paMessage the message in babaeltrace format
     * @return EventMessage the created event message
     */
    EventMessage createMessage(const bt_message* paMessage);
};

#endif // TRACE_MESSAGE_FACTORY_H