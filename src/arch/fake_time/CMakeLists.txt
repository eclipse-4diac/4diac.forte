#*******************************************************************************
# Copyright (c) 2022 Primetals Technologies Austria GmbH
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
#
# Contributors:
#    Christoph Binder - initial implementation
#******************************************************************************

if(FORTE_FAKE_TIME)

  forte_add_definition("-DFORTE_FAKE_TIME")

  forte_add_timerhandler(CFakeTimerHandler faketimerha "fakeTimer")
  forte_add_sourcefile_hcpp(faketimerha)

  forte_add_sourcefile_cpp(forte_architecture_time.cpp)

  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})


endif(FORTE_FAKE_TIME)
