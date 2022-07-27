cmake_minimum_required(VERSION "3.5")

project(cpp-plotting-library LANGUAGES CXX)

include(SFMLSetup.cmake)

find_package(Doxygen REQUIRED dot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CXX_WARNINGS
    "-Wall -Wextra -Wpedantic -Wconversion -Werror"
)
set(CMAKE_CXX_FLAGS "${CXX_WARNINGS}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(src)
add_subdirectory(examples)

doxygen_add_docs(doc src)
