set(SRC Astar.cpp MotionPrimitives.cpp PlanGenerator.cpp PrimitiveParser.cpp)

add_library(plan_generator SHARED ${SRC})

target_include_directories(plan_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(plan_generator workspace_parser)
