/*******************************************************************************
 * Copyright (c) 2005 - 2015 Profactor GmbH, ACIN, fortiss GmbH
 *               2023 Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Thomas Strasser, Alois Zoitl, Gerhard Ebenhofer, Ingo Hegny
 *      - initial implementation and rework communication infrastructure
 *    Martin Jobst - account for data type size in FB initialization
 *******************************************************************************/
#include <string.h>
#include "basicfb.h"
#include "resource.h"

CBasicFB::CBasicFB(forte::core::CFBContainer &paContainer, const SFBInterfaceSpec& paInterfaceSpec,
                   const CStringDictionary::TStringId paInstanceNameId,
                   const SInternalVarsInformation *paVarInternals) :
        CFunctionBlock(paContainer, paInterfaceSpec, paInstanceNameId), mECCState(0),
        cmVarInternals(paVarInternals) {
}

void CBasicFB::setInitialValues() {
  CFunctionBlock::setInitialValues();
  if(cmVarInternals) {
    const CStringDictionary::TStringId *pnDataIds = cmVarInternals->mIntVarsDataTypeNames;
    for (TPortId i = 0; i < cmVarInternals->mNumIntVars; ++i) {
      TForteByte *varsData = nullptr;
      CIEC_ANY *value = createDataPoint(pnDataIds, varsData);
      if (value) { getDI(i)->setValue(*value); }
      delete value;
    }
  }
}

CIEC_ANY* CBasicFB::getVar(CStringDictionary::TStringId *paNameList, unsigned int paNameListSize) {
  CIEC_ANY *poRetVal = CFunctionBlock::getVar(paNameList, paNameListSize);
  if((nullptr == poRetVal) && (1 == paNameListSize)) {
    poRetVal = getInternalVar(*paNameList);
    if(nullptr == poRetVal && !strcmp("!ECC", CStringDictionary::getInstance().get(*paNameList))) { //TODO consider if this can also be an string ID in a different way
      poRetVal = &mECCState;
    }
  }
  return poRetVal;
}

CIEC_ANY* CBasicFB::getInternalVar(CStringDictionary::TStringId paInternalName) {
  CIEC_ANY *retVal = nullptr;
  if(nullptr != cmVarInternals) {
    TPortId unVarId = getPortId(paInternalName, cmVarInternals->mNumIntVars, cmVarInternals->mIntVarsNames);
    if(cgInvalidPortId != unVarId) {
      retVal = getVarInternal(unVarId);
    }
  }
  return retVal;
}

int CBasicFB::toString(char *paValue, size_t paBufferSize) const {
  int usedBuffer = CFunctionBlock::toString(paValue, paBufferSize);
  if (usedBuffer < 1 || cmVarInternals == nullptr || (cmVarInternals != nullptr && cmVarInternals->mNumIntVars == 0)) {
    return usedBuffer; // nothing to do
  }

  --usedBuffer;  // move the pointer to the position of the closing )
  if(usedBuffer > 1) { // not only ()
    strncpy(paValue + usedBuffer, csmToStringSeparator, paBufferSize - usedBuffer);
    usedBuffer += sizeof(csmToStringSeparator) - 1;
  }

  for (size_t i = 0; i < cmVarInternals->mNumIntVars; ++i) {
    const CIEC_ANY *const variable = getVarInternal(i);
    const CStringDictionary::TStringId nameId = cmVarInternals->mIntVarsNames[i];
    int result = writeToStringNameValuePair(paValue + usedBuffer, paBufferSize - usedBuffer, nameId, variable);
    if(result >= 0) {
      usedBuffer += result;
    } else {
      return -1;
    }
    if (paBufferSize - usedBuffer >= sizeof(csmToStringSeparator)) {
      strncpy(paValue + usedBuffer, csmToStringSeparator, paBufferSize - usedBuffer);
      usedBuffer += sizeof(csmToStringSeparator) - 1;
    } else {
      return -1;
    }
  }
  strncpy(paValue + std::max(1, usedBuffer - 2), ")", paBufferSize - std::max(1, usedBuffer - 2)); // overwrite the last two bytes with the closing )
  return std::max(2, usedBuffer - 1);
};

size_t CBasicFB::getToStringBufferSize() const {
  size_t bufferSize =  CFunctionBlock::getToStringBufferSize();
  if(cmVarInternals) {
    for (size_t i = 0; i < cmVarInternals->mNumIntVars; ++i) {
        const CIEC_ANY *const variable = getVarInternal(i);
        const CStringDictionary::TStringId nameId = cmVarInternals->mIntVarsNames[i];
        const char *varName = CStringDictionary::getInstance().get(nameId); 
        bufferSize += strlen(varName) + 4 + variable->getToStringBufferSize();
    }   
  }
   return bufferSize;
}

#ifdef FORTE_TRACE_CTF
void CBasicFB::traceInstanceData() {
  std::vector<std::string> inputs(getFBInterfaceSpec().mNumDIs);
  std::vector<std::string> outputs(getFBInterfaceSpec().mNumDOs);
  std::vector<std::string> internals(cmVarInternals ? cmVarInternals->mNumIntVars : 0);
  std::vector<std::string> internalFbs(getChildren().size());
  std::vector<const char *> inputs_c_str(inputs.size());
  std::vector<const char *> outputs_c_str(outputs.size());
  std::vector<const char *> internals_c_str(internals.size());
  std::vector<const char *> internalFbs_c_str(internalFbs.size());

  for(TPortId i = 0; i < inputs.size(); ++i) {
    CIEC_ANY *value = getDI(i);
    std::string &valueString = inputs[i];
    valueString.reserve(value->getToStringBufferSize());
    value->toString(valueString.data(), valueString.capacity());
    inputs_c_str[i] = valueString.c_str();
  }

  for(TPortId i = 0; i < outputs.size(); ++i) {
    CIEC_ANY *value = getDO(i);
    std::string &valueString = outputs[i];
    valueString.reserve(value->getToStringBufferSize());
    value->toString(valueString.data(), valueString.capacity());
    outputs_c_str[i] = valueString.c_str();
  }

  for(TPortId i = 0; i < internals.size(); ++i) {
    CIEC_ANY *value = getVarInternal(i);
    std::string &valueString = internals[i];
    valueString.reserve(value->getToStringBufferSize());
    value->toString(valueString.data(), valueString.capacity());
    internals_c_str[i] = valueString.c_str();
  }

  TPortId i = 0;
  for(auto child : getChildren()){
    CFunctionBlock &value = static_cast<CFunctionBlock &>(*child);
    std::string &valueString = internalFbs[i];
    valueString.reserve(value.getToStringBufferSize());
    value.toString(valueString.data(), valueString.capacity());
    internalFbs_c_str[i] = valueString.c_str();
    ++i;
  }

  getResource()->getTracer().traceInstanceData(getFBTypeName() ?: "null",
                                     getFullQualifiedApplicationInstanceName('.').c_str() ?: "null",
                                     static_cast<uint32_t >(inputs.size()), inputs_c_str.data(),
                                     static_cast<uint32_t >(outputs.size()), outputs_c_str.data(),
                                     static_cast<uint32_t >(internals.size()), internals_c_str.data(),
                                     static_cast<uint32_t >(internalFbs.size()), internalFbs_c_str.data());
}
#endif

