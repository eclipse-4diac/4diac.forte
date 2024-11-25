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

#ifndef INTERNAL_TRACER_H
#define INTERNAL_TRACER_H

#include <unordered_map>
#include <vector>

#include "EventMessage.h"
#include "stringdict.h"

/**
 * @brief Internal tracer
 * 
 * Receives the data to be traced and store the information as EventMessages. It contains
 * a static variable mapping the resources names to the vector of traced events in that resource,
 * which can be retrieved via a static getter.
 */
class CInternalTracer final {
public: 

    CInternalTracer(CStringDictionary::TStringId instanceName, size_t bufferSize);

    virtual ~CInternalTracer() = default;

    CInternalTracer(const CInternalTracer&) = delete;
    CInternalTracer& operator=(const CInternalTracer&) = delete;

    CInternalTracer(CInternalTracer&&) = delete;
    CInternalTracer& operator=(CInternalTracer&&) = delete;

    void traceInstanceData(const char * const paTypeName, const char * const paInstanceName,
      const uint32_t paInputsLength, const char * const * const paInputs,
      const uint32_t paOutputsLength, const char * const * const paOutputs,
      const uint32_t paInternalLength, const char * const * const paInternal,
      const uint32_t paInternalFBsLength, const char * const * const paInternalFBs);

    void traceReceiveInputEvent(const char * const paTypeName, const char * const paInstanceName, const uint64_t paEventId);

    void traceSendOutputEvent(const char * const paTypeName, const char * const paInstanceName, const uint64_t paEventId);

    void traceInputData( const char * const paTypeName, const char * const paInstanceName,
      const uint64_t paDataId, const char * const paValue);

    void traceOutputData(const char * const paTypeName, const char * const paInstanceName, const uint64_t paDataId, 
      const char * const paValue);

    /**
     * @brief Fills the given vector with the array of const char* information. The vector must already contain the
     * expected amount of elements to be inserted, defined by paLen. This help performance by allocating the vector
     * with a size that won't change while filling it 
     * 
     * @param paIn the input of texts that will be inserted into the vector
     * @param paLen the length of paIn 
     * @param paOut output where to store the passed texts
     */
    void fillStringsVector(const char * const * const paIn, const uint32_t paLen, std::vector<std::string>& paOut);

    bool isEnabled();

    /**
     * @brief Get the map of resource name to the events traced by that resource
     * 
     * @return the map containing the event messages for each resource
     */
    static const std::unordered_map<CStringDictionary::TStringId, std::vector<EventMessage>>& getResourceOutputMap();

private: 
  std::vector<EventMessage>& mOutput;

  static inline std::unordered_map<CStringDictionary::TStringId, std::vector<EventMessage>> smResourceOutputMap;
};

#endif // INTERNAL_TRACER_H
