/*******************************************************************************
 * Copyright (c) 2019, 2023 fortiss GmbH
 *                          Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral - initial implementation
 *   Martin Jobst - add readInputData and writeOutputData
 *******************************************************************************/

#include "TEST_CONDITION_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "TEST_CONDITION_fbt_gen.cpp"
#endif

#include "devlog.h"
#include "resource.h"
#include "criticalregion.h"

unsigned int FORTE_TEST_CONDITION::smExecutedTests = 0;
unsigned int FORTE_TEST_CONDITION::smFailedTests = 0;

bool FORTE_TEST_CONDITION::smfinalReportPrinted = false;

DEFINE_FIRMWARE_FB(FORTE_TEST_CONDITION, g_nStringIdTEST_CONDITION)

const CStringDictionary::TStringId FORTE_TEST_CONDITION::scmDataInputNames[] = {g_nStringIdcheck};
const CStringDictionary::TStringId FORTE_TEST_CONDITION::scmDataInputTypeIds[] = {g_nStringIdBOOL};
const TDataIOID FORTE_TEST_CONDITION::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_TEST_CONDITION::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_TEST_CONDITION::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_TEST_CONDITION::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TForteInt16 FORTE_TEST_CONDITION::scmEOWithIndexes[] = {-1};
const CStringDictionary::TStringId FORTE_TEST_CONDITION::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_TEST_CONDITION::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_TEST_CONDITION::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, nullptr, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

FORTE_TEST_CONDITION::FORTE_TEST_CONDITION(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
        CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
        conn_CNF(this, 0),
        conn_check(nullptr) {
};

void FORTE_TEST_CONDITION::setInitialValues() {
  var_check = 0_BOOL;
}

FORTE_TEST_CONDITION::~FORTE_TEST_CONDITION() {
  CCriticalRegion finalReportRegion(mFinalReportMutex);
  if(!smfinalReportPrinted) {
    smfinalReportPrinted = true;
    DEVLOG_INFO(" ------------------------------------------------------------------------------\n");
    DEVLOG_INFO(" ------------------------ [TEST_CONDITION FINAL REPORT] -----------------------\n");
    if(smFailedTests) {
      DEVLOG_ERROR(" ------------------------ %u tests executed, %u failed -----------------------\n", smExecutedTests, smFailedTests);
    } else {
      DEVLOG_INFO(" ------------------------ %u tests executed, %u failed -----------------------\n", smExecutedTests, smFailedTests);
    }
    DEVLOG_INFO(" ------------------------------------------------------------------------------\n");
  }
}


void FORTE_TEST_CONDITION::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  if(scmEventREQID == paEIID) {
    smExecutedTests++;
    if(var_check) {
      DEVLOG_INFO(" ------------------------------ [TEST_CONDITION_PASSED] %s.%s passed\n", getResource()->getInstanceName(), getInstanceName());
    } else {
      DEVLOG_ERROR("------------------------------ [TEST_CONDITION_FAILED] %s.%s failed ------------------------------\n", getResource()->getInstanceName(),
        getInstanceName());
      smFailedTests++;
    }
    sendOutputEvent(scmEventCNFID, paECET);
  }
}

void FORTE_TEST_CONDITION::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_check, conn_check);
      break;
    }
    default:
      break;
  }
}

void FORTE_TEST_CONDITION::writeOutputData(TEventID) {
  // nothing to do
}

CIEC_ANY *FORTE_TEST_CONDITION::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_check;
  }
  return nullptr;
}

CIEC_ANY *FORTE_TEST_CONDITION::getDO(size_t) {
  return nullptr;
}

CEventConnection *FORTE_TEST_CONDITION::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_TEST_CONDITION::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_check;
  }
  return nullptr;
}

CDataConnection *FORTE_TEST_CONDITION::getDOConUnchecked(TPortId) {
  return nullptr;
}

