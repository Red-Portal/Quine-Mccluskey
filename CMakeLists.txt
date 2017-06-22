cmake_minimum_required(VERSION 3.6)
project(QuineMccluskeyExample)


set(CMAKE_CXX_STANDARD 14)

if(MSVC)
	set(CMAKE_CXX_FLAGS "/WX- /Wall /O2 /Ob2")
else()
	set(CMAKE_CXX_FLAGS "-pthread -Wall -O3")
endif()

# header only library dependency (boost dynamic_bitset)
add_library(dynamic_bitset INTERFACE)
target_include_directories(dynamic_bitset INTERFACE include/dynamic_bitset/include/)

# header only libary dependency (boost config)
add_library(dynamic_bitset INTERFACE)
target_include_directories(boost_config INTERFACE include/boost_config/include/)

# header only library
add_library(QuineMccluskey INTERFACE)
target_include_directories(QuineMccluskey INTERFACE include/)

# example project source directories
set(EXAMPLES ${PROJECT_SOURCE_DIR}/examples)

set(SOURCE_FILES
  ${EXAMPLES}/main.cpp) 

add_executable(QuineMccluskeyExample ${SOURCE_FILES})
target_link_libraries(QuineMccluskeyExample dynamic_bitset QuineMccluskey)
