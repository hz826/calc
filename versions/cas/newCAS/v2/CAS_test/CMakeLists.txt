cmake_minimum_required(VERSION 3.17)
project(CAS_test)

set(CMAKE_CXX_STANDARD 11)

add_executable(CAS_test biginteger.cpp rational.cpp poly.cpp main.cpp trig.cpp)