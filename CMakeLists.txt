# Copyright 2016-2017 John T. Foster

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#    http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
cmake_minimum_required(VERSION 2.8)
project(tadiga LANGUAGES CXX)
enable_testing()

message(STATUS "the compiler string is: ${CMAKE_C_COMPILER_ID}")

#Options
option(BUILD_Trilinos "Build Trilinos with requred TPLs at configure time." OFF)
option(BUILD_OpenCASCADE "Build OpenCASCADE at configure time." OFF)
option(BUILD_ALL_TPLs "Build all required TPLs at configure time." OFF)
option(COVERAGE "Turn on code coverage reporting" OFF)

#If MPI is found, use the libraries
find_package(MPI)
if(MPI_CXX_FOUND)
add_library(mpi INTERFACE IMPORTED)
set_property(TARGET mpi PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${MPI_CXX_INCLUDE_PATH})
set_property(TARGET mpi PROPERTY
    INTERFACE_LINK_LIBRARIES ${MPI_CXX_LIBRARIES})
endif()

#Add module paths
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/coveralls-cmake/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})

#Find or build Trilinos and OpenCASCADE with TPLs as necessary
include(cmake/Trilinos.cmake)
include(cmake/OpenCASCADE.cmake)


#Turn on coveralls code coverage upload
if(COVERAGE)
  include(CodeCoverage)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
  setup_target_for_coverage(coverage ctest coverage)
endif()

add_subdirectory(src)
