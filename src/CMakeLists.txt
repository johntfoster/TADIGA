#
# Main executable for TaDIgA
#

set(Tadiga_HEADERS
    tadiga.h
    tadiga_IGES_geometry.h
    tadiga_factory.h
    tadiga_parser.h
    tadiga_geometry.h
    tadiga_geometry_factory.h
)

set(Tadiga_SOURCES
    ${PROJECT_SOURCE_DIR}/src/tadiga.cc
    ${PROJECT_SOURCE_DIR}/src/tadiga_IGES_geometry.cc
    ${PROJECT_SOURCE_DIR}/src/tadiga_factory.cc
    ${PROJECT_SOURCE_DIR}/src/tadiga_parser.cc
    ${PROJECT_SOURCE_DIR}/src/tadiga_geometry.cc
    ${PROJECT_SOURCE_DIR}/src/tadiga_geometry_factory.cc
    ${PROJECT_SOURCE_DIR}/src/tadiga_geometry.cc

)

add_library(tadigaLib ${Tadiga_SOURCES})
set(Tadiga_LIBRARY tadigaLib)

set(Tadiga_LINK_LIBRARIES
    ${OCC_LIBRARIES}
    ${Tadiga_LIBRARY}
    ${Trilinos_LIBRARIES}
    ${REQUIRED_LIBS}
)

# Setup the coveralls target and tell it to gather
# coverage data for all the lib sources.
if(COVERALLS)
	coveralls_setup(
        "${Tadiga_SOURCES}"
        ${COVERALLS_UPLOAD}                 
        "${PROJECT_SOURCE_DIR}/CMakeModules/coveralls-cmake/cmake")
endif()

add_executable(tadiga tadiga_main.cc)
target_link_libraries(tadiga ${Tadiga_LINK_LIBRARIES})

#
# Install target for Tadiga main executable
#
install(TARGETS tadiga 
    RUNTIME DESTINATION bin
)

add_subdirectory(test)
