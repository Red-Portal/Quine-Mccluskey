cmake_minimum_required(VERSION 3.7)
project(QuineMccluskey)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        src/main.cpp
        src/QM.h
        src/QM.tpp)
add_executable(QuineMccluskey ${SOURCE_FILES})
