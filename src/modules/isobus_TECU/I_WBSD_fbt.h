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

#pragma once

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_string.h"
#include "forte_uint.h"
#include "forte_udint.h"
#include "forte_usint.h"
#include "forte_byte.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


#include "extevhan.h"
#include "esfb.h"
#include "resource.h"


extern "C" void recWBSD(
           bool     qTimedOut,                  // True means cyclic PGN is not received timely
           int32_t  s32TimeStamp,               // Time stamp of the message in ms
           uint16_t wheelbasedmachinespeed,     // SPN_WHEELBASEDMACHINESPEED,     1u, 1u, 16u
           uint32_t wheelbasedmachinedistance,  // SPN_WHEELBASEDMACHINEDISTANCE,  3u, 1u, 32u
           uint8_t  wheelbasedmachinedirection, // SPN_WHEELBASEDMACHINEDIRECTION, 8u, 1u, 2u
           uint8_t  keyswitchstate,             // SPN_KEYSWITCHSTATE,             8u, 3u, 2u
           uint8_t  maxi_timeoftracpower,       // SPN_MAXI_TIMEOFTRACPOWER,       7u, 1u, 8u
           uint8_t  operator_direc_reversed,    // SPN_OPERATOR_DIREC_REVERSED,    8u, 7u, 2u
           uint8_t  start_stop_state            // SPN_START_STOP_STATE,           8u, 5u, 8u
        );



class FORTE_I_WBSD final : public CEventSourceFB {
  DECLARE_FIRMWARE_FB(FORTE_I_WBSD)

  public:
    class CbWBSDHandler : public CExternalEventHandler{
    DECLARE_HANDLER(CbWBSDHandler)
      ;
      public:
        //Static Callback
        static void recWBSD(
                bool     qTimedOut,                  // True means cyclic PGN is not received timely
                int32_t  s32TimeStamp,               // Time stamp of the message in ms
                uint16_t wheelbasedmachinespeed,     // SPN_WHEELBASEDMACHINESPEED,     1u, 1u, 16u
                uint32_t wheelbasedmachinedistance,  // SPN_WHEELBASEDMACHINEDISTANCE,  3u, 1u, 32u
                uint8_t  wheelbasedmachinedirection, // SPN_WHEELBASEDMACHINEDIRECTION, 8u, 1u, 2u
                uint8_t  keyswitchstate,             // SPN_KEYSWITCHSTATE,             8u, 3u, 2u
                uint8_t  maxi_timeoftracpower,       // SPN_MAXI_TIMEOFTRACPOWER,       7u, 1u, 8u
                uint8_t  operator_direc_reversed,    // SPN_OPERATOR_DIREC_REVERSED,    8u, 7u, 2u
                uint8_t  start_stop_state            // SPN_START_STOP_STATE,           8u, 5u, 8u
             );
        //in-Class Callback
        void recWBSD_ic(
                bool     qTimedOut,                  // True means cyclic PGN is not received timely
                int32_t  s32TimeStamp,               // Time stamp of the message in ms
                uint16_t wheelbasedmachinespeed,     // SPN_WHEELBASEDMACHINESPEED,     1u, 1u, 16u
                uint32_t wheelbasedmachinedistance,  // SPN_WHEELBASEDMACHINEDISTANCE,  3u, 1u, 32u
                uint8_t  wheelbasedmachinedirection, // SPN_WHEELBASEDMACHINEDIRECTION, 8u, 1u, 2u
                uint8_t  keyswitchstate,             // SPN_KEYSWITCHSTATE,             8u, 3u, 2u
                uint8_t  maxi_timeoftracpower,       // SPN_MAXI_TIMEOFTRACPOWER,       7u, 1u, 8u
                uint8_t  operator_direc_reversed,    // SPN_OPERATOR_DIREC_REVERSED,    8u, 7u, 2u
                uint8_t  start_stop_state            // SPN_START_STOP_STATE,           8u, 5u, 8u
             );

        /* functions needed for the external event handler interface */
        void enableHandler() override;
        void disableHandler() override;
        void setPriority(int paPriority) override;
        int getPriority() const override;
      private:
        static FORTE_I_WBSD::CbWBSDHandler* g_vth;  //Pointer to instance
  };

  private:

    static FORTE_I_WBSD* g_vts;  //Pointer to instance

    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventINITID = 0;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const TEventID scmEventINITOID = 0;
    static const TEventID scmEventINDID = 1;
    static const TEventID scmEventTIMEOUTID = 2;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

    //in-Class Callback
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
          );

  public:
    FORTE_I_WBSD(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BOOL var_QI;

    CIEC_BOOL var_QO;
    CIEC_STRING var_STATUS;
    CIEC_BOOL var_Q_timeout;
    CIEC_UINT var_timestamp_timeout;
    CIEC_UINT var_timestamp_data;
    CIEC_UINT var_WHEELBASEDMACHINESPEED;
    CIEC_UDINT var_WHEELBASEDMACHINEDISTANCE;
    CIEC_USINT var_MAXI_TIMEOFTRACPOWER;
    CIEC_BYTE var_WHEELBASEDMACHINEDIRECTION;
    CIEC_BYTE var_KEYSWITCHSTATE;
    CIEC_BYTE var_START_STOP_STATE;
    CIEC_BYTE var_OPERATOR_DIREC_REVERSED;

    CIEC_BOOL var_conn_QO;
    CIEC_STRING var_conn_STATUS;
    CIEC_BOOL var_conn_Q_timeout;
    CIEC_UINT var_conn_timestamp_timeout;
    CIEC_UINT var_conn_timestamp_data;
    CIEC_UINT var_conn_WHEELBASEDMACHINESPEED;
    CIEC_UDINT var_conn_WHEELBASEDMACHINEDISTANCE;
    CIEC_USINT var_conn_MAXI_TIMEOFTRACPOWER;
    CIEC_BYTE var_conn_WHEELBASEDMACHINEDIRECTION;
    CIEC_BYTE var_conn_KEYSWITCHSTATE;
    CIEC_BYTE var_conn_START_STOP_STATE;
    CIEC_BYTE var_conn_OPERATOR_DIREC_REVERSED;

    CEventConnection conn_INITO;
    CEventConnection conn_IND;
    CEventConnection conn_TIMEOUT;

    CDataConnection *conn_QI;

    CDataConnection conn_QO;
    CDataConnection conn_STATUS;
    CDataConnection conn_Q_timeout;
    CDataConnection conn_timestamp_timeout;
    CDataConnection conn_timestamp_data;
    CDataConnection conn_WHEELBASEDMACHINESPEED;
    CDataConnection conn_WHEELBASEDMACHINEDISTANCE;
    CDataConnection conn_MAXI_TIMEOFTRACPOWER;
    CDataConnection conn_WHEELBASEDMACHINEDIRECTION;
    CDataConnection conn_KEYSWITCHSTATE;
    CDataConnection conn_START_STOP_STATE;
    CDataConnection conn_OPERATOR_DIREC_REVERSED;

    bool initialize() override;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_INIT(const CIEC_BOOL &paQI, CIEC_BOOL &paQO, CIEC_STRING &paSTATUS, CIEC_BOOL &paQ_timeout, CIEC_UINT &patimestamp_timeout, CIEC_UINT &patimestamp_data, CIEC_UINT &paWHEELBASEDMACHINESPEED, CIEC_UDINT &paWHEELBASEDMACHINEDISTANCE, CIEC_USINT &paMAXI_TIMEOFTRACPOWER, CIEC_BYTE &paWHEELBASEDMACHINEDIRECTION, CIEC_BYTE &paKEYSWITCHSTATE, CIEC_BYTE &paSTART_STOP_STATE, CIEC_BYTE &paOPERATOR_DIREC_REVERSED) {
      var_QI = paQI;
      executeEvent(scmEventINITID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
      paQ_timeout = var_Q_timeout;
      patimestamp_timeout = var_timestamp_timeout;
      patimestamp_data = var_timestamp_data;
      paWHEELBASEDMACHINESPEED = var_WHEELBASEDMACHINESPEED;
      paWHEELBASEDMACHINEDISTANCE = var_WHEELBASEDMACHINEDISTANCE;
      paMAXI_TIMEOFTRACPOWER = var_MAXI_TIMEOFTRACPOWER;
      paWHEELBASEDMACHINEDIRECTION = var_WHEELBASEDMACHINEDIRECTION;
      paKEYSWITCHSTATE = var_KEYSWITCHSTATE;
      paSTART_STOP_STATE = var_START_STOP_STATE;
      paOPERATOR_DIREC_REVERSED = var_OPERATOR_DIREC_REVERSED;
    }

    void operator()(const CIEC_BOOL &paQI, CIEC_BOOL &paQO, CIEC_STRING &paSTATUS, CIEC_BOOL &paQ_timeout, CIEC_UINT &patimestamp_timeout, CIEC_UINT &patimestamp_data, CIEC_UINT &paWHEELBASEDMACHINESPEED, CIEC_UDINT &paWHEELBASEDMACHINEDISTANCE, CIEC_USINT &paMAXI_TIMEOFTRACPOWER, CIEC_BYTE &paWHEELBASEDMACHINEDIRECTION, CIEC_BYTE &paKEYSWITCHSTATE, CIEC_BYTE &paSTART_STOP_STATE, CIEC_BYTE &paOPERATOR_DIREC_REVERSED) {
      evt_INIT(paQI, paQO, paSTATUS, paQ_timeout, patimestamp_timeout, patimestamp_data, paWHEELBASEDMACHINESPEED, paWHEELBASEDMACHINEDISTANCE, paMAXI_TIMEOFTRACPOWER, paWHEELBASEDMACHINEDIRECTION, paKEYSWITCHSTATE, paSTART_STOP_STATE, paOPERATOR_DIREC_REVERSED);
    }
};


