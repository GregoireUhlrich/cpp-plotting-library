set(cpt_libs 
    api-obj 
    graphics-obj 
    plots-obj)
    
add_library(cpt STATIC)
target_link_libraries(cpt ${cpt_libs} ${X11} ${sfml_libs} ${PTHREAD})

add_subdirectory(utils)
add_subdirectory(math_views)
add_subdirectory(plots)
add_subdirectory(graphics)
add_subdirectory(api)