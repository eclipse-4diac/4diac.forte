/*******************************************************************************
 * Copyright (c) 2024 OFFIS e.V.
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Malte Grave - initial implementation
 ********************************************************************************/

#ifndef _DDSHANDLER_H_
#define _DDSHANDLER_H_

#include <extevhan.h>

#include <fastdds/dds/subscriber/DataReader.hpp>

#include "ddslayer.h"

using namespace forte::com_infra;

namespace forte {
namespace com_infra {
class CDDSHandler : public CExternalEventHandler {
  DECLARE_HANDLER(CDDSHandler)

public: // methods overriden from the external event handler
  void enableHandler() override {}
  void disableHandler() override {}
  void setPriority(int paPriority) override {}
  int getPriority() const override { return 0; }

public: // callback methods for data reader listeners
  void onDataAvailable(DataReader *pa_pReader);

public: // custom methods for this handler
  void registerLayer(const GUID_t paReaderGUID, CDDSComLayer *pa_pComLayer);
  void unregisterLayer(const GUID_t paReaderGUID);
  CDDSComLayer *getReaderLayer(const GUID_t paReaderGUID);

private:
  std::map<GUID_t, CDDSComLayer *> mReaderLayer;
};
} // namespace com_infra
} // namespace forte

#endif