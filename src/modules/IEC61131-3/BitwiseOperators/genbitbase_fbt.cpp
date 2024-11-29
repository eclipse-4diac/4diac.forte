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
#include "genbitbase_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "genbitbase_fbt_gen.cpp"
#endif

#include <ctype.h>
#include <stdio.h>
#include "forte_printer.h"
#include "resource.h"
#include "criticalregion.h"


const CStringDictionary::TStringId CGenBitBase::scmDataOutputNames[] = { g_nStringIdOUT };
const CStringDictionary::TStringId CGenBitBase::scmDataOutputTypeIds[] = {g_nStringIdANY_BIT };

const CStringDictionary::TStringId CGenBitBase::scmEventInputNames[] = {g_nStringIdREQ };

const CStringDictionary::TStringId CGenBitBase::scmEventOutputNames[] = { g_nStringIdCNF };

CGenBitBase::CGenBitBase(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CGenFunctionBlock<CFunctionBlock>(paContainer, paInstanceNameId) {
}

void CGenBitBase::readInputData(TEventID) {
  for(TPortId i = 0; i < getFBInterfaceSpec().mNumDIs; ++i) {
    readData(i, *mDIs[i], mDIConns[i]);
  }
}

void CGenBitBase::writeOutputData(TEventID) {
  writeData(0, *mDOs[0], mDOConns[0]);
}

bool CGenBitBase::createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec) {
  const char *pcPos = strrchr(paConfigString, '_');

  if (nullptr != pcPos) {
    pcPos++;
    //we have an underscore and it is the first underscore after AND
    paInterfaceSpec.mNumDIs = static_cast<TPortId>(forte::core::util::strtoul(pcPos, nullptr, 10));
    DEVLOG_DEBUG("DIs: %d;\n", paInterfaceSpec.mNumDIs);
  } else {
    return false;
  }

  if (paInterfaceSpec.mNumDIs < 2) {
    return false;
  }

  //now the number of needed eventInputs and dataOutputs are available in the integer array
  //create the eventInputs
  if (paInterfaceSpec.mNumDIs < CFunctionBlock::scmMaxInterfaceEvents) {

    //create the data inputs
    mDataInputNames = std::make_unique<CStringDictionary::TStringId[]>(paInterfaceSpec.mNumDIs);
    mDataInputTypeIds = std::make_unique<CStringDictionary::TStringId[]>(paInterfaceSpec.mNumDIs);

    char diNames[cgIdentifierLength] = { "IN" };

    for (size_t di = 0; di < paInterfaceSpec.mNumDIs; ++di) {
      forte_snprintf(&(diNames[2]), 5 - 2, "%i", di + 1);
      mDataInputNames[di] = CStringDictionary::getInstance().insert(diNames);
      mDataInputTypeIds[di] = g_nStringIdANY_BIT;
    }

    //setup the interface Specification
    paInterfaceSpec.mNumEIs = 1;
    paInterfaceSpec.mEINames = scmEventInputNames;
    paInterfaceSpec.mNumEOs = 1;
    paInterfaceSpec.mEONames = scmEventOutputNames;
    paInterfaceSpec.mDINames = mDataInputNames.get();
    paInterfaceSpec.mDIDataTypeNames = mDataInputTypeIds.get();
    paInterfaceSpec.mNumDOs = 1;
    paInterfaceSpec.mDONames = scmDataOutputNames;
    paInterfaceSpec.mDODataTypeNames = scmDataOutputTypeIds;
    return true;
  }
  return false;
}
