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
#include "SET_VALUE.h"
#include <mtypes.h>                     /* M1 include files    */
#include <msys_e.h>
#include <mio.h>
#include <mio_e.h>

DEFINE_FIRMWARE_FB(FORTE_SET_VALUE, g_nStringIdSET_VALUE)

const CStringDictionary::TStringId FORTE_SET_VALUE::scmDataInputNames[] = { g_nStringIdMOD_NB, g_nStringIdCHAN_NB, g_nStringIdVALUE };

const CStringDictionary::TStringId FORTE_SET_VALUE::scmDataInputTypeIds[] = { g_nStringIdINT, g_nStringIdINT, g_nStringIdSINT };

const CStringDictionary::TStringId FORTE_SET_VALUE::scmDataOutputNames[] = { g_nStringIdRET_CODE };

const CStringDictionary::TStringId FORTE_SET_VALUE::scmDataOutputTypeIds[] = { g_nStringIdINT };

const TForteInt16 FORTE_SET_VALUE::scmEIWithIndexes[] = { 0, 2 };
const TDataIOID FORTE_SET_VALUE::scmEIWith[] = { 0, scmWithListDelimiter, 2, 1, scmWithListDelimiter };
const CStringDictionary::TStringId FORTE_SET_VALUE::scmEventInputNames[] = { g_nStringIdINIT, g_nStringIdREQ };
const CStringDictionary::TStringId FORTE_SET_VALUE::scmEventInputTypeIds[] = {g_nStringIdEInit, g_nStringIdEvent};

const TDataIOID FORTE_SET_VALUE::scmEOWith[] = { 0, scmWithListDelimiter, 0, scmWithListDelimiter };
const TForteInt16 FORTE_SET_VALUE::scmEOWithIndexes[] = { 0, 2, -1 };
const CStringDictionary::TStringId FORTE_SET_VALUE::scmEventOutputNames[] = { g_nStringIdINITO, g_nStringIdCNF };
const CStringDictionary::TStringId FORTE_SET_VALUE::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};

const SFBInterfaceSpec FORTE_SET_VALUE::scmFBInterfaceSpec = { 2, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes, 2, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes, 3, scmDataInputNames, scmDataInputTypeIds, 1, scmDataOutputNames, scmDataOutputTypeIds, 0, 0 };

void FORTE_SET_VALUE::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch (paEIID){
    case scmEventINITID:
      if(init()){
        sendOutputEvent(scmEventINITOID, paECET);
      }
      break;
    case scmEventREQID:
      RET_CODE() = write();
      sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

bool FORTE_SET_VALUE::init(){
  driverId = mio_GetDrv((short) MOD_NB());
  return driverId != nullptr;
}

SINT32 FORTE_SET_VALUE::write(){
  return mio_SetValue(driverId, static_cast<unsigned int>(CHAN_NB()), VALUE());
}

