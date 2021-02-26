### CMake setup for the measurement unit test executable
###############################################################################
find_package(GTest CONFIG REQUIRED)

enable_testing()

SET(UNITTESTS_CXX_FILES
    sampleTest.cpp
    )

# -----------------------------------------------------------------------------

SET(UNITTESTS_HEADER_FILES
    )

# -----------------------------------------------------------------------------

add_executable(unit_tests
    ${UNITTESTS_CXX_FILES}
    ${UNITTESTS_HEADER_FILES}
    )


target_link_libraries(unit_tests PUBLIC
    DepthCameraSandbox
    GTest::gtest
    GTest::gtest_main
    )

target_include_directories(unit_tests PRIVATE ../include)

SET_TARGET_PROPERTIES(unit_tests PROPERTIES
    FOLDER "tests"
    )

add_test(NAME unit_tests COMMAND unit_tests)
