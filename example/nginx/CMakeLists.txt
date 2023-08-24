CMAKE_MINIMUM_REQUIRED(VERSION 3.02)
PROJECT(owebpp-example-lib-nginx VERSION 0.0.1)

INCLUDE(../../cmake/common.cmake)

INCLUDE_DIRECTORIES(INCLUDE ./ ../../include)
ADD_LIBRARY(owebpp-example-lib-nginx SHARED
	src/main.cpp)

# Generate code to link owebpp and the example
ADD_CUSTOM_TARGET(owebpp-code-generation
  COMMAND
    owebpp-console generate:code ./example_config.yaml ./include/_owebpp_generated_code.hpp
    VERBATIM)
ADD_DEPENDENCIES(owebpp-example-lib-nginx owebpp-code-generation)

INSTALL(TARGETS owebpp-example-lib-nginx
    LIBRARY DESTINATION lib/owebpp/examples)
INSTALL(FILES nginx.conf html/index.html DESTINATION etc/owebpp-example-lib-nginx/)
