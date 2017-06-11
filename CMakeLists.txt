cmake_minimum_required(VERSION 3.6)
project(QuineMccluskey)

set(CMAKE_CXX_STANDARD 14)

if(MSVC)
	set(CMAKE_CXX_FLAGS "/WX- /Wall /O2 /Ob2")
else()
	set(CMAKE_CXX_FLAGS "-pthread -Wall -O3")
endif()

set(EXAMPLES ${PROJECT_SOURCE_DIR}/examples)

# source directories
set(SOURCE_FILES
  include/Term.hpp
  include/QM.hpp
  ${EXAMPLES}/main.cpp) 

add_executable(QuineMccluskey ${SOURCE_FILES})


