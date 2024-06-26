add_library(FFIFO INTERFACE)
target_include_directories(FFIFO INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)

# BUILD_TESTING variable is created by include(CTest)
# It is set to ON by default
if (BUILD_TESTING)
    enable_testing()
    add_executable(FFIFO_test FFIFO_test.cpp)
    target_link_libraries(FFIFO_test PRIVATE 
                                    GTest::gtest_main
                                    FFIFO)

    include(GoogleTest)
    # Finds all the Google tests associated with the executable
    gtest_discover_tests(FFIFO_test)
endif()