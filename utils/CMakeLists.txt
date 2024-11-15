add_library(utils utils_time.cpp utils.cpp geometry.cpp)
target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(utils PUBLIC compiler_flags)