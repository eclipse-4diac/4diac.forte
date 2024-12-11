/*******************************************************************************
 * Copyright (c) 2024 GmbH, HR Agrartechnik GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 *** Name: I_WBSD
 *** Description: Service Interface Function Block Type
 *** Version:
 ***     1.0: 2024-07-09/franz -  -
 *************************************************************************/

#include "I_WBSD_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "I_WBSD_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"



void recWBSD(
           bool     qTimedOut,                  // True means cyclic PGN is not received timely
           int32_t  s32TimeStamp,               // Time stamp of the message in ms
           uint16_t wheelbasedmachinespeed,     // SPN_WHEELBASEDMACHINESPEED,     1u, 1u, 16u
           uint32_t wheelbasedmachinedistance,  // SPN_WHEELBASEDMACHINEDISTANCE,  3u, 1u, 32u
           uint8_t  wheelbasedmachinedirection, // SPN_WHEELBASEDMACHINEDIRECTION, 8u, 1u, 2u
           uint8_t  keyswitchstate,             // SPN_KEYSWITCHSTATE,             8u, 3u, 2u
           uint8_t  maxi_timeoftracpower,       // SPN_MAXI_TIMEOFTRACPOWER,       7u, 1u, 8u
           uint8_t  operator_direc_reversed,    // SPN_OPERATOR_DIREC_REVERSED,    8u, 7u, 2u
           uint8_t  start_stop_state            // SPN_START_STOP_STATE,           8u, 5u, 8u
        )
{
    FORTE_I_WBSD::CbWBSDHandler::recWBSD(
           qTimedOut,                  // True means cyclic PGN is not received timely
           s32TimeStamp,               // Time stamp of the message in ms
           wheelbasedmachinespeed,     // SPN_WHEELBASEDMACHINESPEED,     1u, 1u, 16u
           wheelbasedmachinedistance,  // SPN_WHEELBASEDMACHINEDISTANCE,  3u, 1u, 32u
           wheelbasedmachinedirection, // SPN_WHEELBASEDMACHINEDIRECTION, 8u, 1u, 2u
           keyswitchstate,             // SPN_KEYSWITCHSTATE,             8u, 3u, 2u
           maxi_timeoftracpower,       // SPN_MAXI_TIMEOFTRACPOWER,       7u, 1u, 8u
           operator_direc_reversed,    // SPN_OPERATOR_DIREC_REVERSED,    8u, 7u, 2u
           start_stop_state            // SPN_START_STOP_STATE,           8u, 5u, 8u
        );
}




DEFINE_FIRMWARE_FB(FORTE_I_WBSD, g_nStringIdI_WBSD)

const CStringDictionary::TStringId FORTE_I_WBSD::scmDataInputNames[] = {g_nStringIdQI};
const CStringDictionary::TStringId FORTE_I_WBSD::scmDataInputTypeIds[] = {g_nStringIdBOOL};
const CStringDictionary::TStringId FORTE_I_WBSD::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdQ_timeout, g_nStringIdtimestamp_timeout, g_nStringIdtimestamp_data, g_nStringIdWHEELBASEDMACHINESPEED, g_nStringIdWHEELBASEDMACHINEDISTANCE, g_nStringIdMAXI_TIMEOFTRACPOWER, g_nStringIdWHEELBASEDMACHINEDIRECTION, g_nStringIdKEYSWITCHSTATE, g_nStringIdSTART_STOP_STATE, g_nStringIdOPERATOR_DIREC_REVERSED};
const CStringDictionary::TStringId FORTE_I_WBSD::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdBOOL, g_nStringIdUINT, g_nStringIdUINT, g_nStringIdUINT, g_nStringIdUDINT, g_nStringIdUSINT, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE};
const TDataIOID FORTE_I_WBSD::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_I_WBSD::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_I_WBSD::scmEventInputNames[] = {g_nStringIdINIT};
const TDataIOID FORTE_I_WBSD::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 4, 5, 6, 7, 8, 9, 10, 11, 1, 2, scmWithListDelimiter, 3, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_I_WBSD::scmEOWithIndexes[] = {0, 3, 15};
const CStringDictionary::TStringId FORTE_I_WBSD::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdIND, g_nStringIdTIMEOUT};
const SFBInterfaceSpec FORTE_I_WBSD::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  3, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  12, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_I_WBSD::FORTE_I_WBSD(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CEventSourceFB(paContainer, &scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    var_conn_Q_timeout(var_Q_timeout),
    var_conn_timestamp_timeout(var_timestamp_timeout),
    var_conn_timestamp_data(var_timestamp_data),
    var_conn_WHEELBASEDMACHINESPEED(var_WHEELBASEDMACHINESPEED),
    var_conn_WHEELBASEDMACHINEDISTANCE(var_WHEELBASEDMACHINEDISTANCE),
    var_conn_MAXI_TIMEOFTRACPOWER(var_MAXI_TIMEOFTRACPOWER),
    var_conn_WHEELBASEDMACHINEDIRECTION(var_WHEELBASEDMACHINEDIRECTION),
    var_conn_KEYSWITCHSTATE(var_KEYSWITCHSTATE),
    var_conn_START_STOP_STATE(var_START_STOP_STATE),
    var_conn_OPERATOR_DIREC_REVERSED(var_OPERATOR_DIREC_REVERSED),
    conn_INITO(this, 0),
    conn_IND(this, 1),
    conn_TIMEOUT(this, 2),
    conn_QI(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS),
    conn_Q_timeout(this, 2, &var_conn_Q_timeout),
    conn_timestamp_timeout(this, 3, &var_conn_timestamp_timeout),
    conn_timestamp_data(this, 4, &var_conn_timestamp_data),
    conn_WHEELBASEDMACHINESPEED(this, 5, &var_conn_WHEELBASEDMACHINESPEED),
    conn_WHEELBASEDMACHINEDISTANCE(this, 6, &var_conn_WHEELBASEDMACHINEDISTANCE),
    conn_MAXI_TIMEOFTRACPOWER(this, 7, &var_conn_MAXI_TIMEOFTRACPOWER),
    conn_WHEELBASEDMACHINEDIRECTION(this, 8, &var_conn_WHEELBASEDMACHINEDIRECTION),
    conn_KEYSWITCHSTATE(this, 9, &var_conn_KEYSWITCHSTATE),
    conn_START_STOP_STATE(this, 10, &var_conn_START_STOP_STATE),
    conn_OPERATOR_DIREC_REVERSED(this, 11, &var_conn_OPERATOR_DIREC_REVERSED) {
    setEventChainExecutor(getResource()->getResourceEventExecution());
    g_vts = nullptr;
};

void FORTE_I_WBSD::setInitialValues() {
    var_QI = 0_BOOL;
    var_QO = 0_BOOL;
    var_STATUS = ""_STRING;
    var_Q_timeout = 0_BOOL;
    var_timestamp_timeout = 0_UINT;
    var_timestamp_data = 0_UINT;
    var_WHEELBASEDMACHINESPEED = 0_UINT;
    var_WHEELBASEDMACHINEDISTANCE = 0_UDINT;
    var_MAXI_TIMEOFTRACPOWER = 0_USINT;
    var_WHEELBASEDMACHINEDIRECTION = 0_BYTE;
    var_KEYSWITCHSTATE = 0_BYTE;
    var_START_STOP_STATE = 0_BYTE;
    var_OPERATOR_DIREC_REVERSED = 0_BYTE;
}

void FORTE_I_WBSD::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case cgExternalEventID:
      if(var_Q_timeout == true) {
          var_STATUS = "timeout"_STRING;
          sendOutputEvent(scmEventTIMEOUTID, paECET);
      } else {
          var_STATUS = "OK"_STRING;
          sendOutputEvent(scmEventINDID, paECET);
      }
      break;
    case scmEventINITID:
      var_QO = true_BOOL;
      var_STATUS = "initialized"_STRING;
      sendOutputEvent(scmEventINITOID, paECET);
      break;
  }
}

void FORTE_I_WBSD::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      break;
    }
    default:
      break;
  }
}

void FORTE_I_WBSD::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    case scmEventINDID: {
      writeData(0, var_QO, conn_QO);
      writeData(4, var_timestamp_data, conn_timestamp_data);
      writeData(5, var_WHEELBASEDMACHINESPEED, conn_WHEELBASEDMACHINESPEED);
      writeData(6, var_WHEELBASEDMACHINEDISTANCE, conn_WHEELBASEDMACHINEDISTANCE);
      writeData(7, var_MAXI_TIMEOFTRACPOWER, conn_MAXI_TIMEOFTRACPOWER);
      writeData(8, var_WHEELBASEDMACHINEDIRECTION, conn_WHEELBASEDMACHINEDIRECTION);
      writeData(9, var_KEYSWITCHSTATE, conn_KEYSWITCHSTATE);
      writeData(10, var_START_STOP_STATE, conn_START_STOP_STATE);
      writeData(11, var_OPERATOR_DIREC_REVERSED, conn_OPERATOR_DIREC_REVERSED);
      writeData(1, var_STATUS, conn_STATUS);
      writeData(2, var_Q_timeout, conn_Q_timeout);
      break;
    }
    case scmEventTIMEOUTID: {
      writeData(3, var_timestamp_timeout, conn_timestamp_timeout);
      writeData(1, var_STATUS, conn_STATUS);
      writeData(2, var_Q_timeout, conn_Q_timeout);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_I_WBSD::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
  }
  return nullptr;
}

CIEC_ANY *FORTE_I_WBSD::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
    case 2: return &var_Q_timeout;
    case 3: return &var_timestamp_timeout;
    case 4: return &var_timestamp_data;
    case 5: return &var_WHEELBASEDMACHINESPEED;
    case 6: return &var_WHEELBASEDMACHINEDISTANCE;
    case 7: return &var_MAXI_TIMEOFTRACPOWER;
    case 8: return &var_WHEELBASEDMACHINEDIRECTION;
    case 9: return &var_KEYSWITCHSTATE;
    case 10: return &var_START_STOP_STATE;
    case 11: return &var_OPERATOR_DIREC_REVERSED;
  }
  return nullptr;
}

CEventConnection *FORTE_I_WBSD::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_IND;
    case 2: return &conn_TIMEOUT;
  }
  return nullptr;
}

CDataConnection **FORTE_I_WBSD::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
  }
  return nullptr;
}

CDataConnection *FORTE_I_WBSD::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
    case 2: return &conn_Q_timeout;
    case 3: return &conn_timestamp_timeout;
    case 4: return &conn_timestamp_data;
    case 5: return &conn_WHEELBASEDMACHINESPEED;
    case 6: return &conn_WHEELBASEDMACHINEDISTANCE;
    case 7: return &conn_MAXI_TIMEOFTRACPOWER;
    case 8: return &conn_WHEELBASEDMACHINEDIRECTION;
    case 9: return &conn_KEYSWITCHSTATE;
    case 10: return &conn_START_STOP_STATE;
    case 11: return &conn_OPERATOR_DIREC_REVERSED;
  }
  return nullptr;
}




FORTE_I_WBSD::CbWBSDHandler* FORTE_I_WBSD::CbWBSDHandler::g_vth = nullptr;  //Pointer to instance
FORTE_I_WBSD                   * FORTE_I_WBSD::g_vts                    = nullptr;  //Pointer to instance




DEFINE_HANDLER(FORTE_I_WBSD::CbWBSDHandler);


bool FORTE_I_WBSD::initialize() {
    bool ret = CFunctionBlock::initialize();
      g_vts = this;
    return ret;
}


FORTE_I_WBSD::CbWBSDHandler::CbWBSDHandler(CDeviceExecution& pa_poDeviceExecution)
: CExternalEventHandler(pa_poDeviceExecution)
{
  g_vth = this;
}

FORTE_I_WBSD::CbWBSDHandler::~CbWBSDHandler() {
  g_vth = nullptr;
}


//Static Callback
void FORTE_I_WBSD::CbWBSDHandler::recWBSD(
           bool     qTimedOut,                  // True means cyclic PGN is not received timely
           int32_t  s32TimeStamp,               // Time stamp of the message in ms
           uint16_t wheelbasedmachinespeed,     // SPN_WHEELBASEDMACHINESPEED,     1u, 1u, 16u
           uint32_t wheelbasedmachinedistance,  // SPN_WHEELBASEDMACHINEDISTANCE,  3u, 1u, 32u
           uint8_t  wheelbasedmachinedirection, // SPN_WHEELBASEDMACHINEDIRECTION, 8u, 1u, 2u
           uint8_t  keyswitchstate,             // SPN_KEYSWITCHSTATE,             8u, 3u, 2u
           uint8_t  maxi_timeoftracpower,       // SPN_MAXI_TIMEOFTRACPOWER,       7u, 1u, 8u
           uint8_t  operator_direc_reversed,    // SPN_OPERATOR_DIREC_REVERSED,    8u, 7u, 2u
           uint8_t  start_stop_state            // SPN_START_STOP_STATE,           8u, 5u, 8u
        )
{
  if(g_vth == nullptr)
  {
    //no callback registered
  } else {
    g_vth->recWBSD_ic(
            qTimedOut,                  // True means cyclic PGN is not received timely
            s32TimeStamp,               // Time stamp of the message in ms
            wheelbasedmachinespeed,     // SPN_WHEELBASEDMACHINESPEED,     1u, 1u, 16u
            wheelbasedmachinedistance,  // SPN_WHEELBASEDMACHINEDISTANCE,  3u, 1u, 32u
            wheelbasedmachinedirection, // SPN_WHEELBASEDMACHINEDIRECTION, 8u, 1u, 2u
            keyswitchstate,             // SPN_KEYSWITCHSTATE,             8u, 3u, 2u
            maxi_timeoftracpower,       // SPN_MAXI_TIMEOFTRACPOWER,       7u, 1u, 8u
            operator_direc_reversed,    // SPN_OPERATOR_DIREC_REVERSED,    8u, 7u, 2u
            start_stop_state            // SPN_START_STOP_STATE,           8u, 5u, 8u
            );
  }
}

//in-Class Callback
void FORTE_I_WBSD::CbWBSDHandler::recWBSD_ic(
           bool     qTimedOut,                  // True means cyclic PGN is not received timely
           int32_t  s32TimeStamp,               // Time stamp of the message in ms
           uint16_t wheelbasedmachinespeed,     // SPN_WHEELBASEDMACHINESPEED,     1u, 1u, 16u
           uint32_t wheelbasedmachinedistance,  // SPN_WHEELBASEDMACHINEDISTANCE,  3u, 1u, 32u
           uint8_t  wheelbasedmachinedirection, // SPN_WHEELBASEDMACHINEDIRECTION, 8u, 1u, 2u
           uint8_t  keyswitchstate,             // SPN_KEYSWITCHSTATE,             8u, 3u, 2u
           uint8_t  maxi_timeoftracpower,       // SPN_MAXI_TIMEOFTRACPOWER,       7u, 1u, 8u
           uint8_t  operator_direc_reversed,    // SPN_OPERATOR_DIREC_REVERSED,    8u, 7u, 2u
           uint8_t  start_stop_state            // SPN_START_STOP_STATE,           8u, 5u, 8u
        )
{
  if(FORTE_I_WBSD::g_vts == nullptr) {
    //no callback registered
  } else {
    FORTE_I_WBSD::g_vts->recWBSD(
            qTimedOut,                  // True means cyclic PGN is not received timely
            s32TimeStamp,               // Time stamp of the message in ms
           wheelbasedmachinespeed,     // SPN_WHEELBASEDMACHINESPEED,     1u, 1u, 16u
             wheelbasedmachinedistance,  // SPN_WHEELBASEDMACHINEDISTANCE,  3u, 1u, 32u
             wheelbasedmachinedirection, // SPN_WHEELBASEDMACHINEDIRECTION, 8u, 1u, 2u
             keyswitchstate,             // SPN_KEYSWITCHSTATE,             8u, 3u, 2u
             maxi_timeoftracpower,       // SPN_MAXI_TIMEOFTRACPOWER,       7u, 1u, 8u
             operator_direc_reversed,    // SPN_OPERATOR_DIREC_REVERSED,    8u, 7u, 2u
             start_stop_state            // SPN_START_STOP_STATE,           8u, 5u, 8u
             );
    startNewEventChain(FORTE_I_WBSD::g_vts);
  }
}

void FORTE_I_WBSD::recWBSD(
           bool     qTimedOut,                  // True means cyclic PGN is not received timely
           int32_t  s32TimeStamp,               // Time stamp of the message in ms
           uint16_t wheelbasedmachinespeed,     // SPN_WHEELBASEDMACHINESPEED,     1u, 1u, 16u
           uint32_t wheelbasedmachinedistance,  // SPN_WHEELBASEDMACHINEDISTANCE,  3u, 1u, 32u
           uint8_t  wheelbasedmachinedirection, // SPN_WHEELBASEDMACHINEDIRECTION, 8u, 1u, 2u
           uint8_t  keyswitchstate,             // SPN_KEYSWITCHSTATE,             8u, 3u, 2u
           uint8_t  maxi_timeoftracpower,       // SPN_MAXI_TIMEOFTRACPOWER,       7u, 1u, 8u
           uint8_t  operator_direc_reversed,    // SPN_OPERATOR_DIREC_REVERSED,    8u, 7u, 2u
           uint8_t  start_stop_state            // SPN_START_STOP_STATE,           8u, 5u, 8u
        )
{

       var_Q_timeout                  = CIEC_BOOL(qTimedOut);                  // True means cyclic PGN is not received timely

       if(qTimedOut)  {
           var_timestamp_timeout          = CIEC_UINT(s32TimeStamp);                // Time stamp of the message in ms
       } else {
           var_timestamp_data             = CIEC_UINT(s32TimeStamp);                // Time stamp of the message in ms
           var_WHEELBASEDMACHINESPEED     = CIEC_UINT(wheelbasedmachinespeed);      // SPN_WHEELBASEDMACHINESPEED,     1u, 1u, 16u
           var_WHEELBASEDMACHINEDISTANCE  = CIEC_UDINT(wheelbasedmachinedistance);  // SPN_WHEELBASEDMACHINEDISTANCE,  3u, 1u, 32u
           var_WHEELBASEDMACHINEDIRECTION = CIEC_BYTE(wheelbasedmachinedirection);  // SPN_WHEELBASEDMACHINEDIRECTION, 8u, 1u, 2u
           var_KEYSWITCHSTATE             = CIEC_BYTE(keyswitchstate);              // SPN_KEYSWITCHSTATE,             8u, 3u, 2u
           var_MAXI_TIMEOFTRACPOWER       = CIEC_USINT(maxi_timeoftracpower);       // SPN_MAXI_TIMEOFTRACPOWER,       7u, 1u, 8u
           var_OPERATOR_DIREC_REVERSED    = CIEC_BYTE(operator_direc_reversed);     // SPN_OPERATOR_DIREC_REVERSED,    8u, 7u, 2u
           var_START_STOP_STATE           = CIEC_BYTE(start_stop_state);            // SPN_START_STOP_STATE,           8u, 5u, 8u

       }

}


void FORTE_I_WBSD::CbWBSDHandler::enableHandler() {
  //do nothing
}

void FORTE_I_WBSD::CbWBSDHandler::disableHandler() {
  //do nothing
}

void FORTE_I_WBSD::CbWBSDHandler::setPriority(int) {
  //do nothing
}



int FORTE_I_WBSD::CbWBSDHandler::getPriority() const {
  return 0;
}

















