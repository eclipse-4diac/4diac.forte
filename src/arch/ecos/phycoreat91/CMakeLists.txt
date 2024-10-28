#*******************************************************************************
# Copyright (c) 2010 - 2024 ACIN, fortiss GmbH, Jose Cabral
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#    Alois Zoitl - initial API and implementation and/or initial documentation
#   Christoph Binder - add possibility to configure simulated time
# *******************************************************************************/

SET(SOURCE_GROUP ${SOURCE_GROUP}\\phycoreat91)

forte_add_architecture("Phycore AT91")

if("${FORTE_ARCHITECTURE}" STREQUAL "Phycore AT91")

  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
  
  forte_add_sourcefile_hcpp(../forte_thread ../forte_sync ../forte_sem ../ecostiha)

  forte_add_timerhandler(CECOSTimerHandler ../ecostiha)

  forte_add_sourcefile_cpp(../ecoscppinit.cpp ../../posix/forte_architecture_time.cpp ../../forte_standard_time.cpp ../../common/forte_specific_architecture.cpp)

  forte_add_sourcefile_cpp(../../genforte_printer.cpp)
  forte_add_sourcefile_h(../../forte_architecture_time.h)
  forte_add_to_executable_cpp(main)
  forte_add_sourcefile_cpp(../../genforte_realFunctions.cpp)

  if(FORTE_COM_ETH)
   forte_add_handler(CFDSelectHandler ../sockhand)
   forte_add_sourcefile_hcpp( ../../fdselecthand ../../bsdsocketinterf)
   forte_add_sourcefile_h(../sockhand.h)
  endif(FORTE_COM_ETH)

  forte_add_definition("-Wpointer-arith -Wundef -Woverloaded-virtual -Wno-write-strings")
  forte_add_definition("-W -Wall -Wextra -D_KERNEL -D__ECOS -DFORTE_LITTLE_ENDIAN")
  forte_add_definition("-mcpu=arm7tdmi -msoft-float -mno-thumb-interwork -O2")
  forte_add_definition("-ffunction-sections -fdata-sections -fno-threadsafe-statics -fno-rtti -fno-exceptions")

  forte_add_link_flags("-mcpu=arm7tdmi -msoft-float -W,--gc-sections -nostartfiles -nostdlib -fno-threadsafe-statics -mno-thumb-interwork -Wl,-static -Wl,-M -Wl,-Map -Wl,forte.map -Wl,-cref")

endif()