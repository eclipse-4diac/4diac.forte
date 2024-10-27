/*******************************************************************************
 * Copyright (c) 2024 Jose Cabral
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Jose Cabral
 *      - initial implementation
 *******************************************************************************/

#include "internalTracer.h"
#include "forte_architecture_time.h"

const std::unordered_map<CStringDictionary::TStringId, std::vector<EventMessage>> &CInternalTracer::getResourceOutputMap()
{
  return smResourceOutputMap;
}

CInternalTracer::CInternalTracer(CStringDictionary::TStringId instanceName, size_t) : mOutput{smResourceOutputMap[instanceName]}
{
}

void CInternalTracer::fillStringsVector(const char *const *const paIn, const uint32_t paLen, std::vector<std::string> &paOut)
{
  for (uint32_t i = 0; i < paLen; i++)
  {
    paOut.emplace_back(paIn[i]);
  }
}

void CInternalTracer::traceInstanceData(const char *const paTypeName, const char *const paInstanceName,
                                        const uint32_t paInputsLength, const char *const *const paInputs,
                                        const uint32_t paOutputsLength, const char *const *const paOutputs,
                                        const uint32_t paInternalLength, const char *const *const paInternal,
                                        const uint32_t paInternalFBsLength, const char *const *const paInternalFBs)
{

  std::vector<std::string> inputs(paInputsLength);
  std::vector<std::string> outputs(paOutputsLength);
  std::vector<std::string> internal(paInternalLength);
  std::vector<std::string> internalFBs(paInternalFBsLength);

  fillStringsVector(paInputs, paInputsLength, inputs);
  fillStringsVector(paOutputs, paOutputsLength, outputs);
  fillStringsVector(paInternal, paInternalLength, internal);
  fillStringsVector(paInternalFBs, paInternalFBsLength, internalFBs);

  mOutput.emplace_back("instanceData", std::make_unique<FBInstanceDataPayload>(paTypeName, paInstanceName, inputs, outputs, internal, internalFBs), getNanoSecondsMonotonic());
}

void CInternalTracer::traceReceiveInputEvent(const char *const paTypeName, const char *const paInstanceName, const uint64_t paEventId)
{
  mOutput.emplace_back("receiveInputEvent", std::make_unique<FBInputEventPayload>(paTypeName, paInstanceName, paEventId), getNanoSecondsMonotonic());
}

void CInternalTracer::traceSendOutputEvent(const char *const paTypeName, const char *const paInstanceName, const uint64_t paEventId)
{
  mOutput.emplace_back("sendOutputEvent", std::make_unique<FBOutputEventPayload>(paTypeName, paInstanceName, paEventId), getNanoSecondsMonotonic());
}

void CInternalTracer::traceInputData(const char *const paTypeName, const char *const paInstanceName,
                                     const uint64_t paDataId, const char *const paValue)
{

  mOutput.emplace_back("inputData", std::make_unique<FBDataPayload>(paTypeName, paInstanceName, paDataId, paValue), getNanoSecondsMonotonic());
}

void CInternalTracer::traceOutputData(const char *const paTypeName, const char *const paInstanceName, const uint64_t paDataId,
                                      const char *const paValue)
{
  mOutput.emplace_back("outputData", std::make_unique<FBDataPayload>(paTypeName, paInstanceName, paDataId, paValue), getNanoSecondsMonotonic());
}

bool CInternalTracer::isEnabled()
{
  return true;
}
