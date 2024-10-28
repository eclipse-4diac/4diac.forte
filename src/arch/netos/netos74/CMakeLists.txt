#*******************************************************************************
# Copyright (c) 2011, 2014, 2024 ACIN, fortiss GmbH, Jose Cabral
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#    Alois Zoitl, Patrick Smejkal - initial API and implementation and/or initial documentation
#   Christoph Binder - add possibility to configure simulated time
# *******************************************************************************/

SET(SOURCE_GROUP ${SOURCE_GROUP}\\netos74)

forte_add_architecture("NetOS 7.4")

if("${FORTE_ARCHITECTURE}" STREQUAL "NetOs 7.4")


#######################################################################################
# Buffer root path and convert it to Cygwin format
#######################################################################################
  set(NETOS_ROOT_PATH_WIN ${CMAKE_FIND_ROOT_PATH})
  execute_process(COMMAND cygpath ${CMAKE_FIND_ROOT_PATH} OUTPUT_VARIABLE NETOS_ROOT_PATH_CYG)
  string(REPLACE "\n" "" NETOS_ROOT_PATH_CYG ${NETOS_ROOT_PATH_CYG})

#######################################################################################
# Look for available Board support packages
#######################################################################################
  set(FORTE_NETOS74_BSP "connectme" CACHE STRING "Select NetOS Board Support Package")
  execute_process(COMMAND ls ${NETOS_ROOT_PATH_CYG}/lib/arm7/32b/gnu/bsp OUTPUT_VARIABLE LS_BSP)
  execute_process(COMMAND echo -n ${LS_BSP} OUTPUT_VARIABLE ECHO_BSP)
  string(LENGTH "${ECHO_BSP}" LEN_BSP)
  if(LEN_BSP EQUAL 0)
    message(FATAL_ERROR "No Board Support Package found! Have you installed Digi NET+OS toolchain and set CMAKE_FIND_ROOT_PATH to the root directory of it (default C:\\netos74)?")
  endif(LEN_BSP EQUAL 0)
  string(REPLACE " " ";" AVAILABLE_BSP ${ECHO_BSP})
  set_property(CACHE FORTE_NETOS74_BSP PROPERTY STRINGS ${AVAILABLE_BSP})

#######################################################################################
# Add commands for creating target image
#######################################################################################
  forte_add_post_build_command(COMMAND arm-elf-objcopy.exe ARGS -Obinary src/forte src/forte.uncompressed
                               COMMAND ${NETOS_ROOT_PATH_WIN}/bin/compress.exe ARGS src/forte.uncompressed src/forte.compressed
                               COMMAND ${NETOS_ROOT_PATH_WIN}/bin/boothdr.exe ARGS ${NETOS_ROOT_PATH_WIN}/src/bsp/platforms/${FORTE_NETOS74_BSP}/bootldr.dat src/forte.compressed src/forte.bin connectme_rfid
                               COMMAND cp src/forte.bin image.bin
                               WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                               COMMENT "Create target image (image.bin)...")

#######################################################################################
# COMPILER FLAGS - INCLUDE DIRS
#######################################################################################
  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

  forte_add_timerhandler(CTXTimerHandler ../txtimeha)
  forte_add_sourcefile_cpp(../forte_architecture_time.cpp ../txtimeha.cpp)

  forte_add_sourcefile_cpp(../../common/forte_specific_architecture.cpp)
  forte_add_sourcefile_hcpp(../forte_thread ../forte_sync ../forte_sem)
  forte_add_sourcefile_cpp(appconf_api.c ../root.cpp ../../genforte_printer.cpp)
  forte_add_sourcefile_h(../../forte_architecture_time.h)
  forte_add_sourcefile_cpp(../../genforte_realFunctions.cpp)

  if(FORTE_COM_ETH)
   forte_add_handler(CFDSelectHandler ../sockhand)
   forte_add_sourcefile_hcpp( ../../fdselecthand ../../bsdsocketinterf)
   forte_add_sourcefile_h(../gensockhand.h)
   forte_add_sourcefile_h(../sockhand.h)
  endif(FORTE_COM_ETH)

  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

  # Include-Dirs for NetOS
  forte_add_include_directories(${NETOS_ROOT_PATH_CYG}/h)
  forte_add_include_directories(${NETOS_ROOT_PATH_CYG}/h/shared)
  forte_add_include_directories(${NETOS_ROOT_PATH_CYG}/h/threadx)
  forte_add_include_directories(${NETOS_ROOT_PATH_CYG}/h/tcpip)
  forte_add_include_directories(${NETOS_ROOT_PATH_CYG}/h/snmp)
  forte_add_include_directories(${NETOS_ROOT_PATH_CYG}/h/rphttpd)
  forte_add_include_directories(${NETOS_ROOT_PATH_CYG}/h/fs_intf)
  forte_add_include_directories(${NETOS_ROOT_PATH_CYG}/h/wln)
  forte_add_include_directories(${NETOS_ROOT_PATH_CYG}/h/wps)
  forte_add_include_directories(${NETOS_ROOT_PATH_CYG}/src/treck/include)
  forte_add_include_directories(${NETOS_ROOT_PATH_CYG}/src/treck/source/ossupport)
  forte_add_include_directories(${NETOS_ROOT_PATH_CYG}/src/treck/source/ossupport/netos)

  forte_add_definition(-Wpointer-arith -Wundef -Woverloaded-virtual -Wno-write-strings)
  forte_add_definition(-W -Wall -Wextra -DFORTE_BIG_ENDIAN -DIAM_ENABLED)
  forte_add_definition(-D__GNU__ -DNETOS_GNU_TOOLS -DNETOS_GNU_CLIB_REENT -DNET_OS -DNET_WORKS -D_POSIX_SOURCE)  
  #forte_add_definition(-DBOOT_LOADER)
  forte_add_definition(-DIAM_ENABLED -DNET_OS_SPECIFIC -DFUSION=0 -DTRECK=1 -DNETWORK_STACK=1)
  forte_add_definition(-mbig-endian -mcpu=arm7tdmi)
  forte_add_definition(-ffunction-sections -fdata-sections -fno-threadsafe-statics -fno-rtti -fno-exceptions)


#######################################################################################
# LINKER FLAGS
#######################################################################################
  # Linker-Flags for NetOS
  forte_add_link_directories(${NETOS_ROOT_PATH_CYG}/lib/arm7/32b/gnu)
  forte_add_link_directories(${NETOS_ROOT_PATH_CYG}/lib/32b/gnu)
  forte_add_link_directories(${NETOS_ROOT_PATH_CYG}/lib/arm7/32b/gnu/bsp/${FORTE_NETOS74_BSP})

  forte_add_link_library(-Wl,--start-group)

  # Look for reset.o
  if(EXISTS ${NETOS_ROOT_PATH_WIN}/lib/arm7/32b/gnu/bsp/${FORTE_NETOS74_BSP}/reset.o)
    forte_add_link_library(${NETOS_ROOT_PATH_CYG}/lib/arm7/32b/gnu/bsp/${FORTE_NETOS74_BSP}/reset.o)
  else(EXISTS ${NETOS_ROOT_PATH_WIN}/lib/arm7/32b/gnu/bsp/${FORTE_NETOS74_BSP}/reset.o)
    message(WARNING "reset.o wasn't found where it is expected (${NETOS_ROOT_PATH_WIN}/lib/arm7/32b/gnu/bsp/${FORTE_NETOS74_BSP}/reset.o). Your program maybe won't work without this object. Build BSP first! For further information please refer to the Digi support.")
  endif(EXISTS ${NETOS_ROOT_PATH_WIN}/lib/arm7/32b/gnu/bsp/${FORTE_NETOS74_BSP}/reset.o)

  forte_add_link_library(${NETOS_ROOT_PATH_CYG}/lib/32b/gnu/crt0.o)
  forte_add_link_library(${NETOS_ROOT_PATH_CYG}/lib/32b/gnu/crti.o)
  forte_add_link_library(${NETOS_ROOT_PATH_CYG}/lib/32b/gnu/crtbegin.o)
  forte_add_link_library(${NETOS_ROOT_PATH_CYG}/lib/32b/gnu/crtend.o)
  forte_add_link_library(${NETOS_ROOT_PATH_CYG}/lib/32b/gnu/crtn.o)
  forte_add_link_library(-lbsp -lftpsvr -lflash -lfilesys -lposix -ltx -ldnsclnt -laddp -ltcpip -ltelnsvr)
  forte_add_link_library(-lc -lgcc -lm -lstdc++)
  forte_add_link_library(-Wl,--end-group)

  # Look for image.ld
  if(EXISTS ${NETOS_ROOT_PATH_WIN}/src/bsp/platforms/${FORTE_NETOS74_BSP}/image.ld)
    forte_add_link_flags("-mbig-endian -nostartfiles -nostdlib -mcpu=arm7tdmi -T ${NETOS_ROOT_PATH_CYG}/src/bsp/platforms/${FORTE_NETOS74_BSP}/image.ld")
  else(EXISTS ${NETOS_ROOT_PATH_WIN}/src/bsp/platforms/${FORTE_NETOS74_BSP}/image.ld)
    message(WARNING "image.ld wasn't found where it is expected (${NETOS_ROOT_PATH_WIN}/src/bsp/platforms/${FORTE_NETOS74_BSP}/image.ld). Your program maybe won't work without this object. Build BSP first! For further information please refer to the Digi support.")
    forte_add_link_flags("-mbig-endian -nostartfiles -nostdlib -mcpu=arm7tdmi -T")
  endif(EXISTS ${NETOS_ROOT_PATH_WIN}/src/bsp/platforms/${FORTE_NETOS74_BSP}/image.ld)

endif()