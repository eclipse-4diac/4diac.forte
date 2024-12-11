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
# ISOBUS ISO 11783 TECU integration.
#############################################################################

# option to enable ISOBUS_TECU with cmake
forte_add_module(ISOBUS_TECU OFF "Enable ISOBUS_TECU communication layer")

forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (FORTE_MODULE_ISOBUS_TECU)
  forte_add_sourcefile_hcpp(I_WBSD_fbt)
  forte_add_handler(FORTE_I_WBSD::CbWBSDHandler I_WBSD_fbt)
  forte_add_custom_configuration("#cmakedefine FORTE_MODULE_ISOBUS_TECU")
endif (FORTE_MODULE_ISOBUS_TECU)









