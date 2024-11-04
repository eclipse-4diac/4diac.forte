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

#ifndef _ARROWHEADPUBLISH_H_
#define _ARROWHEADPUBLISH_H_

#include <cfb.h>
#include <typelib.h>
#include <forte_publishevent.h>
#include <forte_wstring.h>
#include "ArrowheadPublishAdp_adp.h"

class FORTE_ArrowheadPublish: public CCompositeFB{
  DECLARE_FIRMWARE_FB(FORTE_ArrowheadPublish)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  CIEC_PublishEvent &publishEvent() {
    return *static_cast<CIEC_PublishEvent*>(getDI(0));
  };

  CIEC_WSTRING &endpoint() {
    return *static_cast<CIEC_WSTRING*>(getDI(1));
  };

  static const TEventID scmEventpublishID = 0;
  static const TForteInt16 scmEIWithIndexes[];
  static const TDataIOID scmEIWith[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];

  static const TEventID scmEventpublishedID = 0;
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SAdapterInstanceDef scmAdapterInstances[];

  FORTE_ArrowheadPublishAdp& ArrowheadPublishAdp() {
    return (*static_cast<FORTE_ArrowheadPublishAdp*>(mAdapters[0]));
  };
  static const int scmArrowheadPublishAdpAdpNum = 0;
  static const SFBInterfaceSpec scmFBInterfaceSpec;


  static const SCFB_FBConnectionData scmEventConnections[];

  static const SCFB_FBConnectionData scmDataConnections[];
  static const SCFB_FBNData scmFBNData;

public:
  COMPOSITE_FUNCTION_BLOCK_CTOR(FORTE_ArrowheadPublish){
  };

  ~FORTE_ArrowheadPublish() override = default;

};

#endif //close the ifdef sequence from the beginning of the file

