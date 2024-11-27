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
#ifndef _GEN_STRUCT_DEMUX_H_
#define _GEN_STRUCT_DEMUX_H_

#include <genfb.h>
#include <stdio.h>

#include <memory>
#include <array>

class GEN_STRUCT_DEMUX : public CGenFunctionBlock<CFunctionBlock> {
    DECLARE_GENERIC_FIRMWARE_FB(GEN_STRUCT_DEMUX)

  private:

    std::unique_ptr<CStringDictionary::TStringId[]> mDoDataTypeNames;
    std::unique_ptr<CStringDictionary::TStringId[]> mDoNames;

    static const CStringDictionary::TStringId scmDataInputNames[];
    std::array<CStringDictionary::TStringId, 1> mDiDataTypeNames;

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

    CIEC_STRUCT& st_IN() {
       return *static_cast<CIEC_STRUCT*>(getDI(0));
    }

    bool initialize() override;
    void setInitialValues() override;
    void copyStructValuesToOutputs();

  public:

    GEN_STRUCT_DEMUX(const GEN_STRUCT_DEMUX &paOther) = delete;
    GEN_STRUCT_DEMUX(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);
    ~GEN_STRUCT_DEMUX() override = default;

};

#endif //_GEN_STRUCT_DEMUX_H_
