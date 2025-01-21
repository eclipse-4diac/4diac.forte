#*******************************************************************************
# Copyright (c) 2010 -2014 Profactor GmbH, ACIN, fortiss GmbH
#               2020 Johannes Kepler University Linz
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
#
# Contributors:
#     Michael Hofmann, Alois Zoitl, Gerhard Ebenhofer, Matthias Plash, Patrick Smejkal - initial API and implementation and/or initial documentation
#     Ernst Blecha - add directory-based module creation
# *******************************************************************************/

MACRO(forte_add_subdirectory DIRECTORY)
  SET(SOURCE_GROUP_BACKUP ${SOURCE_GROUP})
  SET(SOURCE_GROUP ${SOURCE_GROUP}\\${DIRECTORY})
  add_subdirectory(${DIRECTORY})
  SET(SOURCE_GROUP ${SOURCE_GROUP_BACKUP})
ENDMACRO(forte_add_subdirectory)

FUNCTION(forte_add_sourcefile_with_path_h)
  FOREACH(ARG ${ARGV})
    SET_SOURCE_FILES_PROPERTIES(${ARG} PROPERTIES HEADER_FILE_ONLY TRUE)
    SET_PROPERTY(GLOBAL APPEND PROPERTY FORTE_SOURCE_H ${ARG})
    SET_PROPERTY(GLOBAL APPEND PROPERTY FORTE_SOURCE_H_GROUP ${SOURCE_GROUP})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_sourcefile_with_path_h)

FUNCTION(forte_add_sourcefile_with_path_cpp)
  FOREACH(ARG ${ARGV})
  SET_PROPERTY(GLOBAL APPEND PROPERTY FORTE_SOURCE_CPP ${ARG})
    SET_PROPERTY(GLOBAL APPEND PROPERTY FORTE_SOURCE_CPP_GROUP ${SOURCE_GROUP})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_sourcefile_with_path_cpp)

FUNCTION(forte_add_sourcefile_with_path_hcpp)
  FOREACH(ARG ${ARGV})
    forte_add_sourcefile_with_path_h(${ARG}.h)
    forte_add_sourcefile_with_path_cpp(${ARG}.cpp)
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_sourcefile_with_path_hcpp)

FUNCTION(forte_add_sourcefile_h)
  FOREACH(ARG ${ARGV})
    forte_add_sourcefile_with_path_h(${CMAKE_CURRENT_SOURCE_DIR}/${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_sourcefile_h)

FUNCTION(forte_add_sourcefile_with_path_hc)
  FOREACH(ARG ${ARGV})
    forte_add_sourcefile_with_path_h(${ARG}.h)
    forte_add_sourcefile_with_path_c(${ARG}.c)
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_sourcefile_with_path_hc)

FUNCTION(forte_add_sourcefile_hc)
  FOREACH(ARG ${ARGV})
    forte_add_sourcefile_with_path_hc(${CMAKE_CURRENT_SOURCE_DIR}/${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_sourcefile_hc)

FUNCTION(forte_add_sourcefile_c)
  FOREACH(ARG ${ARGV})
  forte_add_sourcefile_with_path_c(${CMAKE_CURRENT_SOURCE_DIR}/${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_sourcefile_c)

FUNCTION(forte_add_sourcefile_with_path_c)
  FOREACH(ARG ${ARGV})
  SET_PROPERTY(GLOBAL APPEND PROPERTY FORTE_SOURCE_C ${ARG})
    SET_PROPERTY(GLOBAL APPEND PROPERTY FORTE_SOURCE_C_GROUP ${SOURCE_GROUP})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_sourcefile_with_path_c)

FUNCTION(forte_add_sourcefile_cpp)
  FOREACH(ARG ${ARGV})
  forte_add_sourcefile_with_path_cpp(${CMAKE_CURRENT_SOURCE_DIR}/${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_sourcefile_cpp)

FUNCTION(forte_add_sourcefile_hcpp)
  FOREACH(ARG ${ARGV})
    forte_add_sourcefile_with_path_hcpp(${CMAKE_CURRENT_SOURCE_DIR}/${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_sourcefile_hcpp)

FUNCTION(forte_add_include_directories)
  FOREACH(ARG ${ARGV})
    SET_PROPERTY(GLOBAL APPEND PROPERTY FORTE_INCLUDE_DIRECTORIES ${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_include_directories)

FUNCTION(forte_add_include_system_directories) #avoid warnings on included folders
  FOREACH(ARG ${ARGV})
    SET_PROPERTY(GLOBAL APPEND PROPERTY FORTE_INCLUDE_SYSTEM_DIRECTORIES ${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_include_system_directories)

FUNCTION(forte_remove_sourcefile_h)
  GET_PROPERTY(SOURCE_H       GLOBAL PROPERTY FORTE_SOURCE_H)
  GET_PROPERTY(SOURCE_H_GROUP GLOBAL PROPERTY FORTE_SOURCE_H_GROUP)
  FOREACH(ARG ${ARGV})  
  LIST(LENGTH SOURCE_H       LIST_LEN)
  MATH(EXPR LIST_LEN ${LIST_LEN}-1)
  FOREACH(POS RANGE ${LIST_LEN}-1)
    LIST(GET SOURCE_H ${POS} FILENAME) 
    STRING(REGEX MATCH ".*/${ARG}$" FOUND ${FILENAME})
    IF(FOUND)
      LIST(REMOVE_AT SOURCE_H  ${POS})
    LIST(REMOVE_AT SOURCE_H_GROUP  ${POS})
      BREAK()
    ENDIF(FOUND)
  ENDFOREACH(POS)
  ENDFOREACH(ARG)
  SET_PROPERTY(GLOBAL PROPERTY FORTE_SOURCE_H ${SOURCE_H})
  SET_PROPERTY(GLOBAL PROPERTY FORTE_SOURCE_H_GROUP ${SOURCE_H_GROUP})
ENDFUNCTION(forte_remove_sourcefile_h)

FUNCTION(forte_remove_sourcefile_cpp)
  GET_PROPERTY(SOURCE_CPP       GLOBAL PROPERTY FORTE_SOURCE_CPP)
  GET_PROPERTY(SOURCE_CPP_GROUP GLOBAL PROPERTY FORTE_SOURCE_CPP_GROUP)
  FOREACH(ARG ${ARGV})
  LIST(LENGTH SOURCE_CPP       LIST_LEN)
  MATH(EXPR LIST_LEN ${LIST_LEN}-1)
  FOREACH(POS RANGE ${LIST_LEN}-1)
    LIST(GET SOURCE_CPP ${POS} FILENAME) 
    STRING(REGEX MATCH ".*/${ARG}$" FOUND ${FILENAME})
    IF(FOUND)
      LIST(REMOVE_AT SOURCE_CPP  ${POS})
    LIST(REMOVE_AT SOURCE_CPP_GROUP  ${POS})
      BREAK()
    ENDIF(FOUND)
  ENDFOREACH(POS)
  ENDFOREACH(ARG)
  SET_PROPERTY(GLOBAL PROPERTY FORTE_SOURCE_CPP ${SOURCE_CPP})
  SET_PROPERTY(GLOBAL PROPERTY FORTE_SOURCE_CPP_GROUP ${SOURCE_CPP_GROUP})
ENDFUNCTION(forte_remove_sourcefile_cpp)

FUNCTION(forte_replace_sourcefile_h)
  FOREACH(ARG ${ARGV})
    forte_remove_sourcefile_h(${ARG})
  forte_add_sourcefile_h(${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_replace_sourcefile_h)

FUNCTION(forte_replace_sourcefile_cpp)
  FOREACH(ARG ${ARGV})
    forte_remove_sourcefile_cpp(${ARG})
  forte_add_sourcefile_cpp(${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_replace_sourcefile_cpp)

# Add a new possible timer to be created. Pass an extra variable to be used as 
# name for the timer handler. If not passed, the default string will be used
FUNCTION(forte_add_timerhandler CLASSNAME FILENAME) 
    set_property(GLOBAL APPEND PROPERTY FORTE_TIMERHANDLER_CLASS ${CLASSNAME})
    set_property(GLOBAL APPEND PROPERTY FORTE_TIMERHANDLER_FILENAME "${FILENAME}.h")
    if(DEFINED ARGV2)
      set(TIMERHANDLER_NAME ${ARGV2})
    else()
      set(TIMERHANDLER_NAME "standard") # default value
    endif()
    set_property(GLOBAL APPEND PROPERTY FORTE_TIMERHANDLER_NAME "${TIMERHANDLER_NAME}")
ENDFUNCTION(forte_add_timerhandler)

MACRO(forte_set_default_timerhandler TIMERHANDLER_NAME) #don't append as there can only be one default timer
  set_property(GLOBAL PROPERTY FORTE_TIMERHANDLER_DEFAULT ${TIMERHANDLER_NAME})
ENDMACRO(forte_set_default_timerhandler)

FUNCTION(forte_add_to_executable_h)
  FOREACH(ARG ${ARGV})
    SET_PROPERTY(GLOBAL APPEND PROPERTY FORTE_EXECUTABLE_H ${CMAKE_CURRENT_SOURCE_DIR}/${ARG}.h)
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_to_executable_h)

FUNCTION(forte_add_to_executable_cpp)
  FOREACH(ARG ${ARGV})
    SET_PROPERTY(GLOBAL APPEND PROPERTY FORTE_EXECUTABLE_CPP ${CMAKE_CURRENT_SOURCE_DIR}/${ARG}.cpp)
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_to_executable_cpp)

FUNCTION(forte_add_link_directories)
  FOREACH(ARG ${ARGV})
    SET_PROPERTY(GLOBAL APPEND PROPERTY FORTE_LINK_DIRECTORIES ${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_link_directories)

FUNCTION(forte_add_link_library)
  FOREACH(ARG ${ARGV})
    set_property(GLOBAL APPEND PROPERTY FORTE_LINK_LIBRARY ${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_link_library)

FUNCTION(forte_add_link_library_beginning)
  get_property(LINK_LIBRARY_1 GLOBAL PROPERTY FORTE_LINK_LIBRARY)
  set_property(GLOBAL PROPERTY FORTE_LINK_LIBRARY "")
  FOREACH(ARG ${ARGV})
    set_property(GLOBAL APPEND PROPERTY FORTE_LINK_LIBRARY ${ARG})
  ENDFOREACH(ARG)
  forte_add_link_library(${LINK_LIBRARY_1}) 
ENDFUNCTION(forte_add_link_library_beginning)

FUNCTION(forte_add_definition)
  FOREACH(ARG ${ARGV})
    set_property(GLOBAL APPEND PROPERTY FORTE_DEFINITION ${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_definition)

FUNCTION(forte_add_link_flags)
FOREACH(ARG ${ARGV})
  set_property(GLOBAL APPEND PROPERTY FORTE_LINK_FLAGS ${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_link_flags)

FUNCTION(forte_add_architecture)
  FOREACH(ARG ${ARGV})
    set_property(GLOBAL APPEND PROPERTY FORTE_ARCHITECTURES ${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_architecture)

MACRO(forte_add_network_layer NAME ONOFF CONFIGNAME CLASSNAME FILENAME DESCRIPTION)
# TODO: parse filename from filename
  set(FORTE_COM_${NAME} ${ONOFF} CACHE BOOL "${DESCRIPTION}")
  IF(FORTE_COM_${NAME})
    FORTE_ADD_SOURCEFILE_HCPP(${FILENAME})
    set_property(GLOBAL APPEND PROPERTY FORTE_LAYER_CLASS ${CLASSNAME})
    set_property(GLOBAL APPEND PROPERTY FORTE_LAYER_CONFIGNAME ${CONFIGNAME})
    set_property(GLOBAL APPEND PROPERTY FORTE_LAYER_FILENAME "${FILENAME}.h")
  ENDIF(FORTE_COM_${NAME})
ENDMACRO(forte_add_network_layer)

MACRO(forte_add_handler CLASSNAME FILENAME)
    FORTE_ADD_SOURCEFILE_H(${FILENAME}.h)
    set_property(GLOBAL APPEND PROPERTY FORTE_HANDLER_CLASS ${CLASSNAME})
    set_property(GLOBAL APPEND PROPERTY FORTE_HANDLER_FILENAME "${FILENAME}.h")
ENDMACRO(forte_add_handler)

MACRO(forte_add_ecet CLASSNAME FILENAME ECET_NAME)
    set_property(GLOBAL APPEND PROPERTY FORTE_ECET_CLASS ${CLASSNAME})
    set_property(GLOBAL APPEND PROPERTY FORTE_ECET_FILENAME "${FILENAME}.h")
    set_property(GLOBAL APPEND PROPERTY FORTE_ECET_NAME "${ECET_NAME}")
ENDMACRO(forte_add_ecet)

MACRO(forte_add_device CLASSNAME FILENAME DEVICE_NAME)
    set_property(GLOBAL APPEND PROPERTY FORTE_DEVICE_CLASSES ${CLASSNAME})
    set_property(GLOBAL APPEND PROPERTY FORTE_DEVICE_FILENAMES "${FILENAME}.h")
    set_property(GLOBAL APPEND PROPERTY FORTE_DEVICE_NAMES "${DEVICE_NAME}")
ENDMACRO(forte_add_device)

MACRO(forte_add_startup_hook FUNCTION_NAME)
    set_property(GLOBAL APPEND PROPERTY FORTE_STARTUP_HOOK_FUNCTIONS ${FUNCTION_NAME})
ENDMACRO(forte_add_startup_hook)


#MACRO(forte_add_module NAME DIRECTORY DESCRIPTION)
# Additional parameters are interpreted as dependencies
MACRO(forte_add_module NAME ONOFF DESCRIPTION)
  # create module with value from cache (does not set the description if the entry exists)
  SET(FORTE_MODULE_${NAME} ${ONOFF} CACHE BOOL "${DESCRIPTION}")
  # update the module description stored in cache
  SET(FORTE_MODULE_${NAME} ${FORTE_MODULE_${NAME}} CACHE BOOL "${DESCRIPTION}" FORCE)

  FOREACH(dependencies ${ARGN})
    IF(NOT ${dependencies})
      RETURN()
    ENDIF(NOT ${dependencies})
  ENDFOREACH(dependencies)
  IF(NOT FORTE_MODULE_${NAME})
    RETURN()
  ENDIF(NOT FORTE_MODULE_${NAME})
ENDMACRO(forte_add_module)

MACRO(forte_add_directory_module)
  # use the current directory name as basis for naming the module
  GET_FILENAME_COMPONENT(MODULENAME ${CMAKE_CURRENT_LIST_DIR} NAME)
  SET(MODULENAME "EXTERNAL_${MODULENAME}")

  forte_directory_listing(DESCRIPTION "*.cpp" "*.c" "*.h")

  # add the module (stops execution if module is disabled!)
  forte_add_module(${MODULENAME} OFF ${DESCRIPTION})
ENDMACRO(forte_add_directory_module)

MACRO(forte_add_io NAME DESCRIPTION)
  set(FORTE_IO_${NAME} OFF CACHE BOOL "${DESCRIPTION}")
ENDMACRO(forte_add_io)

set(FORTE_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/../src CACHE INTERNAL "")

# Additional parameters are interpreted as I/O standard function blocks
MACRO(forte_set_process_interface NAME)
  if(DEFINED CACHE{FORTE_PROCESS_INTERFACE})
    if(NOT "${NAME}" STREQUAL "$CACHE{FORTE_PROCESS_INTERFACE}")
      message(FATAL_ERROR "Cannot use process interface ${NAME}, $CACHE{FORTE_PROCESS_INTERFACE} is already used!")
    endif()
  else()
    set(FORTE_PROCESS_INTERFACE ${NAME} CACHE INTERNAL "The used process interface.")
    FOREACH(fb ${ARGN})
      message(DEBUG "Add I/O FB " ${fb})
      forte_add_sourcefile_with_path_hcpp(${FORTE_SRC_DIR}/stdfblib/io/${fb}_fbt)
    ENDFOREACH()
  endif()
ENDMACRO(forte_set_process_interface)

FUNCTION(forte_create_modules_file FORTE_MODULE_LIST)
  INCLUDE(${FORTE_BUILDSUPPORT_DIRECTORY}/generate_modules_cmake_file.cmake)
ENDFUNCTION(forte_create_modules_file)

FUNCTION(forte_replacefile_if_changed SOURCE DESTINATION)
  execute_process( COMMAND ${CMAKE_COMMAND} -E compare_files ${SOURCE} ${DESTINATION} RESULT_VARIABLE test_not_successful OUTPUT_QUIET ERROR_QUIET )

  IF( test_not_successful)
    file(REMOVE ${DESTINATION})
    file(RENAME ${SOURCE} ${DESTINATION})
  ENDIF( test_not_successful)
ENDFUNCTION(forte_replacefile_if_changed SOURCE DESTINATION)

FUNCTION(forte_add_extension_file)
  FOREACH(ARG ${ARGV})
    SET_PROPERTY(GLOBAL APPEND PROPERTY FORTE_EXTENSION_FILES ${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_extension_file)

FUNCTION(forte_add_post_build_command)
  FOREACH(ARG ${ARGV})
    set_property(GLOBAL APPEND PROPERTY FORTE_POST_BUILD_COMMAND ${ARG})
  ENDFOREACH(ARG)
ENDFUNCTION(forte_add_post_build_command)

FUNCTION(forte_directory_listing VARIABLE EXTENSION)
  # retrieve all files matching the given extension(s)
  file(GLOB FILES LIST_DIRECTORIES false CONFIGURE_DEPENDS ${EXTENSION} ${ARGN})
  # loop over the files, extract the name
  FOREACH(FILE ${FILES})
    get_filename_component(FILENAME ${FILE} NAME)
    list(APPEND FILENAMES ${FILENAME})
  ENDFOREACH()
  # create a newline-seperated list of files
  list(JOIN FILENAMES "\n" FILENAMESTRING)
  set(${VARIABLE} "${CMAKE_CURRENT_LIST_DIR}\n${FILENAMESTRING}" PARENT_SCOPE)
ENDFUNCTION(forte_directory_listing)

FUNCTION(forte_add_all_sourcefiles)
  forte_add_all_sourcefiles_h()
  forte_add_all_sourcefiles_c()
  forte_add_all_sourcefiles_cpp()
ENDFUNCTION(forte_add_all_sourcefiles)

FUNCTION(forte_add_all_sourcefiles_h)
  file(GLOB FILES LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.h")
  forte_add_sourcefile_with_path_h(${FILES})
ENDFUNCTION(forte_add_all_sourcefiles_h)

FUNCTION(forte_add_all_sourcefiles_c)
  file(GLOB FILES LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.c")
  forte_add_sourcefile_with_path_c(${FILES})
ENDFUNCTION(forte_add_all_sourcefiles_c)

FUNCTION(forte_add_all_sourcefiles_cpp)
  file(GLOB FILES LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp")
  forte_add_sourcefile_with_path_cpp(${FILES})
ENDFUNCTION(forte_add_all_sourcefiles_cpp)

FUNCTION(forte_add_all_sourcefiles_recursive)
  forte_add_all_sourcefiles_recursive_h()
  forte_add_all_sourcefiles_recursive_c()
  forte_add_all_sourcefiles_recursive_cpp()
ENDFUNCTION(forte_add_all_sourcefiles_recursive)

FUNCTION(forte_add_all_sourcefiles_recursive_h)
  file(GLOB_RECURSE FILES LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.h")
  forte_add_sourcefile_with_path_h(${FILES})
ENDFUNCTION(forte_add_all_sourcefiles_recursive_h)

FUNCTION(forte_add_all_sourcefiles_recursive_c)
  file(GLOB_RECURSE FILES LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.c")
  forte_add_sourcefile_with_path_c(${FILES})
ENDFUNCTION(forte_add_all_sourcefiles_recursive_c)

FUNCTION(forte_add_all_sourcefiles_recursive_cpp)
  file(GLOB_RECURSE FILES LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp")
  forte_add_sourcefile_with_path_cpp(${FILES})
ENDFUNCTION(forte_add_all_sourcefiles_recursive_cpp)

## forte_add_systemtest_hard (test_name bootfile_name timeout)
## Fails if any error has been logged
FUNCTION(forte_add_systemtest_hard arg1 arg2 arg3)
  FILE(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${arg2}" file_str)
  STRING(REPLACE "\\" "\\\\" file_str ${file_str})
  ADD_TEST(NAME ${arg1} COMMAND $<TARGET_FILE:forte> -f ${file_str})
  set_tests_properties (${arg1} PROPERTIES TIMEOUT ${arg3})
  SET_TESTS_PROPERTIES(${arg1} PROPERTIES FAIL_REGULAR_EXPRESSION "ERROR: T|==ERROR") #==ERROR is the output when memore leak happens
ENDFUNCTION(forte_add_systemtest_hard)

## forte_add_systemtest_soft (test_name bootfile_name timeout)
## Fails only by TEST_CONDITION FBs. This is for the case when a FB has to be tested in all
## its cases, and some of the cases produce logging error
FUNCTION(forte_add_systemtest_soft arg1 arg2 arg3)
  FILE(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${arg2}" file_str)
  STRING(REPLACE "\\" "\\\\" file_str ${file_str})
  ADD_TEST(NAME ${arg1} COMMAND $<TARGET_FILE:forte> -f ${file_str})
  set_tests_properties (${arg1} PROPERTIES TIMEOUT ${arg3})
  SET_TESTS_PROPERTIES(${arg1} PROPERTIES FAIL_REGULAR_EXPRESSION "TEST_CONDITION_FAILED|==ERROR") #==ERROR is the output when memore leak happens
ENDFUNCTION(forte_add_systemtest_soft)

# forte_add_multi_systemtests (TEST_NAME TIMEOUT IS_HARD FILE_NAME EXTRA_ARGS [FILE_NAME EXTRA_ARGS] ...)
FUNCTION(forte_add_multi_systemtests)
   
  FILE(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}/buildsupport/multi_test.cmake" scriptFile)
  STRING(REPLACE "\\" "\\\\" scriptFile ${scriptFile})

  LIST(GET ARGV 0 TEST_NAME)
  LIST(GET ARGV 1 TEST_TIMEOUT)
  LIST(GET ARGV 2 TEST_ISHARD)
  
  SET(NEXT_IS_FILE 1)
  SET(NEXT_PORT 61499)
  SET(COUNTER 0)

  FOREACH(ARG ${ARGV})
     IF(${COUNTER} GREATER 2)

       IF(${NEXT_IS_FILE})
         FILE(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${ARG}" file_str1)
         STRING(REPLACE "\\" "\\\\" file_str1 ${file_str1})
         LIST(APPEND TEST_SYS_FILES "${file_str1}")
         SET(NEXT_IS_FILE 0)
       ELSE(${NEXT_IS_FILE})
         STRING(FIND "${ARG}" "-c" FLAG_POSITION)
         IF(${FLAG_POSITION} EQUAL -1)
           STRING(APPEND ARG " -c localhost:${NEXT_PORT}")
           MATH(EXPR NEXT_PORT "${NEXT_PORT}+1")
         ENDIF(${FLAG_POSITION} EQUAL -1)
         
         LIST(APPEND TEST_EXTRA_ARGS "${ARG}")
         MATH(EXPR EXTRA_ARG_COUNTER "${EXTRA_ARG_COUNTER}+1")
         SET(NEXT_IS_FILE 1)
       ENDIF(${NEXT_IS_FILE})
     
     ENDIF(${COUNTER} GREATER 2) 
     MATH(EXPR COUNTER "${COUNTER}+1")
  ENDFOREACH(ARG)

  STRING(REPLACE ";" "<->" TEST_SYS_FILES "${TEST_SYS_FILES}")
  STRING(REPLACE ";" "<->" TEST_EXTRA_ARGS "${TEST_EXTRA_ARGS}")
   
  ADD_TEST(NAME ${TEST_NAME} COMMAND ${CMAKE_COMMAND}
         -DCMD=$<TARGET_FILE:forte>
         -DSYS_FILES=${TEST_SYS_FILES}
         -DEXTRA_ARGS=${TEST_EXTRA_ARGS}
         -P ${scriptFile})
  
  SET_TESTS_PROPERTIES(${TEST_NAME} PROPERTIES TIMEOUT ${TEST_TIMEOUT})

  IF(${TEST_ISHARD})
    SET_TESTS_PROPERTIES(${TEST_NAME} PROPERTIES FAIL_REGULAR_EXPRESSION "ERROR: T|==ERROR") #==ERROR is the output when memore leak happens
  ELSE(${TEST_ISHARD})
    SET_TESTS_PROPERTIES(${TEST_NAME} PROPERTIES FAIL_REGULAR_EXPRESSION "TEST_CONDITION_FAILED|==ERROR") #==ERROR is the output when memore leak happens
  ENDIF(${TEST_ISHARD}) 
ENDFUNCTION(forte_add_multi_systemtests)

FUNCTION(forte_add_env_file test file)
  FILE(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${file}" file_str)
  STRING(REPLACE "\\" "\\\\" file_str ${file_str})
  set_tests_properties(${test} PROPERTIES ENVIRONMENT "FORTE_BOOT_FILE=${file_str}")
ENDFUNCTION(forte_add_env_file)

FUNCTION(forte_add_custom_configuration arg1)
  SET_PROPERTY(GLOBAL APPEND_STRING PROPERTY FORTE_CUSTOM_CONFIGURATIONS_GLOBAL "${arg1}" \n\n)
ENDFUNCTION(forte_add_custom_configuration)

INCLUDE(${FORTE_BUILDSUPPORT_DIRECTORY}/opcua.cmake)
