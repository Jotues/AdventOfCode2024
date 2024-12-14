cmake_minimum_required(VERSION 3.0.0)
project(AdventOfCode2024 VERSION 0.1.0 LANGUAGES CXX)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)
target_compile_options(compiler_flags INTERFACE -Wall -Wextra -Wshadow -Wformat=2 -Wpedantic)

include(CTest)
enable_testing()

add_subdirectory(utils)

add_executable(day01 day01.cpp)
target_link_libraries(day01 utils compiler_flags)
target_include_directories(day01 PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(day02 day02.cpp)
target_link_libraries(day02 utils compiler_flags)
target_include_directories(day02 PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(day03 day03.cpp)
target_link_libraries(day03 utils compiler_flags)
target_include_directories(day03 PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(day04 day04.cpp)
target_link_libraries(day04 utils compiler_flags)
target_include_directories(day04 PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(day05 day05.cpp)
target_link_libraries(day05 utils compiler_flags)
target_include_directories(day05 PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(day06 day06.cpp)
target_link_libraries(day06 utils compiler_flags)
target_include_directories(day06 PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(day07 day07.cpp)
target_link_libraries(day07 utils compiler_flags)
target_include_directories(day07 PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(day08 day08.cpp)
target_link_libraries(day08 utils compiler_flags)
target_include_directories(day08 PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(day09 day09.cpp)
target_link_libraries(day09 utils compiler_flags)
target_include_directories(day09 PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(day10 day10.cpp)
target_link_libraries(day10 utils compiler_flags)
target_include_directories(day10 PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(day11 day11.cpp)
target_link_libraries(day11 utils compiler_flags)
target_include_directories(day11 PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(day12 day12.cpp)
target_link_libraries(day12 utils compiler_flags)
target_include_directories(day12 PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(day13 day13.cpp)
target_link_libraries(day13 utils compiler_flags)
target_include_directories(day13 PUBLIC "${PROJECT_BINARY_DIR}")

add_executable(day14 day14.cpp)
target_link_libraries(day14 utils compiler_flags)
target_include_directories(day14 PUBLIC "${PROJECT_BINARY_DIR}")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
