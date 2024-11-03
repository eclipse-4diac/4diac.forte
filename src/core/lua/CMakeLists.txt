#*******************************************************************************
# Copyright (c) 2017 fortiss GmbH
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#    Monika Wenger
# *    - initial API and implementation and/or initial documentation
# *******************************************************************************/
#############################################################################
# core/lua
#############################################################################

find_package(PkgConfig)

if("${FORTE_USE_LUATYPES}" STREQUAL "LuaJIT")
  set(LUAJIT_LIBRARY "" CACHE FILEPATH "LuaJit Library")
  set(LUAJIT_INCLUDE_DIR "" CACHE PATH "LuaJit Include Directory")
  forte_add_include_directories(${LUAJIT_INCLUDE_DIR})
  forte_add_link_library(${LUAJIT_LIBRARY})
  if(UNIX AND NOT APPLE)
    set(LUAJIT_MATH_LIBRARY "" CACHE FILEPATH "LuaJit Math Library")
    forte_add_link_library(${LUAJIT_MATH_LIBRARY})
  endif(UNIX AND NOT APPLE)
elseif("${FORTE_USE_LUATYPES}" STREQUAL "Lua")

  pkg_check_modules (LUA lua)

  if(NOT DEFINED LUA_FOUND)
    find_package(Lua REQUIRED)
  endif(NOT DEFINED LUA_FOUND)

  forte_add_include_directories(${LUA_INCLUDE_DIRS})
  forte_add_link_library(${LUA_LIBRARIES})

endif("${FORTE_USE_LUATYPES}" STREQUAL "LuaJIT")

forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

forte_add_sourcefile_hcpp(luaengine luatype)
forte_add_sourcefile_hcpp(luabfb luabfbtypeentry)
forte_add_sourcefile_hcpp(luaadapter luaadaptertypeentry)
forte_add_sourcefile_hcpp(luacfb luacfbtypeentry)
