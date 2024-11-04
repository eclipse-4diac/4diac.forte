/*******************************************************************************
 * Copyright (c) 2017, 2024 fortiss GmbH, Monika Wenger, Johannes Kepler University Linz
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Johannes Messmer - initial API and implementation and/or initial documentation
 *   Monika Wenger, Alois Zoitl - migration to current runtime
 *******************************************************************************/

#pragma once

#include <funcbloc.h>
#include <forte_bool.h>
#include <forte_uint.h>
#include <forte_wstring.h>

#include <io/configFB/io_configFB_controller.h>

class RevPiConfig: public forte::core::io::IOConfigFBController{
  DECLARE_FIRMWARE_FB(RevPiConfig)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BOOL &QI() {
    return *static_cast<CIEC_BOOL*>(getDI(0));
  };

  CIEC_WSTRING &DigitalInput_1() {
    return *static_cast<CIEC_WSTRING*>(getDI(1));
  };

  CIEC_WSTRING &DigitalInput_2() {
    return *static_cast<CIEC_WSTRING*>(getDI(2));
  };

  CIEC_WSTRING &DigitalInput_3() {
    return *static_cast<CIEC_WSTRING*>(getDI(3));
  };

  CIEC_WSTRING &DigitalInput_4() {
    return *static_cast<CIEC_WSTRING*>(getDI(4));
  };

  CIEC_WSTRING &DigitalInput_5() {
    return *static_cast<CIEC_WSTRING*>(getDI(5));
  };

  CIEC_WSTRING &DigitalInput_6() {
    return *static_cast<CIEC_WSTRING*>(getDI(6));
  };

  CIEC_WSTRING &DigitalInput_7() {
    return *static_cast<CIEC_WSTRING*>(getDI(7));
  };

  CIEC_WSTRING &DigitalInput_8() {
    return *static_cast<CIEC_WSTRING*>(getDI(8));
  };

  CIEC_WSTRING &DigitalInput_9() {
    return *static_cast<CIEC_WSTRING*>(getDI(9));
  };

  CIEC_WSTRING &DigitalInput_10() {
    return *static_cast<CIEC_WSTRING*>(getDI(10));
  };

  CIEC_WSTRING &DigitalInput_11() {
    return *static_cast<CIEC_WSTRING*>(getDI(11));
  };

  CIEC_WSTRING &DigitalInput_12() {
    return *static_cast<CIEC_WSTRING*>(getDI(12));
  };

  CIEC_WSTRING &DigitalInput_13() {
    return *static_cast<CIEC_WSTRING*>(getDI(13));
  };

  CIEC_WSTRING &DigitalInput_14() {
    return *static_cast<CIEC_WSTRING*>(getDI(14));
  };

  CIEC_WSTRING &DigitalOutput_1() {
    return *static_cast<CIEC_WSTRING*>(getDI(15));
  };

  CIEC_WSTRING &DigitalOutput_2() {
    return *static_cast<CIEC_WSTRING*>(getDI(16));
  };

  CIEC_WSTRING &DigitalOutput_3() {
    return *static_cast<CIEC_WSTRING*>(getDI(17));
  };

  CIEC_WSTRING &DigitalOutput_4() {
    return *static_cast<CIEC_WSTRING*>(getDI(18));
  };

  CIEC_WSTRING &DigitalOutput_5() {
    return *static_cast<CIEC_WSTRING*>(getDI(19));
  };

  CIEC_WSTRING &DigitalOutput_6() {
    return *static_cast<CIEC_WSTRING*>(getDI(20));
  };

  CIEC_WSTRING &DigitalOutput_7() {
    return *static_cast<CIEC_WSTRING*>(getDI(21));
  };

  CIEC_WSTRING &DigitalOutput_8() {
    return *static_cast<CIEC_WSTRING*>(getDI(22));
  };

  CIEC_WSTRING &DigitalOutput_9() {
    return *static_cast<CIEC_WSTRING*>(getDI(23));
  };

  CIEC_WSTRING &DigitalOutput_10() {
    return *static_cast<CIEC_WSTRING*>(getDI(24));
  };

  CIEC_WSTRING &DigitalOutput_11() {
    return *static_cast<CIEC_WSTRING*>(getDI(25));
  };

  CIEC_WSTRING &DigitalOutput_12() {
    return *static_cast<CIEC_WSTRING*>(getDI(26));
  };

  CIEC_WSTRING &DigitalOutput_13() {
    return *static_cast<CIEC_WSTRING*>(getDI(27));
  };

  CIEC_WSTRING &DigitalOutput_14() {
    return *static_cast<CIEC_WSTRING*>(getDI(28));
  };

  CIEC_UINT &UpdateInterval() {
    return *static_cast<CIEC_UINT*>(getDI(29));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_BOOL &QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  };

  CIEC_WSTRING &STATUS() {
    return *static_cast<CIEC_WSTRING*>(getDO(1));
  };

  static const TEventID scm_nEventINITID = 0;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];

  static const TEventID scm_nEventINITOID = 0;
  static const TEventID scm_nEventINDID = 1;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

   FORTE_FB_DATA_ARRAY(2, 30, 2, 0);

virtual void setInitialValues();

public:
  FUNCTION_BLOCK_CTOR_WITH_BASE_CLASS(RevPiConfig, forte::core::io::IOConfigFBController){
  };

  virtual ~RevPiConfig(){};

protected:
  forte::core::io::IODeviceController* createDeviceController(CDeviceExecution& paDeviceExecution);
  void setConfig ();

};
