cmake_minimum_required (VERSION 2.6)

include_directories()

set(C_INCLUDES ${YOUR_DIRECTORY})

add_definitions(-DPRT_PLAT_LINUXUSER)

project (PingPong)

# The version number.
set (PingPong_VERSION_MAJOR 1)
set (PingPong_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/PingPongConfig.h.in"
  "${PROJECT_BINARY_DIR}/PingPongConfig.h"
  )
 
# add the binary tree to the search path for include files
# so that we will find PingPongConfig.h
include_directories("${PROJECT_BINARY_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/PrtRuntime")
add_subdirectory (PrtRuntime) 
set (EXTRA_LIBS ${EXTRA_LIBS} pthread PrtRuntime)
 
# add the executable
add_executable (PingPong 
                PingPong.c 
                test.c )

target_link_libraries (PingPong ${EXTRA_LIBS})

