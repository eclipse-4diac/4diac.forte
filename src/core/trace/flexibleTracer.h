

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

#ifndef FLEXIBLE_TRACER_H
#define FLEXIBLE_TRACER_H

#include <variant>
#include <string>

#include "stringdict.h"
#include "barectf_platform_forte.h"
#include "internalTracer.h"

/**
 * @brief A tracer that can be changed to use the existing tracers: BarectfPlatformFORTE and CInternalTracer
 * 
 */
class CFlexibleTracer final {
public: 

    CFlexibleTracer(CStringDictionary::TStringId instanceName, size_t bufferSize);

    ~CFlexibleTracer() = default;

    CFlexibleTracer(const CFlexibleTracer&) = delete;
    CFlexibleTracer& operator=(const CFlexibleTracer&) = delete;

    CFlexibleTracer(CFlexibleTracer&&) = delete;
    CFlexibleTracer& operator=(CFlexibleTracer&&) = delete;

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

    bool isEnabled();

    /**
     * @brief Select the tracer to use
     * @param paTracerName An empty string to use the BarectfPlatformFORTE, any other string for the CInternalTracer
     */
    static void setTracer(std::string paTracerName);

private:

  static inline std::string mCurrentTracer;

  std::variant<std::monostate, BarectfPlatformFORTE, CInternalTracer> mTracer{};
};

#endif // FLEXIBLE_TRACER_H
