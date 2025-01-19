/*******************************************************************************
 * Copyright (c) 2022, 2024 Markus Meingast, Johannes Kepler University Linz
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Markus Meingast - initial implementation
 *******************************************************************************/

#pragma once

#include "RMT_DEV.h"
#include "OPCUA_MGR.h"

class OPCUA_DEV : public RMT_DEV {
public:

  OPCUA_MGR mOPCUAMgr;

  OPCUA_DEV(const std::string &paMGRID = "opc.tcp://localhost:4840");
  virtual ~OPCUA_DEV();

  virtual int startDevice(void);
};
