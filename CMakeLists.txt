cmake_minimum_required(VERSION 3.6)
project(QuineMccluskey)

set(CMAKE_CXX_STANDARD 14)

if(NOT MSVC)
	set(CMAKE_CXX_FLAGS "/WX- /Wall /Ox /Ob2")
else()
	set(CMAKE_CXX_FLAGS "-pthread -Wall -O3")
endif()

# GTEST paths
add_subdirectory(googletest/googletest)
enable_testing()
set(GTEST_LIBS_DIR ${PROJECT_SOURCE_DIR}/googletest/googletest)

# includes
include_directories(${GTEST_LIBS_DIR}/include)

# project SourceFiles
set(SOURCE_FILES
  src/Term.hpp
  src/QM.hpp)

# test project sourcefiles
set(TEST_SOURCE_FILES
  ${SOURCE_FILES}
  test/main.cpp
  test/QMTest.cpp
  test/TermTest.cpp)

# project executable
## add_executable(QuineMccluskey ${SOURCE_FILES})
add_executable(QuineMccluskeyTest ${TEST_SOURCE_FILES})

set(PROJECT_TEST QuineMccluskeyTest)

# dependency
##add_dependencies(QuineMccluskeyTest googletest)

# linking shared libraries
if(NOT WIN32 OR MINGW)
  target_link_libraries(${PROJECT_TEST}
	${GTEST_LIBS_DIR}/libgtest.a
	${GTEST_LIBS_DIR}/libgtest_main.a)
else()
  target_link_libraries(${PROJECT_TEST}
	debug ${GTEST_LIBS_DIR}/Debug/gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
	optimized ${GTEST_LIBS_DIR}/Release/gtest${CMAKE_FIND_LIBRARY_SUFFIXES})
  target_link_libraries(${PROJECT_TEST}
	debug ${GTEST_LIBS_DIR}/Debug/gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	optimized ${GTEST_LIBS_DIR}/Release/gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES})
endif()

# add test
add_test(${PROJECT_TEST} ${PROJECT_TEST})
