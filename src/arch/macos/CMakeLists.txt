#*******************************************************************************
# Copyright (c) 2016, 2024 fortiss GmbH, Jose Cabral
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
#
# Contributors:
#   Alois Zoitl - initial API and implementation and/or initial documentation
#   Christoph Binder - add possibility to configure simulated time
# *******************************************************************************/

SET(SOURCE_GROUP ${SOURCE_GROUP}\\macos)

forte_add_architecture(MacOs)

if("${FORTE_ARCHITECTURE}" STREQUAL "MacOs")

  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

  # on MacOs linked string dict is currently not working, turn it off per default
  SET(FORTE_LINKED_STRINGDICT OFF CACHE BOOL "" FORCE)

  forte_add_timerhandler(CPCTimerHandler ../posix/pctimeha)
  forte_add_sourcefile_cpp(../posix/forte_architecture_time.cpp ../forte_standard_time.cpp ../posix/pctimeha.cpp)

  forte_add_sourcefile_cpp(../common/forte_specific_architecture.cpp)
  forte_add_sourcefile_hcpp(../posix/forte_thread forte_sync forte_sem)
  forte_add_sourcefile_cpp(../genforte_printer.cpp)
  forte_add_sourcefile_cpp(../genforte_fileio.cpp)
  forte_add_sourcefile_h(../forte_architecture_time.h)
  forte_add_sourcefile_cpp(../genforte_realFunctions.cpp  ../utils/timespec_utils.cpp)

  forte_add_to_executable_cpp(../main)

  if(FORTE_COM_ETH)
   forte_add_handler(CFDSelectHandler sockhand)
   forte_add_sourcefile_hcpp( ../fdselecthand ../bsdsocketinterf)
   forte_add_sourcefile_h(../gensockhand.h)
   forte_add_sourcefile_h(../posix/sockhand.h)
  endif(FORTE_COM_ETH)

  forte_add_definition("-W -Wall -Wextra -Woverloaded-virtual -Wconversion -DFORTE_LITTLE_ENDIAN")

  set(FORTE_RTTI_AND_EXCEPTIONS FALSE CACHE BOOL "Enable RTTI and Exceptions")
  mark_as_advanced(FORTE_RTTI_AND_EXCEPTIONS)
  IF(NOT FORTE_RTTI_AND_EXCEPTIONS)
    forte_add_definition("-fno-rtti -fno-exceptions")
  ENDIF(NOT FORTE_RTTI_AND_EXCEPTIONS)

  set(FORTE_POSIX_GENERATE_MAP_FILE FALSE CACHE BOOL "Enable the generation of map files")
  mark_as_advanced(FORTE_POSIX_GENERATE_MAP_FILE)
  IF(FORTE_POSIX_GENERATE_MAP_FILE)
    forte_add_link_flags("-Wl,-M -Wl,-Map -Wl,forte.map -Wl,-cref")
  ENDIF(FORTE_POSIX_GENERATE_MAP_FILE)  

  forte_add_link_library("-lpthread")  

endif()
