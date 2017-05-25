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
if(NOT DEFINED yaml-cpp_DIR)
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
      execute_process(COMMAND brew --prefix OUTPUT_VARIABLE HOMEBREW_PREFIX)
      if(DEFINED HOMEBREW_PREFIX)
          find_package(PkgConfig QUIET)
          pkg_check_modules(__yaml-cpp QUIET yaml-cpp)
      endif()
  elseif(UNIX)
      set(yaml-cpp_DIR "/usr/local/share/cmake/")
  endif()
endif()

if(__yaml-cpp_FOUND)
    find_path(yaml-cpp_INCLUDE_DIR yaml-cpp/yaml.h
        HINTS ${__yaml-cpp_INCLUDEDIR}
              ${__yaml-cpp_INCLUDE_DIRS}
        PATH_SUFFIXES yaml-cpp)
    find_library(yaml-cpp_LIBRARY NAMES yaml-cpp libyaml-cpp
        HINTS ${__yaml-cpp_LIBRARY_DIRS}
              ${__yaml-cpp_LIBDIR})
else()
    find_package(yaml-cpp QUIET PATHS 
        ${yaml-cpp_DIR}
        /opt
        /opt/local
        /usr
        /usr/local
        PATH_SUFFIXES
        yaml-cpp
        )
    find_path(yaml-cpp_INCLUDE_DIR yaml-cpp/yaml.h
        PATHS 
        ${yaml-cpp_INCLUDE_DIRS}
        /opt
        /opt/local
        /usr
        /usr/local
        PATH_SUFFIXES 
        yaml-cpp
        include
        inc
        include/yaml-cpp)
    find_library(yaml-cpp_LIBRARY NAMES yaml-cpp libyaml-cpp
        PATHS ${yaml-cpp_LIBRARIES} ${yaml-cpp_INCLUDE_DIR}/..
        /opt
        /opt/local
        /usr
        /usr/local
        PATH_SUFFIXES 
        yaml-cpp
        lib
        lib64
        x86_64-linux-gnu
        lib/x86_64-linux-gnu)
endif()

if(yaml-cpp_LIBRARY)
    get_filename_component(yaml-cpp_LIBRARY_DIR ${yaml-cpp_LIBRARY} PATH)
endif()

set(yaml-cpp_LIBRARIES ${yaml-cpp_LIBRARY})
set(yaml-cpp_INCLUDE_DIRS ${yaml-cpp_INCLUDE_DIR})

if(DEFINED yaml-cpp_LIBRARIES AND yaml-cpp_INCLUDE_DIRS)
    set(yaml-cpp_FOUND TRUE)
endif()

if(yaml-cpp_FOUND)
    message(STATUS "yaml-cpp found")
    message(STATUS "-- yaml-cpp library: ${yaml-cpp_LIBRARIES}")
    message(STATUS "-- yaml-cpp include directory: ${yaml-cpp_INCLUDE_DIRS}\n")
endif()
