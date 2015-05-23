cmake_minimum_required(VERSION 2.6)

# include dir
include_directories(${CMAKE_SOURCE_DIR}/../src)
include_directories(${CMAKE_SOURCE_DIR}/../obj)



option(SYLVAN_OPERATION_STATS "Create operation statistics" OFF)
option(SYLVAN_CACHE_STATS "Create cache statistics" OFF)

include(CheckIncludeFiles)
check_include_files(hwloc.h HAVE_HWLOC)
if(HAVE_HWLOC)
    set(EXTRA_LIBS ${EXTRA_LIBS} hwloc)
    set(HWLOC_DEF "USE_HWLOC=1")
else()
    set(HWLOC_DEF "USE_HWLOC=0")
endif()

check_include_files("gperftools/profiler.h" HAVE_PROFILER)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # add argp library for OSX
    set(ARGP_LIBS "argp")
endif()

set(CMAKE_CXX_FLAGS "-fpermissive -D${HWLOC_DEF}")

add_executable(Main main.cpp)

target_link_libraries(Main ${CMAKE_SOURCE_DIR}/../build/libsylvan.a m pthread  ${EXTRA_LIBS})
