/*******************************************************************************
 * Copyright (c) 2006 - 2015 ACIN, Profactor GmbH, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer, Ingo Hegny, Monika Wenger,
 *    - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include "RT_E_SWITCH_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RT_E_SWITCH_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_RT_E_SWITCH, g_nStringIdRT_E_SWITCH)

const CStringDictionary::TStringId FORTE_RT_E_SWITCH::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdG, g_nStringIdTmin, g_nStringIdDeadline_EO1, g_nStringIdWCET_EO1, g_nStringIdDeadline_EO2, g_nStringIdWCET_EO2};
const CStringDictionary::TStringId FORTE_RT_E_SWITCH::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdTIME, g_nStringIdTIME, g_nStringIdTIME, g_nStringIdTIME, g_nStringIdTIME};
const CStringDictionary::TStringId FORTE_RT_E_SWITCH::scmDataOutputNames[] = {g_nStringIdQO};
const CStringDictionary::TStringId FORTE_RT_E_SWITCH::scmDataOutputTypeIds[] = {g_nStringIdBOOL};
const TDataIOID FORTE_RT_E_SWITCH::scmEIWith[] = {0, 2, 3, 4, 5, 6, scmWithListDelimiter, 1, scmWithListDelimiter};
const TForteInt16 FORTE_RT_E_SWITCH::scmEIWithIndexes[] = {0, 7};
const CStringDictionary::TStringId FORTE_RT_E_SWITCH::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdEI};
const CStringDictionary::TStringId FORTE_RT_E_SWITCH::scmEventInputTypeIds[] = {g_nStringIdEInit, g_nStringIdEvent};
const TDataIOID FORTE_RT_E_SWITCH::scmEOWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_RT_E_SWITCH::scmEOWithIndexes[] = {0, -1, -1};
const CStringDictionary::TStringId FORTE_RT_E_SWITCH::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdEO1, g_nStringIdEO2};
const CStringDictionary::TStringId FORTE_RT_E_SWITCH::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent, g_nStringIdEvent};
const SFBInterfaceSpec FORTE_RT_E_SWITCH::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  3, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  7, scmDataInputNames, scmDataInputTypeIds,
  1, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_RT_E_SWITCH::FORTE_RT_E_SWITCH(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    conn_INITO(this, 0),
    conn_EO1(this, 1),
    conn_EO2(this, 2),
    conn_QI(nullptr),
    conn_G(nullptr),
    conn_Tmin(nullptr),
    conn_Deadline_EO1(nullptr),
    conn_WCET_EO1(nullptr),
    conn_Deadline_EO2(nullptr),
    conn_WCET_EO2(nullptr),
    conn_QO(this, 0, &var_conn_QO) {
};

void FORTE_RT_E_SWITCH::setInitialValues() {
  var_QI = 0_BOOL;
  var_G = 0_BOOL;
  var_Tmin = 0_TIME;
  var_Deadline_EO1 = 0_TIME;
  var_WCET_EO1 = 0_TIME;
  var_Deadline_EO2 = 0_TIME;
  var_WCET_EO2 = 0_TIME;
  var_QO = 0_BOOL;
}

void FORTE_RT_E_SWITCH::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventEIID:
      if(mInitialized){
        CEventConnection *eoCon;
        if(!var_G){
          eoCon = getEOConUnchecked(scmEventEO1ID);
          if(eoCon->isConnected()){
            eoCon->triggerEvent(&mECEO1);
            mECEO1.resumeSelfSuspend();
          }
        }
        else{
          eoCon = getEOConUnchecked(scmEventEO2ID);
          if(eoCon->isConnected()){
            eoCon->triggerEvent(&mECEO2);
            mECEO2.resumeSelfSuspend();
          }
        }
      }
      break;
    case scmEventINITID:
      if(var_QI){
        if(!mInitialized){
          mECEO1.changeExecutionState(EMGMCommandType::Start);
          mECEO2.changeExecutionState(EMGMCommandType::Start);
          mInitialized = true;
        }
        mECEO1.setDeadline(var_Deadline_EO1);
        mECEO2.setDeadline(var_Deadline_EO2);
      }
      else{
        mECEO1.changeExecutionState(EMGMCommandType::Stop);
        mECEO2.changeExecutionState(EMGMCommandType::Stop);
        mInitialized = false;
      }
      var_QO = var_QI;
      sendOutputEvent(scmEventINITOID, paECET);
      break;
  }
}

void FORTE_RT_E_SWITCH::readInputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(2, var_Tmin, conn_Tmin);
      readData(3, var_Deadline_EO1, conn_Deadline_EO1);
      readData(4, var_WCET_EO1, conn_WCET_EO1);
      readData(5, var_Deadline_EO2, conn_Deadline_EO2);
      readData(6, var_WCET_EO2, conn_WCET_EO2);
      break;
    }
    case scmEventEIID: {
      readData(1, var_G, conn_G);
      break;
    }
    default:
      break;
  }
}

void FORTE_RT_E_SWITCH::writeOutputData(TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      break;
    }
    case scmEventEO1ID: {
      break;
    }
    case scmEventEO2ID: {
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_RT_E_SWITCH::getDI(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_G;
    case 2: return &var_Tmin;
    case 3: return &var_Deadline_EO1;
    case 4: return &var_WCET_EO1;
    case 5: return &var_Deadline_EO2;
    case 6: return &var_WCET_EO2;
  }
  return nullptr;
}

CIEC_ANY *FORTE_RT_E_SWITCH::getDO(size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
  }
  return nullptr;
}

CEventConnection *FORTE_RT_E_SWITCH::getEOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_EO1;
    case 2: return &conn_EO2;
  }
  return nullptr;
}

CDataConnection **FORTE_RT_E_SWITCH::getDIConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_G;
    case 2: return &conn_Tmin;
    case 3: return &conn_Deadline_EO1;
    case 4: return &conn_WCET_EO1;
    case 5: return &conn_Deadline_EO2;
    case 6: return &conn_WCET_EO2;
  }
  return nullptr;
}

CDataConnection *FORTE_RT_E_SWITCH::getDOConUnchecked(TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
  }
  return nullptr;
}
