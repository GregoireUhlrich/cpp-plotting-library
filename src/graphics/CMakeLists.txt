add_subdirectory(internal)

set(graphics_sources
    figure_window.cpp
    subplot_texture.cpp
    plot_canvas.cpp
)

add_library(graphics-obj OBJECT ${graphics_sources})
target_link_libraries(graphics-obj ${sfml_libs} ${PTHREAD})
set_target_properties(graphics-obj PROPERTIES POSITION_INDEPENDENT_CODE 1)