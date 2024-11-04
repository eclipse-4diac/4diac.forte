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

#ifndef _ELITEBOARD_H_
#define _ELITEBOARD_H_

#include "core/io/configFB/io_configFB_controller.h"
#include "PortAdapter_adp.h"
#include "forte_array_at.h"
#include "funcbloc.h"
#include <extevhandlerhelper.h>
#include <handler/EliteBoardDeviceController.h>

class FORTE_EliteBoard : public forte::core::io::IOConfigFBController {
  DECLARE_FIRMWARE_FB(FORTE_EliteBoard)

private:
  static const TEventID scmEventMAPID = 0;

  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];

  static const TEventID scmEventMAPOID = 0;

  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const int scmPortAAdpNum = 0;
  static const int scmPortBAdpNum = 1;
  static const int scmPortCAdpNum = 2;
  static const int scmPortDAdpNum = 3;
  static const int scmPortEAdpNum = 4;
  static const int scmPortFAdpNum = 5;
  static const int scmPortGAdpNum = 6;
  static const int scmPortHAdpNum = 7;
  static const int scmPortIAdpNum = 8;
  static const int scmPortJAdpNum = 9;
  static const int scmPortKAdpNum = 10;

  static const SAdapterInstanceDef scmAdapterInstances[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;

  FORTE_PortAdapter &st_PortA() {
    return (*static_cast<FORTE_PortAdapter *>(mAdapters[0]));
  };

  FORTE_PortAdapter &st_PortB() {
    return (*static_cast<FORTE_PortAdapter *>(mAdapters[1]));
  };

  FORTE_PortAdapter &st_PortC() {
    return (*static_cast<FORTE_PortAdapter *>(mAdapters[2]));
  };

  FORTE_PortAdapter &st_PortD() {
    return (*static_cast<FORTE_PortAdapter *>(mAdapters[3]));
  };

  FORTE_PortAdapter &st_PortE() {
    return (*static_cast<FORTE_PortAdapter *>(mAdapters[4]));
  };

  FORTE_PortAdapter &st_PortF() {
    return (*static_cast<FORTE_PortAdapter *>(mAdapters[5]));
  };

  FORTE_PortAdapter &st_PortG() {
    return (*static_cast<FORTE_PortAdapter *>(mAdapters[6]));
  };

  FORTE_PortAdapter &st_PortH() {
    return (*static_cast<FORTE_PortAdapter *>(mAdapters[7]));
  };

  FORTE_PortAdapter &st_PortI() {
    return (*static_cast<FORTE_PortAdapter *>(mAdapters[8]));
  };

  FORTE_PortAdapter &st_PortJ() {
    return (*static_cast<FORTE_PortAdapter *>(mAdapters[9]));
  };

  FORTE_PortAdapter &st_PortK() {
    return (*static_cast<FORTE_PortAdapter *>(mAdapters[10]));
  };


  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;
 
  void setConfig() {}
  
  EliteBoardDeviceController& mEventHandler;
  int mCurrentAdapterIndex = 0;
  static const int mAdapterCount = scmPortKAdpNum + 1;

  forte::core::io::IODeviceController *
  createDeviceController(CDeviceExecution &paDeviceExecution);
  FORTE_PortAdapter &getPortAdapterByIndex(int index);
  bool configurePortFB(int index);

public:

  FORTE_EliteBoard(const CStringDictionary::TStringId paInstanceNameId, 
      forte::core::CFBContainer &paContainer);

  ~FORTE_EliteBoard() override = default;
};

#endif // _ELITEBOARD_H_
