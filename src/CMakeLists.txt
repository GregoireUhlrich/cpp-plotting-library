set(sfml_libs sfml-graphics sfml-window sfml-system)

set(cpt_libs 
    interface-obj 
    graphics-obj 
    plots-obj)
    
add_library(cpt SHARED)
target_link_libraries(cpt ${cpt_libs} X11 ${sfml_libs} pthread)

add_library(cpt-static STATIC)
target_link_libraries(cpt-static ${cpt_libs} X11 ${sfml_libs} pthread)

add_subdirectory(utils)
add_subdirectory(math_views)
add_subdirectory(plots)
add_subdirectory(graphics)
add_subdirectory(interface)