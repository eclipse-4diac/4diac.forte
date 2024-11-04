/*******************************************************************************
 * Copyright (c) 2018, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral - initial implementation
 *******************************************************************************/

#ifndef _REGISTERSERVICEADP_H_
#define _REGISTERSERVICEADP_H_

#include <adapter.h>
#include <typelib.h>
#include <forte_serviceregistryentry.h>
#include <forte_wstring.h>

class FORTE_RegisterServiceAdp: public CAdapter{
  DECLARE_ADAPTER_TYPE(FORTE_RegisterServiceAdp)

private:
 private:
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
 public:
  CIEC_ServiceRegistryEntry &serviceRegistryEntry() {
    return *static_cast<CIEC_ServiceRegistryEntry*>((isSocket()) ? getDO(0) : getDI(0));
  };

  CIEC_WSTRING &endpoint() {
    return *static_cast<CIEC_WSTRING*>((isSocket()) ? getDO(1) : getDI(1));
  };

 public:
  static const TEventID scmEventdoneRegisterID = 0;
  TEventID doneRegister() {
    return mParentAdapterListEventID + scmEventdoneRegisterID;
  }
  static const TEventID scmEventdoneUnregisterID = 1;
  TEventID doneUnregister() {
    return mParentAdapterListEventID + scmEventdoneUnregisterID;
  }
 private:
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];

 public:
  static const TEventID scmEventregisterServiceID = 0;
  TEventID registerService() {
    return mParentAdapterListEventID + scmEventregisterServiceID;
  }
  static const TEventID scmEventunregisterServiceID = 1;
  TEventID unregisterService() {
    return mParentAdapterListEventID + scmEventunregisterServiceID;
  }
 private:
  static const TForteInt16 scmEOWithIndexes[];
  static const TDataIOID scmEOWith[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpecSocket;

  static const SFBInterfaceSpec scmFBInterfaceSpecPlug;


public:
  ADAPTER_CTOR(FORTE_RegisterServiceAdp){
  };

  ~FORTE_RegisterServiceAdp() override = default;

};

#endif //close the ifdef sequence from the beginning of the file

