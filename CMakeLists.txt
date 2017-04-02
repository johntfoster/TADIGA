
# CMakeLists.txt file for Tadiga
#

Cmake_minimum_required (VERSION 2.8)

enable_testing ()
project(TaDIgA)

option(COVERALLS "Turn on coveralls support" OFF)
option(COVERALLS_UPLOAD "Upload the generated coveralls json" ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules/coveralls-cmake/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules/open-cascade" ${CMAKE_MODULE_PATH})



# MPI configuration
# use the FindMPI module to find a version of MPI
# expose CMAKE_CXX_COMPILER so that the user can change it to the MPI compiler

mark_as_advanced (CLEAR CMAKE_CXX_COMPILER)

mark_as_advanced (CLEAR CMAKE_CXX_FLAGS)
if (NOT CMAKE_CXX_FLAGS)
  set (CMAKE_CXX_FLAGS "-DMPICH_IGNORE_CXX_SEEK" CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif (NOT CMAKE_CXX_FLAGS)


find_package(opencascade REQUIRED)




#
# Trilinos configuration
#
set(TRILINOS_DIR CACHE PATH "Path to Trilinos directory")
SET(CMAKE_PREFIX_PATH ${TRILINOS_DIR} ${CMAKE_PREFIX_PATH})
FIND_PACKAGE(Trilinos REQUIRED)
MESSAGE("Trilinos installation:")
MESSAGE("   Trilinos_DIR = ${Trilinos_DIR}")
MESSAGE("   Trilinos_VERSION = ${Trilinos_VERSION}")
MESSAGE("   Trilinos_PACKAGE_LIST = ${Trilinos_PACKAGE_LIST}")
MESSAGE("   Trilinos_TPL_LIST = ${Trilinos_TPL_LIST}")
MESSAGE("   Trilinos_TPL_INCLUDE_DIRS = ${Trilinos_TPL_INCLUDE_DIRS}")
MESSAGE("   Trilinos_TPL_LIBRARIES = ${Trilinos_TPL_LIBRARIES}")
MESSAGE("   Trilinos_TPL_LIBRARY_DIRS = ${Trilinos_TPL_LIBRARY_DIRS}")
MESSAGE("   Trilinos_BUILD_SHARED_LIBS = ${Trilinos_BUILD_SHARED_LIBS}")
MESSAGE("   Trilinos_CXX_COMPILER_FLAGS = ${Trilinos_CXX_COMPILER_FLAGS}")
# Hack for now until Trilinos exports cmake variable for binaries directory
SET(Trilinos_BINARY_PATH ${Trilinos_LIBRARY_DIRS}/../bin)
#
# Remove PyTrilinos if it's there to avoid errors, we don't use it in Tadiga
#
LIST(REMOVE_ITEM Trilinos_LIBRARIES "pytrilinos")
#
# verbose output
MESSAGE("   Trilinos_LIBRARIES = ${Trilinos_LIBRARIES}")
MESSAGE("   Trilinos_INCLUDE_DIRS = ${Trilinos_INCLUDE_DIRS}")
MESSAGE("   Trilinos_LIBRARY_DIRS = ${Trilinos_LIBRARY_DIRS}")
MESSAGE("")

LIST(FIND Trilinos_TPL_LIST yaml-cpp yaml-cpp_Package_Index)
IF(yaml-cpp_Package_Index GREATER -1)
    MESSAGE("-- Trilinos was compiled with TPL_ENABLE_yaml-cpp.\n\n   Will compile TaDIgA to support YAML input files. (currently the only option)\n\n")
    ADD_DEFINITIONS(-DUSE_YAML)
ENDIF()



# Optional Installation helpers
# Note that some of this functionality depends on CMAKE > 2.8.8
set(INCLUDE_INSTALL_DIR include)
set(LIB_INSTALL_DIR lib)
include(CMakePackageConfigHelpers)


# include for all directories
# Collection of include and lib directories
set(INCLUDE_DIRS 
${OCC_INCLUDE_DIR}
${Trilinos_INCLUDE_DIRS} 
${Trilinos_TPL_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}
${CMAKE_SOURCE_DIR}/src
)

include_directories(${INCLUDE_DIRS})

# link directories 
set(REQUIRED_LIBS
  ${Trilinos_TPL_LIBRARIES}
)

#Turn on coveralls code coverage upload
if (COVERALLS)
	include(Coveralls)
	coveralls_turn_on_coverage()
endif()


add_subdirectory(src)
