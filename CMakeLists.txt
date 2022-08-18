cmake_minimum_required(VERSION "3.5")

project(cpp-plotting-library LANGUAGES CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

include(SFMLSetup.cmake)

message(NOTICE "-- Fetching GoogleTest ...")
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
message(NOTICE "-- GoogleTest setup successful!")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    set(PTHREAD "")
    set(X11 "")
    set(CXX_WARNINGS "")
    set(CMAKE_CXX_FLAGS "/EHsc")
else()
    set(PTHREAD pthread)
    set(X11     x11)
    set(CXX_WARNINGS
        "-Wall -Wextra -Wpedantic -Wconversion"
    )
endif()

set(CMAKE_CXX_FLAGS "${CXX_WARNINGS}")

# Setup testing
set(CMAKE_CXX_FLAGS_COVERAGE "-g -O0 -fprofile-arcs -ftest-coverage")
enable_testing()

if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    set(ENABLE_COVERAGE 1)
else()
    set(ENABLE_COVERAGE 0)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)

find_package(Doxygen COMPONENTS dot)
if (Doxygen_FOUND)
    doxygen_add_docs(doc src)
else()
    message(WARNING "Doxygen has not been found and the target \"doc\" could not be generated.")
endif()
