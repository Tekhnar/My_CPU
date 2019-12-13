cmake_minimum_required(VERSION 3.15)
project(processor)

set(CMAKE_CXX_STANDARD 14)

add_executable(processor main.cpp my_stack.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(TXLIN REQUIRED txlin)
target_link_libraries(processor ${TXLIN_LIBRARIES})
target_include_directories(processor PUBLIC ${TXLIN_INCLUDE_DIRS})
target_compile_options(processor PUBLIC ${TXLIN_CFLAGS_OTHER})