CMAKE_MINIMUM_REQUIRED(VERSION 3.02)
PROJECT(owebpp-console VERSION 0.0.1)

INCLUDE(../../cmake/common.cmake)

INCLUDE_DIRECTORIES(INCLUDE ./include)
ADD_EXECUTABLE(owebpp-translation
	src/main.cpp)
