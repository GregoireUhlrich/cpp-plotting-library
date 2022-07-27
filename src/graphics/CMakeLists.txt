cmake_minimum_required(VERSION 3.5)

find_package(SFML 2.5.1 COMPONENTS system graphics audio network REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

set(SFML_LIBS sfml-graphics sfml-window sfml-system)

set(GUI_SOURCES
    pad.hpp)

add_library(graphics-obj OBJECT ${GUI_SOURCES})
target_link_libraries(graphics-obj PRIVATE ${SFML_LIBS})
set_property(TARGET graphics-obj PROPERTY POSITION_INDEPENDENT_CODE 1)
