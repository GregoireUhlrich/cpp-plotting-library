if(ENABLE_COVERAGE)
    include(CodeCoverage.cmake)
endif()

add_subdirectory(units)

if(ENABLE_COVERAGE)
    set(UNIT_TEST_LABEL "units")
    SETUP_TARGET_FOR_COVERAGE(${UNIT_TEST_LABEL})
endif()
