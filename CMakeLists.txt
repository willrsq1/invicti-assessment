cmake_minimum_required(VERSION 3.10)

project(invi_a)

add_executable(invi_a files/srcs/main.cpp files/srcs/findingLoginPage.cpp files/srcs/getLoginPageData.cpp files/srcs/parsing.cpp)

include(FetchContent)

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git GIT_TAG 871ed52d350214a034f6ef8a3b8f51c5ce1bd400) # The commit hash for 1.9.0. Replace with the latest from: https://github.com/libcpr/cpr/releases

set(CPR_BUILD_TESTS OFF)
set(CPR_BUILD_TESTS_SSL OFF)
set(CPR_GENERATE_COVERAGE OFF)


FetchContent_MakeAvailable(cpr)

target_link_libraries(invi_a PRIVATE cpr::cpr)
