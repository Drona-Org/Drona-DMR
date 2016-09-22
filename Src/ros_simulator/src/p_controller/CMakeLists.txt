cmake_minimum_required(VERSION 2.8.3)
project(p_controller)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  quadrotor_msgs
  roscpp
  rospy
  std_msgs
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PCompile.cmake)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   quadrotor_msgs#   std_msgs
# )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES p_controller
  CATKIN_DEPENDS quadrotor_msgs roscpp rospy std_msgs
  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(p_ros src/InitRos.cpp src/ModelFunctions.cpp)

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(p_controller ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_subdirectory(../../../Lib/PlanGenerator ${CMAKE_BINARY_DIR}/PlanGenerator)

## Compile P source
set(P_COMPILER_PATH ${CMAKE_SOURCE_DIR}/../../../Submodules/P/Bld/Drops/Debug/x86/Binaries/Pc.exe)
set(P_BUILT_LIB_PATH ${CMAKE_SOURCE_DIR}/../../../Submodules/P/Bld/Drops/PrtUser)
set(P_LIB_INCLUDE_PATH ${P_BUILT_LIB_PATH}/include)
set(P_LIB_LINK_PATH ${P_BUILT_LIB_PATH}/lib)

set(test_plan_executor_dir src/test_plan_executor)
get_filename_component(test_motion_planner_dir src/TestMotionPlanner REALPATH)

p_compile(TestPlanExecutor src/test_plan_executor/StubMotionPlanner.p)

p_compile(TestMotionPlaner ${test_motion_planner_dir}/TestDriver.p)

target_include_directories(p_ros PRIVATE 
  ../../../Lib/Compat
  ${P_LIB_INCLUDE_PATH}
)

## Declare a C++ executable
add_executable(test_plan_executor 
  ${TestPlanExecutor_GENERATED_SRCS} 
  ${test_plan_executor_dir}/tester.c 
  ${test_plan_executor_dir}/Constructors.c 
)
set_property(TARGET test_plan_executor PROPERTY C_STANDARD 99)
target_include_directories(test_plan_executor PRIVATE 
  ../../../Lib/Compat
  ${TestPlanExecutor_INCLUDE_DIRS}
)

add_executable(test_motion_planner 
  ${TestMotionPlaner_GENERATED_SRCS} 
  ${test_motion_planner_dir}/tester.c 
  ${test_motion_planner_dir}/Constructors.c
  ${test_motion_planner_dir}/HelperFunctions.cpp
  ${test_motion_planner_dir}/../../SoftwareStack/Utilities/Timer/Timer.c
)
set_property(TARGET test_motion_planner PROPERTY C_STANDARD 99)
target_include_directories(test_motion_planner PRIVATE 
  ../../../Lib/Compat
  ${TestMotionPlaner_INCLUDE_DIRS}
)
# target_compile_definitions(test_motion_planner PRIVATE -DUSE_EMPTY)

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(p_ros ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(test_plan_executor ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(test_motion_planner ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(p_ros
  workspace_parser
  goto_solver
  Prt
  ${catkin_LIBRARIES}
)

target_link_libraries(test_plan_executor
  p_ros
  ${TestPlanExecutor_LINK_LIBS}
  ${catkin_LIBRARIES}
)

target_link_libraries(test_motion_planner
  p_ros
  plan_generator
  ${TestMotionPlaner_LINK_LIBS}
  ${catkin_LIBRARIES}
)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS p_controller p_controller_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_p_controller.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
