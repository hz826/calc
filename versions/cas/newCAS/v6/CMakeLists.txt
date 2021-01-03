cmake_minimum_required(VERSION 3.17)
project(v6)

set(CMAKE_CXX_STANDARD 11)

add_executable(v6 main.cpp biginteger.cpp rational.cpp poly.cpp trig.cpp factor.cpp radicalextension.cpp expr.cpp)