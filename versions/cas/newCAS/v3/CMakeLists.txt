cmake_minimum_required(VERSION 3.17)
project(v3)

set(CMAKE_CXX_STANDARD 11)

add_executable(v3 main.cpp rational.cpp poly.cpp trig.cpp factor.cpp radicalextension.cpp)