cmake_minimum_required(VERSION "3.5")

project(cpp-plotting-library LANGUAGES CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

include(SFMLSetup.cmake)
set(sfml_libs sfml-graphics sfml-window sfml-system)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    set(PTHREAD "")
    set(X11 "")
    set(CXX_WARNINGS "-Wall")
else()
    set(PTHREAD pthread)
    set(X11     X11)
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

add_compile_definitions(CPT_ABSOLUTE_FONT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data/fonts/")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)

find_package(Doxygen COMPONENTS dot)
if (Doxygen_FOUND)
    set(DOXYGEN_WARN_IF_UNDOCUMENTED "NO")
    set(DOXYGEN_TYPEDEF_HIDES_STRUCT "YES")
    set(DOXYGEN_INCLUDE_GRAPH        "NO")
    doxygen_add_docs(
        doc 
        ${CMAKE_CURRENT_SOURCE_DIR}/src 
        COMMENT "Generate CPT Documentation")
else()
    message(WARNING "Doxygen has not been found and the target \"doc\" could not be generated.")
endif()
