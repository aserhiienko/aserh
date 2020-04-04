cmake_minimum_required(VERSION 3.4.1)

include(ExternalProject)
project(Projects CXX)

message(STATUS "CMAKE_SYSTEM_INFO_FILE = ${CMAKE_SYSTEM_INFO_FILE}")
message(STATUS "CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR = ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "CMAKE_SYSTEM = ${CMAKE_SYSTEM}")
message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_GENERATOR = ${CMAKE_GENERATOR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("/std:c++latest" COMPILER_SUPPORTS_CXXLATEST)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)

if (COMPILER_SUPPORTS_CXXLATEST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
elseif(COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
 set(default_cmake_args -G "${CMAKE_GENERATOR}")

 #
#
# googletest
#
#

ExternalProject_Add(
    googletest
    GIT_REPOSITORY "git@github.com:google/googletest.git"
    GIT_TAG "release-1.10.0"
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/dependencies/googletest"
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CMAKE_ARGS ${default_cmake_args} -Dgtest_force_shared_crt:BOOL=ON
    TEST_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

ExternalProject_Get_Property(googletest SOURCE_DIR)
ExternalProject_Get_Property(googletest BINARY_DIR)
set(googletest_source_dir ${SOURCE_DIR})
set(googletest_binary_dir ${BINARY_DIR})
message(STATUS "googletest_source_dir = ${googletest_source_dir}")
message(STATUS "googletest_binary_dir = ${googletest_binary_dir}")
add_library(
    ProjectsLibrary
    STATIC
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    )
    target_include_directories(
    ProjectsLibrary
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)
add_executable(
    ProjectsTests
    ${CMAKE_SOURCE_DIR}/tests/main.cpp
    )

    target_include_directories(
        ProjectsTests
        PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/tests
        ${CMAKE_SOURCE_DIR}/dependencies/googletest/googlemock/include
        ${CMAKE_SOURCE_DIR}/dependencies/googletest/googletest/include
    )
    add_dependencies(
    ProjectsTests
    ProjectsLibrary
    googletest
)

if (APPLE)

    set(ProjectsTestLibraries
        debug ${CMAKE_BINARY_DIR}/Debug/libProjectsLibrary.a
        debug ${googletest_binary_dir}/lib/Debug/libgmockd.a
        debug ${googletest_binary_dir}/lib/Debug/libgtestd.a
        debug ${googletest_binary_dir}/lib/Debug/libgtest_maind.a
        optimized ${CMAKE_BINARY_DIR}/Release/libProjectsLibrary.a
        optimized ${googletest_binary_dir}/lib/Release/libgmock.a
        optimized ${googletest_binary_dir}/lib/Release/libgtest.a
        optimized ${googletest_binary_dir}/lib/Release/libgtest_main.a
        )
elseif (WIN32)
    set(ProjectsTestLibraries
        debug ${CMAKE_BINARY_DIR}/Debug/ProjectsLibrary.lib
        debug ${googletest_binary_dir}/lib/Debug/gmockd.lib
        debug ${googletest_binary_dir}/lib/Debug/gtestd.lib
        debug ${googletest_binary_dir}/lib/Debug/gtest_maind.lib
        optimized ${CMAKE_BINARY_DIR}/Release/ProjectsLibrary.lib
        optimized ${googletest_binary_dir}/lib/Release/gmock.lib
        optimized ${googletest_binary_dir}/lib/Release/gtest.lib
        optimized ${googletest_binary_dir}/lib/Release/gtest_main.lib
        )
endif()

target_link_libraries(
    ProjectsTests
    ${ProjectsTestLibraries}
    )
   
    