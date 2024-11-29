#*******************************************************************************
# Copyright (c) 2024 Martin Erich Jobst
#
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
#
# Contributors:
#    Martin Jobst - initial API and implementation and/or initial documentation
# *******************************************************************************/

SET(SOURCE_GROUP ${SOURCE_GROUP}\\io)
forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

forte_add_all_sourcefiles_cpp()
