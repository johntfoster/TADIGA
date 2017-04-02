#
# Unit tests for TaDIgA
#

add_executable(tadiga_parser_test 
    ./tadiga_standard_test_main.cc
    ./tadiga_parser_test.cc)
target_link_libraries(tadiga_parser_test ${Tadiga_LINK_LIBRARIES})
add_test(tadiga_parser ./tadiga_parser_test)

add_executable(tadiga_IGES_geometry_test 
    ./tadiga_standard_test_main.cc
    ./tadiga_IGES_geometry_test.cc)
target_link_libraries(tadiga_IGES_geometry_test ${Tadiga_LINK_LIBRARIES})
add_test(tadiga_IGES_geometry ./tadiga_IGES_geometry_test)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test.igs
        ${CMAKE_CURRENT_BINARY_DIR}/test.igs COPYONLY)

    add_executable(tadiga_geometry_test 
    ./tadiga_standard_test_main.cc
    ./tadiga_geometry_test.cc)
target_link_libraries(tadiga_geometry_test ${Tadiga_LINK_LIBRARIES})
add_test(tadiga_geometry ./tadiga_geometry_test)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test.igs
        ${CMAKE_CURRENT_BINARY_DIR}/test.igs COPYONLY)


