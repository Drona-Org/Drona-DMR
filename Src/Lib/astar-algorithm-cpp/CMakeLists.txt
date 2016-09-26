add_library(stlastar STATIC fsa.h stlastar.h)
set_target_properties(stlastar PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(stlastar PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})