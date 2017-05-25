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

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE Tadiga_GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
mark_as_advanced(Tadiga_GIT_COMMIT_HASH)

# Pass version info to source code
configure_file(
  ${PROJECT_SOURCE_DIR}/src/tadiga_version.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/src/tadiga_version.h
)

set(Tadiga_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/tadiga.cc
    ${CMAKE_CURRENT_LIST_DIR}/tadiga_IGES_geometry.cc
    ${CMAKE_CURRENT_LIST_DIR}/tadiga_factory.cc
    ${CMAKE_CURRENT_LIST_DIR}/tadiga_parser.cc
    ${CMAKE_CURRENT_LIST_DIR}/tadiga_geometry.cc
    ${CMAKE_CURRENT_LIST_DIR}/tadiga_geometry_factory.cc
)
mark_as_advanced(Tadiga_SOURCES)


add_library(tadiga_library ${Tadiga_SOURCES})
target_link_libraries(tadiga_library PRIVATE trilinos opencascade)
if(MPI_FOUND)
    target_link_libraries(tadiga_library PRIVATE mpi)
endif()
set_property(TARGET tadiga_library PROPERTY OUTPUT_NAME tadiga)
target_sources(tadiga_library PUBLIC ${Tadiga_SOURCES})
target_include_directories(tadiga_library PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_compile_features(tadiga_library PUBLIC cxx_auto_type)

#
# Link the main Tadiga executable
#
add_executable(tadiga tadiga_main.cc)
target_include_directories(tadiga PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src)
target_link_libraries(tadiga tadiga_library)

#
# Install target for Tadiga main executable
#
install(TARGETS tadiga 
    RUNTIME DESTINATION bin
)

add_subdirectory(test)
