#*******************************************************************************
# Copyright (c) 2018 - 2024 fortiss GmbH, Jose Cabral
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
#
# Contributors:
#    Jose Cabral - initial API and implementation and/or initial documentation
#   Christoph Binder - add possibility to configure simulated time
# *******************************************************************************/

SET(SOURCE_GROUP ${SOURCE_GROUP}\\nios2)

forte_add_architecture("Nios2")

if("${FORTE_ARCHITECTURE}" STREQUAL "Nios2")

  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)
  
  SET(FORTE_ECOS_FOLDER "" CACHE STRING "")
  #The usage of system directories removes the warnings but also wraps the headers with extern C, 
  #a problem for the semaphore that includes C++ headers and fails at templates
  forte_add_include_directories(${FORTE_ECOS_FOLDER}/include) 
  forte_add_link_directories(${FORTE_ECOS_FOLDER}/lib)

  forte_add_sourcefile_hcpp(../forte_thread ../forte_sync ../forte_sem ../forte_instance ../ecostiha)

  forte_add_timerhandler(CECOSTimerHandler ../ecostiha)
  forte_add_sourcefile_cpp(../../posix/forte_architecture_time.cpp ../../forte_standard_time.cpp)

  forte_add_sourcefile_cpp(../ecoscppinit.cpp ../../genforte_printer.cpp ../../common/forte_specific_architecture.cpp)
  forte_add_sourcefile_h(../../forte_architecture_time.h)
  forte_add_sourcefile_cpp(../../genforte_realFunctions.cpp)

  if(FORTE_COM_ETH)
   forte_add_handler(CFDSelectHandler ../sockhand)
   forte_add_sourcefile_hcpp( ../../fdselecthand ../../bsdsocketinterf)
   forte_add_sourcefile_h(../sockhand.h)
  endif(FORTE_COM_ETH)

  forte_add_definition("-W -Wall -Wextra -D_KERNEL -D__ECOS -DFORTE_LITTLE_ENDIAN")
  forte_add_definition("-Wa,-relax-all -ffunction-sections -fdata-sections -fno-threadsafe-statics -fno-rtti -fno-exceptions")

endif()