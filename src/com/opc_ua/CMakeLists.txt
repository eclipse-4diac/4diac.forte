#*******************************************************************************************

# Copyright (c) 2015-2016 Florian Froschermeier <florian.froschermeier@tum.de>, fortiss GmbH
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#     Florian Froschermeier
#       - initial integration of OPC Unified Architecture into FORTE
#     Stefan Profanter
#       - refactoring and adaption to new concept
# ******************************************************************************************

#############################################################################
# OPC Unified Architecture (UA) integration.
# For integration the open-source OPC-UA communication stack/library
# from (open62541 - http://open62541.org/) was used.
#############################################################################

# option to enable OPC UA with cmake
forte_add_network_layer(OPC_UA OFF "opc_ua" COPC_UA_Layer opcua_layer "Enable OPC UA communication layer")

forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (FORTE_COM_OPC_UA)

    forte_add_sourcefile_with_path_cpp(${CMAKE_BINARY_DIR}/com/opc_ua/opcua_nodesets.cpp) # created file
    
    forte_add_sourcefile_with_path_cpp(${CMAKE_BINARY_DIR}/com/opc_ua/opcua_types.cpp) # created file

    SET(FORTE_COM_OPC_UA_PORT 4840 CACHE STRING "Port where the OPC_UA server will listen")
    SET(FORTE_COM_OPC_UA_SERVER_PUB_INTERVAL 100.0 CACHE STRING "OPC UA Server publishing interval in ms")
    SET(FORTE_COM_OPC_UA_CLIENT_PUB_INTERVAL 100.0 CACHE STRING "OPC UA Client requested publishing interval via OPC UA data subscription in ms")
    SET(FORTE_COM_OPC_UA_MULTICAST OFF CACHE BOOL "Enable multicast support for OPC UA and registering with LDS")
    SET(FORTE_COM_OPC_UA_INCLUDE_DIR "" CACHE PATH "ABSOLUTE path to open62541.h file in the OPC UA project")
    SET(FORTE_COM_OPC_UA_LIB_DIR "" CACHE PATH "ABSOLUTE path to OPC UA folder with object library FORTE_COM_OPC_UA_LIB")
    SET(FORTE_COM_OPC_UA_CUSTOM_HOSTNAME CACHE STRING "Custom hostname which is used for the OPC UA app name and app uri")
    SET(FORTE_COM_OPC_UA_ENCRYPTION OFF CACHE BOOL "The open62541 lilbrary was compiled using encryption")

    # OPEN62541 library to be linked to forte
    IF ("${FORTE_ARCHITECTURE}" STREQUAL "Win32")
        SET(FORTE_COM_OPC_UA_LIB "open62541.lib" CACHE STRING "OPC_UA Library file in FORTE_COM_OPC_UA_DIR to be linked to forte (normally with name libopen62541 and a extension according to the type and OS)")
        forte_add_link_library("iphlpapi") #pubsub uses functions in this library
        forte_add_definition("-DUA_ARCHITECTURE_WIN32")
    ELSE ()
        SET(FORTE_COM_OPC_UA_LIB "libopen62541.a" CACHE STRING "OPC_UA Library file in FORTE_COM_OPC_UA_DIR to be linked to forte (normally with name libopen62541 and a extension according to the type and OS)")
        IF ("${FORTE_ARCHITECTURE}" STREQUAL "VxWorks")
          forte_add_definition("-DUA_ARCHITECTURE_VXWORKS")
        ELSEIF ("${FORTE_ARCHITECTURE}" STREQUAL "Nios2")
          forte_add_definition("-DUA_ARCHITECTURE_ECOS")
        ELSEIF ("${FORTE_ARCHITECTURE}" STREQUAL "FreeRTOSLwIP")
          forte_add_definition("-DUA_ARCHITECTURE_FREERTOSLWIP")
        ELSE()
          forte_add_definition("-DUA_ARCHITECTURE_POSIX")
        ENDIF("${FORTE_ARCHITECTURE}" STREQUAL "VxWorks")
    ENDIF ("${FORTE_ARCHITECTURE}" STREQUAL "Win32")
    forte_add_include_system_directories(${FORTE_COM_OPC_UA_INCLUDE_DIR})
    forte_add_link_directories(${FORTE_COM_OPC_UA_LIB_DIR})
    forte_add_link_library_beginning(${FORTE_COM_OPC_UA_LIB})

    forte_add_handler(COPC_UA_Local_Handler opcua_local_handler)
    forte_add_handler(COPC_UA_Remote_Handler opcua_remote_handler)
    # OPC UA Event Layer
    forte_add_network_layer(OPC_UA_Events OFF "ua_ev" COPC_UA_Event_Layer opcua_event_layer "Enable OPC UA Event Support")
    forte_add_network_layer(OPC_UA_AC OFF "ua_ac" COPC_UA_AC_Layer opcua_ac_layer "Enable OPC UA A&C Support")
    forte_add_sourcefile_hcpp(opcua_local_handler opcua_helper opcua_remote_handler opcua_handler_abstract opcua_client_information opcua_action_info opcua_objectstruct_helper 
        opcua_client_config_parser)
    if (NOT EXISTS ${FORTE_COM_OPC_UA_INCLUDE_DIR})
        message(SEND_ERROR "FORTE_COM_OPC_UA_INCLUDE_DIR not set or does not exist")
    endif (NOT EXISTS ${FORTE_COM_OPC_UA_INCLUDE_DIR})

    file(TO_CMAKE_PATH "${FORTE_COM_OPC_UA_LIB_DIR}/${FORTE_COM_OPC_UA_LIB}" FORTE_COM_OPC_UA_LIB_PATH)
    if (NOT EXISTS ${FORTE_COM_OPC_UA_LIB} AND NOT EXISTS ${FORTE_COM_OPC_UA_LIB_PATH})
        message(SEND_ERROR "OPC UA library not found '${FORTE_COM_OPC_UA_LIB}'. Check the value of FORTE_COM_OPC_UA_LIB_DIR and optionally define an absolute path for FORTE_COM_OPC_UA_LIB.")
    endif()
    
    forte_add_custom_configuration("#define FORTE_COM_OPC_UA_PORT ${FORTE_COM_OPC_UA_PORT}") 
    forte_add_custom_configuration("extern TForteUInt16 gOpcuaServerPort\;")
    forte_add_custom_configuration("#include <string>")
    forte_add_custom_configuration("extern std::string gOpcuaClientConfigFile\;")
    forte_add_custom_configuration("#define FORTE_COM_OPC_UA_SERVER_PUB_INTERVAL ${FORTE_COM_OPC_UA_SERVER_PUB_INTERVAL}")
    forte_add_custom_configuration("#define FORTE_COM_OPC_UA_CLIENT_PUB_INTERVAL ${FORTE_COM_OPC_UA_CLIENT_PUB_INTERVAL}")
    
    forte_add_custom_configuration("#cmakedefine FORTE_COM_OPC_UA")
    forte_add_custom_configuration("#cmakedefine FORTE_COM_OPC_UA_MULTICAST")
    forte_add_custom_configuration("#cmakedefine FORTE_COM_OPC_UA_CUSTOM_HOSTNAME \"${FORTE_COM_OPC_UA_CUSTOM_HOSTNAME}\"")
    
    forte_opcua_add_type(forte_localizedtext LocalizedText "UA")

    add_subdirectory(FBs)    
    add_subdirectory(types)
    add_subdirectory(detail)

    
    if(FORTE_COM_OPC_UA_ENCRYPTION)
      SET(FORTE_COM_OPC_UA_ENCRYPTION_INCLUDE_DIR "" CACHE STRING "ABSOLUTE path to encryption headers")
      SET(FORTE_COM_OPC_UA_ENCRYPTION_LIB_DIR "" CACHE STRING "ABSOLUTE path to encryption libraries")
      
      forte_add_include_system_directories(${FORTE_COM_OPC_UA_ENCRYPTION_INCLUDE_DIR})
      forte_add_link_directories(${FORTE_COM_OPC_UA_ENCRYPTION_LIB_DIR})

      set(FORTE_COM_OPC_UA_ENCRYPTION_MBEDTLS TRUE CACHE BOOL "Was open62541 built against mbedtls instead of openssl/libressl?")

      if (FORTE_COM_OPC_UA_ENCRYPTION_MBEDTLS)
        forte_add_link_library("mbedcrypto")
        forte_add_link_library("mbedtls")
        forte_add_link_library("mbedx509")
        if ("${FORTE_ARCHITECTURE}" STREQUAL "Win32")
          forte_add_link_library("bcrypt")
        endif()
      else()
        forte_add_link_library(ssl)
        forte_add_link_library(crypto)
      endif()
    endif()  
endif (FORTE_COM_OPC_UA)
