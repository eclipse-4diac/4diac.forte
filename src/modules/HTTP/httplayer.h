/*******************************************************************************
 * Copyright (c) 2017-2018 Marc Jakobi, github.com/MrcJkb, fortiss GmbH
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *    Marc Jakobi - initial implementation for HTTP clients
 *    Jose Cabral - Merge old HTTPIpLayer to this one and use CIEC_STRING
 ********************************************************************************/

#ifndef _HTTPCOMLAYER_H_
#define _HTTPCOMLAYER_H_

#include <forte_config.h>
#include "comlayer.h"
#include <forte_string.h>
#include "ipcomlayer.h"


class CIEC_ANY;

namespace forte {

  namespace com_infra {

    class CHttpComLayer : public CComLayer{
      public:
        CHttpComLayer(CComLayer* paUpperLayer, CBaseCommFB* paComFB);
        virtual ~CHttpComLayer();

        EComResponse sendData(void *paData, unsigned int paSize); // top interface, called from top
        EComResponse recvData(const void *paData, unsigned int paSize);

        EComResponse openConnection(char *paLayerParameter);
        void closeConnection();

        EComResponse processInterrupt();

        /** enum representing the HTTP request type */
        enum ERequestType{
          /** HTTP GET */
          e_GET,
          /** HTTP PUT */
          e_PUT,
          /** not ready */
          e_NOTSET,
        };

      protected:

      private:

        /**
         * Parse the HTTP response and checks the returned code
         * @param paData buffer with the HTTP response
         * @return OK if return code is as expected
         */
        EComResponse handleHTTPResponse(char *paData);

        /**
         * Copy the received data to the buffer
         */
        void handledRecvData();

        /** Serializes the data to a char* */
        bool serializeData(const CIEC_ANY& paCIECData);

        void closeSocket(CIPComSocketHandler::TSocketDescriptor *paSocketID);

        EComResponse openHTTPConnection();

        EComResponse mInterruptResp;

        /** Represents the HTTP request type (0 = GET, 1 = PUT). */
        ERequestType mRequestType;
        /** HTTP Host */
        CIEC_STRING mHost;
        /** Path in host */
        CIEC_STRING mPath;
        /** Data to be sent */
        CIEC_STRING mReqData;
        /** Port of the host */
        TForteUInt16 mPort;
        /** Request  to be sent to Host */
        CIEC_STRING mRequest;

        char mRecvBuffer[cg_unIPLayerRecvBufferSize];
        unsigned int mBufFillSize;

        CIPComSocketHandler::TSocketDescriptor mSocketID;

        /** Expected response code (default: HTTP/1.1 200 OK) */
        CIEC_STRING mExpectedRspCode;

        /** Ouput response is to be written to a data output */
        bool hasOutputResponse;
    };

  }
}

#endif /* _HTTPCOMLAYER_H_ */
