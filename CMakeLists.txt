cmake_minimum_required(VERSION 3.10)

project(invi_a)

add_executable(invi_a main.cpp)

set(CPR_DIR "${CMAKE_SOURCE_DIR}/lib/cpr")

add_subdirectory(${CPR_DIR})

target_link_libraries(invi_a PRIVATE cpr::cpr)
