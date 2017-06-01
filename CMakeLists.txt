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
project(trilinos-build LANGUAGES CXX)

#Options
option(BUILD_Trilinos "Build Trilinos with requred TPLs at configure time." ON)

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

#Find or build Trilinos and TPLs as necessary
include(cmake/OpenCASCADE.cmake)
