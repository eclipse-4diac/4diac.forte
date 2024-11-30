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

#ifndef _DDSCOMLAYER_H_
#define _DDSCOMLAYER_H_

#include "ddspubsub.h"

#include "comlayer.h"

using namespace eprosima::fastrtps::rtps;

namespace forte {

namespace com_infra {

class CDDSComLayer : public CComLayer {
public:
  CDDSComLayer(CComLayer *paUpperLayer, CBaseCommFB *paComFB)
      : CComLayer(paUpperLayer, paComFB) {}
  virtual ~CDDSComLayer(){};

  EComResponse openConnection(char *pa_acLayerParameter) override;
  bool checkIO(std::string paDisplayName, unsigned int paSDCount,
               unsigned int paRDCount);
  bool openPublisherConnection();
  bool openSubscriberConnection();
  void closeConnection() override;

  EComResponse sendData(void *paData, unsigned int paSize) override;
  EComResponse recvData(const void *paData, unsigned int paSize) override;

  EComResponse processInterrupt() override;

  // other methods

private:
  forte::com_infra::EComServiceType m_eCommServiceType;

  std::string m_sPubTopicName;
  std::string m_sPubTopicType;

  std::string m_sSubTopicName;
  std::string m_sSubTopicType;

  CDDSPubSub *m_pPublisher;
  CDDSPubSub *m_pSubscriber;

  std::queue<SRequestInfo> *m_pRequestInfos;
  EPubSubRole m_enPubSubRole;
};

} // namespace com_infra

} // namespace forte

#endif /* _DDSCOMLAYER_H_ */
