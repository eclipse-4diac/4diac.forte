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
#ifndef _GEN_E_MUX_H_
#define _GEN_E_MUX_H_

#include <genfb.h>

class GEN_E_MUX : public CGenFunctionBlock<CFunctionBlock>{
  DECLARE_GENERIC_FIRMWARE_FB(GEN_E_MUX)

  private:
    static const CStringDictionary::TStringId scmDataOutputNames[], scmDODataTypeIds[];

    static const TEventID scmEventEOID = 0;
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];

    CStringDictionary::TStringId *mEventInputNames;
    CStringDictionary::TStringId *mEventInputTypeIds;

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEI) override;
    void writeOutputData(TEventID paEO) override;

    bool createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec) override;

    CIEC_UINT& K(){
      return *static_cast<CIEC_UINT*>(getDO(0));
    }

  public:
    GEN_E_MUX(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);
    ~GEN_E_MUX() override;

};
#endif //_GEN_E_MUX_H_
