cmake_minimum_required(VERSION 3.28)
project(Checkers)

set(CMAKE_CXX_STANDARD 20)

set (JAVA_HOME "/Users/alieksieiev/Library/Java/JavaVirtualMachines/openjdk-22.0.1/Contents/Home")
include_directories(${JAVA_HOME}/include)
include_directories(${JAVA_HOME}/include/darwin)

add_library(Checkers SHARED library.cpp Board.cpp
        CheckersJNI.h
        SelectedCell.cpp)
