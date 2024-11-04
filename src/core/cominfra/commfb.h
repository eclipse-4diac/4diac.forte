/*******************************************************************************
 * Copyright (c) 2006, 2023 ACIN, Profactor GmbH, fortiss GmbH
 *                          Johannes Kepler University
 *                          Martin Erich Jobst
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
 *    Martin Jobst - add generic readInputData and writeOutputData
 *******************************************************************************/
#ifndef _COMMFB_H_
#define _COMMFB_H_

#include <forte_config.h>
#include "basecommfb.h"
#include "comtypes.h"

namespace forte {
  namespace com_infra {

    class CCommFB : public CBaseCommFB {
    public:
      ~CCommFB() override;

      EMGMResponse changeExecutionState(EMGMCommandType paCommand) override;

    protected:
      CCommFB(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer, forte::com_infra::EComServiceType paCommServiceType);

      void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

      void readInputData(TEventID paEI) override;
      void writeOutputData(TEventID paEO) override;

      static const TEventID scmEventINITID = 0;
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmSendNotificationEventID = 1;
      static const TEventID scmReceiveNotificationEventID = 1;

      static const char * const scmDefaultIDPrefix;
      static const char * const scmDefaultIDSuffix;

      static char *extractLayerIdAndParams(char **paRemainingID, char **paLayerParams);

      char *getDefaultIDString(const char *paID) override;

      EComResponse receiveData() override;
      EComResponse sendData() override;

    private:
      static const CStringDictionary::TStringId scmRequesterEventInputNameIds[];
      static const CStringDictionary::TStringId scmRequesterEventOutputNameIds[];

      static const CStringDictionary::TStringId scmResponderEventInputNameIds[];
      static const CStringDictionary::TStringId scmResponderEventOutputNameIds[];

      static const CStringDictionary::TStringId scmEventInputTypeIds[];
      static const CStringDictionary::TStringId scmEventOutputTypeIds[];

        bool createInterfaceSpec(const char* paConfigString, SFBInterfaceSpec& paInterfaceSpec) override;

        void configureDIs(const char* paDIConfigString, SFBInterfaceSpec& paInterfaceSpec) const;
        void configureDOs(const char* paDOConfigString, SFBInterfaceSpec& paInterfaceSpec) const;
    };

  }
}

#endif //_COMMFB_H_
