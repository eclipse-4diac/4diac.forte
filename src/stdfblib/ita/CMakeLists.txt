#*******************************************************************************
# Copyright (c) 2010, 2024 ACIN, Johannes Kepler University Linz
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#    Alois Zoitl
# *    - initial API and implementation and/or initial documentation
#    Markus Meingast
# *    - Add OPCUA_DEV and OPCUA_MGR to build configuration
# *******************************************************************************/
#############################################################################
# Ita FB
#############################################################################
SET(SOURCE_GROUP ${SOURCE_GROUP}\\ita)
forte_add_sourcefile_hcpp(DEV_MGR EMB_RES RMT_DEV RMT_RES CommandParser)

forte_add_device(RMT_DEV)

if (FORTE_COM_OPC_UA)
  forte_add_sourcefile_hcpp(Config_EMB_RES)
  
  forte_add_device(OPCUA_DEV)
  if("${FORTE_DEVICE}" STREQUAL "OPCUA_DEV")
    forte_add_sourcefile_hcpp(OPCUA_DEV OPCUA_MGR)
  endif()
endif ()

if(FORTE_FAKE_TIME)
  forte_add_device(FakeTimeDev)
  if("${FORTE_DEVICE}" STREQUAL "FakeTimeDev")
    forte_add_sourcefile_hcpp(FakeTimeDev)
  endif()
endif()

forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(FORTE_SUPPORT_BOOT_FILE)
  forte_add_sourcefile_hcpp(ForteBootFileLoader)
endif(FORTE_SUPPORT_BOOT_FILE)
