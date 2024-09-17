add_library(MA MA.cpp)
target_include_directories(MA PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(MA PRIVATE FFIFO)
# BUILD_TESTING variable is created by include(CTest)
# It is set to ON by default
if (BUILD_TESTING)
    enable_testing()
    add_executable(MA_test MA_test.cpp)
    target_link_libraries(MA_test PRIVATE 
                                    GTest::gtest_main
                                    MA)

    include(GoogleTest)
    # Finds all the Google tests associated with the executable
    gtest_discover_tests(MA_test)
endif()