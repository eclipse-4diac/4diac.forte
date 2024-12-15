#********************************************************************************
# Copyright (c) 2010 - 2015 Profactor GmbH, AIT, fortiss GmbH
#               2010-2015, 2020 TU Wien/ACIN
#               2022 Martin Erich Jobst
#               2024 Jose Cabral
#
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#    Michael Hofmann, Alois Zoitl, Gerhard Ebenhofer, Ingo Hegny, Thomas Strasser,
#    Martin Melik Merkumians
#      - initial API and implementation and/or initial documentation
#    Martin Melik Merkumians - adds compiler feature check for nullptr
#    Martin Jobst
#      - add CTF tracing support
# *******************************************************************************/

CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

PROJECT(FORTE)

if(NOT (${CMAKE_HOST_SYSTEM_NAME} STREQUAL ${CMAKE_SYSTEM_NAME}))
    MESSAGE("Cross compiling")
    SET(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS 1)
    SET(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 1)
    SET(CMAKE_CXX_RESPONSE_FILE_LINK_FLAG "@")
    SET(CMAKE_CXX_CREATE_STATIC_LIBRARY "<CMAKE_AR> rc <TARGET> <LINK_FLAGS> <OBJECTS>")
endif(NOT (${CMAKE_HOST_SYSTEM_NAME} STREQUAL ${CMAKE_SYSTEM_NAME}))

SET(FORTE_BUILDSUPPORT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/buildsupport" CACHE PATH "forte build support directory.")
mark_as_advanced(FORTE_BUILDSUPPORT_DIRECTORY)
#http://www.varsanofiev.com/inside/eclipse_and_windows.htm

#include forte cmake-functions
INCLUDE(${FORTE_BUILDSUPPORT_DIRECTORY}/forte.cmake)
INCLUDE(${FORTE_BUILDSUPPORT_DIRECTORY}/check_compiler_features.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${FORTE_BUILDSUPPORT_DIRECTORY})

set(FORTE_TEST_NEEDED_COMPILER_FEATURES ON CACHE BOOL "Check for compiler features and either apply fixes or error messages if not supported")
mark_as_advanced(FORTE_TEST_NEEDED_COMPILER_FEATURES)

if (FORTE_TEST_NEEDED_COMPILER_FEATURES)
  TEST_NEEDED_FORTE_COMPILER_FEATURES()
endif()


forte_add_definition("-DFORTE_COMPILATION") #Allow to tell external modules/middleware that forte is being compiled, so special defines can be added

#######################################################################################
# Determine how to build FORTE
#######################################################################################
set(FORTE_BUILD_EXECUTABLE ON CACHE BOOL "Build FORTE as an executable")
mark_as_advanced(FORTE_BUILD_EXECUTABLE)

set(FORTE_BUILD_STATIC_LIBRARY OFF CACHE BOOL "Build FORTE as static library")
mark_as_advanced(FORTE_BUILD_STATIC_LIBRARY)

set(FORTE_BUILD_SHARED_LIBRARY OFF CACHE BOOL "Build FORTE as shared library")
mark_as_advanced(FORTE_BUILD_SHARED_LIBRARY)

SET(FORTE_C_INTERFACE OFF CACHE BOOL "Build C interface to Forte")
mark_as_advanced(FORTE_C_INTERFACE)

if(FORTE_BUILD_EXECUTABLE)
  SET(FORTE_EXECUTABLE_NAME forte)
endif(FORTE_BUILD_EXECUTABLE)

if(FORTE_BUILD_STATIC_LIBRARY)
  if(FORTE_C_INTERFACE)
    SET(FORTE_STATIC_LIBRARY_NAME forte-c-static)
  else()
    SET(FORTE_STATIC_LIBRARY_NAME forte-static)
  endif(FORTE_C_INTERFACE)
endif(FORTE_BUILD_STATIC_LIBRARY)

if(FORTE_BUILD_SHARED_LIBRARY)
  if(FORTE_C_INTERFACE)
    SET(FORTE_SHARED_LIBRARY_NAME forte-c-shared)
  else()
    SET(FORTE_SHARED_LIBRARY_NAME forte-shared)
  endif(FORTE_C_INTERFACE)
endif(FORTE_BUILD_SHARED_LIBRARY)

#######################################################################################
# Determine the loglevel
#######################################################################################
string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_LOWERCASE)
if(BUILD_TYPE_LOWERCASE STREQUAL "debug")
    if(FORTE_LOGLEVEL MATCHES "NOLOG")
        message("Log Level is set to NOLOG and CMAKE_BUILD_TYPE is set to Debug. Are sure you don't want to log anything?")
    endif(FORTE_LOGLEVEL MATCHES "NOLOG")
    if(NOT DEFINED FORTE_LOGLEVEL)
    	message("No Log Level was specified. Setting Log Level to Debug default LOGINFO.")
        set(FORTE_LOGLEVEL "LOGINFO" CACHE STRING "Loglevel to use" FORCE)
    endif(NOT DEFINED FORTE_LOGLEVEL)
else(BUILD_TYPE_LOWERCASE STREQUAL "debug")
    if(NOT DEFINED FORTE_LOGLEVEL)
        message("No Log Level was specified. Setting Log Level to Release default LOGERROR.")
        set(FORTE_LOGLEVEL "LOGERROR" CACHE STRING "Loglevel to use" FORCE)
    endif(NOT DEFINED FORTE_LOGLEVEL)
    if(NOT (FORTE_LOGLEVEL MATCHES "NOLOG"))
        message("According to CMAKE_BUILD_TYPE you are not debugging, but still you have some logging info. Do you really want to log something?")
    endif(NOT (FORTE_LOGLEVEL MATCHES "NOLOG"))
endif(BUILD_TYPE_LOWERCASE STREQUAL "debug")

set_property(CACHE FORTE_LOGLEVEL PROPERTY STRINGS LOGDEBUG LOGERROR LOGWARNING LOGINFO NOLOG)

forte_add_definition("-D${FORTE_LOGLEVEL}")

SET(FORTE_TRACE_EVENTS OFF CACHE BOOL "FORTE will log the events received at and sent from function blocks")
mark_as_advanced(FORTE_TRACE_EVENTS)
if(FORTE_TRACE_EVENTS)
forte_add_definition("-DFORTE_TRACE_EVENTS")
endif(FORTE_TRACE_EVENTS)

set(FORTE_SUPPORT_QUERY_CMD ON CACHE BOOL "Enable support for the query management commands")
mark_as_advanced(FORTE_SUPPORT_QUERY_CMD)
if(FORTE_SUPPORT_QUERY_CMD)
  forte_add_definition("-DFORTE_SUPPORT_QUERY_CMD")
endif(FORTE_SUPPORT_QUERY_CMD)

######################################################################################
set(FORTE_SYSTEM_TESTS OFF CACHE BOOL "FORTE System Tests")
if(FORTE_SYSTEM_TESTS)
  ENABLE_TESTING()
  ADD_SUBDIRECTORY(systemtests)
endif(FORTE_SYSTEM_TESTS)

#######################################################################################
SET(FORTE_STRINGDICTFIXEDMEMORY OFF CACHE BOOL "FORTE string dict will reallocate memory if necessary when this flag is turned off")
mark_as_advanced(FORTE_STRINGDICTFIXEDMEMORY)

if(FORTE_STRINGDICTFIXEDMEMORY)
  forte_add_definition("-DFORTE_STRING_DICT_FIXED_MEMORY")
endif(FORTE_STRINGDICTFIXEDMEMORY)

set(FORTE_SUPPORT_BOOT_FILE ON CACHE BOOL "Enable FORTE boot file loading on FORTE start-up")
mark_as_advanced(FORTE_SUPPORT_BOOT_FILE)
if(FORTE_SUPPORT_BOOT_FILE)
  forte_add_definition("-DFORTE_SUPPORT_BOOT_FILE")
  SET(FORTE_BootfileLocation "forte.fboot" CACHE STRING "Path to the bootfile")
  forte_add_custom_configuration("#define FORTE_BOOT_FILE_LOCATION \"${FORTE_BootfileLocation}\"")
  forte_add_custom_configuration("extern char* gCommandLineBootFile\;")
  mark_as_advanced(FORTE_BootfileLocation)
endif(FORTE_SUPPORT_BOOT_FILE)

set(FORTE_SUPPORT_MONITORING ON CACHE BOOL "Enable FORTE monitoring functionalities")
mark_as_advanced(FORTE_SUPPORT_MONITORING)
if(FORTE_SUPPORT_MONITORING)
  forte_add_custom_configuration("#define FORTE_SUPPORT_MONITORING")
endif(FORTE_SUPPORT_MONITORING)


if (WIN32)
  if (MSVC)
    set(FORTE_ADDITIONAL_CXX_FLAGS "/MP " CACHE STRING "Additional compile flags appended to CMAKE_CXX_FLAGS.")
    mark_as_advanced(FORTE_ADDITIONAL_CXX_FLAGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FORTE_ADDITIONAL_CXX_FLAGS}")
  endif(MSVC)

  option(FORTE_WINDOWS_XP_COMPAT OFF "Enable some workarounds for Windows XP compatibility")
  if (FORTE_WINDOWS_XP_COMPAT)
    add_definitions(-DWINDOWS_XP_COMPAT=1)
    add_definitions(-D_WIN32_WINNT=0x0501)
    add_definitions(-DUA_ARCHITECTURE_WEC7)
  endif()
endif(WIN32)

if (APPLE)
  add_compile_options("-Dpthread_condattr_setclock(a,b)=(0)")
endif ()

#######################################################################################
# dynamic type loading
#######################################################################################
set(FORTE_USE_LUATYPES "None" CACHE STRING "Enable Lua FB types")
list(APPEND luas "LuaJIT" "Lua")
set_property(CACHE FORTE_USE_LUATYPES PROPERTY STRINGS None ${luas})
if(NOT ("${FORTE_USE_LUATYPES}" STREQUAL "None"))
  set(FORTE_DYNAMIC_TYPE_LOAD ON BOOL "Enable dynamic type loading")
  forte_add_definition("-DFORTE_DYNAMIC_TYPE_LOAD")
  if(NOT FORTE_SUPPORT_QUERY_CMD)
    set(FORTE_SUPPORT_QUERY_CMD ON CACHE BOOL "Enable support for the query management commands")
    forte_add_definition("-DFORTE_SUPPORT_QUERY_CMD")
  endif(NOT FORTE_SUPPORT_QUERY_CMD)
else()
  unset(FORTE_DYNAMIC_TYPE_LOAD)
  unset(LUAJIT_LIBRARY CACHE)
  unset(LUAJIT_INCLUDE_DIR CACHE)
  unset(LUAJIT_MATH_LIBRARY CACHE)
endif(NOT ("${FORTE_USE_LUATYPES}" STREQUAL "None"))

#######################################################################################
# CTF tracing
#######################################################################################
SET(FORTE_TRACE_CTF OFF CACHE BOOL "FORTE Common Trace Format (CTF) tracing")
SET(FORTE_TRACE_CTF_BUFFER_SIZE 4096 CACHE STRING "FORTE Common Trace Format (CTF) trace buffer size")
if(FORTE_TRACE_CTF)
  forte_add_custom_configuration("#define FORTE_TRACE_CTF")
  forte_add_custom_configuration("#define FORTE_TRACE_CTF_BUFFER_SIZE ${FORTE_TRACE_CTF_BUFFER_SIZE}")
endif(FORTE_TRACE_CTF)

#######################################################################################
# stacktrace
#######################################################################################
SET(FORTE_STACKTRACE OFF CACHE BOOL "Enable generation of stacktraces on error")
SET(FORTE_STACKTRACE_IMPL "boost" CACHE STRING "FORTE stacktrace implementation")
set_property(CACHE FORTE_STACKTRACE_IMPL PROPERTY STRINGS boost cxx23)
if(FORTE_STACKTRACE)
  forte_add_custom_configuration("#define FORTE_STACKTRACE")
  string(TOUPPER "${FORTE_STACKTRACE_IMPL}" FORTE_STACKTRACE_IMPL_UPPER)
  forte_add_custom_configuration("#define FORTE_STACKTRACE_${FORTE_STACKTRACE_IMPL_UPPER}")
endif(FORTE_STACKTRACE)

#######################################################################################
# Early definition of option how to generate stringlist for every source file
#######################################################################################
SET(FORTE_LINKED_STRINGDICT ON CACHE BOOL "FORTE will resolve references to the stringdict at link-stage and not compile-stage. This will reduce compiletime if the stringdict changes.")
mark_as_advanced(FORTE_LINKED_STRINGDICT)

#######################################################################################
# clang-tidy
#######################################################################################
set(FORTE_CLANG_TIDY_MODE "OFF" CACHE STRING "Run clang-tidy with the compiler.")
set_property(CACHE FORTE_CLANG_TIDY_MODE PROPERTY STRINGS "OFF" "WARNING" "FIX")
mark_as_advanced(FORTE_CLANG_TIDY_MODE)

if(NOT ("${FORTE_CLANG_TIDY_MODE}" STREQUAL "OFF"))
    find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)

    if(CLANG_TIDY_COMMAND)
        if("${FORTE_CLANG_TIDY_MODE}" STREQUAL "FIX")
            set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND};-fix-errors")
            message("Applying clang-tidy fixes via ${CLANG_TIDY_COMMAND}.")
        elseif("${FORTE_CLANG_TIDY_MODE}" STREQUAL "WARNING")
            set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
        endif()

    else(CLANG_TIDY_COMMAND)
        message(FATAL_ERROR "clang-tidy is configured but not found!")
    endif(CLANG_TIDY_COMMAND)

    if(NOT CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
        configure_file(.clang-tidy .clang-tidy COPYONLY)
    endif()
else()
    unset(CMAKE_CXX_CLANG_TIDY CACHE)
endif(NOT ("${FORTE_CLANG_TIDY_MODE}" STREQUAL "OFF"))


#######################################################################################
# Add subdirectories
#######################################################################################
set(FORTE_TESTS OFF CACHE BOOL "Build Tests")
IF(FORTE_TESTS)
    set(FORTE_TESTS_LINK_DIRS "" CACHE PATH "Test specific library directories")
    set(FORTE_TESTS_INC_DIRS "" CACHE PATH "Test specific include directories")
    if("${FORTE_ARCHITECTURE}" STREQUAL "Posix")
        set(FORTE_TEST_CODE_COVERAGE_ANALYSIS OFF CACHE BOOL "Perform code coverage analyis with GCOV and presentation with LCOV")
        mark_as_advanced(FORTE_TEST_CODE_COVERAGE_ANALYSIS)
        set(FORTE_TEST_SANITIZE OFF CACHE BOOL "Perform address sanitizer analysis")
    endif()
ENDIF(FORTE_TESTS)

set(FORTE_USE_TEST_CONFIG_IN_FORTE ON CACHE BOOL "Add the test definitions and compiler options to the base forte") #this is needed for posix and win32 options
mark_as_advanced(FORTE_USE_TEST_CONFIG_IN_FORTE)


ADD_SUBDIRECTORY(src)

#######################################################################################
# process interface
#######################################################################################
if(NOT DEFINED CACHE{FORTE_PROCESS_INTERFACE})
    message("Building forte without a process interface.")
else()
    message("Using process interface: " $CACHE{FORTE_PROCESS_INTERFACE})
endif()

#######################################################################################
# FORTE Tests
#######################################################################################
IF(FORTE_TESTS)
    enable_testing()
    ADD_SUBDIRECTORY(tests)
ENDIF(FORTE_TESTS)

# ######################################################################################
# FORTE forte_config.h
# ######################################################################################
SET(FORTE_TicksPerSecond "1000" CACHE STRING "FORTE ticks per second")
mark_as_advanced(FORTE_TicksPerSecond)

SET(FORTE_EventChainEventListSize "256" CACHE STRING "FORTE eventchain event list size")
mark_as_advanced(FORTE_EventChainEventListSize)

SET(FORTE_EventChainExternalEventListSize "16" CACHE STRING "FORTE eventchain external event list size")
mark_as_advanced(FORTE_EventChainExternalEventListSize)

SET(FORTE_CommunicationInterruptQueueSize "10" CACHE STRING "FORTE Communication interrupt queue size")
mark_as_advanced(FORTE_CommunicationInterruptQueueSize)

if(FORTE_DYNAMIC_TYPE_LOAD)
SET(FORTE_IPLayerRecvBufferSize "20000" CACHE STRING "FORTE IP layer recv buffer size")
else()
SET(FORTE_IPLayerRecvBufferSize "1500" CACHE STRING "FORTE IP layer recv buffer size")
endif(FORTE_DYNAMIC_TYPE_LOAD)
mark_as_advanced(FORTE_IPLayerRecvBufferSize)

SET(FORTE_MGM_MAX_SUPPORTED_NAME_HIERACHY "30" CACHE STRING "Max supported hierarchy that can be provided in a management commands")
mark_as_advanced(FORTE_MGM_MAX_SUPPORTED_NAME_HIERACHY)

SET(FORTE_STRINGDICTINITIALSTRINGBUFSIZE "8000" CACHE STRING "FORTE string dict's initial string buffer size")
mark_as_advanced(FORTE_STRINGDICTINITIALSTRINGBUFSIZE)

SET(FORTE_STRINGINITIALSIZE "128" CACHE STRING "FORTE string initial size")
mark_as_advanced(FORTE_STRINGINITIALSIZE)

SET(FORTE_STRINGDICTINITIALMAXNROFSTRINGS "300" CACHE STRING "FORTE string dict's initial max nr of strings")
mark_as_advanced(FORTE_STRINGDICTINITIALMAXNROFSTRINGS)

GET_PROPERTY(FORTE_CUSTOM_CONFIGURATIONS_LOCAL GLOBAL PROPERTY FORTE_CUSTOM_CONFIGURATIONS_GLOBAL)

#Create a file with the custom configurations first and read from it
file(WRITE ${CMAKE_BINARY_DIR}/forte_custom_config.h.in ${FORTE_CUSTOM_CONFIGURATIONS_LOCAL})
CONFIGURE_FILE(${CMAKE_BINARY_DIR}/forte_custom_config.h.in ${CMAKE_BINARY_DIR}/forte_custom_config.h)
file(READ ${CMAKE_BINARY_DIR}/forte_custom_config.h FORTE_CUSTOM_CONFIGURATIONS_CONFIGURED)
file(REMOVE ${CMAKE_BINARY_DIR}/forte_custom_config.h.in)
file(REMOVE ${CMAKE_BINARY_DIR}/forte_custom_config.h)
SET(FORTE_CUSTOM_CONFIGURATIONS ${FORTE_CUSTOM_CONFIGURATIONS_CONFIGURED})

forte_add_include_directories(${CMAKE_BINARY_DIR})
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/forte_config.h.in ${CMAKE_BINARY_DIR}/forte_config.new.h)
forte_replacefile_if_changed(${CMAKE_BINARY_DIR}/forte_config.new.h ${CMAKE_BINARY_DIR}/forte_config.h)
file(REMOVE ${CMAKE_BINARY_DIR}/forte_config.new.h)

#######################################################################################
# Check FORTE_ARCHITECTURE has a valid value
#######################################################################################
if("${FORTE_ARCHITECTURE}" STREQUAL "None")
  message(FATAL_ERROR "No valid architecture chosen! Please check FORTE_ARCHITECTURE.")
endif("${FORTE_ARCHITECTURE}" STREQUAL "None")


#######################################################################################
# Setup Forte-Executeable with all Functionblocks
#######################################################################################
GET_PROPERTY(SOURCE_CPP              GLOBAL PROPERTY FORTE_SOURCE_CPP)
LIST(APPEND SOURCE_FILES_TMP           ${SOURCE_CPP})
GET_PROPERTY(SOURCE_C                GLOBAL PROPERTY FORTE_SOURCE_C)
LIST(APPEND SOURCE_FILES_TMP           ${SOURCE_C})

#######################################################################################
# Setup Forte-Executeable with all Functionblocks
#######################################################################################
GET_PROPERTY(SOURCE_TEST_CPP              GLOBAL PROPERTY FORTE_TEST_SOURCE_CPP)
LIST(APPEND SOURCE_FILES_TMP           ${SOURCE_TEST_CPP})

# Resolve to absolute path, Remove duplicate files, 
FOREACH( FBLIB_FILE ${SOURCE_FILES_TMP})
	get_filename_component(mod_fblib_file ${FBLIB_FILE} ABSOLUTE)
  STRING(REGEX MATCH  ".*stringlist\\.(cpp|h).*" REGEX_STRINGS ${FBLIB_FILE})
  IF(NOT REGEX_STRINGS)
  STRING(REGEX MATCH  ".*forteinit\\.(cpp|h).*" REGEX_STRINGS ${FBLIB_FILE})
  ENDIF(NOT REGEX_STRINGS)
  IF(NOT REGEX_STRINGS)
    LIST(APPEND SOURCE_FILES ${mod_fblib_file})
  ENDIF()
ENDFOREACH(FBLIB_FILE)
LIST(REMOVE_DUPLICATES SOURCE_FILES)

#######################################################################################
# Generate stringlist for every source file
#######################################################################################
SET(FORTE_MODIFY_SOURCES_ON_MISSING_GENERATED_INCLUDES ON CACHE BOOL "FORTE change the source-files if includes for the generated includes are missing.")
mark_as_advanced(FORTE_MODIFY_SOURCES_ON_MISSING_GENERATED_INCLUDES)

if(FORTE_LINKED_STRINGDICT)
  FOREACH( FBLIB_FILE ${SOURCE_FILES})
    # Do not pars stringlist, as these files will be generated
    STRING(REGEX MATCH  ".*stringlist\\.(cpp|h).*" REGEX_STRINGS ${FBLIB_FILE})
    IF(NOT REGEX_STRINGS)
      STRING(REGEX MATCH  ".*forteinit\\.(cpp|h).*" REGEX_STRINGS ${FBLIB_FILE})
    ENDIF(NOT REGEX_STRINGS)
    IF(NOT REGEX_STRINGS)
      # Just the File name
      STRING(REGEX REPLACE  ".*/" "" FBLIB_FILE_NAME ${FBLIB_FILE})
      STRING(REGEX REPLACE  "\\." "_gen." FBLIB_FILE_NAME ${FBLIB_FILE_NAME})

      IF(EXISTS "${FBLIB_FILE}")
        FILE(READ ${FBLIB_FILE} FILE_STRING)
        STRING(REGEX MATCH "#include \"([^\\\"]*${FBLIB_FILE_NAME})\"" FBLIB_GEN_INCLUDE ${FILE_STRING})
      ENDIF()

      IF(FBLIB_GEN_INCLUDE)
          SET(FBLIB_GEN_PATH "${CMAKE_MATCH_1}")
      ELSE(FBLIB_GEN_INCLUDE)
          SET(FBLIB_GEN_PATH "${FBLIB_FILE_NAME}")
      ENDIF(FBLIB_GEN_INCLUDE)
      ADD_CUSTOM_COMMAND(OUTPUT ${FORTE_BINARY_DIR}/src_gen/${FBLIB_GEN_PATH} COMMAND ${CMAKE_COMMAND} -DFORTE_MODIFY_SOURCES_ON_MISSING_GENERATED_INCLUDES:STRING="${FORTE_MODIFY_SOURCES_ON_MISSING_GENERATED_INCLUDES}" -DFORTE_SOURCE_DIR:STRING="${FORTE_SOURCE_DIR}/src" -DFORTE_BINARY_DIR:STRING="${FORTE_BINARY_DIR}/src_gen" -DFBLIB_FILE:STRING="${FBLIB_FILE}" -P ${FORTE_BUILDSUPPORT_DIRECTORY}/generate_stringlist_include_files.cmake MAIN_DEPENDENCY ${FBLIB_FILE})
      set_source_files_properties(${FORTE_BINARY_DIR}/src_gen/${FBLIB_GEN_PATH} HEADER_FILE_ONLY true)
    ENDIF(NOT REGEX_STRINGS)
  ENDFOREACH(FBLIB_FILE)
  # this is a hack; add_custom_target is always run, but we only want to run builds on modified files, maybe only valid for visual studio projects
  add_library(forte_stringlist_externals STATIC ${SOURCE_FILES})
  
  if(FORTE_BUILD_EXECUTABLE)
      ADD_DEPENDENCIES (forte forte_stringlist_externals)
  endif(FORTE_BUILD_EXECUTABLE)

  if(FORTE_BUILD_STATIC_LIBRARY)
    ADD_DEPENDENCIES (${FORTE_STATIC_LIBRARY_NAME} forte_stringlist_externals)
  endif(FORTE_BUILD_STATIC_LIBRARY)
  
  if(FORTE_BUILD_SHARED_LIBRARY)
    ADD_DEPENDENCIES (${FORTE_SHARED_LIBRARY_NAME} forte_stringlist_externals)
  endif(FORTE_BUILD_SHARED_LIBRARY)
endif(FORTE_LINKED_STRINGDICT)

if(FORTE_COM_OPC_UA)
  forte_opcua_configure()
endif()

# ######################################################################################
# Forte Simulated Time
# ######################################################################################
set(FORTE_FAKE_TIME OFF CACHE BOOL "Forte configuration for using simulated progression of time")
