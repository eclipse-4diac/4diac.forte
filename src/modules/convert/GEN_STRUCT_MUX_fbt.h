/*******************************************************************************
 * Copyright (c) 2020, 2023 Johannes Kepler University
 *                          Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - initial API and implementation and/or initial documentation
 *   Martin Jobst - add generic readInputData and writeOutputData
 *******************************************************************************/
#ifndef _GEN_STRUCT_MUX_H_
#define _GEN_STRUCT_MUX_H_

#include <genfb.h>
#include <stdio.h>

class GEN_STRUCT_MUX : public CGenFunctionBlock<CFunctionBlock> {
    DECLARE_GENERIC_FIRMWARE_FB(GEN_STRUCT_MUX)

  private:
    static const CStringDictionary::TStringId scmDataOutputNames[];

    static const TEventID scmEventREQID = 0;
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];

    static const TEventID scmEventCNFID = 0;
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEI) override;
    void writeOutputData(TEventID paEO) override;

    bool createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec) override;

    CIEC_STRUCT& st_OUT() {
       return *static_cast<CIEC_STRUCT*>(getDO(0));
     }

    bool initialize() override;
    void setInitialValues() override;
    void copyStructValuesToInputs();

  public:

    GEN_STRUCT_MUX(const GEN_STRUCT_MUX &paOther) = delete;
    GEN_STRUCT_MUX(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);
    ~GEN_STRUCT_MUX() override;

    static CStringDictionary::TStringId getStructNameId(const char *paConfigString);

    static size_t calcStructTypeNameSize(CIEC_STRUCT &paStruct);

};

#endif //_GEN_STRUCT_MUX_H_
