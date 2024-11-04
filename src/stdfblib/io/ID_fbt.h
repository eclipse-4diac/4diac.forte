/*************************************************************************
 * Copyright (c) 2015, 2016 fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Gerd Kainz - initial API and implementation and/or initial documentation
 *   Jose Cabral - Modification to double
 *************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_string.h"
#include "forte_dword.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

#include "processinterface.h"

/*! /brief generic class for IW function blocks providing access to one word physical input
 *
 * In order that this FB can be used implementations need to provide a class CProcessInterface
 * this class needs to inherit from CProcessInterfaceBase and provide the following functions
 *
 *   - bool initialise(bool paInput, CEventChainExecutionThread *const paECET)
 *     Initialize the physical input identified with the value of the PARAMS input
 *       - @param paInput: if true it should be an input, if false it should be an output
 *       - @return true on success, false on error
 *
 *   - bool deinitialise()
 *     Deinitialize the physical port
 *       - @return true on success, false on error
 *
 *   - bool readDWord()
 *     Read the value of the physical input word and apply it to the function block's OUT() data output
 *       - @return true on success, false on error
 *
 * TODO a higher flexibility and easier use could be achieve if the base class would be a template parameter. However
 *   currently it is very hard to templatize a function block class.
 */
class FORTE_ID final : public CProcessInterface {
  DECLARE_FIRMWARE_FB(FORTE_ID)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  static const TEventID scmEventINITID = 0;
  static const TEventID scmEventREQID = 1;
  static const TDataIOID scmEIWith[];
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];
  static const TEventID scmEventINITOID = 0;
  static const TEventID scmEventCNFID = 1;
  static const TEventID scmEventINDID = 2;
  static const TDataIOID scmEOWith[]; 
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;

  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
  void setInitialValues() override;

public:
  FORTE_ID(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_BOOL var_QI;
  CIEC_STRING var_PARAMS;
  CIEC_BOOL var_QO;
  CIEC_STRING var_STATUS;
  CIEC_DWORD var_IN;
  CIEC_BOOL var_conn_QO;
  CIEC_STRING var_conn_STATUS;
  CIEC_DWORD var_conn_IN;
  CEventConnection conn_INITO;
  CEventConnection conn_CNF;
  CEventConnection conn_IND;
  CDataConnection *conn_QI;
  CDataConnection *conn_PARAMS;
  CDataConnection conn_QO;
  CDataConnection conn_STATUS;
  CDataConnection conn_IN;
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  void evt_INIT(const CIEC_BOOL &pa_QI, const CIEC_STRING &pa_PARAMS, CIEC_BOOL &pa_QO, CIEC_STRING &pa_STATUS, CIEC_DWORD &pa_IN) {
    var_QI = pa_QI;
    var_PARAMS = pa_PARAMS;
    receiveInputEvent(scmEventINITID, nullptr);
    pa_QO = var_QO;
    pa_STATUS = var_STATUS;
    pa_IN = var_IN;
  }
  void evt_REQ(const CIEC_BOOL &pa_QI, const CIEC_STRING &pa_PARAMS, CIEC_BOOL &pa_QO, CIEC_STRING &pa_STATUS, CIEC_DWORD &pa_IN) {
    var_QI = pa_QI;
    var_PARAMS = pa_PARAMS;
    receiveInputEvent(scmEventREQID, nullptr);
    pa_QO = var_QO;
    pa_STATUS = var_STATUS;
    pa_IN = var_IN;
  }
  void operator()(const CIEC_BOOL &pa_QI, const CIEC_STRING &pa_PARAMS, CIEC_BOOL &pa_QO, CIEC_STRING &pa_STATUS, CIEC_DWORD &pa_IN) {
    evt_INIT(pa_QI, pa_PARAMS, pa_QO, pa_STATUS, pa_IN);
  }
};



