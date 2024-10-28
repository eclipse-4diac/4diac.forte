#/*******************************************************************************
# Copyright (c) 2016, 2024 fortiss GmbH, Jose Cabral
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#   Jose Cabral - initial API and implementation and/or initial documentation
#   Christoph Binder - add possibility to configure simulated time
# *******************************************************************************/

SET(SOURCE_GROUP ${SOURCE_GROUP}\\vxworks)

forte_add_architecture(VxWorks)

if("${FORTE_ARCHITECTURE}" STREQUAL "VxWorks")
  message(STATUS "VXWORKS: Set an environment variable WIND_BASE to any value")
  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

  forte_add_timerhandler(CPCTimerHandler ../posix/pctimeha)
  forte_add_sourcefile_hcpp(../posix/pctimeha)

  forte_add_sourcefile_cpp(forte_architecture_time.cpp)

  forte_add_sourcefile_cpp(../common/forte_specific_architecture.cpp)
  forte_add_to_executable_cpp(../main)

  forte_add_sourcefile_hcpp(forte_thread forte_sync forte_sem)
  forte_add_sourcefile_cpp(../genforte_printer.cpp)
  forte_add_sourcefile_cpp(../genforte_fileio.cpp)
  forte_add_sourcefile_h(../forte_architecture_time.h)

  forte_add_sourcefile_hcpp(../utils/timespec_utils)
  forte_add_sourcefile_cpp(../genforte_realFunctions.cpp)

  SET(FORTE_VXWORKS_FIND_DIR_AUTOMATICALLY ON CACHE BOOL "Selects the rest of needed directories from the CMAKE_FIND_ROOT_PATH")
  SET(FORTE_VXWORKS_VSB_CONFIG_FILE "" CACHE STRING "VSB Configuration file")
  SET(FORTE_VXWORKS_MUNCH_TCL_FILE "" CACHE STRING "Munch tcl file")

  if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    SET(FORTE_VXWORKS_TCL_SHELL "tclsh.exe" CACHE STRING "The tclsh shell which executes on the FORTE_VXWORKS_MUNCH_TCL_FILE. You might need to set the full path here to the executable")
  else(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    SET(FORTE_VXWORKS_TCL_SHELL "tclsh" CACHE STRING "The tclsh shell which executes on the FORTE_VXWORKS_MUNCH_TCL_FILE. You might need to set the full path here to the executable")
  endif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")

  SET(FORTE_VXWORKS_INCLUDE "" CACHE STRING "Include directories")  
  set(FORTE_VXWORKS_TAGS "" CACHE STRING "Tags file")    

  set(FORTE_VXWORKS_ARCHITECTURE "pentium" CACHE STRING "Architecture of the hardware")
  set(FORTE_VXWORKS_CPU "ATOM" CACHE STRING "CPU of the hardware")
  set(FORTE_VXWORKS_TOOL_FAMILY "gnu" CACHE STRING "tool family used to compile")
  set(FORTE_VXWORKS_TOOL "gnu" CACHE STRING "tool used to compile")

  string(TOLOWER ${FORTE_VXWORKS_CPU} FORTE_VXWORKS_CPU_low)

  if (FORTE_VXWORKS_FIND_DIR_AUTOMATICALLY)
    set(FORTE_VXWORKS_VSB_CONFIG_FILE "${CMAKE_FIND_ROOT_PATH}/target/lib/h/config/vsbConfig.h" CACHE STRING "VSB Configuration file" FORCE)
    set(FORTE_VXWORKS_MUNCH_TCL_FILE "${CMAKE_FIND_ROOT_PATH}/host/resource/hutils/tcl/munch.tcl" CACHE STRING "Munch tcl utility" FORCE)
    set(FORTE_VXWORKS_INCLUDE "${CMAKE_FIND_ROOT_PATH}/target/h;${CMAKE_FIND_ROOT_PATH}/target/h/wrn/coreip" CACHE STRING "Include directories separated by ;" FORCE)
    set(FORTE_VXWORKS_TAGS "${CMAKE_FIND_ROOT_PATH}/target/lib/tags/${FORTE_VXWORKS_ARCHITECTURE}/${FORTE_VXWORKS_CPU}/common/dkm.tags" CACHE STRING "Tags file" FORCE)  
    get_filename_component(COMPILER_FOLDER ${CMAKE_CXX_COMPILER} DIRECTORY)
    set(FORTE_VXWORKS_CMAKE_NM ${COMPILER_FOLDER}/nm${FORTE_VXWORKS_ARCHITECTURE})
  endif(FORTE_VXWORKS_FIND_DIR_AUTOMATICALLY)

  foreach(ARG ${FORTE_VXWORKS_INCLUDE}) 
     forte_add_include_system_directories(${ARG})
  endforeach()

  #for DKM
  forte_add_definition(-DVXWORKS -march=${FORTE_VXWORKS_CPU_low} -mmovbe -nostdlib -fno-builtin -fno-defer-pop 
  -fno-implicit-fp -ansi -fno-zero-initialized-in-bss -D_WRS_KERNEL -Wall -MD -MP -DCPU=_VX_${FORTE_VXWORKS_CPU} -D_VX_CPU=_VX_${FORTE_VXWORKS_CPU}
  -DTOOL_FAMILY=${FORTE_VXWORKS_TOOL_FAMILY} -DTOOL=${FORTE_VXWORKS_TOOL} -DIP_PORT_VXWORKS=69 -D_VSB_CONFIG_FILE=\"${FORTE_VXWORKS_VSB_CONFIG_FILE}\")

  forte_add_post_build_command(COMMAND ${FORTE_VXWORKS_CMAKE_NM} forte.vxe > nmFile.txt
                               COMMAND ${FORTE_VXWORKS_TCL_SHELL} ${FORTE_VXWORKS_MUNCH_TCL_FILE} -c ${FORTE_VXWORKS_ARCHITECTURE} -tags ${FORTE_VXWORKS_TAGS} < nmFile.txt 1> ctdt.c 
                               COMMAND ${CMAKE_C_COMPILER} -march=${FORTE_VXWORKS_CPU_low} -mmovbe -nostdlib -fno-builtin -fno-defer-pop -fno-implicit-fp -fdollars-in-identifiers -Wall 
                                    -DCPU=_VX_${FORTE_VXWORKS_CPU} -D_VX_CPU=_VX_${FORTE_VXWORKS_CPU} -DTOOL_FAMILY=${FORTE_VXWORKS_TOOL_FAMILY} -DTOOL=${FORTE_VXWORKS_TOOL} -D_WRS_KERNEL 
                                    -DIP_PORT_VXWORKS=69 -D_VSB_CONFIG_FILE=\"${FORTE_VXWORKS_VSB_CONFIG_FILE}\" -o ctdt.o ctdt.c 
                               COMMAND ${CMAKE_C_COMPILER} -r -nostdlib -Wl,-X -T ${CMAKE_FIND_ROOT_PATH}/target/h/tool/${FORTE_VXWORKS_TOOL}/ldscripts/link.OUT -o forte.out ctdt.o forte.vxe)

  if(FORTE_COM_ETH)
   forte_add_handler(CFDSelectHandler sockhand)
   forte_add_sourcefile_hcpp( ../fdselecthand ../bsdsocketinterf)
   forte_add_sourcefile_h(../gensockhand.h)
   forte_add_sourcefile_h(sockhand.h)
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

  forte_add_custom_configuration("#define PRIuFAST64 \"I64u\"")

  forte_add_custom_configuration("typedef unsigned long long uint_fast64_t\;")

endif()
