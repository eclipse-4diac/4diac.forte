/*******************************************************************************
 * Copyright (c) 2014, 2024 fortiss GmbH, HR Agrartechnik GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *

 *** Name: QE
 *** Description: Output service interface function block for event output data
 *** Version:
 ***     1.0: 2014-08-26/Waldemar Eisenmenger - fortiss GmbH -
 ***     1.1: 2014-08-30/Alois Zoitl - fortiss GmbH -
 ***     1.2: 2015-06-10/Monika Wenger - fortiss GmbH -
 ***     1.3: 2024-05-16/Franz Höpfinger - HR Agrartechnik GmbH - copied over QX to QE, and removed the OUT
 *************************************************************************/

#include "QE_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "QE_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_QE, g_nStringIdQE)

const CStringDictionary::TStringId FORTE_QE::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdPARAMS};
const CStringDictionary::TStringId FORTE_QE::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING};
const CStringDictionary::TStringId FORTE_QE::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_QE::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING};
const TDataIOID FORTE_QE::scmEIWith[] = {0, 1, scmWithListDelimiter, 0, scmWithListDelimiter};
const TForteInt16 FORTE_QE::scmEIWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_QE::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const TDataIOID FORTE_QE::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_QE::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_QE::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const SFBInterfaceSpec FORTE_QE::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_QE::FORTE_QE(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CProcessInterface(paContainer, &scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_INITO(this, 0),
    conn_CNF(this, 1),
    conn_QI(nullptr),
    conn_PARAMS(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS) {
};

void FORTE_QE::setInitialValues() {
  var_QI = 0_BOOL;
  var_PARAMS = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = ""_STRING;
}

void FORTE_QE::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventINITID:
        if (var_QI) {
          var_QO = CIEC_BOOL(CProcessInterface::initialise(false, paECET)); //initialise as output
        } else {
          var_QO = CIEC_BOOL(CProcessInterface::deinitialise());
        }
        sendOutputEvent(scmEventINITOID, paECET);
      break;
    case scmEventREQID:
        if (var_QI) {
          var_QO = CIEC_BOOL(CProcessInterface::write(var_QO));
        } else {
          var_QO = false_BOOL;
        }
        sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

void FORTE_QE::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_PARAMS, conn_PARAMS);
      break;
    }
    case scmEventREQID: {
      readData(0, var_QI, conn_QI);
      break;
    }
    default:
      break;
  }
}

void FORTE_QE::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    case scmEventCNFID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_QE::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_PARAMS;
  }
  return nullptr;
}

CIEC_ANY *FORTE_QE::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_QE::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_QE::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_PARAMS;
  }
  return nullptr;
}

CDataConnection *FORTE_QE::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

