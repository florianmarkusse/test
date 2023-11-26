cmake_minimum_required(VERSION 3.18)
project(test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

### Options ###
option(BUILD_SHARED_LIBS "Build shared libraries instead of static libraries" OFF)
option(CMAKE_BUILD_TYPE "Build type (Debug, Release, Profiling)" "Release")
option(BUILD_TESTS "Build the test executable" OFF)

### Flags ###
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wconversion -Wno-sign-conversion -Wno-missing-field-initializers -Wdouble-promotion -Wvla -W")

if (CMAKE_BUILD_TYPE STREQUAL "Profiling")
    SET(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
endif()

set(FLO_TEST_LIBRARY "${PROJECT_NAME}-${CMAKE_BUILD_TYPE}")

if(BUILD_SHARED_LIBS)
    set(LIBRARY_TYPE "SHARED")
else()
    set(LIBRARY_TYPE "STATIC")
endif()

add_library(${FLO_TEST_LIBRARY} ${LIBRARY_TYPE}
    "src/test.c"
)

set(FLO_TEST_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
target_include_directories(${FLO_TEST_LIBRARY} PRIVATE ${FLO_TEST_INCLUDES})

# Libraries
set(LIBRARY_DIR ${CMAKE_SOURCE_DIR}/libs)
target_include_directories(${FLO_TEST_LIBRARY} PRIVATE ${LIBRARY_DIR}/util/include)

target_link_libraries(${FLO_TEST_LIBRARY} PRIVATE ${LIBRARY_DIR}/util/build/libutil-Release.a)

target_compile_options(${FLO_TEST_LIBRARY} PRIVATE
    $<$<CONFIG:Debug>:-O0 -g3>
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Profiling>:-O2 -pg>
)

target_compile_definitions(${FLO_TEST_LIBRARY} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:>
    $<$<CONFIG:Profiling>:>
)

if("${BUILD_TESTS}" AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    add_subdirectory(tests)
endif()

