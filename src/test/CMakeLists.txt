find_package(ament_cmake_gtest REQUIRED)
include(GoogleTest) 

# Add the test executable to the project
ament_add_gtest_executable(run_test test.cpp)
ament_add_gtest_executable(run_test_intensity test_intensity.cpp)

# Link the test executable with the library and gtest
target_link_libraries(run_test plycpp gtest_main pthread)
target_link_libraries(run_test_intensity plycpp gtest_main pthread)

# Add a test target
gtest_discover_tests(run_test_intensity)
gtest_discover_tests(run_test)

install(TARGETS run_test_intensity
    DESTINATION bin/${PROJECT_NAME}
)
install(TARGETS run_test
    DESTINATION bin/${PROJECT_NAME}
)

# Add the directory containing the header files for the test fixtures
target_include_directories(run_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(run_test_intensity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
