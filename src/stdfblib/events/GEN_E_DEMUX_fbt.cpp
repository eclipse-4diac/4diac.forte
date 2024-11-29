/*******************************************************************************
 * Copyright (c) 2011, 2023 ACIN, Profactor GmbH, fortiss GmbH
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
 *   Alois Zoitl, Matthias Plasch
 *     - initial API and implementation and/or initial documentation
 *    Alois Zoitl - introduced new CGenFB class for better handling generic FBs
 *    Martin Jobst - add generic readInputData and writeOutputData
 *******************************************************************************/
#include "GEN_E_DEMUX_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GEN_E_DEMUX_fbt_gen.cpp"
#endif
#include <stdio.h>

#include "resource.h"
#include "criticalregion.h"

DEFINE_GENERIC_FIRMWARE_FB(GEN_E_DEMUX, g_nStringIdGEN_E_DEMUX)

const CStringDictionary::TStringId GEN_E_DEMUX::scmDataInputNames[] = { g_nStringIdK };
const CStringDictionary::TStringId GEN_E_DEMUX::scmDIDataTypeIds[] = { g_nStringIdUINT };

const CStringDictionary::TStringId GEN_E_DEMUX::scmEventInputNames[] = { g_nStringIdEI };
const CStringDictionary::TStringId GEN_E_DEMUX::scmEventInputTypeIds[] = { g_nStringIdEvent };

GEN_E_DEMUX::GEN_E_DEMUX(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CGenFunctionBlock<CFunctionBlock>(paContainer, paInstanceNameId), mEventOutputNames(nullptr){
}

void GEN_E_DEMUX::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  if(scmEventEIID == paEIID && static_cast<CIEC_UINT::TValueType>(K()) < getFBInterfaceSpec().mNumEOs) {
    sendOutputEvent(static_cast<CIEC_UINT::TValueType>(K()), paECET); // the value of K corresponds to the output event ID;
  }
}

void GEN_E_DEMUX::readInputData(TEventID) {
  readData(0, *mDIs[0], mDIConns[0]);
}

void GEN_E_DEMUX::writeOutputData(TEventID) {
}

bool GEN_E_DEMUX::createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec){
  const char *acPos = strrchr(paConfigString, '_');

  if(nullptr != acPos){
    ++acPos;
    if('D' != *acPos){
      //we have an underscore and it is not the first underscore after E
      paInterfaceSpec.mNumEOs = static_cast<TEventID>(forte::core::util::strtoul(acPos, nullptr, 10));

      if(paInterfaceSpec.mNumEOs < CFunctionBlock::scmMaxInterfaceEvents){
        mEventOutputNames = std::make_unique<CStringDictionary::TStringId[]>(paInterfaceSpec.mNumEOs);
        
        generateGenericInterfacePointNameArray("EO", mEventOutputNames.get(), paInterfaceSpec.mNumEOs);

        paInterfaceSpec.mNumEIs = 1;
        paInterfaceSpec.mEINames = scmEventInputNames;
        paInterfaceSpec.mEONames = mEventOutputNames.get();
        paInterfaceSpec.mEITypeNames = scmEventInputTypeIds;
        paInterfaceSpec.mEOTypeNames = nullptr;
        paInterfaceSpec.mNumDIs = 1;
        paInterfaceSpec.mDINames = scmDataInputNames;
        paInterfaceSpec.mDIDataTypeNames = scmDIDataTypeIds;
        paInterfaceSpec.mNumDOs = 0;
        paInterfaceSpec.mDONames = nullptr;
        paInterfaceSpec.mDODataTypeNames = nullptr;
        return true;
      }
    }
  }
  return false;
}
