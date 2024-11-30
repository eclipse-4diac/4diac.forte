#*******************************************************************************
# *******************************************************************************
# Copyright (c) 2024 Malte Grave
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#     Malte Grave
# *******************************************************************************/
# *******************************************************************************/

forte_add_network_layer(DDS OFF "dds" CDDSComLayer ddslayer "Enable a DDS Com Layer")
if(FORTE_COM_DDS)

  SET(FORTE_COM_DDS_INCLUDE_DIR "" CACHE PATH "ABSOLUTE path to the DDS library include files e.g. using the FastDDS project")
  SET(FORTE_COM_DDS_LIB_DIR "" CACHE PATH "ABSOLUTE path to the DSS library folder with object files e.g. using the FastDDS project")

  forte_add_include_system_directories(${FORTE_COM_DDS_INCLUDE_DIR})
  forte_add_link_directories(${FORTE_COM_DDS_LIB_DIR})

  # include this directory
  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
  forte_add_handler(CDDSHandler ddshandler)
  forte_add_sourcefile_hcpp(ddspubsub ddshandler)

  # include types
  add_subdirectory("types/action_msgs")
  add_subdirectory("types/example_interfaces")
  add_subdirectory("types/example_message")
  add_subdirectory("types/turtlesim")
  add_subdirectory("types/unique_identifier_msgs")

  # include util
  forte_add_sourcefile_hcpp(util/convert)

  # add link libraries
  forte_add_link_library(
    fastrtps 
    fastcdr 
    tinyxml2
    foonathan_memory-0.7.1-dbg
  )

  # fast-dds requires this
  forte_add_definition("-fexceptions")
  forte_add_definition("-pthread")

  forte_add_custom_configuration("#cmakedefine FORTE_COM_DDS")
  # The DDS layer needs the runtime type information due to Fast DDS
  forte_add_definition("-frtti")
endif(FORTE_COM_DDS)
