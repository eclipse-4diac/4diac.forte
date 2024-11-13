/*******************************************************************************
 * Copyright (c) 2018, 2024 fortiss GmbH
 *                          Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl  - initial API and implementation and/or initial documentation
 *   Martin Jobst - add smart pointer for internal FBs
 *******************************************************************************/
#ifndef TESTS_CORE_FBTESTS_FBTESTERGLOBALFIXTURE_H_
#define TESTS_CORE_FBTESTS_FBTESTERGLOBALFIXTURE_H_

#include "device.h"
#include "EMB_RES.h"

#include <memory>

class CTesterDevice : public CDevice {
  public:
    CTesterDevice(const CStringDictionary::TStringId paInstanceNameId = CStringDictionary::scmInvalidStringId);

    void awaitShutdown() override {
      // nothing to be done to join
    }

    CIEC_ANY *getDI(size_t) override {
      return nullptr;
    }

    CDataConnection **getDIConUnchecked(TPortId) override {
      return nullptr;
    }

    CResource &getTestResource() {
      return *mResource;
    }

  private:
    forte::core::CInternalFB<EMB_RES> mResource;

    constexpr static SFBInterfaceSpec scTestDevSpec = {
    0, nullptr, nullptr, nullptr, nullptr,
    0, nullptr, nullptr, nullptr, nullptr,
    0, nullptr, nullptr,
    0, nullptr, nullptr,
    0, nullptr,
    0, nullptr
  };
};


/**Global fixture for providing the resource and device needed for fb testing
 *
 */
class CFBTestDataGlobalFixture{

  public:
    CFBTestDataGlobalFixture();
    ~CFBTestDataGlobalFixture();

    static CResource &getResource(){
      return smTestDev->getTestResource();
    }

  private:
    static std::unique_ptr<CTesterDevice> smTestDev;
};



#endif
