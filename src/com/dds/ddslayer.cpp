/*******************************************************************************
 * Copyright (c) 2024 OFFIS e.V.
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Malte Grave - initial implementation
 ********************************************************************************/

#include <boost/regex.h>
#include <memory>
#include <string>

#include "ddslayer.h"

#include "ddshandler.h"

#include "basecommfb.h"
#include "comtypes.h"
#include "devlog.h"
#include "forte_struct.h"

// according to https://design.ros2.org/articles/topic_and_service_names.html
// square brackets, semicolons and colons are not valid parts of valid dds
// topic, therefore the following style can be used
//
// ID data input for this:
// dds[topic_name:topic_type] for publisher and subscriber
// dds[topic_name:topic_type;topic_name:topic_type] for clients and servers
// clients: left-pub right-sub => send request, await response
// server: left-sub right-pub => await request, send response

using namespace forte::com_infra;

EComResponse CDDSComLayer::openConnection(char *pa_acLayerParameter) {

  this->m_eCommServiceType = getCommFB()->getComServiceType();

  std::string layerParams = pa_acLayerParameter;
  std::string left, right;
  std::string leftTopicName, leftTopicType, rightTopicName, rightTopicType;

  // split the string on ";"
  size_t semicolon_pos = layerParams.find(";");
  if (semicolon_pos != std::string::npos) {
    left = layerParams.substr(0, semicolon_pos);
    right = layerParams.substr(semicolon_pos + 1);
  } else
    left = layerParams;

  // split each substring on ":"
  size_t colon_pos = left.find(":");
  if (colon_pos != std::string::npos) {
    leftTopicName = left.substr(0, colon_pos);
    leftTopicType = left.substr(colon_pos + 1);
  }

  colon_pos = right.find(":");
  if (colon_pos != std::string::npos) {
    rightTopicName = right.substr(0, colon_pos);
    rightTopicType = right.substr(colon_pos + 1);
  }

  DEVLOG_DEBUG(
      ("[DDS Layer] Left topic name is '" + leftTopicName + "'.\n").c_str());
  DEVLOG_DEBUG(
      ("[DDS Layer] Left topic type is '" + leftTopicType + "'.\n").c_str());
  DEVLOG_DEBUG(
      ("[DDS Layer] Right topic name is '" + rightTopicName + "'.\n").c_str());
  DEVLOG_DEBUG(
      ("[DDS Layer] Right topic type is '" + rightTopicType + "'.\n").c_str());

  // Clients and servers are needed to implement ROS services correctly.
  // They compose of a publisher and subscriber at the same time and share data
  // between them.

  switch (this->m_eCommServiceType) {

  case EComServiceType::e_Publisher:
    this->m_enPubSubRole = EPubSubRole::NONE;
    this->m_sPubTopicName = leftTopicName;
    this->m_sPubTopicType = leftTopicType;
    if (!this->checkIO("Publisher", 1, 0))
      return EComResponse::e_InitInvalidId;
    if (!this->openPublisherConnection())
      return EComResponse::e_InitInvalidId;
    return EComResponse::e_InitOk;

  case EComServiceType::e_Subscriber:
    this->m_enPubSubRole = EPubSubRole::NONE;
    this->m_sSubTopicName = leftTopicName;
    this->m_sSubTopicType = leftTopicType;
    if (!this->checkIO("Subscriber", 0, 1))
      return EComResponse::e_InitInvalidId;
    if (!this->openSubscriberConnection())
      return EComResponse::e_InitInvalidId;
    return EComResponse::e_InitOk;

  case EComServiceType::e_Server:
    this->m_enPubSubRole = EPubSubRole::SERVER;
    this->m_sSubTopicName = leftTopicName;
    this->m_sSubTopicType = leftTopicType;
    this->m_sPubTopicName = rightTopicName;
    this->m_sPubTopicType = rightTopicType;
    this->m_pRequestInfos = new std::queue<SRequestInfo>();
    if (!this->checkIO("Server", 1, 1))
      return EComResponse::e_InitInvalidId;
    if (!this->openSubscriberConnection())
      return EComResponse::e_InitInvalidId;
    this->m_pSubscriber->setIdentityQueue(this->m_pRequestInfos);
    if (!this->openPublisherConnection())
      return EComResponse::e_InitInvalidId;
    this->m_pPublisher->setIdentityQueue(this->m_pRequestInfos);
    return EComResponse::e_InitOk;

  case EComServiceType::e_Client:
    this->m_enPubSubRole = EPubSubRole::CLIENT;
    this->m_sPubTopicName = leftTopicName;
    this->m_sPubTopicType = leftTopicType;
    this->m_sSubTopicName = rightTopicName;
    this->m_sSubTopicType = rightTopicType;
    this->m_pRequestInfos = new std::queue<SRequestInfo>();
    if (!this->checkIO("Client", 1, 1))
      return EComResponse::e_InitInvalidId;
    if (!this->openPublisherConnection())
      return EComResponse::e_InitInvalidId;
    this->m_pPublisher->setIdentityQueue(this->m_pRequestInfos);
    if (!this->openSubscriberConnection())
      return EComResponse::e_InitInvalidId;
    this->m_pSubscriber->setIdentityQueue(this->m_pRequestInfos);
    return EComResponse::e_InitOk;
  }
}

bool CDDSComLayer::checkIO(std::string paDisplayName, unsigned int paSDCount,
                           unsigned int paRDCount) {
  auto fb = this->getCommFB();

  // check for valid SD count
  if (fb->getNumSD() != paSDCount) {
    DEVLOG_ERROR(("[DDS Layer] " + paDisplayName + "s need exactly " +
                  std::to_string(paSDCount) + " SD input.\n")
                     .c_str());
    return false;
  }
  auto *data = static_cast<CIEC_STRUCT *>(fb->getSDs()[0]);

  // check for valid type on SD
  if (paSDCount && data->getDataTypeID() != CIEC_ANY::EDataTypeID::e_STRUCT) {
    DEVLOG_ERROR("[DDS Layer] Only STRUCT is supported on SD input.\n");
    return false;
  }

  // check for valid RD count
  if (fb->getNumRD() != paRDCount) {
    DEVLOG_ERROR(("[DDS Layer] " + paDisplayName + "s need exactly " +
                  std::to_string(paRDCount) + " RD output.\n")
                     .c_str());
    return false;
  }
  auto rds = fb->getRDs()[0];
  // check for valid type on RD
  if (paRDCount &&
      rds->unwrap().getDataTypeID() != CIEC_ANY::EDataTypeID::e_STRUCT) {
    DEVLOG_ERROR("[DDS Layer] Only STRUCT is supported on RD output.\n");
    return false;
  }

  return true;
}

bool CDDSComLayer::openPublisherConnection() {
  CBaseCommFB *fb = this->getCommFB();
  CIEC_STRUCT *data = static_cast<CIEC_STRUCT *>(fb->getSDs()[0]);

  this->m_pPublisher = CDDSPubSub::selectPubSub(
      this->m_sPubTopicName, this->m_sPubTopicType, this->m_enPubSubRole);

  if (this->m_pPublisher == nullptr) {
    DEVLOG_ERROR("[DDS Layer] Topic type unknown.\n");
    return false;
  }

  if (!this->m_pPublisher->validateType(data->unwrap().getTypeNameID())) {
    DEVLOG_ERROR("[DDS Layer] Data type not correct.\n");
    return false;
  }

  if (!this->m_pPublisher->initPublisher()) {
    DEVLOG_ERROR("[DDS Layer] Could not initialize publisher.\n");
    return false;
  }

  return true;
}

bool CDDSComLayer::openSubscriberConnection() {
  CBaseCommFB *fb = this->getCommFB();
  auto data = fb->getRDs()[0];

  this->m_pSubscriber = CDDSPubSub::selectPubSub(
      this->m_sSubTopicName, this->m_sSubTopicType, this->m_enPubSubRole);
  if (this->m_pSubscriber == nullptr) {
    DEVLOG_ERROR(
        ("[DDS Layer] Topic type unknown: " + this->m_sSubTopicType + "\n")
            .c_str());
    return false;
  }
  if (!this->m_pSubscriber->validateType(data->unwrap().getTypeNameID())) {
    DEVLOG_ERROR(
        ("[DDS Layer] Data type not correct: " + this->m_sSubTopicType + "\n")
            .c_str());
    return false;
  }
  if (!this->m_pSubscriber->initSubscriber(
          &this->getExtEvHandler<CDDSHandler>())) {
    DEVLOG_ERROR("[DDS Layer] Could not initialize subscriber.\n");
    return false;
  }

  this->getExtEvHandler<CDDSHandler>().registerLayer(
      this->m_pSubscriber->getReaderGUID().value(), this);

  return true;
}

void CDDSComLayer::closeConnection() {
  delete this->m_pPublisher;
  delete this->m_pSubscriber;
  this->getExtEvHandler<CDDSHandler>().unregisterLayer(
      this->m_pSubscriber->getReaderGUID().value());
  delete this->m_pRequestInfos;
}

EComResponse CDDSComLayer::sendData(void *paData, unsigned int paSize) {
  auto data = static_cast<CIEC_STRUCT *>(
      &((static_cast<CIEC_ANY **>(paData)[0])->unwrap()));
  char sendDebug[1024] = {};
  data->toString(sendDebug, sizeof(sendDebug));
  switch (this->m_pPublisher->publish(data)) {
  case false:
    DEVLOG_ERROR(("[DDS Layer] Failed to send data on '" +
                  this->m_sPubTopicName + "': " + sendDebug + "\n")
                     .c_str());
    return EComResponse::e_ProcessDataSendFailed;

  case true:
    DEVLOG_DEBUG(("[DDS Layer] Sending data on '" + this->m_sPubTopicName +
                  "': " + sendDebug + "\n")
                     .c_str());
    return EComResponse::e_ProcessDataOk;
  }
}

EComResponse CDDSComLayer::recvData(const void *paData, unsigned int paSize) {
  // receive data via the subscriber
  std::optional<std::unique_ptr<CIEC_STRUCT>> ciecStructOpt =
      this->m_pSubscriber->receive();
  if (ciecStructOpt.has_value()) {
    CIEC_STRUCT &ciecStruct = *(*ciecStructOpt);
    char recvDebug[255] = {};
    ciecStruct.toString(recvDebug, sizeof(recvDebug));
    DEVLOG_DEBUG(("[DDS Layer] Received data on '" + this->m_sSubTopicName +
                  "': " + recvDebug + "\n")
                     .c_str());
    this->getCommFB()->getRDs()[0]->unwrap().setValue(ciecStruct);
    this->mFb->interruptCommFB(this);

    return EComResponse::e_ProcessDataOk;
  }

  return EComResponse::e_Nothing;
}

EComResponse CDDSComLayer::processInterrupt() {
  // we don't need to do anything here (only 1 layer)
  return EComResponse::e_ProcessDataOk;
}
