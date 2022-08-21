set(api_sources
    figure.cpp
    subplot.cpp
    axis.cpp
    ticks.cpp
    grid_layout.cpp
)

add_library(api-obj OBJECT ${api_sources})
target_link_libraries(api-obj ${sfml_libs} ${PTHREAD})
set_target_properties(api-obj PROPERTIES POSITION_INDEPENDENT_CODE 1)