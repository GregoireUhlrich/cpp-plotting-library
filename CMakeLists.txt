cmake_minimum_required(VERSION "3.5")

project(cpp-plotting-library LANGUAGES CXX)

include(SFMLSetup.cmake)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

find_package(Doxygen REQUIRED dot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CXX_WARNINGS
    "-Wall -Wextra -Wpedantic -Wconversion -Werror"
)
set(CMAKE_CXX_FLAGS "${CXX_WARNINGS}")

# Setup testing
set(CMAKE_CXX_FLAGS_COVERAGE "-g -O0 -fprofile-arcs -ftest-coverage")
enable_testing()

if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    set(ENABLE_COVERAGE 1)
else()
    set(ENABLE_COVERAGE 0)
endif()

include_directories(src)
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)

doxygen_add_docs(doc src)
