cmake_minimum_required(VERSION 3.7)
project(QuineMccluskey)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
		src/Term.hpp
		src/Term.cpp
        #src/QM.hpp
        #src/QM.cpp
        src/main.cpp)

add_executable(QuineMccluskey ${SOURCE_FILES})
