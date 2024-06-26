add_library(PT_ROBUST PT_ROBUST.cpp)
target_include_directories(PT_ROBUST PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(PT_ROBUST PRIVATE FFIFO)
# BUILD_TESTING variable is created by include(CTest)
# It is set to ON by default
if (BUILD_TESTING)
    enable_testing()
    add_executable(PT_ROBUST_test PT_ROBUST_test.cpp)
    target_link_libraries(PT_ROBUST_test PRIVATE 
                                    GTest::gtest_main
                                    PT_ROBUST)

    include(GoogleTest)
    # Finds all the Google tests associated with the executable
    gtest_discover_tests(PT_ROBUST_test)
endif()