add_executable(simple_window simple_window.cpp)
target_link_libraries(simple_window sfml-graphics sfml-window sfml-system)

add_executable(plot_view plot_view.cpp)
target_link_libraries(plot_view sfml-graphics sfml-window sfml-system)

add_executable(sample_error sample_error.cpp)
target_link_libraries(sample_error sfml-graphics sfml-window sfml-system)

add_executable(sample_array sample_array.cpp)
target_link_libraries(sample_array sfml-graphics sfml-window sfml-system)
