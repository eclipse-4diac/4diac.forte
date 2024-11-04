/*******************************************************************************
 * Copyright (c)2018 Johannes Kepler University
 *               2023 Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - initial API and implementation and/or initial documentation
 *   Martin Jobst
 *     - refactor for ANY variant
 *     - add generic readInputData and writeOutputData
 *******************************************************************************/
#ifndef _GENBITBASE_H_
#define _GENBITBASE_H_

#include "../genfb.h"
#include "forte_any_bit_variant.h"

class CGenBitBase : public CGenFunctionBlock<CFunctionBlock> {

  protected:
    CGenBitBase(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);
    ~CGenBitBase() override;

    CIEC_ANY_BIT_VARIANT& var_IN(size_t paIndex) {
      return *static_cast<CIEC_ANY_BIT_VARIANT *>(getDI(paIndex));
    }

    CIEC_ANY_BIT_VARIANT &var_OUT(){
      return *static_cast<CIEC_ANY_BIT_VARIANT *>(getDO(0));
    }

    static const TEventID scmEventREQID = 0;
    static const TEventID scmEventCNFID = 0;

  private:
    CStringDictionary::TStringId *mDataInputNames;
    CStringDictionary::TStringId *mDataInputTypeIds;

    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];

    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];

    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];

    void readInputData(TEventID paEI) override;
    void writeOutputData(TEventID paEO) override;

    bool createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec) override;
};

#endif /* _GENBITBASE_H_ */
