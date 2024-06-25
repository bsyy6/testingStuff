# CMakeLists.txt
cmake_minimum_required( VERSION 3.16 )
project( PT_ROBUST VERSION 0.0.1
                    DESCRIPTION "first"
                    LANGUAGES CXX)
include(CTest)
enable_testing()
add_subdirectory(${PROJECT_NAME})
add_subdirectory(example)
add_subdirectory(external)
