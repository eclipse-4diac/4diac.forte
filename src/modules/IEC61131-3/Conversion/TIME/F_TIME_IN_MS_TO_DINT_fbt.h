/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: F_TIME_IN_MS_TO_DINT
 *** Description: Convert TIME in MS to UDINT
 *** Version:
 ***     1.0: 2023-04-28/Martin Jobst -  -
 ***     1.1: 2023-08-21/Franz Höpfinger - HR Agrartechnik GmbH -
 *************************************************************************/

#pragma once

#include "simplefb.h"
#include "forte_time.h"
#include "forte_dint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_F_TIME_IN_MS_TO_DINT final : public CSimpleFB {
  DECLARE_FIRMWARE_FB(FORTE_F_TIME_IN_MS_TO_DINT)

private:
  static const CStringDictionary::TStringId scmDataInputNames[];
  static const CStringDictionary::TStringId scmDataInputTypeIds[];
  static const CStringDictionary::TStringId scmDataOutputNames[];
  static const CStringDictionary::TStringId scmDataOutputTypeIds[];
  static const TEventID scmEventREQID = 0;
  static const TDataIOID scmEIWith[];
  static const TForteInt16 scmEIWithIndexes[];
  static const CStringDictionary::TStringId scmEventInputNames[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];
  static const TEventID scmEventCNFID = 0;
  static const TDataIOID scmEOWith[];
  static const TForteInt16 scmEOWithIndexes[];
  static const CStringDictionary::TStringId scmEventOutputNames[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];

  static const SFBInterfaceSpec scmFBInterfaceSpec;

  CIEC_ANY *getVarInternal(size_t) override;

  void alg_REQ(void);

  void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

  void readInputData(TEventID paEIID) override;
  void writeOutputData(TEventID paEIID) override;
  void setInitialValues() override;

public:
  FORTE_F_TIME_IN_MS_TO_DINT(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  CIEC_TIME var_IN;

  CIEC_DINT var_OUT;

  CIEC_DINT var_conn_OUT;

  CEventConnection conn_CNF;

  CDataConnection *conn_IN;

  CDataConnection conn_OUT;

  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CIEC_ANY *getDIO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  CInOutDataConnection **getDIOInConUnchecked(TPortId) override;
  CInOutDataConnection *getDIOOutConUnchecked(TPortId) override;

  void evt_REQ(const CIEC_TIME &paIN, CIEC_DINT &paOUT) {
    var_IN = paIN;
    receiveInputEvent(scmEventREQID, nullptr);
    paOUT = var_OUT;
  }

  void operator()(const CIEC_TIME &paIN, CIEC_DINT &paOUT) {
    evt_REQ(paIN, paOUT);
  }
};


