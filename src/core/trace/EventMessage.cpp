#include "EventMessage.h"

#include <array>
#include <iomanip>


// ******************** //
// EventMessage methods //
// ******************** //

EventMessage::EventMessage(std::string paEventType, std::unique_ptr<AbstractPayload> paPayload, int64_t paTimestamp) : 
  mEventType(std::move(paEventType)), mPayload(std::move(paPayload)), mTimestamp(paTimestamp){
}

EventMessage::EventMessage(const EventMessage& paOther) {
  *this = paOther;
}

EventMessage& EventMessage::operator=(const EventMessage& paOther) {
  this->mEventType = paOther.mEventType;
  this->mTimestamp = paOther.mTimestamp;
  this->mPayload = paOther.mPayload->clone();
  return *this;
}

std::string EventMessage::getPayloadString() const {
  return mEventType + (mPayload != nullptr ? ": " + mPayload->getString() : "");
}

std::string EventMessage::getTimestampString() const {
  auto nanoseconds = mTimestamp;
  auto milliseconds = mTimestamp / 1000000;
  
  auto seconds = milliseconds / 1000;
  auto minutes = seconds / 60;
  auto hours = minutes / 60;

  nanoseconds %= 1000000000;
  seconds %= 60;
  minutes %= 60;

  std::stringstream ss;
  ss << "[" << 
      std::setw(2) << std::setfill('0') << hours + 1 << ":" <<
      std::setw(2) << std::setfill('0') << minutes << ":" <<
      std::setw(2) << std::setfill('0') << seconds << "." <<
      std::setw(6) << std::setfill('0') << nanoseconds <<  "]";

  return ss.str();
}

bool EventMessage::operator==(const EventMessage& paOther) const {
  return mEventType == paOther.mEventType  && 
    (mPayload == nullptr) ? (paOther.mPayload == nullptr) : (paOther.mPayload != nullptr && *mPayload == *paOther.mPayload);
}

std::string EventMessage::getEventType() const {
  return mEventType;
}

int64_t EventMessage::getTimestamp() const { 
  return mTimestamp;
}

// *********************** //
// AbstractPayload Methods //
// *********************** //
AbstractPayload::AbstractPayload(std::string paTypeName, std::string paInstanceName) 
  : mTypeName(std::move(paTypeName)), mInstanceName(std::move(paInstanceName))  {
}

std::string AbstractPayload::getString() const {
  return "{ typeName = \"" + mTypeName + "\", instanceName = \"" + mInstanceName + "\"" + specificPayloadString() + " }";
}

bool AbstractPayload::operator==(const AbstractPayload& paOther) const {
  return mTypeName == paOther.mTypeName && mInstanceName == paOther.mInstanceName && specificPayloadEqual(paOther);
}

// std::string AbstractPayload::getTypeName() const {
//   return mTypeName;
// }


// ******************* //
// FBInputEventPayload //
// ******************* //
FBInputEventPayload::FBInputEventPayload(std::string paTypeName, std::string paInstanceName, const uint64_t paEventId) : 
  AbstractPayload(std::move(paTypeName), std::move(paInstanceName)),
  mEventId(paEventId) {
}

std::unique_ptr<AbstractPayload> FBInputEventPayload::clone() const {
  return std::make_unique<FBInputEventPayload>(*this);
}

std::string FBInputEventPayload::specificPayloadString() const {
  return ", eventId = " + std::to_string(mEventId);
}

bool FBInputEventPayload::specificPayloadEqual(const AbstractPayload& paOther) const {
  if(const auto childInstance = dynamic_cast<const FBInputEventPayload*>(&paOther); childInstance != nullptr){
    return mEventId == childInstance->mEventId;
  }
  return false;
}

// ******************* //
// FBOutputEventPayload //
// ******************* //
FBOutputEventPayload::FBOutputEventPayload(std::string paTypeName, std::string paInstanceName, const uint64_t paEventId) : 
  AbstractPayload(std::move(paTypeName), std::move(paInstanceName)),
   mEventId(paEventId) {
}

std::unique_ptr<AbstractPayload> FBOutputEventPayload::clone() const {
  return std::make_unique<FBOutputEventPayload>(*this);
}

std::string FBOutputEventPayload::specificPayloadString() const {
  return ", eventId = " + std::to_string(mEventId);
}

bool FBOutputEventPayload::specificPayloadEqual(const AbstractPayload& paOther) const {
  if(const auto childInstance = dynamic_cast<const FBOutputEventPayload*>(&paOther); childInstance != nullptr){
      return mEventId == childInstance->mEventId; 
  }
  return false;
}

// ************* //
// FBDataPayload //
// ************* //
FBDataPayload::FBDataPayload(std::string paTypeName, std::string paInstanceName, uint64_t paDataId, std::string paValue) :
  AbstractPayload(std::move(paTypeName), std::move(paInstanceName)),
  mDataId(paDataId), mValue(paValue){
}

std::unique_ptr<AbstractPayload> FBDataPayload::clone() const {
  return std::make_unique<FBDataPayload>(*this);
}

std::string FBDataPayload::specificPayloadString() const {
  auto convertedString = mValue;

  // add backslash to quoutes and double quotes
  for(auto toReplace : {"\"", "\'"}){
    for(auto pos = convertedString.find(toReplace); pos != std::string::npos; pos = convertedString.find(toReplace, pos + 2)){
      convertedString.insert(pos, "\\");
    }
  }
  return ", dataId = " + std::to_string(mDataId) + ", value = \"" + convertedString + "\"";
}

bool FBDataPayload::specificPayloadEqual(const AbstractPayload& paOther) const {
  if(const auto childInstance = dynamic_cast<const FBDataPayload*>(&paOther); childInstance != nullptr){
    return mDataId == childInstance->mDataId && mValue == childInstance->mValue;
  }
  return false;
}

// ********************* //
// FBInstanceDataPayload //
// ********************* //
FBInstanceDataPayload::FBInstanceDataPayload(std::string paTypeName, std::string paInstanceName, const std::vector<std::string>& paInputs,
    const std::vector<std::string>& paOutputs, const std::vector<std::string>& paInternal, const std::vector<std::string>& paInternalFB) : 
      AbstractPayload(std::move(paTypeName), std::move(paInstanceName)),
      mInputs(paInputs), mOutputs(paOutputs), mInternal(paInternal), mInternalFB(paInternalFB)
{
}

std::unique_ptr<AbstractPayload> FBInstanceDataPayload::clone() const {
  return std::make_unique<FBInstanceDataPayload>(*this);
}

std::string FBInstanceDataPayload::specificPayloadString() const {

  auto createStringFromVector = [](const std::vector<std::string>& vec) -> std::string {
    std::string result = "[";
    for(size_t i = 0; i < vec.size(); i++) {
      if(i != 0) {
        result += ",";
      }
      result += " [" + std::to_string(i) + "] = \"" + vec[i] + "\""; 
    }
    result += " ]";
    return result;
  };

  return ", _inputs_len = " + std::to_string(mInputs.size()) + ", inputs = " + createStringFromVector(mInputs) +
    ", _outputs_len = " + std::to_string(mOutputs.size()) + ", outputs = " + createStringFromVector(mOutputs) +
    ", _internal_len = " + std::to_string(mInternal.size()) + ", internal = " + createStringFromVector(mInternal) +
    ", _internalFB_len = " + std::to_string(mInternalFB.size()) + ", internalFB = " + createStringFromVector(mInternalFB);
}

bool FBInstanceDataPayload::specificPayloadEqual(const AbstractPayload& paOther) const {
  if(const auto childInstance = dynamic_cast<const FBInstanceDataPayload*>(&paOther); childInstance != nullptr){
   return mInputs == childInstance->mInputs 
        && mOutputs == childInstance->mOutputs 
        && mInternal == childInstance->mInternal 
        && mInternalFB == childInstance->mInternalFB;
  }
  return false;
}
