add_executable(simple_window simple_window.cpp)
add_executable(plot_build plot_build.cpp)

target_link_libraries(simple_window sfml-graphics sfml-window sfml-system)
target_link_libraries(plot_build
    PUBLIC graphics-obj
    PRIVATE sfml-graphics sfml-window sfml-system)
