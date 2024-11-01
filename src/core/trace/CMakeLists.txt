#############################################################################
# Copyright (c) 2022 Martin Erich Jobst
#
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
#
# Contributors:
#    Martin Jobst
#      - initial API and implementation and/or initial documentation
#############################################################################

find_package(barectf REQUIRED)

add_custom_command(
    OUTPUT barectf.h barectf.c barectf-bitfield.h metadata
    COMMAND barectf ${CMAKE_CURRENT_SOURCE_DIR}/config.yaml
    MAIN_DEPENDENCY config.yaml
    DEPENDS barectf
    COMMENT "Generating tracer for Common Trace Format (CTF) with barectf"
)

add_library(forte_trace STATIC
        ${CMAKE_CURRENT_BINARY_DIR}/barectf.h
        ${CMAKE_CURRENT_BINARY_DIR}/barectf.c
        ${CMAKE_CURRENT_BINARY_DIR}/barectf-bitfield.h
)
target_include_directories(forte_trace
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

forte_add_link_library(forte_trace)
forte_add_include_directories(${CMAKE_CURRENT_BINARY_DIR})
forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

forte_add_sourcefile_hcpp(barectf_platform_forte)

if(FORTE_TRACE_CTF_TEST)
  forte_add_sourcefile_hcpp(EventMessage)
  forte_add_sourcefile_hcpp(internalTracer)
  forte_add_sourcefile_hcpp(flexibleTracer)

  set(FORTE_TRACER_INCLUDE flexibleTracer.h)
  set(FORTE_TRACER CFlexibleTracer)

else(FORTE_TRACE_CTF_TEST)
  set(FORTE_TRACER_INCLUDE barectf_platform_forte.h)
  set(FORTE_TRACER BarectfPlatformFORTE)
endif(FORTE_TRACE_CTF_TEST)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tracerConfig.h.in ${CMAKE_BINARY_DIR}/tracerConfig.h)
