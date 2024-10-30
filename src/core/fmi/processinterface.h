/*******************************************************************************
 * Copyright (c) 2016 -2019 fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Jose Cabral - initial API and implementation and/or initial documentation
 *******************************************************************************/
#ifndef _PROCESSINTERFACE_H_
#define _PROCESSINTERFACE_H_

#include <../stdfblib/io/processinterfacebase.h>
#include "fmuValueContainer.h"
#include <vector>
#include <string>
#include <fstream>

class CFMUProcessInterface : public CProcessInterfaceBase{
  public:
    CFMUProcessInterface(forte::core::CFBContainer &paContainer, const SFBInterfaceSpec& paInterfaceSpec, const CStringDictionary::TStringId paInstanceNameId);
    CFMUProcessInterface(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    void setValueContainer(fmuValueContainer* paValueContainer);

    ~CFMUProcessInterface() override;

    void executeEvent(TEventID, CEventChainExecutionThread *const) override {};

  protected:
    bool initialise(bool paIsInput, CEventChainExecutionThread *const paECET);
    bool deinitialise();
    bool writePin();
    bool readPin();
    bool readWord();
    bool writeWord();

    bool readDWord() {
      return false; //not implemented
    }
    bool writeDWord() {
      return false; //not implemented
    }

  private:
    static const char * const scmOK;
    static const char * const scmNOTINITIALIZED;
    static const char * const scmINTERNALERROR;

    bool mInitialized;

    fmuValueContainer* mValue;
};

//tell the IX and QX FB that this is the process interface to be used
typedef CFMUProcessInterface CProcessInterface;

#endif /* _PROCESSINTERFACE_H_ */
