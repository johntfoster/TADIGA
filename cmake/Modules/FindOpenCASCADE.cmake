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
if(NOT DEFINED OpenCASCADE_DIR)
    #Check if MacOS is operating system
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        #See if Homebrew is installed 
        execute_process(COMMAND brew --prefix OUTPUT_VARIABLE HOMEBREW_PREFIX)
        mark_as_advanced(HOMEBREW_PREFIX)
        if(DEFINED HOMEBREW_PREFIX)
            set(OpenCASCADE_DIR "${HOMEBREW_PREFIX}/Cellar/opencascade/*/")
        endif()
    endif()
endif()


find_path(OpenCASCADE_INCLUDE_DIRS Standard_Version.hxx
          PATHS ${OpenCASCADE_DIR} 
                /opt
                /opt/local
                /usr
                /usr/local
                ${CMAKE_CURRENT_BINARY_DIR}/oce-build
                PATH_SUFFIXES 
                include
                inc
                include/oce
                include/occ
                include/opencascade
                opencascade oce occ)

if(OpenCASCADE_INCLUDE_DIRS STREQUAL Standard_Version.hxx-NOTFOUND)
    unset(OpenCASCADE_INCLUDE_DIRS)
else()
    if(DEFINED OpenCASCADE_FIND_COMPONENTS)
        foreach(library ${OpenCASCADE_FIND_COMPONENTS})
            find_library(${library}_LIB ${library}
                PATHS ${OpenCASCADE_INCLUDE_DIRS}/..
                      ${OpenCASCADE_INCLUDE_DIRS}/../..
                      /usr
                PATH_SUFFIXES lib lib64 x86_64-linux-gnu lib/x86_64-linux-gnu)
            mark_as_advanced(${library}_LIB)
            if(${${library}_LIB} STREQUAL ${${library}_LIB}-NOTFOUND)
                unset(OpenCASCADE_LIBRARIES)
            else()
                set(OpenCASCADE_LIBRARIES ${OpenCASCADE_LIBRARIES} ${${library}_LIB})
            endif()
        endforeach()
    else()
        message(FATAL_ERROR "OpenCASCADE required components must be specified individually, 
                             OpenCASCADE is too large to link all libraries.")
    endif()
endif()


if(DEFINED OpenCASCADE_INCLUDE_DIRS AND DEFINED OpenCASCADE_LIBRARIES)
    set(OpenCASCADE_FOUND TRUE)
endif()

