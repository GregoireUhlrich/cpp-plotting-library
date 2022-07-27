cmake_minimum_required(VERSION 3.5)

set(GEOMETRY_SOURCES
    point.hpp
    angle.hpp)

add_library(geometry-obj OBJECT ${GEOMETRY_SOURCES})
target_link_libraries(geometry-obj)
set_property(TARGET geometry-obj PROPERTY POSITION_INDEPENDENT_CODE 1)