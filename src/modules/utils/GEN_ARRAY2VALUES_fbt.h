/*******************************************************************************
 * Copyright (c) 2014, 2023 Profactor GmbH, fortiss GbmH
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
 *   Matthias Plasch, Alois Zoitl
 *   - initial API and implementation and/or initial documentation
 *    Alois Zoitl - introduced new CGenFB class for better handling generic FBs
 *    Martin Jobst - add generic readInputData and writeOutputData
 *******************************************************************************/
#ifndef _GEN_ARRAY2VALUES_H_
#define _GEN_ARRAY2VALUES_H_

#include <genfb.h>

class GEN_ARRAY2VALUES : public CGenFunctionBlock<CFunctionBlock> {
  DECLARE_GENERIC_FIRMWARE_FB(GEN_ARRAY2VALUES)

  private:
    CStringDictionary::TStringId *mDataOutputNames;
    CStringDictionary::TStringId *mDataOutputTypeIds;

    static const CStringDictionary::TStringId scmDataInputNames[];
    CStringDictionary::TStringId *mDataInputTypeIds;

    CIEC_ARRAY &IN_Array(){
      return *static_cast<CIEC_ARRAY *>(getDI(0));
    }
    ;

    static const TEventID scmEventREQID = 0;
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];

    static const TEventID scmEventCNFID = 0;
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];

    //self-defined members
    size_t mDOutputs;
    CStringDictionary::TStringId mValueTypeID;

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEI) override;
    void writeOutputData(TEventID paEO) override;

    bool createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec) override;

  public:
    GEN_ARRAY2VALUES(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);
    ~GEN_ARRAY2VALUES() override;

};

#endif //_GEN_ARRAY2VALUES_H_

