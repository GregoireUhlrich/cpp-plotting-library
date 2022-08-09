set(sfml_libs sfml-graphics sfml-window sfml-system)

add_library(cpt SHARED)
target_link_libraries(cpt plotter-obj X11 ${sfml_libs} pthread)

add_library(cpt-static STATIC)
target_link_libraries(cpt-static plotter-obj X11 ${sfml_libs} pthread)

add_subdirectory(utils)
add_subdirectory(math_views)
add_subdirectory(plotter)