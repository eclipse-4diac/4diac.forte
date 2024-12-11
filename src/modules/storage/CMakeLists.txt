#*******************************************************************************
# Copyright (c) 2024 HR Agrartechnik GmbH
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors: 
#     Franz Hoepfinger - initial API and implementation and/or initial documentation
# *******************************************************************************/



#############################################################################
# FORTE_MODULE_STORAGE  integration.
#############################################################################

# option to enable this Module 'FORTE_MODULE_STORAGE' with cmake
forte_add_module(STORAGE OFF "Interacting with ini File")

forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (FORTE_MODULE_STORAGE)
  forte_add_custom_configuration("#cmakedefine FORTE_MODULE_STORAGE")

  forte_add_subdirectory(ini)

endif (FORTE_MODULE_STORAGE)