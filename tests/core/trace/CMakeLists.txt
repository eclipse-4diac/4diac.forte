#*******************************************************************************
# Copyright (c) 2024
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#    Jose Cabral  - initial API and implementation and/or initial documentation
# *******************************************************************************/


# an extra CMake variable is added since test tracing requires extra libraries which
# need to be compiled and might be too cumbersome
SET(FORTE_TRACE_CTF_TEST OFF CACHE BOOL "Include CTF trace tests")
mark_as_advanced(FORTE_TRACE_CTF_TEST)
if(FORTE_TRACE_CTF_TEST)

  SET(SOURCE_GROUP ${SOURCE_GROUP}\\trace)

  forte_test_add_sourcefile_cpp(ctfTracerTest.cpp)
  forte_test_add_sourcefile_cpp(TraceReaderSink.cpp)
  forte_test_add_sourcefile_cpp(bt2MessageFactory.cpp)


  forte_test_add_link_library(babeltrace2)

  SET(CTF_OUTPUT_DIR ${CMAKE_BINARY_DIR}/ctfOutput)
  SET(METADATA_FILE ${CMAKE_BINARY_DIR}/src/core/trace/metadata)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_BINARY_DIR}/config.h)
endif(FORTE_TRACE_CTF_TEST)
