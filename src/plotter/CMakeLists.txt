add_subdirectory(internal)

set(plotter_sources 
    figure.cpp
)

add_library(plotter-obj OBJECT ${plotter_sources})
target_link_libraries(plotter-obj ${sfml_libs} pthread)
set_target_properties(plotter-obj PROPERTIES POSITION_INDEPENDENT_CODE 1)