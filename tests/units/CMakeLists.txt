include(FetchContent)

message(NOTICE "-- Fetching GoogleTest ...")
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
message(NOTICE "-- GoogleTest setup successful!")

function(ADD_UNIT_TEST NAME)
    add_executable(${NAME}.x ${NAME}.cpp)
    target_link_libraries(${NAME}.x gtest_main)
    include(GoogleTest)
    gtest_discover_tests(${NAME}.x PROPERTIES LABELS units)
endfunction()

ADD_UNIT_TEST(sample_unit_test)
