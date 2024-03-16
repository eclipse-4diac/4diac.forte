/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: TOD2TOD
 *** Description:
 *** Version:
 ***     1.0: 2023-04-28/Martin Jobst -  -
 *************************************************************************/

#pragma once

#include "simplefb.h"
#include "forte_time_of_day.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_TOD2TOD final : public CSimpleFB {
  DECLARE_FIRMWARE_FB(FORTE_TOD2TOD)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventREQID = 0;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const TEventID scmEventCNFID = 0;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    CIEC_ANY *getVarInternal(size_t) override;

    void alg_REQ(void);

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

  public:
    FORTE_TOD2TOD(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_TIME_OF_DAY var_IN;

    CIEC_TIME_OF_DAY var_OUT;

    CIEC_TIME_OF_DAY var_conn_OUT;

    CEventConnection conn_CNF;

    CDataConnection *conn_IN;

    CDataConnection conn_OUT;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_REQ(const CIEC_TIME_OF_DAY &paIN, CIEC_TIME_OF_DAY &paOUT) {
      var_IN = paIN;
      executeEvent(scmEventREQID, nullptr);
      paOUT = var_OUT;
    }

    void operator()(const CIEC_TIME_OF_DAY &paIN, CIEC_TIME_OF_DAY &paOUT) {
      evt_REQ(paIN, paOUT);
    }
};


