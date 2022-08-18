set(interface_sources
    figure.cpp
    subplot.cpp
    axis.cpp
    ticks.cpp
    grid_layout.cpp
)

add_library(interface-obj OBJECT ${interface_sources})
target_link_libraries(interface-obj ${sfml_libs} ${PTHREAD})
set_target_properties(interface-obj PROPERTIES POSITION_INDEPENDENT_CODE 1)