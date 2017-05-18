cmake_minimum_required(VERSION 3.0.0)
project(mybot)

# Add compiler warnings
set(COMPILER_WARNINGS "-W -Wall -Wextra -Wno-unused-parameter -Wno-comment")

if(NOT SOURCES)
    message(FATAL_ERROR "Cannot find sources! Aborting...")
endif()

# Optimizations
if(NATIVE STREQUAL "no" OR NOT NATIVE)
    set(NATIVE "")
elseif(NATIVE STREQUAL "yes")
    set(NATIVE "-march=native -mtune=native")
endif()

if(NOT OPTIMIZATION_LEVEL OR OPTIMIZATION_LEVEL STREQUAL "no")
    set(OPTIMIZATION_LEVEL "")
else()
    set(OPTIMIZATION_LEVEL "-O${OPTIMIZATION_LEVEL}")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED on)
    set(CMAKE_CXX_FLAGS "-pthread")
    set(CMAKE_CXX_FLAGS_RELEASE
        "${OPTIMIZATION_LEVEL} ${NATIVE} ${ARCH} ${COMPILER_WARNINGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "-g ${COMPILER_WARNINGS} -ggdb")
endif()

add_subdirectory(opt/cppgram)

add_executable(mybot SOURCES)
target_link_libraries(mybot ${CPPGRAM_LIBRARIES})
include_directories(${CPPGRAM_INCLUDE})
