/*******************************************************************************
 * Copyright (c) 2005, 2023 ACIN, Profactor GmbH, fortiss GmbH
 *                          Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl, Thomas Strasser, Gunnar Grabmair, Martin Melik Merkumians,
 *   Ingo Hegny, Gerhard Ebenhofer
 *    - initial API and implementation and/or initial documentation
 *   Martin Jobst - add generic readInputData and writeOutputData
 *******************************************************************************/
#ifndef _TIMEDFB_H_
#define _TIMEDFB_H_

#include "../core/esfb.h"
#include "../arch/timerha.h"
#include "../core/resource.h"

/*!\brief Base class for timed function block like E_CYCLE or E_DELAY providing this interface
 */
class CTimedFB : public CEventSourceFB{
protected:
  static const SFBInterfaceSpec scmFBInterfaceSpec;
  static const CStringDictionary::TStringId scmEINameIds[];
  static const CStringDictionary::TStringId scmEventInputTypeIds[];
  static const CStringDictionary::TStringId scmEONameIds[];
  static const CStringDictionary::TStringId scmEventOutputTypeIds[];
  static const CStringDictionary::TStringId scmDINameIds[];
  static const CStringDictionary::TStringId scmDIDataTypeNameIds[];

  static const TEventID csmEventSTARTID = 0;
  static const TEventID csmEventSTOPID = 1;

  static const TEventID csmEOID = 0;


  bool mActive; //!> flag to indicate that the timed fb is currently active

  CTimedFB(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

  /*!\brief execute the input events of timed FBs as far it is possible
   *
   * Derived Timed FBs only normally need only the start event as this is different for each timed FB type (e.g. periodic vs. onetimeshot)
   */
  void executeEvent(TEventID paEIID, CEventChainExecutionThread * const paECET) override;

  void readInputData(TEventID paEI) override;
  void writeOutputData(TEventID paEO) override;

public:
  CIEC_TIME var_DT;
  CDataConnection *conn_DT;
  CEventConnection conn_EO;

  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;

  EMGMResponse changeExecutionState(EMGMCommandType paCommand) override;
};

#endif /*TIMEDFB_H_*/
