#*******************************************************************************
# Copyright (c) 2017 fortiss GmbH
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#    Johannes Messmer
# *   - initial API and implementation and/or initial documentation
# *******************************************************************************/

#############################################################################
# IO
#############################################################################

set(FORTE_IO OFF CACHE BOOL "Enable IO Modules")

if(NOT FORTE_IO)
  return()
endif(NOT FORTE_IO)

SET(SOURCE_GROUP ${SOURCE_GROUP}\\io)

forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(configFB)
add_subdirectory(device)
add_subdirectory(mapper)

forte_add_sourcefile_hcpp(processinterface)
forte_set_process_interface("Modular IO" IE IX QE_fbt QX IB QB IW QW ID QD IL QL)
