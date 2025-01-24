/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: E_TRIG
 *** Description: Service Interface Function Block Type
 *** Version:
 ***     1.0: 2025-01-08/mario -  -
 *************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_string.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

class FORTE_E_TRIG final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_E_TRIG)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const TEventID scmEventREQID = 0;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const TEventID scmEventCNFID = 0;
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

    void triggerEvents(forte::core::CFBContainer* paContainer, TEventTypeID paEventType);

  public:
    FORTE_E_TRIG(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_STRING var_EVENTTYPE;

    CEventConnection conn_CNF;

    CDataConnection *conn_EVENTTYPE;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_REQ(const CIEC_STRING &paEVENTTYPE) {
      var_EVENTTYPE = paEVENTTYPE;
      executeEvent(scmEventREQID, nullptr);
    }

    void operator()(const CIEC_STRING &paEVENTTYPE) {
      evt_REQ(paEVENTTYPE);
    }
};

