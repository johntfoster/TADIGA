# Copyright 2016-2017 John T. Foster, Katy R. Hanson

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#    http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
add_library(tadiga_standard_test ./tadiga_standard_test_main.cc)
target_link_libraries(tadiga_standard_test PUBLIC tadiga_library)

add_executable(tadiga_parser_test ./tadiga_parser_test.cc)
target_link_libraries(tadiga_parser_test tadiga_standard_test)
add_test(tadiga_parser ${CMAKE_BINARY_DIR}/src/test/tadiga_parser_test)


add_executable(tadiga_IGES_geometry_test ./tadiga_IGES_geometry_test.cc)
target_link_libraries(tadiga_IGES_geometry_test tadiga_standard_test)
add_test(tadiga_IGES_geometry ./tadiga_IGES_geometry_test)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test.igs
        ${CMAKE_CURRENT_BINARY_DIR}/test.igs COPYONLY)


add_executable(tadiga_geometry_test ./tadiga_geometry_test.cc)
target_link_libraries(tadiga_geometry_test tadiga_standard_test)
add_test(tadiga_geometry ./tadiga_geometry_test)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test.igs
        ${CMAKE_CURRENT_BINARY_DIR}/test.igs COPYONLY)


