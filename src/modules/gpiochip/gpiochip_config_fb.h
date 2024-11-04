/*******************************************************************************
 * Copyright (c) 2023 OFFIS e.V.
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jörg Walter - initial implementation
 *******************************************************************************/

#pragma once

#include <funcbloc.h>
#include <forte_bool.h>
#include <forte_uint.h>
#include <forte_wstring.h>
#include <io/configFB/io_configFB_controller.h>

class GPIOChipConfigFB : public forte::core::io::IOConfigFBController {
  DECLARE_FIRMWARE_FB(GPIOChipConfigFB)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  CIEC_BOOL &QI() {
    return *static_cast<CIEC_BOOL*>(getDI(0));
  };

  CIEC_WSTRING &VALUE() {
    return *static_cast<CIEC_WSTRING*>(getDI(1));
  };

  CIEC_UINT &ChipNumber() {
    return *static_cast<CIEC_UINT*>(getDI(2));
  };

  CIEC_UINT &LineNumber() {
    return *static_cast<CIEC_UINT*>(getDI(3));
  };

  CIEC_UINT &ReadWriteMode() {
    return *static_cast<CIEC_UINT*>(getDI(4));
  };

  CIEC_UINT &BiasMode() {
    return *static_cast<CIEC_UINT*>(getDI(5));
  };

  CIEC_BOOL &ActiveLow() {
    return *static_cast<CIEC_BOOL*>(getDI(6));
  };


  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  CIEC_BOOL &QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  };

  CIEC_WSTRING &STATUS() {
    return *static_cast<CIEC_WSTRING*>(getDO(1));
  };

  static const TEventID scmEventINITID = 0;
  static const TForteInt16 scmEIWithIndexes[];
  static const TDataIOID scmEIWith[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];

  static const TEventID scmEventINITOID = 0;
  static const TEventID scmEventINDID = 1;
  static const TForteInt16 scmEOWithIndexes[];
  static const TDataIOID scmEOWith[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;


  void setInitialValues() override;
  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;

  protected:
    forte::core::io::IODeviceController* createDeviceController(CDeviceExecution &paDeviceExecution);
  
    void setConfig();

    void onStartup(CEventChainExecutionThread * const paECET) override;

  public:
    FUNCTION_BLOCK_CTOR_WITH_BASE_CLASS(GPIOChipConfigFB, forte::core::io::IOConfigFBController){}

};

