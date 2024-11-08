/*******************************************************************************
 * Copyright (c) 2014, 2023 Profactor GmbH, fortiss GmbH,
 *                          Johannes Kepler University, Martin Erich Jobst
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
 *   Martin Jobst
 *     - refactor for ANY variant
 *     - add generic readInputData and writeOutputData
 *******************************************************************************/

#include "GEN_ADD_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GEN_ADD_fbt_gen.cpp"
#endif

#include <ctype.h>
#include <stdio.h>
#include "ifSpecBuilder.h"
#include "forte_printer.h"
#include "resource.h"
#include "criticalregion.h"

DEFINE_GENERIC_FIRMWARE_FB(GEN_ADD, g_nStringIdGEN_ADD)

GEN_ADD::GEN_ADD(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CGenFunctionBlock<CFunctionBlock>(paContainer, paInstanceNameId), mDInputs(0){
}

void GEN_ADD::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch (paEIID){
    case scmEventREQID:
      if(mDInputs) {
        var_OUT() = var_IN(0);
        for (size_t i = 1; i < mDInputs; ++i) {
          var_OUT() = std::visit([](auto &&paOUT, auto &&paIN) -> CIEC_ANY_MAGNITUDE_VARIANT {
              using T = std::decay_t<decltype(paOUT)>;
              using U = std::decay_t<decltype(paIN)>;
              using deductedType = typename forte::core::mpl::get_add_operator_result_type<T, U>::type;
              if constexpr (!std::is_same<deductedType, forte::core::mpl::NullType>::value) {
                return func_ADD(paOUT, paIN);
              }
              DEVLOG_ERROR("Adding incompatible types %s and %s\n",
                           CStringDictionary::getInstance().get(paOUT.getTypeNameID()),
                           CStringDictionary::getInstance().get(paIN.getTypeNameID()));
              return paOUT;
          }, static_cast<CIEC_ANY_MAGNITUDE_VARIANT::variant&>(var_OUT()), 
             static_cast<CIEC_ANY_MAGNITUDE_VARIANT::variant&>(var_IN(i)));
        }
      }
      sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

void GEN_ADD::readInputData(TEventID) {
  for(TPortId i = 0; i < getFBInterfaceSpec().mNumDIs; ++i) {
    readData(i, *mDIs[i], mDIConns[i]);
  }
}

void GEN_ADD::writeOutputData(TEventID) {
  writeData(0, *mDOs[0], mDOConns[0]);
}

bool GEN_ADD::createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec){
  const char *pcPos = strrchr(paConfigString, '_');
  if(nullptr != pcPos){
    pcPos++;
    //we have an underscore and it is the first underscore after AND
    mDInputs = static_cast<unsigned int>(forte::core::util::strtoul(pcPos, nullptr, 10));
    DEVLOG_DEBUG("DIs: %d;\n", mDInputs);
  }
  else{
    return false;
  }

  if(mDInputs < 2){
    return false;
  }

  //now the number of needed eventInputs and dataOutputs are available in the integer array
  //create the eventInputs

  static const std::array<CStringDictionary::TStringId, 1>anEventInputNames = { g_nStringIdREQ };
  static const std::array<CStringDictionary::TStringId, 1>anEventOutputNames = { g_nStringIdCNF };
  static const std::array<CStringDictionary::TStringId, 1>anDataOutputNames = { g_nStringIdOUT };
  static const std::array<CStringDictionary::TStringId, 1>anDataOutputTypeIds = { g_nStringIdANY_MAGNITUDE };
  static const std::array<CStringDictionary::TStringId, 1>anEventInputTypes = { g_nStringIdEvent };
  static const std::array<CStringDictionary::TStringId, 1>anEventOutputTypes = { g_nStringIdEvent };

  forte::core::util::CIfSpecBuilder isb;
  isb.mEI.setStaticEvents(anEventInputNames);
  isb.mEO.setStaticEvents(anEventOutputNames);
  isb.mEITypes.setStaticEvents(anEventInputTypes);
  isb.mEOTypes.setStaticEvents(anEventOutputTypes);
  isb.mDI.addDataRange("IN", static_cast<int>(mDInputs), g_nStringIdANY_MAGNITUDE);
  isb.mDO.setStaticData(anDataOutputNames, anDataOutputTypeIds);
  return isb.build(mIfSpecStorage, paInterfaceSpec);
}
