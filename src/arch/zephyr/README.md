# Hints for building 4diac FORTE for Zephyr OS

In general, the same instructions as for the other target platforms apply. You can build via cmake-gui or use the setup_zephyr.sh script.

The easiest integration into a Zephyr application can be achieved by adding 4diac FORTE to the app's West / CMake build process. This has the
important benefit that you don't have to discover and set all the compiler paths, includes, flags, by yourself.

4diac FORTE requires Zephyr OS version 3.5 or later.

## Integrating 4diac FORTE into a Zephyr app

In your app's CMakeLists.txt, add the following snippet:

```
# 4diac FORTE as Zephyr library module

zephyr_get_compile_definitions_for_lang_as_string(CXX cxx_definitions)
zephyr_get_compile_options_for_lang_as_string(CXX cxx_options)
zephyr_get_include_directories_for_lang_as_string(CXX cxx_includes)
zephyr_get_system_include_directories_for_lang_as_string(CXX cxx_system_includes)

set(external_project_cxxflags
	"${cxx_definitions} ${cxx_options} ${cxx_includes} ${cxx_system_includes} -Wno-error"
)

include(ExternalProject)

set(forte_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/lib/org.eclipse.4diac.forte)
set(FORTE_LIB_DIR ${forte_src_dir}/bin/zephyr/src)

ExternalProject_Add(forte
	SOURCE_DIR ${forte_src_dir}
	BINARY_DIR ${forte_src_dir}/bin/zephyr
	CONFIGURE_COMMAND
		cmake -G "Ninja"
			-DCMAKE_C_COMPILER_WORKS=ON
			-DCMAKE_CXX_COMPILER_WORKS=ON
			-DNULLPTR_SUPPORTED=ON
			-DCMAKE_SYSTEM_NAME=Generic
			-DFORTE_ARCHITECTURE=Zephyr
			-DFORTE_TESTS=OFF
			-DFORTE_SUPPORT_BOOT_FILE=ON
			-DFORTE_BUILD_EXECUTABLE=OFF
			-DFORTE_BUILD_STATIC_LIBRARY=ON
			-DFORTE_C_INTERFACE=ON
			-DFORTE_MODULE_CONVERT=ON
			-DFORTE_MODULE_IEC61131=ON
			-DFORTE_IO=ON
			-DFORTE_IO_ZEPHYR=ON
			-DFORTE_COM_ETH=ON
			-DFORTE_COM_FBDK=ON
			-DFORTE_COM_LOCAL=ON
			-DFORTE_MODULE_UTILS=ON
			-DFORTE_EXTERNAL_MODULES_DIRECTORY=${forte_src_dir}/ExportedFBs
			-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
			-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
			-DFORTE_LOGLEVEL=NOLOG
			-DCMAKE_BUILD_TYPE=MINSIZEREL
			-DCMAKE_C_FLAGS_DEBUG="-g"
			-DCMAKE_CXX_FLAGS=${external_project_cxxflags}
			-DFORTE_SOURCE_DIR=${forte_src_dir}
			../../
	BUILD_COMMAND
		ninja
	BUILD_BYPRODUCTS ${FORTE_LIB_DIR}/libforte-c-static.a
	INSTALL_COMMAND ""
)

add_dependencies(forte zephyr_interface)

add_library(forte_lib STATIC IMPORTED GLOBAL)
add_dependencies(forte_lib forte)
set_target_properties(forte_lib PROPERTIES IMPORTED_LOCATION ${FORTE_LIB_DIR}/libforte-c-static.a)
target_include_directories(forte_lib INTERFACE ${forte_src_dir}/src/arch)
```

```
target_link_libraries(app PUBLIC forte_lib)
```

Adapt the value of `forte_src_dir` to your actual FORTE source tree location.

In your app's `prj.conf`, turn on the required C++ support:

```
# Supporting FORTE logging system on Zephyr's logging subsys
CONFIG_LOG=y
CONFIG_LOG_MODE_IMMEDIATE=n
CONFIG_LOG_BACKEND_UART=n
CONFIG_SHELL_LOG_BACKEND=y

# For C library support
CONFIG_NEWLIB_LIBC=y
CONFIG_NEWLIB_LIBC_FLOAT_PRINTF=y

# For C++ standard library support
CONFIG_CPP=y
CONFIG_STD_CPP20=y
CONFIG_REQUIRES_FULL_LIBCPP=y
CONFIG_COMPILER_OPT="-Werror"

# Dynamic thread creation for 4diac FORTE
CONFIG_DYNAMIC_THREAD=y
CONFIG_DYNAMIC_THREAD_ALLOC=y

CONFIG_INIT_STACKS=y
CONFIG_THREAD_STACK_INFO=y
CONFIG_KERNEL_MEM_POOL=y
CONFIG_HEAP_MEM_POOL_SIZE=64000

# TCP/IP networking for 4diac FORTE
CONFIG_NETWORKING=y
CONFIG_NET_SOCKETS=y
CONFIG_POSIX_API=y
CONFIG_NET_ARP=y
CONFIG_NET_UDP=y
CONFIG_NET_TCP=y

CONFIG_NET_CONFIG_SETTINGS=y
CONFIG_NET_L2_ETHERNET=y
CONFIG_NET_IPV6=y
CONFIG_NET_IPV4=y

CONFIG_NET_MAX_CONN=20
CONFIG_NET_CONTEXT_RCVTIMEO=y
CONFIG_ZVFS_OPEN_MAX=12
CONFIG_NET_MAX_CONTEXTS=16

CONFIG_NET_PROMISCUOUS_MODE=y
# CONFIG_ETH_MCUX_PROMISCUOUS_MODE=y # required by NXP MCUX SOCs

CONFIG_NET_IF_MCAST_IPV4_ADDR_COUNT=4

# LittleFS support
CONFIG_FLASH=y
CONFIG_FLASH_MAP=y
CONFIG_FLASH_PAGE_LAYOUT=y

CONFIG_FILE_SYSTEM=y
CONFIG_FILE_SYSTEM_LITTLEFS=y

# IO drivers support
CONFIG_GPIO=y
CONFIG_ADC=y
CONFIG_ADC_ASYNC=y
CONFIG_PWM=y
```

## Implementing and extending a Modular IO Controller Configuration FB

Use the ZephyrIO function block template for modular IO included with the 4diac IDE TypeLibrary to start a controller configuration FB. The FBT is located in `.../TypeLibrary/io/zephyr/ZephyrIO.fbt` of 4diac projects. The exported FB for compiling and linking with FORTE is provided in `src/modules/zephyr/types/ZephyrIO_fbt.*` of the FORTE sources. We recommend that you perform a 4diac IDE Type Export once to familiarize yourself with the non-generated implementation portions in the provided `ZephyrIO_fbt.*` sources. In order to sucessfully do this, run the 4diac IDE Type Export Wizard, and leave the "Overwrite with warning" checkbox unselected, plus when asked whether to perform an overwrite or merge, always choose Merge.

In detail, the header file for Zephyr modular IO controller configuration FBs has to be merged with the following non-automatic sections:

- The includes
- The base class specification
- Removing the executeEvent() override
- The section containing number of IOs, setConfig(), and onStartup()


The compilation unit file in turn to be merged with the following non-automatic sections:

- The includes
- The base class specification
- Removing the executeEvent() override
- The section containing setConfig(), and onStartup()

Next, copy the `.FBT` and `_fbt.*` to match your own board, and seek and replace all uses of `ZephyrIO` in the files to match your new name. Verify that export and merge still gives the expected result.

In order to add the actual IOs of your board configuration, you can look at the differences between ZephyrIO and Esp32EthernetKitIO. The latter has a sample set of GPIO input/output, ADC, and PWM, and it should all be sufficiently self explaining if you know your way around developing applications with the Zephyr OS.

