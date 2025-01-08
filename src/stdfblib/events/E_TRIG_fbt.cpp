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

#include "E_TRIG_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_TRIG_fbt_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_E_TRIG, g_nStringIdE_TRIG)

const CStringDictionary::TStringId FORTE_E_TRIG::scmDataInputNames[] = {g_nStringIdEVENTTYPE};
const CStringDictionary::TStringId FORTE_E_TRIG::scmDataInputTypeIds[] = {g_nStringIdSTRING};
const TDataIOID FORTE_E_TRIG::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_E_TRIG::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_E_TRIG::scmEventInputNames[] = {g_nStringIdREQ};
const TForteInt16 FORTE_E_TRIG::scmEOWithIndexes[] = {-1};
const CStringDictionary::TStringId FORTE_E_TRIG::scmEventOutputNames[] = {g_nStringIdCNF};
const SFBInterfaceSpec FORTE_E_TRIG::scmFBInterfaceSpec = {
  1, scmEventInputNames, nullptr, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, nullptr, nullptr, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

FORTE_E_TRIG::FORTE_E_TRIG(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_EVENTTYPE(""_STRING),
    conn_CNF(this, 0),
    conn_EVENTTYPE(nullptr) {
};

void FORTE_E_TRIG::setInitialValues() {
  var_EVENTTYPE = ""_STRING;
}

void FORTE_E_TRIG::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      const TEventTypeID eventTypeId = CStringDictionary::getInstance().getId(var_EVENTTYPE.c_str());
      if (eventTypeId != CStringDictionary::scmInvalidStringId) {
        triggerEvents(getResource(), eventTypeId);
        sendOutputEvent(scmEventCNFID, paECET);
      }
      break;
  }
}

void FORTE_E_TRIG::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_EVENTTYPE, conn_EVENTTYPE);
      break;
    }
    default:
      break;
  }
}

void FORTE_E_TRIG::writeOutputData(TEventID) {
  // nothing to do
}

CIEC_ANY *FORTE_E_TRIG::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_EVENTTYPE;
  }
  return nullptr;
}

CIEC_ANY *FORTE_E_TRIG::getDO(size_t) {
  return nullptr;
}

CEventConnection *FORTE_E_TRIG::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_E_TRIG::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_EVENTTYPE;
  }
  return nullptr;
}

CDataConnection *FORTE_E_TRIG::getDOConUnchecked(TPortId) {
  return nullptr;
}

void FORTE_E_TRIG::triggerEvents(forte::core::CFBContainer* paContainer, TEventTypeID paEventType) {
  if (paContainer != nullptr) {
    if (paContainer->isFB()) {
      static_cast<CFunctionBlock*>(paContainer)->triggerEventsOfType(paEventType);
    }
    if (paContainer->isDynamicContainer()) {
      for (auto child: paContainer->getChildren()) {
        triggerEvents(child, paEventType);
      }
    }
  }
}
