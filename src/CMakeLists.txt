#*******************************************************************************
# Copyright (c) 2010 - 2014 Profactor GmbH, ACIN, nxtControl GmbH, fortiss GmbH
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#    Micheal Hofmann, Alois Zoitl, Stanislav Meduna, Gerhard Ebenhofer, 
# *   Matthias Plasch
# *     - initial API and implementation and/or initial documentation
# *******************************************************************************/

set(FORTE_EXTERNAL_MODULES_DIRECTORY "" CACHE PATH "Path to a directory with FORTE modules located outside of the FORTE source code")
SET(FORTE_MODULE_LIST modules;com;external)
forte_create_modules_file("${FORTE_MODULE_LIST}")
forte_add_subdirectory(arch)
forte_add_subdirectory(core)
foreach(FORTE_MODULE_DIR ${FORTE_MODULE_LIST})
  string(COMPARE EQUAL "${FORTE_MODULE_DIR}" external _isExternal)
  if(NOT _isExternal)
    forte_add_subdirectory("${FORTE_MODULE_DIR}")
  endif()
endforeach(FORTE_MODULE_DIR)
if(EXISTS ${FORTE_EXTERNAL_MODULES_DIRECTORY})
  INCLUDE(${CMAKE_BINARY_DIR}/src/external/CMakeLists.txt)
endif()
forte_add_subdirectory(stdfblib)

SET(SOURCE_GROUP core)  
forte_add_sourcefile_with_path_hcpp(${FORTE_BINARY_DIR}/stringlist)
set_source_files_properties(${FORTE_BINARY_DIR}/stringlist.h PROPERTIES GENERATED TRUE)
set_source_files_properties(${FORTE_BINARY_DIR}/stringlist.cpp PROPERTIES GENERATED TRUE)

#######################################################################################
# Exclude FBs
#######################################################################################
set(FORTE_EXCLUDE_FBS "" CACHE STRING "Exclude Function blocks")
mark_as_advanced(FORTE_EXCLUDE_FBS)

IF(FORTE_EXCLUDE_FBS)
  STRING(REGEX MATCHALL "[^ ,;][^ ,;]*" FBLIST ${FORTE_EXCLUDE_FBS})

  FOREACH(FB ${FBLIST})
    forte_remove_sourcefile_h(${FB}.h)
    forte_remove_sourcefile_cpp(${FB}.cpp)
  ENDFOREACH(FB)
ENDIF(FORTE_EXCLUDE_FBS)

GET_PROPERTY(PLATFORM_REMOVES              GLOBAL PROPERTY FORTE_PLATFORM_REMOVES)
FOREACH(FB ${PLATFORM_REMOVES})
  forte_remove_sourcefile_h(${FB}.h)
  forte_remove_sourcefile_cpp(${FB}.cpp)
ENDFOREACH(FB)

#############################################################################
# Configure Network Layers
#############################################################################

GET_PROPERTY(LAYER_CLASS GLOBAL PROPERTY FORTE_LAYER_CLASS)
GET_PROPERTY(LAYER_CONFIGNAME GLOBAL PROPERTY FORTE_LAYER_CONFIGNAME)
GET_PROPERTY(LAYER_FILENAME GLOBAL PROPERTY FORTE_LAYER_FILENAME)
LIST(LENGTH LAYER_CLASS       LAYER_CLASS_LEN)
math(EXPR LAYER_CLASS_LEN           ${LAYER_CLASS_LEN}-1)

SET(LAYERMANAGER_INCLUDE "")

FOREACH(POS RANGE ${LAYER_CLASS_LEN}-1)
  LIST(GET LAYER_CLASS      ${POS} CLASS) 
  LIST(GET LAYER_CONFIGNAME ${POS} CONFIGNAME)
  LIST(GET LAYER_FILENAME   ${POS} FILENAME)
  SET(LAYERMANAGER_INCLUDE  "${LAYERMANAGER_INCLUDE}#include<${FILENAME}>\n")
  if("${POS}" GREATER  "0")
    SET(LAYERMANAGER_INSTANCE "${LAYERMANAGER_INSTANCE}  else ")
  endif()
  SET(LAYERMANAGER_INSTANCE "${LAYERMANAGER_INSTANCE}if(0 == strcmp(\"${CONFIGNAME}\", paLayerIdentifier)){\n    mNewLayer = new ${CLASS}(paUpperLayer, paComFB);\n  }\n")
ENDFOREACH(POS)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/core/cominfra/comlayersmanager.cpp.in ${CMAKE_BINARY_DIR}/core/cominfra/comlayersmanager_new.cpp)
forte_replacefile_if_changed(${CMAKE_BINARY_DIR}/core/cominfra/comlayersmanager_new.cpp ${CMAKE_BINARY_DIR}/core/cominfra/comlayersmanager.cpp)
file(REMOVE ${CMAKE_BINARY_DIR}/core/cominfra/comlayersmanager_new.cpp)

#############################################################################
# Configure Handlers
#############################################################################

GET_PROPERTY(HANDLER_CLASS GLOBAL PROPERTY FORTE_HANDLER_CLASS)
GET_PROPERTY(HANDLER_FILENAME GLOBAL PROPERTY FORTE_HANDLER_FILENAME)
LIST(LENGTH HANDLER_CLASS       HANDLER_CLASS_LEN_ORIGINAL)

if(${HANDLER_CLASS_LEN_ORIGINAL} GREATER 0)

math(EXPR HANDLER_CLASS_LEN           ${HANDLER_CLASS_LEN_ORIGINAL}-1)

SET(HANDLERMANAGER_INCLUDE "")
SET(HANDLERMANAGER_INSTANCE "")
SET(HANDLERMANAGER_VARIABLES "")
  
SET(HANDLER_ID 1)
FOREACH(POS RANGE ${HANDLER_CLASS_LEN}-1)
  LIST(GET HANDLER_CLASS      ${POS} CLASS) 
  LIST(GET HANDLER_FILENAME   ${POS} FILENAME)
  SET(HANDLERMANAGER_INCLUDE  "${HANDLERMANAGER_INCLUDE}#include <${FILENAME}>\n")
  
  SET(HANDLERMANAGER_VARIABLES  "${HANDLERMANAGER_VARIABLES}const size_t ${CLASS}::mHandlerIdentifier = ${HANDLER_ID};\n")
  SET(HANDLERMANAGER_INSTANCE "${HANDLERMANAGER_INSTANCE}  paDeviceExecution.mRegisteredEventHandlers[${HANDLER_ID}].mHandler = new ${CLASS}(paDeviceExecution);\n")
  math(EXPR HANDLER_ID           ${HANDLER_ID}+1)
ENDFOREACH(POS)

endif(${HANDLER_CLASS_LEN_ORIGINAL} GREATER 0)

math(EXPR HANDLER_CLASS_LEN_ORIGINAL ${HANDLER_CLASS_LEN_ORIGINAL}+1)
SET(FORTE_NUMBER_OF_HANDLERS ${HANDLER_CLASS_LEN_ORIGINAL} PARENT_SCOPE)


CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/core/deviceExecutionHandlers.cpp.in ${CMAKE_BINARY_DIR}/core/deviceExecutionHandlers_new.cpp)
forte_replacefile_if_changed(${CMAKE_BINARY_DIR}/core/deviceExecutionHandlers_new.cpp ${CMAKE_BINARY_DIR}/core/deviceExecutionHandlers.cpp)
file(REMOVE ${CMAKE_BINARY_DIR}/core/deviceExecutionHandlers_new.cpp)

#############################################################################
# Configure Timers
#############################################################################

GET_PROPERTY(TIMERHANDLER_CLASS GLOBAL PROPERTY FORTE_TIMERHANDLER_CLASS)
GET_PROPERTY(TIMERHANDLER_FILENAME GLOBAL PROPERTY FORTE_TIMERHANDLER_FILENAME)
GET_PROPERTY(TIMERHANDLER_NAME GLOBAL PROPERTY FORTE_TIMERHANDLER_NAME)
GET_PROPERTY(TIMERHANDLER_DEFAULT GLOBAL PROPERTY FORTE_TIMERHANDLER_DEFAULT)

if(NOT DEFINED TIMERHANDLER_DEFAULT)
  set(TIMERHANDLER_DEFAULT "standard")
endif()

SET(TIMERHANDLER_INCLUDE "")
SET(TIMERHANDLER_CREATE "")

LIST(LENGTH TIMERHANDLER_CLASS TIMERHANDLER_CLASS_LEN)
math(EXPR TIMERHANDLER_CLASS_LEN ${TIMERHANDLER_CLASS_LEN}-1)

FOREACH(POS RANGE ${TIMERHANDLER_CLASS_LEN})

  LIST(GET TIMERHANDLER_CLASS      ${POS} CLASS) 
  LIST(GET TIMERHANDLER_FILENAME   ${POS} FILENAME)
  LIST(GET TIMERHANDLER_NAME       ${POS} NAME_)

  SET(TIMERHANDLER_INCLUDE  "${TIMERHANDLER_INCLUDE}#include \"${FILENAME}\"\n")

  SET(TIMERHANDLER_ENUM  "${TIMERHANDLER_ENUM}    ${NAME_},\n")
  
  SET(TIMERHANDLER_CREATE "${TIMERHANDLER_CREATE}  if(timerHandlerToCreate == AvailableTimers::${NAME_}) return new ${CLASS}(paDeviceExecution);\n")
ENDFOREACH(POS)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/arch/timerHandlerFactory.h.in ${CMAKE_BINARY_DIR}/arch/timerHandlerFactory_new.h)
forte_replacefile_if_changed(${CMAKE_BINARY_DIR}/arch/timerHandlerFactory_new.h ${CMAKE_BINARY_DIR}/arch/timerHandlerFactory.h)
file(REMOVE ${CMAKE_BINARY_DIR}/arch/timerHandlerFactory_new.h)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/arch/timerHandlerFactory.cpp.in ${CMAKE_BINARY_DIR}/arch/timerHandlerFactory_new.cpp)
forte_replacefile_if_changed(${CMAKE_BINARY_DIR}/arch/timerHandlerFactory_new.cpp ${CMAKE_BINARY_DIR}/arch/timerHandlerFactory.cpp)
file(REMOVE ${CMAKE_BINARY_DIR}/arch/timerHandlerFactory_new.cpp)

#############################################################################
# Configure ECETs
#############################################################################

GET_PROPERTY(ECET_CLASS GLOBAL PROPERTY FORTE_ECET_CLASS)
GET_PROPERTY(ECET_FILENAME GLOBAL PROPERTY FORTE_ECET_FILENAME)
GET_PROPERTY(ECET_NAME GLOBAL PROPERTY FORTE_ECET_NAME)

LIST(LENGTH ECET_CLASS ECET_CLASS_LEN)
math(EXPR ECET_CLASS_LEN  ${ECET_CLASS_LEN}-1)

SET(ECET_INCLUDE "")
SET(ECET_CREATE "")
SET(ECET_ENUM "")


FOREACH(POS RANGE ${ECET_CLASS_LEN})
  LIST(GET ECET_CLASS      ${POS} CLASS) 
  LIST(GET ECET_FILENAME   ${POS} FILENAME)
  LIST(GET ECET_NAME   ${POS} NAME_)

  SET(ECET_INCLUDE  "${ECET_INCLUDE}#include \"${FILENAME}\"\n")

  SET(ECET_ENUM  "${ECET_ENUM}\n    ${NAME_},")

  SET(ECET_CREATE "${ECET_CREATE}  if(ecetToCreate == AvailableEcets::${NAME_}) return new ${CLASS}();\n")
ENDFOREACH(POS)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/core/ecetFactory.cpp.in ${CMAKE_BINARY_DIR}/core/ecetFactory_new.cpp)
forte_replacefile_if_changed(${CMAKE_BINARY_DIR}/core/ecetFactory_new.cpp ${CMAKE_BINARY_DIR}/core/ecetFactory.cpp)
file(REMOVE ${CMAKE_BINARY_DIR}/core/ecetFactory_new.cpp)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/core/ecetFactory.h.in ${CMAKE_BINARY_DIR}/core/ecetFactory_new.h)
forte_replacefile_if_changed(${CMAKE_BINARY_DIR}/core/ecetFactory_new.h ${CMAKE_BINARY_DIR}/core/ecetFactory.h)
file(REMOVE ${CMAKE_BINARY_DIR}/core/ecetFactory_new.h)

######################################################################################
# Available Devices 
######################################################################################

GET_PROPERTY(DEVICE_CLASSES GLOBAL PROPERTY FORTE_DEVICE_CLASSES)
GET_PROPERTY(DEVICE_FILENAMES GLOBAL PROPERTY FORTE_DEVICE_FILENAMES)
GET_PROPERTY(DEVICE_NAMES GLOBAL PROPERTY FORTE_DEVICE_NAMES)

LIST(LENGTH DEVICE_CLASSES DEVICE_CLASSES_LEN)

IF(${DEVICE_CLASSES_LEN} EQUAL 1)
  # only one device present

  LIST(GET DEVICE_CLASSES     0 CLASS) 
  LIST(GET DEVICE_FILENAMES   0 FILENAME)

  SET(SINGLE_DEVICE_INCLUDE "#include \"${FILENAME}\"\n")
  SET(SINGLE_DEVICE_CREATE "  return (paMGRID.length() != 0) ? std::make_unique<${CLASS}>(paMGRID) : std::make_unique<${CLASS}>(); ")

ELSE()
  forte_add_definition("-DFORTE_MULTIPLE_DEVICES")

  forte_add_sourcefile_with_path_cpp(${CMAKE_BINARY_DIR}/deviceFactory.cpp) # created file

  set(FORTE_DEVICE_DEFAULT "RMT_DEV" CACHE STRING "The default device to use")

  if(NOT "${FORTE_DEVICE_DEFAULT}" IN_LIST DEVICE_NAMES)
    message(FATAL_ERROR "${FORTE_DEVICE_DEFAULT} is not a valid device. Choose one of the following: ${DEVICE_NAMES}")
  endif()

  math(EXPR DEVICE_CLASSES_LEN  ${DEVICE_CLASSES_LEN}-1)

  SET(DEVICE_INCLUDE "")
  SET(DEVICE_CREATE "")
  SET(DEVICE_ENUM "")

  FOREACH(POS RANGE ${DEVICE_CLASSES_LEN})
    LIST(GET DEVICE_CLASSES     ${POS} CLASS) 
    LIST(GET DEVICE_FILENAMES   ${POS} FILENAME)
    LIST(GET DEVICE_NAMES   ${POS} DEVICE_NAME)

    SET(DEVICE_INCLUDE  "${DEVICE_INCLUDE}#include \"${FILENAME}\"\n")

    SET(DEVICE_ENUM  "${DEVICE_ENUM}\n     ${DEVICE_NAME},")

    SET(DEVICE_STRING_TO_ENUM  "${DEVICE_STRING_TO_ENUM}  if(paDevice == \"${DEVICE_NAME}\") {\n    deviceToCreate = AvailableDevices::${DEVICE_NAME};\n    return true;\n  }\n")


    SET(DEVICE_CREATE "${DEVICE_CREATE}  if(deviceToCreate == AvailableDevices::${DEVICE_NAME})\n    return (paMGRID.length() != 0) ? std::make_unique<${CLASS}>(paMGRID) : std::make_unique<${CLASS}>();\n")
  ENDFOREACH(POS)

  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/deviceFactory.cpp.in ${CMAKE_BINARY_DIR}/deviceFactory_new.cpp)
  forte_replacefile_if_changed(${CMAKE_BINARY_DIR}/deviceFactory_new.cpp ${CMAKE_BINARY_DIR}/deviceFactory.cpp)
  file(REMOVE ${CMAKE_BINARY_DIR}/deviceFactory_new.cpp)
ENDIF()

# configure the deviceFactory header for single and multiple devices
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/deviceFactory.h.in ${CMAKE_BINARY_DIR}/deviceFactory_new.h)
forte_replacefile_if_changed(${CMAKE_BINARY_DIR}/deviceFactory_new.h ${CMAKE_BINARY_DIR}/deviceFactory.h)
file(REMOVE ${CMAKE_BINARY_DIR}/deviceFactory_new.h)

#############################################################################
# Configure startuphook
#############################################################################

GET_PROPERTY(STARTUP_HOOK_FUNCTIONS GLOBAL PROPERTY FORTE_STARTUP_HOOK_FUNCTIONS)
LIST(APPEND STARTUP_HOOK_FUNCTIONS_LIST ${STARTUP_HOOK_FUNCTIONS})

SET(FORTE_STARTUP_HOOKS_DECLS "")
SET(FORTE_STARTUP_HOOKS_CALLS "")

FOREACH(STARTUP_HOOK_FUNCTION ${STARTUP_HOOK_FUNCTIONS_LIST})
  SET(FORTE_STARTUP_HOOKS_DECLS  "${FORTE_STARTUP_HOOKS_DECLS}void ${STARTUP_HOOK_FUNCTION}(int argc, char *arg[]); \n")
  
  SET(FORTE_STARTUP_HOOKS_CALLS  "${FORTE_STARTUP_HOOKS_CALLS}  ${STARTUP_HOOK_FUNCTION}(argc, arg);\n")
ENDFOREACH()

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/arch/startuphook.cpp.in ${CMAKE_BINARY_DIR}/src_gen/startuphook_new.cpp)
forte_replacefile_if_changed(${CMAKE_BINARY_DIR}/src_gen/startuphook_new.cpp ${CMAKE_BINARY_DIR}/src_gen/startuphook.cpp)
file(REMOVE ${CMAKE_BINARY_DIR}/src_gen/startuphook_new.cpp)


#############################################################################
# Load FORTE Extension Files
#############################################################################

GET_PROPERTY(EXTENSION_FILES GLOBAL PROPERTY FORTE_EXTENSION_FILES)
LIST(LENGTH EXTENSION_FILES len)
IF(len GREATER 0)
  LIST(REMOVE_DUPLICATES EXTENSION_FILES)
  FOREACH(FILE ${EXTENSION_FILES})
  INCLUDE("${FILE}")
  ENDFOREACH(FILE)
ENDIF(len GREATER 0)

#######################################################################################
# Setup Forte with all Functionblocks
#######################################################################################

#forte init is needed for the temporary forte library, which then is linked to the main.cpp

forte_add_sourcefile_with_path_hcpp(${FORTE_BINARY_DIR}/forteinit)
set_source_files_properties(${FORTE_BINARY_DIR}/forteinit.h PROPERTIES GENERATED TRUE)
set_source_files_properties(${FORTE_BINARY_DIR}/forteinit.cpp PROPERTIES GENERATED TRUE)

GET_PROPERTY(SOURCE_TIMER_CPP         GLOBAL PROPERTY FORTE_TIMER_CPP)
GET_PROPERTY(SOURCE_TIMER_H           GLOBAL PROPERTY FORTE_TIMER_H)

forte_add_sourcefile_with_path_h(${SOURCE_TIMER_H})
forte_add_sourcefile_with_path_cpp(${SOURCE_TIMER_CPP})

GET_PROPERTY(SOURCE_H              GLOBAL PROPERTY FORTE_SOURCE_H)
GET_PROPERTY(SOURCE_H_GROUP        GLOBAL PROPERTY FORTE_SOURCE_H_GROUP)
LIST(APPEND SOURCE_FILES           ${SOURCE_H})
LIST(APPEND SOURCE_FILES_GROUP     ${SOURCE_H_GROUP})

GET_PROPERTY(SOURCE_CPP              GLOBAL PROPERTY FORTE_SOURCE_CPP)
GET_PROPERTY(SOURCE_CPP_GROUP_STRUCT GLOBAL PROPERTY FORTE_SOURCE_CPP_GROUP)
LIST(APPEND SOURCE_FILES             ${SOURCE_CPP})
LIST(APPEND SOURCE_FILES_GROUP       ${SOURCE_CPP_GROUP_STRUCT})

GET_PROPERTY(SOURCE_C                GLOBAL PROPERTY FORTE_SOURCE_C)
GET_PROPERTY(SOURCE_C_GROUP_STRUCT   GLOBAL PROPERTY FORTE_SOURCE_C_GROUP)
LIST(APPEND SOURCE_FILES             ${SOURCE_C})
LIST(APPEND SOURCE_FILES_GROUP       ${SOURCE_C_GROUP_STRUCT})

GET_PROPERTY(SOURCE_EXECUTABLE_CPP    GLOBAL PROPERTY FORTE_EXECUTABLE_CPP)
GET_PROPERTY(SOURCE_EXECUTABLE_H      GLOBAL PROPERTY FORTE_EXECUTABLE_H)

#############################################################################
# Add Files to source-group
#############################################################################
LIST(LENGTH SOURCE_FILES       SOURCE_LEN)
LIST(LENGTH SOURCE_FILES_GROUP SOURCE_GROUP_LEN)
math(EXPR SOURCE_LEN           ${SOURCE_LEN}-1)
math(EXPR SOURCE_GROUP_LEN     ${SOURCE_GROUP_LEN}-1)

FOREACH(POS RANGE ${SOURCE_LEN}-1)
  LIST(GET SOURCE_FILES        ${POS} FILE) 
  LIST(GET SOURCE_FILES_GROUP  ${POS} GROUP) 
  source_group(${GROUP} FILES  ${FILE})
ENDFOREACH(POS)

# remove duplicate entries
LIST(LENGTH SOURCE_FILES len)
IF(len GREATER 0)
  LIST(REMOVE_DUPLICATES SOURCE_FILES)
ENDIF(len GREATER 0)

SET(WRITE_FILE "")
FOREACH(FILE ${SOURCE_FILES})
  SET(WRITE_FILE "${WRITE_FILE}${FILE}\n")
ENDFOREACH(FILE)
FILE(WRITE ${CMAKE_BINARY_DIR}/file_list.txt "${WRITE_FILE}")

######################################################################################
# Architecutre to build 4diac FORTE on
######################################################################################
set(FORTE_ARCHITECTURE "None" CACHE STRING "Architecture to build FORTE on")
GET_PROPERTY(architectures GLOBAL PROPERTY FORTE_ARCHITECTURES)
list(SORT architectures)
set_property(CACHE FORTE_ARCHITECTURE PROPERTY STRINGS None ${architectures})

#######################################################################################
# Create Files
#######################################################################################

# setting the C++ version has to be done directly before defining the targets only then modules can override this setting 
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
elseif(CMAKE_CXX_STANDARD LESS 17)
  set(CMAKE_CXX_STANDARD 17)
endif()
if(NOT DEFINED CMAKE_CXX_STANDARD_REQUIRED)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

#######################################################################################
# Create an object library with all configurations needed which 
# is then used by the others targets
#######################################################################################
set(FORTE_BASE_TARGET_NAME FORTE_LITE)
add_library(${FORTE_BASE_TARGET_NAME} OBJECT ${SOURCE_FILES}) #no executables.
target_compile_features(${FORTE_BASE_TARGET_NAME} PUBLIC cxx_std_17)

#######################################################################################
# Link Libraries to the Executable
#######################################################################################
# get Linker-Directories from Modules
get_property(LINK_LIBRARY GLOBAL PROPERTY FORTE_LINK_LIBRARY)
target_link_libraries(${FORTE_BASE_TARGET_NAME} INTERFACE ${LINK_LIBRARY})

#######################################################################################
# Define global link flags
#######################################################################################

get_property(existing_link_flags GLOBAL PROPERTY LINK_FLAGS)
if(existing_link_flags)
  set_property(GLOBAL APPEND PROPERTY FORTE_LINK_FLAGS ${existing_link_flags})
endif()

GET_PROPERTY(link_flags GLOBAL PROPERTY FORTE_LINK_FLAGS)

target_link_options(${FORTE_BASE_TARGET_NAME} INTERFACE ${link_flags})

#######################################################################################
# Define global Include-directorys
#######################################################################################

forte_add_include_directories(./)
forte_add_include_directories(${FORTE_BINARY_DIR})
forte_add_include_directories(${FORTE_BINARY_DIR}/src_gen)

GET_PROPERTY(INCLUDE_DIRECTORIES GLOBAL PROPERTY FORTE_INCLUDE_DIRECTORIES)

LIST(LENGTH INCLUDE_DIRECTORIES len)
IF(len GREATER 0)
  LIST(REMOVE_DUPLICATES INCLUDE_DIRECTORIES)
  LIST(REVERSE INCLUDE_DIRECTORIES) # bugfix, for replaced include files
ENDIF(len GREATER 0)

GET_PROPERTY(INCLUDE_SYSTEM_DIRECTORIES GLOBAL PROPERTY FORTE_INCLUDE_SYSTEM_DIRECTORIES)
LIST(LENGTH INCLUDE_SYSTEM_DIRECTORIES len)
IF(len GREATER 0)
  LIST(REMOVE_DUPLICATES INCLUDE_SYSTEM_DIRECTORIES)
  LIST(REVERSE INCLUDE_SYSTEM_DIRECTORIES) # bugfix, for replaced include files
ENDIF(len GREATER 0)

target_include_directories(${FORTE_BASE_TARGET_NAME} PUBLIC ${INCLUDE_DIRECTORIES})
target_include_directories(${FORTE_BASE_TARGET_NAME} SYSTEM PUBLIC ${INCLUDE_SYSTEM_DIRECTORIES})

#######################################################################################
# Define directories for Libraries
#######################################################################################
GET_PROPERTY(LINK_DIRECTORIES GLOBAL PROPERTY FORTE_LINK_DIRECTORIES)
LIST(LENGTH LINK_DIRECTORIES len)
IF(len GREATER 0)
  LIST(REMOVE_DUPLICATES LINK_DIRECTORIES)
ENDIF(len GREATER 0)

target_link_directories(${FORTE_BASE_TARGET_NAME} INTERFACE ${LINK_DIRECTORIES})

#######################################################################################
# Define compile definitions
#######################################################################################
GET_PROPERTY(DEFINITIONS GLOBAL PROPERTY FORTE_DEFINITION)
# the following should be added to the ${FORTE_BASE_TARGET_NAME} target, but it 
# was not working in windows for some reason
ADD_DEFINITIONS(${DEFINITIONS}) 

set(FORTE_LINK_STATIC OFF CACHE BOOL "Force static linking of forte binary")

if(FORTE_BUILD_EXECUTABLE)
  ADD_EXECUTABLE (${FORTE_EXECUTABLE_NAME} ${SOURCE_EXECUTABLE_CPP} ${FORTE_EXECUTABLE_H})
  if (FORTE_LINK_STATIC)
    set_target_properties(${FORTE_EXECUTABLE_NAME} PROPERTIES LINK_SEARCH_START_STATIC ON)
    set_target_properties(${FORTE_EXECUTABLE_NAME} PROPERTIES LINK_SEARCH_END_STATIC ON)
    target_link_options(${FORTE_EXECUTABLE_NAME} PRIVATE -static-libgcc -static-libstdc++ -static)
  endif()
  TARGET_LINK_LIBRARIES (${FORTE_EXECUTABLE_NAME} PUBLIC ${FORTE_BASE_TARGET_NAME})
  install(TARGETS ${FORTE_EXECUTABLE_NAME} RUNTIME DESTINATION bin)
  message("Building executable")
endif(FORTE_BUILD_EXECUTABLE)

# function for configuring common things in both static and shared c libraries
FUNCTION(configure_c_library LIBRARY_NAME)
  target_sources(${LIBRARY_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/arch/c_interface/forte_c.cpp)
  set_target_properties(${TARGET_NAME}
    PROPERTIES PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/arch/c_interface/forte_c.h)

  install(TARGETS ${TARGET_NAME} 
      LIBRARY DESTINATION bin
      PUBLIC_HEADER DESTINATION include)
ENDFUNCTION()

if(FORTE_BUILD_STATIC_LIBRARY)
  message("Building static library")

  ADD_LIBRARY (${FORTE_STATIC_LIBRARY_NAME} STATIC)
  TARGET_LINK_LIBRARIES (${FORTE_STATIC_LIBRARY_NAME} PUBLIC ${FORTE_BASE_TARGET_NAME})

  if(FORTE_C_INTERFACE)
   configure_c_library(${FORTE_STATIC_LIBRARY_NAME})
  else()
    install(TARGETS ${FORTE_STATIC_LIBRARY_NAME} ARCHIVE DESTINATION bin)
  endif(FORTE_C_INTERFACE)

  endif(FORTE_BUILD_STATIC_LIBRARY)

if(FORTE_BUILD_SHARED_LIBRARY)
  message("Building shared library")

  if(WIN32)
    message(WARNING "Shared library in windows might not be linkable.")
  endif(WIN32)
  
  ADD_LIBRARY (${FORTE_SHARED_LIBRARY_NAME} SHARED)
  TARGET_LINK_LIBRARIES (${FORTE_SHARED_LIBRARY_NAME} PUBLIC ${FORTE_BASE_TARGET_NAME})
  set_target_properties(${FORTE_BASE_TARGET_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
  set_target_properties(${FORTE_SHARED_LIBRARY_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)


  if(FORTE_C_INTERFACE)
    configure_c_library(${FORTE_SHARED_LIBRARY_NAME})

    # hide all symbols except the ones from the C interface
    # NOTE: This is still not working. The dynamic symbols are still being exported
    # --exclude-libs is an option for gcc but it does not work with OBJECT libraries
    # Exporting the dynamic symbols makes the loading time of the library longer
    # but it still can be used as usual
    set_target_properties(${FORTE_SHARED_LIBRARY_NAME} PROPERTIES 
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON)
    set_target_properties(${FORTE_SHARED_LIBRARY_NAME} PROPERTIES 
        C_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON)

    IF (WIN32 OR CYGWIN)
      SET(FORTE_SHARED_PREFIX "__declspec(dllexport)")
    else()
      SET(FORTE_SHARED_PREFIX "__attribute__((visibility(\"default\")))")
    endif()
    target_compile_definitions(${FORTE_SHARED_LIBRARY_NAME} PRIVATE FORTE_SHARED_PREFIX=${FORTE_SHARED_PREFIX})
  else()
    install(TARGETS ${FORTE_SHARED_LIBRARY_NAME} ARCHIVE DESTINATION bin)
  endif(FORTE_C_INTERFACE)
endif(FORTE_BUILD_SHARED_LIBRARY)

#######################################################################################
# Generate stringlist and modules
#######################################################################################

#forte init is needed for the temporary forte library, which then is linked to the main.cpp
ADD_CUSTOM_TARGET(forte_init_generator COMMAND ${CMAKE_COMMAND} -DFORTE_BINARY_DIR:STRING="${CMAKE_BINARY_DIR}" -DFORTE_SOURCE_DIR:STRING="${CMAKE_SOURCE_DIR}" -DFORTE_LITTLE_ENDIAN:STRING=${FORTE_LITTLE_ENDIAN} -DFORTE_BIG_ENDIAN:STRING=${FORTE_BIG_ENDIAN} -DFORTE_LOGLEVEL:STRING="${FORTE_LOGLEVEL}" -P ${FORTE_BUILDSUPPORT_DIRECTORY}/generate_init.cmake)  #
ADD_DEPENDENCIES (forte_init_generator forte_generate_modules_cmake_files)
ADD_DEPENDENCIES (${FORTE_BASE_TARGET_NAME} forte_init_generator)

ADD_CUSTOM_TARGET(forte_generate_modules_cmake_files COMMAND ${CMAKE_COMMAND}
  -DFORTE_MODULE_LIST:LISTS="${FORTE_MODULE_LIST}"
  -P ${FORTE_BUILDSUPPORT_DIRECTORY}/generate_modules_cmake_file.cmake)

ADD_CUSTOM_TARGET(forte_stringlist_generator COMMAND ${CMAKE_COMMAND} -DFORTE_LINKED_STRINGDICT:STRING="${FORTE_LINKED_STRINGDICT}" -DFORTE_BINARY_DIR:STRING="${CMAKE_BINARY_DIR}" -DFORTE_SOURCE_DIR:STRING="${CMAKE_CURRENT_SOURCE_DIR}" -P ${FORTE_BUILDSUPPORT_DIRECTORY}/generate_stringlist.cmake)
ADD_DEPENDENCIES (${FORTE_BASE_TARGET_NAME} forte_stringlist_generator)
ADD_DEPENDENCIES (forte_stringlist_generator forte_generate_modules_cmake_files)

#######################################################################################
# Generate stringlist for every source file
#######################################################################################
if(FORTE_LINKED_STRINGDICT)
  set(ENABLE_GENERATED_SOURCE_CPP ON)
  ADD_DEPENDENCIES (${FORTE_BASE_TARGET_NAME} forte_stringlist_externals)
endif(FORTE_LINKED_STRINGDICT)

#######################################################################################
# Enable autogenerated source files
#######################################################################################
if(ENABLE_GENERATED_SOURCE_CPP)
    ADD_DEFINITIONS("-DFORTE_ENABLE_GENERATED_SOURCE_CPP")
endif(ENABLE_GENERATED_SOURCE_CPP)

#######################################################################################
# Add post build commands
#######################################################################################
GET_PROPERTY(POST_BUILD_COM GLOBAL PROPERTY FORTE_POST_BUILD_COMMAND)
STRING(LENGTH "${POST_BUILD_COM}" LEN_POST_BUILD_COM)
if(NOT LEN_POST_BUILD_COM EQUAL 0)
  if(FORTE_BUILD_EXECUTABLE)
    ADD_CUSTOM_COMMAND(TARGET ${FORTE_BUILD_EXECUTABLE} POST_BUILD ${POST_BUILD_COM})
  endif(FORTE_BUILD_EXECUTABLE)

  if(FORTE_BUILD_STATIC_LIBRARY)
    ADD_CUSTOM_COMMAND(TARGET ${FORTE_STATIC_LIBRARY_NAME} POST_BUILD ${POST_BUILD_COM})
  endif(FORTE_BUILD_STATIC_LIBRARY)
  
  if(FORTE_BUILD_SHARED_LIBRARY)
    ADD_CUSTOM_COMMAND(TARGET ${FORTE_SHARED_LIBRARY_NAME} POST_BUILD ${POST_BUILD_COM})
  endif(FORTE_BUILD_SHARED_LIBRARY)
endif(NOT LEN_POST_BUILD_COM EQUAL 0)
