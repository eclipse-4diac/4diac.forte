#ifndef _FORTE_TESTS_CORE_TRACE_EVENT_MESSAGE_H_
#define _FORTE_TESTS_CORE_TRACE_EVENT_MESSAGE_H_

#include <memory>
#include <string>
#include <vector>

class AbstractPayload;

/**
 * @brief Represents a trace event message according to the config.yaml description
 * 
 * It abstracts any type of possible message defined in config.yaml. The word event in the name
 * has not relation to the events in 61499, but is also the term used in BareCTF tracer for each
 * instance of something that was traced. Although this is independent from BareCTF, it was used as 
 * a base for this implementation.
 * 
 * Each event message has a type, a timestamp and a payload which depends on the type of message.
 */
class EventMessage {
public:

  /**
   * @brief Construct a new Event Message object
   *  
   * @param paEventType the type of event message to create
   * @param paPayload the payload of the message 
   * @param paTimestamp the timestamp when the event message happenned
   */
  EventMessage(std::string paEventType, std::unique_ptr<AbstractPayload> paPayload, int64_t paTimestamp);

  virtual ~EventMessage() = default;

  EventMessage(const EventMessage& paOther);
  EventMessage& operator=(const EventMessage& paOther);

  EventMessage(EventMessage&& paOther) = default;
  EventMessage& operator=(EventMessage&& paOther) = default;

  /**
   * @brief Get the string representation of the payload. Used for debugging pusposses
   * 
   * @return string representation of the payload
   */
  std::string getPayloadString() const;

  /**
   * @brief Get the string representation of the timestamp. Used for debugging pusposses
   * 
   * @return string representation of the timestamp
   */
  std::string getTimestampString() const;

  int64_t getTimestamp() const;

  bool operator==(const EventMessage& paOther) const;

  /**
   * @brief Get a copy of the payload
   * 
   * @tparam T Child payload class
   * @return copy of the payload of the message
   */
  template<typename T>
  std::unique_ptr<T> getPayload() const;

  /**
   * @brief Get the event type of the message
   * 
   * @return event type of the message
   */
  std::string getEventType() const;

  /**
   * @brief Get the name of type of the payload
   * 
   * @return type of the payload
   */

private:
  std::string mEventType;
  std::unique_ptr<AbstractPayload> mPayload;
  int64_t mTimestamp;
};

/**
 * @brief Parent class for all types of payloads with the common information for all types of payloads,
 * which includes the type name and instance name of the Function Block that generated the trace.
 */
class AbstractPayload {
public:

  /**
   * @brief Construct a new Abstract Payload object
   * 
   * @param paTypeName type name of the function block that generated the trace
   * @param paInstanceName instance name of the function block that generated the trace 
   */
  AbstractPayload(std::string paTypeName, std::string paInstanceName);

  virtual ~AbstractPayload() = default;

  AbstractPayload(const AbstractPayload&) = default;
  AbstractPayload& operator=(const AbstractPayload&) = default;

  AbstractPayload(AbstractPayload&) = default;
  AbstractPayload& operator=(AbstractPayload&&) = default;

  /**
   * @brief Get the string representation of the payload. Used for debugging pusposses
   * 
   * @return string representation of the payload
   */
  std::string getString() const;

  /**
   * @brief Makes a copy of the payload. The implementation is done in the child class
   * 
   * @return copy of the payload
   */
  virtual std::unique_ptr<AbstractPayload> clone() const = 0;

  bool operator==(const AbstractPayload& paOther) const;

protected:

  /**
   * @brief Equal operator interface implemented by the child class
   * 
   * @param paOther the other payload to compare to
   * @return true if the payloads are equal, false otherwise 
   */
  virtual bool specificPayloadEqual(const AbstractPayload& paOther) const = 0;

  /**
   * @brief Get a string representation of the payload. Implemented in the child and used for debug purpossed
   * 
   * @return the string representation of the payload
   */
  virtual std::string specificPayloadString() const = 0;

  std::string mTypeName;
  std::string mInstanceName;
};

/**
 * @brief Payload representation of an input event message. It contains the event ID of the Function Block that was triggered
 * 
 */
class FBInputEventPayload : public AbstractPayload {
public:
  FBInputEventPayload(std::string paTypeName, std::string paInstanceName, const uint64_t paEventId);

private:

  std::unique_ptr<AbstractPayload> clone() const override;

  std::string specificPayloadString() const override;

  bool specificPayloadEqual(const AbstractPayload& paOther) const override;
 
  uint64_t mEventId;
};

/**
 * @brief Payload representation of an output event message. It contains the event ID of the Function Block that was triggered
 * 
 */
class FBOutputEventPayload : public AbstractPayload {
public:
  FBOutputEventPayload(std::string paTypeName, std::string paInstanceName, const uint64_t paEventId);

  std::unique_ptr<AbstractPayload> clone() const override;

  std::string specificPayloadString() const override;

  bool specificPayloadEqual(const AbstractPayload& paOther) const override;
 
  uint64_t mEventId;
  uint64_t mEventCounter;
  std::vector<std::string> mOutputs;
};

/**
 * @brief Payload representation of the data of a Function block. It contains the data ID of the Function Block and the 
 * string representation of its value
 * 
 */
class FBDataPayload : public AbstractPayload {
public:
  FBDataPayload(std::string paTypeName, std::string paInstanceName, uint64_t paDataId, std::string paValue);

private:
  std::unique_ptr<AbstractPayload> clone() const override;

  std::string specificPayloadString() const override;

  bool specificPayloadEqual(const AbstractPayload& paOther) const override;

  uint64_t mDataId;
  std::string mValue;
};

/**
 * @brief Payload representation of the instance of Function block. It contains the values of the inputs, outputs,
 * internal variables and internal Funtion Blocks 
 */
class FBInstanceDataPayload : public AbstractPayload {
public:
  FBInstanceDataPayload(std::string paTypeName, std::string paInstanceName, 
        const std::vector<std::string>& paInputs,
        const std::vector<std::string>& paOutputs,
        const std::vector<std::string>& paInternal,
        const std::vector<std::string>& paInternalFB);

private:

  std::unique_ptr<AbstractPayload> clone() const override;

  std::string specificPayloadString() const override;

  bool specificPayloadEqual(const AbstractPayload& paOther) const override;

  std::vector<std::string> mInputs;
  std::vector<std::string> mOutputs;
  std::vector<std::string> mInternal;
  std::vector<std::string> mInternalFB;
};

template<typename T>
std::unique_ptr<T> EventMessage::getPayload() const {
  return std::unique_ptr<T>(dynamic_cast<T*>(mPayload->clone().release()));
}

#endif //  _FORTE_TESTS_CORE_TRACE_EVENT_MESSAGE_H_