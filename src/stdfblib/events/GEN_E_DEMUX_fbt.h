/*******************************************************************************
 * Copyright (c) 2011, 2023 ACIN
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
 *   Alois Zoitl
 *     - initial API and implementation and/or initial documentation
 *    Alois Zoitl - introduced new CGenFB class for better handling generic FBs
 *    Martin Jobst - add generic readInputData and writeOutputData
 *******************************************************************************/
#ifndef _GEN_E_DEMUX_H_
#define _GEN_E_DEMUX_H_

#include <genfb.h>

class GEN_E_DEMUX : public CGenFunctionBlock<CFunctionBlock>{
  DECLARE_GENERIC_FIRMWARE_FB(GEN_E_DEMUX)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[], scmDIDataTypeIds[];

    static const TEventID scmEventEIID = 0;
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];

    CStringDictionary::TStringId *mEventOutputNames;
    CStringDictionary::TStringId *mEventOutputTypeIds;

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEI) override;
    void writeOutputData(TEventID paEO) override;

    bool createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec) override;

    CIEC_UINT& K(){
      return *static_cast<CIEC_UINT*>(getDI(0));
    }

  public:
    GEN_E_DEMUX(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);
    ~GEN_E_DEMUX() override;

};
#endif //_GEN_E_DEMUX_H_
