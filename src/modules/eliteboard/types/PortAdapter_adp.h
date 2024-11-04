/*******************************************************************************
 * Copyright (c) 2021, 2022 Jonathan Lainer (kontakt@lainer.co.at)
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jonathan Lainer - Initial implementation.
 *******************************************************************************/

#ifndef _PORTADAPTER_H_
#define _PORTADAPTER_H_

#include "adapter.h"
#include "forte_array_at.h"
#include "forte_dword.h"
#include "typelib.h"

class FORTE_PortAdapter : public CAdapter {
  DECLARE_ADAPTER_TYPE(FORTE_PortAdapter)

private:
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];

public:
  static const TEventID scmEventMAPOID = 0;

private:
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];

public:
  static const TEventID scmEventMAPID = 0;

private:
  static const TDataIOID scmEOWith[];
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpecSocket;

  static const SFBInterfaceSpec scmFBInterfaceSpecPlug;

public:
  TEventID MAPO() { return mParentAdapterListEventID + scmEventMAPOID; }

  TEventID MAP() { return mParentAdapterListEventID + scmEventMAPID; }

  CIEC_DWORD &GPIO_Port_Addr() {
    return *static_cast<CIEC_DWORD *>((isSocket()) ? getDO(0) : getDI(0));
  }

private:

public:
  FORTE_PortAdapter(CStringDictionary::TStringId paAdapterInstanceName,
                    forte::core::CFBContainer &paContainer, bool paIsPlug)
      : CAdapter(paContainer, &scmFBInterfaceSpecSocket,
                 paAdapterInstanceName, &scmFBInterfaceSpecPlug,
                 paIsPlug){};

  ~FORTE_PortAdapter() override = default;
};

#endif // _PORTADAPTER_H_
