set(plots_sources
    line_plot.cpp
)

add_library(plots-obj OBJECT ${plots_sources})
target_link_libraries(plots-obj ${sfml_libs} pthread)
set_target_properties(plots-obj PROPERTIES POSITION_INDEPENDENT_CODE 1)