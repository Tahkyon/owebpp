CMAKE_MINIMUM_REQUIRED(VERSION 3.02)
PROJECT(owebpp-console VERSION 0.0.1)

INCLUDE_DIRECTORIES(INCLUDE ./include ../include)
ADD_EXECUTABLE(owebpp-console
	src/Generation/RouteCodeGenerator.cpp
	src/main.cpp)

target_link_libraries(owebpp-console -lyaml-cpp)

INSTALL(PROGRAMS owebpp-console DESTINATION bin)
