cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
set(ROS_BUILD_TYPE Debug)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

include($ENV{ROS_ROOT}/core/rosbuild/FindPkgConfig.cmake)
pkg_search_module(SBPL REQUIRED sbpl)
include_directories(${SBPL_INCLUDE_DIRS})
link_directories(${SBPL_LIBRARY_DIRS})

include_directories(/usr/local/include)
include_directories(/opt/local/include)
link_directories(/opt/local/lib) 
link_directories(/usr/local/lib) 

rosbuild_add_boost_directories()
rosbuild_add_library(env src/environment_quad.cpp)
target_link_libraries(env ${SBPL_LIBRARIES} yaml-cpp)
rosbuild_link_boost(env thread)
rosbuild_add_executable(nav src/navigate.cpp)
target_link_libraries(nav env ${SBPL_LIBRARIES})
rosbuild_add_executable(path_pub src/path_publishing.cpp)
target_link_libraries(path_pub env ${SBPL_LIBRARIES})
#rosbuild_add_executable(map_visual src/map_visual.cpp)
#target_link_libraries(map_visual env ${SBPL_LIBRARIES})
rosbuild_add_executable(test_waypoints src/test_waypoints.cpp)
