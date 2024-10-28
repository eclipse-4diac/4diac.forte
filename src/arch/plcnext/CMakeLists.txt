#*******************************************************************************
# Copyright (c) 2018, 2024 Johannes Kepler University, Jose Cabral  
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

SET(SOURCE_GROUP ${SOURCE_GROUP}\\posix)

forte_add_architecture(PLCnext)

if("${FORTE_ARCHITECTURE}" STREQUAL "PLCnext")

  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

  forte_add_timerhandler(CPCTimerHandler ../posix/pctimeha)
  forte_add_sourcefile_cpp(../posix/forte_architecture_time.cpp ../forte_standard_time.cpp ../posix/pctimeha.cpp)

  forte_add_sourcefile_cpp(../common/forte_specific_architecture.cpp)
  forte_add_sourcefile_hcpp(../posix/forte_thread ../posix/forte_sync ../posix/forte_sem)
  forte_add_sourcefile_cpp(../genforte_printer.cpp)
  forte_add_sourcefile_cpp(../genforte_fileio.cpp)
  forte_add_sourcefile_h(../forte_architecture_time.h)
  forte_add_sourcefile_hcpp(../utils/timespec_utils)
  forte_add_sourcefile_cpp(../genforte_realFunctions.cpp)

  forte_add_sourcefile_hcpp(ForteComponent ForteComponentProgramProvider ForteIOHandler ForteLibrary)

  if(FORTE_COM_ETH)
   forte_add_handler(CFDSelectHandler sockhand)
   forte_add_sourcefile_hcpp( ../fdselecthand ../bsdsocketinterf)
   forte_add_sourcefile_h(../gensockhand.h)
   forte_add_sourcefile_h(sockhand.h)
  endif(FORTE_COM_ETH)

  forte_add_definition("-W -Wall -Wextra -Woverloaded-virtual -Wconversion -DFORTE_LITTLE_ENDIAN")

  forte_add_definition("-std=c++11 -fmessage-length=0 -fPIC -Wno-unknown-pragmas -Wno-reorder -Wno-strict-aliasing")
  forte_add_definition("-fno-gnu-unique")

  #TODO find a way to make this instalation dir independent
  forte_add_definition("-I/opt/pxc/2.2.1/sysroots/cortexa9t2hf-neon-pxc-linux-gnueabi/usr/include/plcnext")

  forte_add_link_flags("-fno-gnu-unique")

  set(FORTE_BUILD_SHARED_LIBRARY ON CACHE BOOL "Build FORTE as static library" FORCE)
  set(FORTE_BUILD_EXECUTABLE OFF CACHE BOOL "Build FORTE as an executable" FORCE)

  #TODO add library builder path as config option  
  forte_add_post_build_command(COMMAND /home/az/prog/phoenix/EngineeringLibraryBuilder.exe /out ../ForteLibrary.pcwlx /file None:libforte-shared.so: /file MetaLibrary:${CMAKE_CURRENT_SOURCE_DIR}/Config/ForteLibrary.libmeta: /file MetaComponent:${CMAKE_CURRENT_SOURCE_DIR}/Config/ForteComponent/ForteComponent.compmeta:ForteComponent /file MetaProgram:${CMAKE_CURRENT_SOURCE_DIR}/Config/ForteComponent/ForteIOHandler/ForteIOHandler.progmeta:ForteComponent/ForteIOHandler /folder Logical\ Elements,FolderType=Root /folder Logical\ Elements/ForteComponent,FolderType=MetaComponentFolder /folder Logical\ Elements/ForteComponent/ForteIOHandler,FolderType=MetaProgramFolder > libbuild.txt)

endif()
