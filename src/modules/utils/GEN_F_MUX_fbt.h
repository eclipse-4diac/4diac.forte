/*******************************************************************************
 * Copyright (c) 2012, 2023 Profactor GmbH, ACIN, fortiss Gmbh
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
 *   Matthias Plasch, Monika Wenger, Alois Zoitl
 *   - initial API and implementation and/or initial documentation
 *    Alois Zoitl - introduced new CGenFB class for better handling generic FBs
 *    Martin Jobst - add generic readInputData and writeOutputData
 *******************************************************************************/
#ifndef _GEN_F_MUX_H_
#define _GEN_F_MUX_H_

#include <genfb.h>

#include <memory>

class GEN_F_MUX : public CGenFunctionBlock<CFunctionBlock> {
  DECLARE_GENERIC_FIRMWARE_FB(GEN_F_MUX)

  private:
    //we know for sure that there is one output event
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];

    static const TEventID scmEventEOID = 0;

    std::unique_ptr<CStringDictionary::TStringId[]> mEventInputNames;
    std::unique_ptr<CStringDictionary::TStringId[]> mDataOutputNames;
    std::unique_ptr<CStringDictionary::TStringId[]> mDataInputNames;
    std::unique_ptr<CStringDictionary::TStringId[]> mDataOutputTypeIds;
    std::unique_ptr<CStringDictionary::TStringId[]> mDataInputTypeIds;

    //self-defined members
    size_t mEInputs{0};
    size_t mEOutputs{0};
    size_t mDInputs{0};
    size_t mDOutputs{0};

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEI) override;
    void writeOutputData(TEventID paEO) override;

    bool createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec) override;

  public:
    GEN_F_MUX(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);
    ~GEN_F_MUX() override = default;
};
#endif //_GEN_F_MUX_H_
