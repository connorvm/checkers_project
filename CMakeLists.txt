cmake_minimum_required (VERSION 3.2)

project (checkers CXX)

add_executable(checkers checkers.cpp main.cpp)

set_property(TARGET checkers PROPERTY CXX_STANDARD 11)
set_property(TARGET checkers PROPERTY CXX_STANDARD_REQUIRED ON) 