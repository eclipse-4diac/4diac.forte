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

#ifndef _DDSPUBSUB_H_
#define _DDSPUBSUB_H_

#include <optional>
#include <queue>

// forte
#include "basecommfb.h"
#include "stringdict.h"

// fast dds generic
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

// fast dds publisher
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>

// fast dds subscriber
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>

namespace forte {
namespace com_infra {
class CDDSHandler;
}
} // namespace forte

using namespace forte::com_infra;
using namespace eprosima::fastdds::dds;
using namespace eprosima::fastrtps::types;
using namespace eprosima::fastrtps::rtps;

// enum representing the role of this pub sub
enum EPubSubRole { NONE, SERVER, CLIENT };

// struct for request meta data, needed for servers and clients
struct SRequestInfo {
  GUID_t guid;
  SequenceNumber_t sequence;
};

class CDDSPubSub {
public:
  CDDSPubSub(std::string pa_sTopicName, EPubSubRole pa_enRole)
      : m_sTopicName(pa_sTopicName), m_pParticipant(nullptr), m_pTopic(nullptr),
        m_pPublisher(nullptr), m_pWriter(nullptr), mSequenceNumber(0),
        m_enRole(pa_enRole) {}
  virtual ~CDDSPubSub();
  static CDDSPubSub *selectPubSub(std::string pa_sTopicName,
                                  std::string pa_sTopicType,
                                  EPubSubRole pa_enPubSubRole);

  bool initCommon();
  bool initPublisher();
  bool initSubscriber(CDDSHandler *pa_pHandler);
  void setIdentityQueue(std::queue<SRequestInfo> *pa_pRequestInfo);
  std::optional<GUID_t> getReaderGUID();

  virtual std::string registerType(DomainParticipant *pa_pParticipant) = 0;
  virtual bool validateType(const CStringDictionary::TStringId paTypeId) = 0;
  virtual bool publish(CIEC_STRUCT *pa_pData) = 0;
  // read in data and construct a CIEC_STRUCT
  virtual std::optional<std::unique_ptr<CIEC_STRUCT>> receive() = 0;

protected:
  bool write(void *pa_pData);
  ReturnCode_t take(bool *pa_pTaken, void *pa_pData);

private:
  std::string m_sTopicName;
  std::string m_sTopicType;

  DomainParticipant *m_pParticipant;
  Topic *m_pTopic;

  Publisher *m_pPublisher;
  DataWriter *m_pWriter;

  Subscriber *m_pSubscriber;
  DataReader *m_pReader;
  class CSubListener : public DataReaderListener {
  public:
    CSubListener() {}
    ~CSubListener() override {}

    CDDSHandler *m_pHandler;

    inline void on_data_available(DataReader *pa_pReader);
  } mReaderListener;

  std::queue<SRequestInfo> *m_pRequestInfos;
  SequenceNumber_t mSequenceNumber;
  EPubSubRole m_enRole;
};

#endif /* _DDSPUBSUB_H_ */
