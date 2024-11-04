/*******************************************************************************
 * Copyright (c) 2019, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral - initial implementation
 *******************************************************************************/

#ifndef _SUBSCRIBEEVENTADP_H_
#define _SUBSCRIBEEVENTADP_H_

#include <adapter.h>
#include <typelib.h>
#include <forte_eventfilter.h>
#include <forte_wstring.h>

class FORTE_SubscribeEventAdp: public CAdapter{
  DECLARE_ADAPTER_TYPE(FORTE_SubscribeEventAdp)

private:
 private:
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
 public:
  CIEC_EventFilter &eventFilter() {
    return *static_cast<CIEC_EventFilter*>((isSocket()) ? getDO(0) : getDI(0));
  };

  CIEC_WSTRING &endpoint() {
    return *static_cast<CIEC_WSTRING*>((isSocket()) ? getDO(1) : getDI(1));
  };

 public:
  static const TEventID scmEventSubscribedID = 0;
  int Subscribed() {
    return mParentAdapterListEventID + scmEventSubscribedID;
  }
  static const TEventID scmEventUnsubscribedID = 1;
  int Unsubscribed() {
    return mParentAdapterListEventID + scmEventUnsubscribedID;
  }
 private:
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];

 public:
  static const TEventID scmEventSubscribeID = 0;
  int Subscribe() {
    return mParentAdapterListEventID + scmEventSubscribeID;
  }
  static const TEventID scmEventUnsubscribeID = 1;
  int Unsubscribe() {
    return mParentAdapterListEventID + scmEventUnsubscribeID;
  }
 private:
  static const TForteInt16 scmEOWithIndexes[];
  static const TDataIOID scmEOWith[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpecSocket;

  static const SFBInterfaceSpec scmFBInterfaceSpecPlug;


public:
  ADAPTER_CTOR(FORTE_SubscribeEventAdp){
  };

  ~FORTE_SubscribeEventAdp() override = default;

};

#endif //close the ifdef sequence from the beginning of the file

