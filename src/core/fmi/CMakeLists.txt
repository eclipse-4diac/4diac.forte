#*******************************************************************************
# Copyright (c) 2016,2017 fortiss GmbH
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#    Jose Cabral
# *    - initial API and implementation and/or initial documentation
# *******************************************************************************/
#############################################################################
# core/fmi
#############################################################################

set(FORTE_ENABLE_FMU OFF CACHE BOOL "Enable FORTE FMU Export. It generates a shared library")

if(FORTE_ENABLE_FMU)

  set(FORTE_BUILD_SHARED_LIBRARY ON CACHE BOOL "" FORCE)
  set(FORTE_BUILD_STATIC_LIBRARY OFF CACHE BOOL "" FORCE)
  set(FORTE_BUILD_EXECUTABLE OFF CACHE BOOL "" FORCE)
  
  forte_add_definition("-DFORTE_FMU") 
  IF(NOT FORTE_LOG_LEVEL STREQUAL "NOLOG")
    forte_add_definition("-DFMU_DEBUG") 
    message("Adding logging FMU")
  ENDIF()

  set(FORTE_FMU_INCLUDE "" CACHE STRING "Folder to include in the compilation. Specify here the location of the fmi headers")

  forte_add_include_system_directories(${FORTE_FMU_INCLUDE})
  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR}) #for <processinterface.h>

  forte_add_subdirectory(comm)

  forte_add_timerhandler(fmiTimerHandler fmiTimerHandler "fmi")

  forte_add_ecet(CFMUEventChainExecutionThread fmuEcet "fmi")

  forte_add_sourcefile_cpp(fmiInterface.cpp)
  forte_add_sourcefile_hcpp(fmuValueContainer fmuInstance processinterface fmuEcet fmiTimerHandler)
  forte_set_process_interface("FORTE FMU" IX QX IW QW)
  forte_add_sourcefile_hcpp(../../arch/utils/timespec_utils)
   
endif(FORTE_ENABLE_FMU)

