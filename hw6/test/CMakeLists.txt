cmake_minimum_required(VERSION 3.5)

project(test)

add_executable(test test.cpp containers.h)
set_target_properties(test PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
