cmake_minimum_required(VERSION 3.5)

project(main)

add_executable(main main.cpp containers.h containers.ipp test.h)
set_target_properties(main PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
