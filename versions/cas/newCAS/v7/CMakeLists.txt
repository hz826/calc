cmake_minimum_required(VERSION 3.17)
project(v7)

set(CMAKE_CXX_STANDARD 11)

add_executable(v7 main.cpp biginteger.cpp rational.cpp poly.cpp trig.cpp factor.cpp radicalextension.cpp expr.cpp reader.cpp)