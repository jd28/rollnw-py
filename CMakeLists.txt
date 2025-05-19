cmake_minimum_required(VERSION 3.15)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)

include(cmake/Cache.cmake)
include(cmake/Sanitizers.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(ROLLNW_PY_BUILD_DOCS "Build documentation" OFF)

find_package(Python 3.10
  REQUIRED COMPONENTS Interpreter Development.Module
  OPTIONAL_COMPONENTS Development.SABIModule)

set(ROLLNW_BUILD_PYTHON ON)
add_subdirectory(external/rollnw)
add_subdirectory(external/nanobind)
add_subdirectory(src)

if(ROLLNW_PY_BUILD_DOCS)
add_subdirectory(docs)
endif()
