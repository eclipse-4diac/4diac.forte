/*******************************************************************************
 * Copyright (c) 2006-2015 ACIN, Profactor GmbH, fortiss GmbH
 *                      2018 Johannes Kepler University
 *               2023 Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Rene Smodic, Thomas Strasser, Alois Zoitl, Michael Hofmann,
 *    Martin Melik-Merkumians, Ingo Hegny, Patrick Smejkal
 *      - initial implementation and rework communication infrastructure
 *    Alois Zoitl - introduced new CGenFB class for better handling generic FBs
 *    Martin Jobst - account for new FB layout and varying data type size
 *******************************************************************************/
#ifndef _SRC_CORE_COMINFRA_BASECOMMFB_H_
#define _SRC_CORE_COMINFRA_BASECOMMFB_H_

#include <forte_config.h>
#include "comtypes.h"
#include "../genfb.h"
#include "../esfb.h"
#include "forte_sync.h"

namespace forte {
  namespace com_infra {

    class CComLayer;

    class CBaseCommFB : public CGenFunctionBlock<CEventSourceFB> {
    public:
      ~CBaseCommFB() override;

      EMGMResponse changeExecutionState(EMGMCommandType paCommand) override;

      forte::com_infra::EComServiceType getComServiceType() const {
        return mCommServiceType;
      }

      TPortId getNumSD() const {
        return getFBInterfaceSpec().mNumDIs - 2;
      }

      TPortId getNumRD() const {
        return getFBInterfaceSpec().mNumDOs - 2;
      }

      CIEC_ANY **getSDs() {
        return mDIs + 2;
      }

      CIEC_ANY **getRDs() {
        return mDOs + 2;
      }

      void interruptCommFB(CComLayer *paComLayer);

      CIEC_BOOL& QI() {
        return *static_cast<CIEC_BOOL*>(getDI(0));
      }

#ifdef FORTE_USE_WSTRING_DATATYPE
      CIEC_WSTRING& ID() {
        return *static_cast<CIEC_WSTRING*>(getDI(1));
      }

      CIEC_WSTRING& STATUS() {
        return *static_cast<CIEC_WSTRING*>(getDO(1));
      }
#else
      //TODO after fixing discussion on the new compliance profile fix these values to STRING
      CIEC_STRING& ID() {
        return *static_cast<CIEC_STRING*>(getDI(1));
      }

      CIEC_STRING& STATUS() {
        return *static_cast<CIEC_STRING*>(getDO(1));
      }
#endif

      CIEC_BOOL& QO() {
        return *static_cast<CIEC_BOOL*>(getDO(0));
      }

      CSyncObject &getFBLock(){
        return mFBLock;
      }

    protected:
      CBaseCommFB(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer, forte::com_infra::EComServiceType paCommServiceType);

      /*!\brief Extract the id and the parameter and the ID. The format is ID[PARAMS] where the opening and closing brackets are actually a opening and a closing brackets. They can be escaped using the $ sign.
       * The opening bracket should only be escaped if it's part of the ID (although not recommended).
       * The closing bracket should only be escaped if part of PARAMS.
       * The $ sign should always be escaped
       *
       * @param paRemainingID The string to be analyzed. After return, it is already positioned for the next layer
       * @param paLayerParams pointer to the found PARAMS
       * @return ID with layer configuration
       */
       static char *extractLayerIdAndParams(char **paRemainingID, char **paLayerParams);

      /*!\brief Generate a layer ID formed by a root with a prefix and a suffix
      *
      * @param paPrefix the prefix to prepend
      * @param paIDRoot the root which would get appended and prepended
      * @param paSuffix the suffix to append
      * @return ID with layer configuration
      */
      static char *buildIDString(const char *paPrefix, const char *paIDRoot, const char *paSuffix);

      virtual EComResponse receiveData() = 0;
      virtual EComResponse sendData() = 0;

      /*!\brief Close the connection and delete the communication stack
      *
      * This function, aided by the the layer destructor, will close and
      * delete bottom layers after closing its connection.
      */
      void closeConnection();

      static const char * const scmResponseTexts[];

      /*!\brief Create the whole communication stack and open the connection
      *
      * This function will configure every layer.
      *
      * \return status of the opening process
      */
      EComResponse openConnection();

      /*\brief go through the given commID and create the according stack of communciation layers
      */
      EComResponse createComstack(char *commID);

      /*!\brief Generate the default layer ID
      *
      *  If the ID string does not contain [], this function will be called
      *  to generate a default layer configuration. This function may be
      *  overwritten by special Comfbs to provide their own default layer
      *  config. See for example GEN_PUBL or GEN_SUBL.
      *
      * @param paID original ID
      * @return ID with layer configuration
      */
      virtual char * getDefaultIDString(const char *paID) = 0;

      EComServiceType mCommServiceType;
      CComLayer *mTopOfComStack;
      unsigned int mComInterruptQueueCount; //!< number of triggers pending from the network
      CComLayer *mInterruptQueue[cgCommunicationInterruptQueueSize];

    private:
      CSyncObject mFBLock;

    public:
      CBaseCommFB(const CBaseCommFB&) = delete;
      CBaseCommFB& operator=(const CBaseCommFB& paOther) = delete;
    };

  }
}

#endif //_SRC_CORE_COMINFRA_BASECOMMFB_H_
