cmake_minimum_required(VERSION 3.30)
project(AlgebraChecker)

set(CMAKE_CXX_STANDARD 26)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")
set(SOURCE_FILES main.cpp)
add_executable(AlgebraChecker ${SOURCE_FILES})
