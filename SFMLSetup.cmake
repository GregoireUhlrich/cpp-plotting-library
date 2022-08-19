message(NOTICE "-- Fetching SFML ...")

function(set_sfml_module_properties NAME)
    set_target_properties(${NAME} PROPERTIES CXX_STANDARD 98 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
endfunction()

# Uncomment and use when shared libs will be enabled
#if(BUILD_SFML_SHARED_LIBS)
#    set(BUILD_SHARED_LIBS ${BUILD_SHARED_SFML_LIBS})
#else()
#    set(BUILD_SHARED_LIBS 0)
#endif()

set(BUILD_SHARED_LIBS 0)

include(FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(sfml)

set_sfml_module_properties(sfml-system)
set_sfml_module_properties(sfml-window)
set_sfml_module_properties(sfml-graphics)
set_sfml_module_properties(sfml-network)
set_sfml_module_properties(sfml-audio)

message(NOTICE "-- SFML setup successful!")
