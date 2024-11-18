#!/bin/bash
echo "----------------------------------------------------------------------------"
echo " Automatically set up development environment for Zephyr-platform"
echo "----------------------------------------------------------------------------"
echo ""
echo " Includes 64bit-datatypes, float-datatypes, Ethernet-Interface,"
echo " ASN1-encoding, ..."
echo ""
echo " To include tests set directories for boost-test-framework and "
echo " set FORTE_TESTS-option to 'ON'"
echo ""
echo "----------------------------------------------------------------------------"

export forte_src_dir=${PWD}
export forte_bin_dir="bin/zephyr"
export FORTE_BUILDSUPPORT_DIRECTORY="${PWD}/buildsupport"
export forte_external_modules_dir="${PWD}/ExportedFBs"

#set to boost-include directory
export forte_boost_test_inc_dirs=""
#set to boost-library directory
export forte_boost_test_lib_dirs=""

if [ ! -d "$forte_bin_dir" ]; then
  mkdir -p "$forte_bin_dir"
fi

if [ -d "$forte_bin_dir" ]; then

  echo "For building forte go to $forte_bin_dir and execute \"ninja\""
  echo "forte can be found at ${forte_bin_dir}/src"
  echo "forte_tests can be found at ${forte_bin_dir}/tests"

  cd "./$forte_bin_dir"

  for arg in "$@"; do
    export "$arg"
  done

  cmake -G "Ninja" \
    -DCMAKE_C_COMPILER_WORKS=ON \
    -DCMAKE_CXX_COMPILER_WORKS=ON \
    -DNULLPTR_SUPPORTED=ON \
    -DCMAKE_SYSTEM_NAME=Generic \
    -DFORTE_ARCHITECTURE=Zephyr \
    -DFORTE_TESTS=OFF \
    -DFORTE_SUPPORT_BOOT_FILE=ON \
    -DFORTE_BUILD_EXECUTABLE=OFF \
    -DFORTE_BUILD_STATIC_LIBRARY=ON \
    -DFORTE_C_INTERFACE=ON \
    -DFORTE_MODULE_CONVERT=ON \
    -DFORTE_MODULE_IEC61131=ON \
    -DFORTE_IO=ON \
    -DFORTE_IO_ZEPHYR=ON \
    -DFORTE_COM_ETH=ON \
    -DFORTE_COM_FBDK=ON \
    -DFORTE_COM_LOCAL=ON \
    -DFORTE_MODULE_UTILS=ON \
    -DFORTE_EXTERNAL_MODULES_DIRECTORY="${forte_external_modules_dir}" \
    -DCMAKE_C_COMPILER="${CMAKE_C_COMPILER}" \
    -DCMAKE_CXX_COMPILER="${CMAKE_CXX_COMPILER}" \
    -DFORTE_LOGLEVEL=LOGINFO \
    -DCMAKE_BUILD_TYPE=MINSIZEREL \
    -DCMAKE_C_FLAGS="${CMAKE_C_FLAGS}" \
    -DCMAKE_C_FLAGS_DEBUG="-g ${CMAKE_C_FLAGS}" \
    -DCMAKE_C_FLAGS_MINSIZEREL="-Os -DNDEBUG ${CMAKE_C_FLAGS}" \
    -DCMAKE_C_FLAGS_RELEASE="-O3 -DNDEBUG ${CMAKE_C_FLAGS}" \
    -DCMAKE_C_FLAGS_RELWITHDEBINFO="-O2 -g -DNDEBUG ${CMAKE_C_FLAGS}" \
    -DCMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS}" \
    -DCMAKE_CXX_FLAGS_DEBUG="-g ${CMAKE_CXX_FLAGS}" \
    -DCMAKE_CXX_FLAGS_MINSIZEREL="-Os -DNDEBUG ${CMAKE_CXX_FLAGS}" \
    -DCMAKE_CXX_FLAGS_RELEASE="-O3 -DNDEBUG ${CMAKE_CXX_FLAGS}" \
    -DCMAKE_CXX_FLAGS_RELWITHDEBINFO="-O2 -g -DNDEBUG ${CMAKE_CXX_FLAGS}" \
    -DFORTE_ZEPHYR_INCLUDES="${FORTE_ZEPHYR_INCLUDES}" \
    -DFORTE_SOURCE_DIR="${forte_src_dir}" \
    -DFORTE_TESTS_INC_DIRS="${forte_boost_test_inc_dirs}" \
    -DFORTE_TESTS_LINK_DIRS="${forte_boost_test_inc_dirs}" \
    ../../

else
  echo "unable to create ${forte_bin_dir}"
  exit 1
fi
