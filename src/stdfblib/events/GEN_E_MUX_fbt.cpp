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
#include "GEN_E_MUX_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GEN_E_MUX_fbt_gen.cpp"
#endif
#include <stdio.h>

#include "resource.h"
#include "criticalregion.h"

DEFINE_GENERIC_FIRMWARE_FB(GEN_E_MUX, g_nStringIdGEN_E_MUX);

const CStringDictionary::TStringId GEN_E_MUX::scmDataOutputNames[] = { g_nStringIdK };
const CStringDictionary::TStringId GEN_E_MUX::scmDODataTypeIds[] = { g_nStringIdUINT };

const CStringDictionary::TStringId GEN_E_MUX::scmEventOutputNames[] = { g_nStringIdEO };
const CStringDictionary::TStringId GEN_E_MUX::scmEventOutputTypeIds[] = { g_nStringIdEvent };

GEN_E_MUX::GEN_E_MUX(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CGenFunctionBlock<CFunctionBlock>(paContainer, paInstanceNameId), mEventInputNames(nullptr){
}

GEN_E_MUX::~GEN_E_MUX(){
  delete[] mEventInputNames;
  delete[] mEventInputTypeIds;
}

void GEN_E_MUX::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  if(paEIID < getFBInterfaceSpec().mNumEIs){
    K() = CIEC_UINT(static_cast<TForteUInt16>(paEIID));
    sendOutputEvent(scmEventEOID, paECET);
  }
}

void GEN_E_MUX::readInputData(TEventID) {
}

void GEN_E_MUX::writeOutputData(TEventID) {
  writeData(0, *mDOs[0], mDOConns[0]);
}

bool GEN_E_MUX::createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec){
  const char *acPos = strrchr(paConfigString, '_');

  if(nullptr != acPos){
    ++acPos;
    if('M' != *acPos){
      //we have an underscore and it is not the first underscore after E
      paInterfaceSpec.mNumEIs = static_cast<TEventID>(forte::core::util::strtoul(acPos, nullptr, 10));

      if(paInterfaceSpec.mNumEIs < CFunctionBlock::scmMaxInterfaceEvents && paInterfaceSpec.mNumEIs >= 2){
        mEventInputNames = new CStringDictionary::TStringId[paInterfaceSpec.mNumEIs];
        mEventInputTypeIds = new CStringDictionary::TStringId[paInterfaceSpec.mNumEIs];
        const CStringDictionary::TStringId eventID = g_nStringIdEvent;
        std::fill_n(mEventInputTypeIds, paInterfaceSpec.mNumEIs, eventID);
        generateGenericInterfacePointNameArray("EI", mEventInputNames, paInterfaceSpec.mNumEIs);

        paInterfaceSpec.mEINames = mEventInputNames;
        paInterfaceSpec.mNumEOs = 1;
        paInterfaceSpec.mEONames = scmEventOutputNames;
        paInterfaceSpec.mEITypeNames = mEventInputNames;
        paInterfaceSpec.mEOTypeNames = scmEventOutputTypeIds;
        paInterfaceSpec.mNumDIs = 0;
        paInterfaceSpec.mDINames = nullptr;
        paInterfaceSpec.mDIDataTypeNames = nullptr;
        paInterfaceSpec.mNumDOs = 1;
        paInterfaceSpec.mDONames = scmDataOutputNames;
        paInterfaceSpec.mDODataTypeNames = scmDODataTypeIds;
        return true;
      }
      else{
        if(paInterfaceSpec.mNumEIs >= CFunctionBlock::scmMaxInterfaceEvents){
          DEVLOG_ERROR("Cannot configure FB-Instance E_MUX_%d. Number of event inputs exceeds maximum of %d.\n", paInterfaceSpec.mNumEIs, CFunctionBlock::scmMaxInterfaceEvents);
        }
        else{
          DEVLOG_ERROR("Cannot configure FB-Instance E_MUX_%d. Number of event inputs smaller than minimum of 2.\n", paInterfaceSpec.mNumEIs);
        }
      }
    }
  }
  return false;
}
