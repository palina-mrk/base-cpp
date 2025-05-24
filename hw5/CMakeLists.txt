cmake_minimum_required(VERSION 3.5)

project(05.homework)

add_executable(test test.cpp)
set_target_properties(test PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
