set(api_sources
    session.cpp
    figure.cpp
    subplot.cpp
    ticks.cpp
    grid_layout.cpp
    axis.cpp
)

add_library(api-obj OBJECT ${api_sources})
target_link_libraries(api-obj ${sfml_libs} ${PTHREAD})
set_target_properties(api-obj PROPERTIES POSITION_INDEPENDENT_CODE 1)
