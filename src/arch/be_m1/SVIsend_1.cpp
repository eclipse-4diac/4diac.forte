/*******************************************************************************
 * Copyright (c) 2011 ACIN
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *  Alois Zoitl - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include "SVIsend_1.h"

DEFINE_FIRMWARE_FB(FORTE_SVIsend_1, g_nStringIdSVIsend_1)

const CStringDictionary::TStringId FORTE_SVIsend_1::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdID, g_nStringIdSD_1};

const CStringDictionary::TStringId FORTE_SVIsend_1::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdANY};

const CStringDictionary::TStringId FORTE_SVIsend_1::scmDataOutputNames[] = {g_nStringIdQO};

const CStringDictionary::TStringId FORTE_SVIsend_1::scmDataOutputTypeIds[] = {g_nStringIdBOOL};

const TForteInt16 FORTE_SVIsend_1::scmEIWithIndexes[] = {0, 4};
const TDataIOID FORTE_SVIsend_1::scmEIWith[] = {0, 1, 2, scmWithListDelimiter, 0, 1, 2, scmWithListDelimiter};
const CStringDictionary::TStringId FORTE_SVIsend_1::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_SVIsend_1::scmEventInputTypeIds[] = {g_nStringIdEInit, g_nStringIdEvent};

const TDataIOID FORTE_SVIsend_1::scmEOWith[] = {0, scmWithListDelimiter, 0, scmWithListDelimiter};
const TForteInt16 FORTE_SVIsend_1::scmEOWithIndexes[] = {0, 2, -1};
const CStringDictionary::TStringId FORTE_SVIsend_1::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_SVIsend_1::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};

const SFBInterfaceSpec FORTE_SVIsend_1::scmFBInterfaceSpec = {
  2,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  2,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,  3,  scmDataInputNames, scmDataInputTypeIds,
  1,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};


void FORTE_SVIsend_1::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID){
    case scmEventINITID:
      if(true == QI()){
        QO() = registerSVIvar(ID(),SD_1(),SVI_F_OUT);
      }
      sendOutputEvent(scmEventINITOID, paECET);
      if (true == QO()) {
        printf("Alles OK send\n");
      } else {
        printf("Alles FALSCH send\n");
      }
      break;

    case scmEventREQID:
      sendOutputEvent(scmEventCNFID, paECET);
      break;
    default:
      break;
  }
}



