cmake_minimum_required (VERSION 3.0)
project(test)

add_library(test SHARED test.cpp)
add_executable(main main.cpp)
target_link_libraries(main test)
