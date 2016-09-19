set(SRC WorkspaceParser.cpp tinyxml2.cpp)

add_library(workspace_parser SHARED ${SRC})

target_include_directories(workspace_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
