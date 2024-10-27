

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

#include "flexibleTracer.h"

void CFlexibelTracer::setTracer(std::string paTracerName) {
  CFlexibelTracer::mCurrentTracer = std::move(paTracerName);
}

CFlexibelTracer::CFlexibelTracer(CStringDictionary::TStringId instanceName, size_t bufferSize) {
  if(mCurrentTracer == ""){
    mTracer.emplace<BarectfPlatformFORTE>(instanceName, bufferSize);
  } else {
    mTracer.emplace<CInternalTracer>(instanceName, bufferSize);
  }
}

void CFlexibelTracer::traceInstanceData(const char * const paTypeName, const char * const paInstanceName,
  const uint32_t paInputsLength, const char * const * const paInputs,
  const uint32_t paOutputsLength, const char * const * const paOutputs,
  const uint32_t paInternalLength, const char * const * const paInternal,
  const uint32_t paInternalFBsLength, const char * const * const paInternalFBs){
      
  std::visit(
    [&](auto &&paTracer){
      using T = std::decay_t<decltype(paTracer)>;
      if constexpr (std::is_same_v<T, std::monostate> == false) {
        paTracer.traceInstanceData(paTypeName, paInstanceName, 
          paInputsLength, paInputs, 
          paOutputsLength, paOutputs, 
          paInternalLength, paInternal, 
          paInternalFBsLength, paInternalFBs);
      }
    }, 
    mTracer
  );
}


void CFlexibelTracer::traceReceiveInputEvent(const char * const paTypeName, const char * const paInstanceName, const uint64_t paEventId){
  std::visit(
    [&](auto &&paTracer){
      using T = std::decay_t<decltype(paTracer)>;
      if constexpr (std::is_same_v<T, std::monostate> == false) {
        paTracer.traceReceiveInputEvent(paTypeName, paInstanceName, paEventId);
      }
    }, 
    mTracer
  );
}


void CFlexibelTracer::traceSendOutputEvent(const char * const paTypeName, const char * const paInstanceName, const uint64_t paEventId){
    std::visit(
      [&](auto &&paTracer){
        using T = std::decay_t<decltype(paTracer)>;
        if constexpr (std::is_same_v<T, std::monostate> == false) {
          paTracer.traceSendOutputEvent(paTypeName, paInstanceName, paEventId);
        }
      }, 
      mTracer
    );
}


void CFlexibelTracer::traceInputData( const char * const paTypeName, const char * const paInstanceName,
  const uint64_t paDataId, const char * const paValue){
  
   std::visit(
      [&](auto &&paTracer){
        using T = std::decay_t<decltype(paTracer)>;
        if constexpr (std::is_same_v<T, std::monostate> == false) {
          paTracer.traceInputData(paTypeName, paInstanceName, paDataId, paValue);
        }
      }, 
      mTracer
    );
}


void CFlexibelTracer::traceOutputData(const char * const paTypeName, const char * const paInstanceName, 
  const uint64_t paDataId, const char * const paValue){

   std::visit(
      [&](auto &&paTracer){
        using T = std::decay_t<decltype(paTracer)>;
        if constexpr (std::is_same_v<T, std::monostate> == false) {
          paTracer.traceOutputData(paTypeName, paInstanceName, paDataId, paValue);
        }
      }, 
      mTracer
    );
}

bool CFlexibelTracer::isEnabled() {

  return std::visit(
      [](auto &&paTracer) -> bool {
        using T = std::decay_t<decltype(paTracer)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
          return false;
        } else {
          return paTracer.isEnabled();
        }
      }, 
      mTracer
    );
}



