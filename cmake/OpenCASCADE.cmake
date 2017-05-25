# Copyright 2017 John T. Foster

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#    http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#If all TPLs are requested, this implies building OpenCASCADE
if(BUILD_ALL_TPS)
    set(BUILD_OpenCASCADE TRUE)
endif()

#If BUILD_OpenCASACADE=OFF we need to look for a OpenCASCADE installation
if(NOT BUILD_OpenCASCADE)
    find_package(OpenCASCADE QUIET COMPONENTS TKernel TKG3d TKXSBase TKBRep TKTopAlgo TKIGES TKMath)
message(STATUS "-- OpenCASCADE include directory: ${OpenCASCADE_INCLUDE_DIRS}")
message(STATUS "-- OpenCASCADE libraries: ${OpenCASCADE_LIBRARIES}")
    if(OpenCASCADE_FOUND)
        message(STATUS "OpenCASCADE/OCC found!")
    endif()
endif()

if(NOT OpenCASCADE_FOUND OR BUILD_OpenCASCADE)
    message(STATUS "Download, configure, and build OpenCASCADE Community Edition libraries")
    configure_file(cmake/OpenCASCADE-build.cmake.in oce-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/oce-download)
    execute_process(COMMAND ${CMAKE_COMMAND} --build .  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/oce-download)
    find_package(OpenCASCADE REQUIRED COMPONENTS TKernel)
    message(STATUS "OpenCASCADE Community Edition built successfully.\n")
endif()

message(STATUS "-- OpenCASCADE include directory: ${OpenCASCADE_INCLUDE_DIRS}")
message(STATUS "-- OpenCASCADE libraries: ${OpenCASCADE_LIBRARIES}")

add_library(opencascade INTERFACE IMPORTED)
set_property(TARGET opencascade PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${OpenCASCADE_INCLUDE_DIRS})
set_property(TARGET opencascade PROPERTY
    INTERFACE_LINK_LIBRARIES ${OpenCASCADE_LIBRARIES})
