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

#If all TPLs are requested, this implies building Trilinos
if(BUILD_ALL_TPS)
    set(BUILD_Trilinos TRUE)
endif()

#If BUILD_TRILINOS=OFF we need to look for a Trilinos installation and then
#ensure that all the necessary components and TPLs are installed
if(NOT BUILD_Trilinos)
    find_package(Trilinos 12.10 QUIET PATHS ${Trilinos_DIR} REQUIRED)

    message("\n-- Trilinos found!\n")

    #Check for yaml-cpp
    list(FIND Trilinos_TPL_LIST yaml-cpp yaml-cpp_Package_Index)
    if(yaml-cpp_Package_Index GREATER -1)
        message("-- -- Trilinos was compiled with TPL_ENABLE_yaml-cpp.")
    else()
        message("-- -- Trilinos was NOT compiled with TPL_ENABLE_yaml-cpp. (required)")
        set(MISSING_TRILINOS_PACKAGE TRUE)
    endif()

    #Check for Boost
    list(FIND Trilinos_TPL_LIST Boost Boost_Package_Index)
    if(Boost_Package_Index GREATER -1)
        message("-- -- Trilinos was compiled with TPL_ENABLE_Boost.")
    else()
        message("-- -- Trilinos was NOT compiled with TPL_ENABLE_Boost. (required)")
        set(MISSING_TRILINOS_PACKAGE TRUE)
    endif()

    #Check for BLAS
    list(FIND Trilinos_TPL_LIST BLAS BLAS_Package_Index)
    if(BLAS_Package_Index GREATER -1)
        message("-- -- Trilinos was compiled with TPL_ENABLE_BLAS.")
    else()
        message("-- -- Trilinos was NOT compiled with TPL_ENABLE_BLAS. (required)")
        set(MISSING_TRILINOS_PACKAGE TRUE)
    endif()

    #Check for LAPACK
    list(FIND Trilinos_TPL_LIST LAPACK LAPACK_Package_Index)
    if(LAPACK_Package_Index GREATER -1)
        message("-- -- Trilinos was compiled with TPL_ENABLE_LAPACK.")
    else()
        message("-- -- Trilinos was NOT compiled with TPL_ENABLE_LAPACK. (required)")
        set(MISSING_TRILINOS_PACKAGE TRUE)
    endif()

    #Check for Teuchos
    list(FIND Trilinos_PACKAGE_LIST Teuchos teuchos_Package_Index)
    if(teuchos_Package_Index GREATER -1)
        message("-- -- Trilinos was compiled with Trilinos_ENABLE_Teuchos.")
    else()
        message("-- -- Trilinos was NOT compiled with Trilinos_ENABLE_Teuchos. (required)")
        set(MISSING_TRILINOS_PACKAGE TRUE)
    endif()

    #Check for Tpetra
    list(FIND Trilinos_PACKAGE_LIST Tpetra tpetra_Package_Index)
    if(tpetra_Package_Index GREATER -1)
        message("-- -- Trilinos was compiled with Trilinos_ENABLE_Tpetra.")
    else()
        message("-- -- Trilinos was NOT compiled with Trilinos_ENABLE_Tpetra. (required)")
        set(MISSING_TRILINOS_PACKAGE TRUE)
    endif()

    #Check for Aprepro
    list(FIND Trilinos_PACKAGE_LIST SEACASAprepro SEACASAprepro_Package_Index)
    if(SEACASAprepro_Package_Index GREATER -1)
        message("-- -- Trilinos was compiled with Trilinos_ENABLE_SEACASAprepro.")
    else()
        message("-- -- Trilinos was NOT compiled with Trilinos_ENABLE_SEACASAprepro. (required)")
        set(MISSING_TRILINOS_PACKAGE TRUE)
    endif()

    if(MISSING_TRILINOS_PACKAGE)
        message(FATAL_ERROR "\nERROR! One or more required TPLs were NOT enabled in the Trilinos build. Either envoke -DBUILD_TRILINOS:BOOL=ON to enable building of Trilinos at configure time or reinstall Trilinos with the missing TPLs enabled.\n")
    endif()

else()

    #If we are requiring a Trilinos build, we need to check for the required TPLs 
    #or install them, first Boost
    if(NOT BUILD_ALL_TPLs)
        find_package(Boost)
    endif()
    if(NOT Boost_FOUND OR BUILD_ALL_TPLs)
        message(STATUS "Download Boost headers\n")
        configure_file(cmake/Boost-build.cmake.in boost-download/CMakeLists.txt)
        execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/boost-download)
        execute_process(COMMAND ${CMAKE_COMMAND} --build .  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/boost-download)
        unset(Boost_FOUND)
        set(BOOST_ROOT ${CMAKE_BINARY_DIR}/boost-src)
        find_package(Boost REQUIRED)
    endif()

    #Now yaml-cpp
    if(NOT BUILD_ALL_TPLs)
        find_package(yaml-cpp MODULE QUIET)
    endif()
    if(NOT yaml-cpp_FOUND OR BUILD_ALL_TPLs)
        message(STATUS "Download, configure, and build yaml-cpp library")
        configure_file(cmake/yaml-cpp-build.cmake.in yaml-cpp-download/CMakeLists.txt)
        execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/yaml-cpp-download)
        execute_process(COMMAND ${CMAKE_COMMAND} --build .  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/yaml-cpp-download)
        unset(yaml-cpp_FOUND)
        find_package(yaml-cpp REQUIRED NO_MODULE PATHS ${CMAKE_BINARY_DIR}/yaml-cpp-build)
        set(yaml-cpp_INCLUDE_DIRS ${YAML_CPP_INCLUDE_DIR})
        set(yaml-cpp_LIBRARIES ${YAML_CPP_LIBRARIES})
        message(STATUS "-- yaml-cpp include directory: ${yaml-cpp_INCLUDE_DIRS}")
        message(STATUS "-- yaml-cpp library: ${yaml-cpp_LIBRARIES}\n")
    endif()

    message(STATUS "Download, configure and build Trilinos\n")

    configure_file(cmake/Trilinos-build.cmake.in trilinos-download/CMakeLists.txt)

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/trilinos-download)
    execute_process(COMMAND ${CMAKE_COMMAND} --build .  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/trilinos-download)

    unset(Trilinos_DIR CACHE)
    find_package(Trilinos PATHS ${CMAKE_BINARY_DIR}/trilinos/lib/cmake/Trilinos NO_DEFAULT_PATH REQUIRED)
    message(STATUS "Trilinos version ${Trilinos_VERSION} built successfully.\n")

endif()

add_library(trilinos INTERFACE IMPORTED)
set_property(TARGET trilinos PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${Trilinos_INCLUDE_DIRS} ${Trilinos_TPL_INCLUDE_DIRS})
set_property(TARGET trilinos PROPERTY
    INTERFACE_LINK_LIBRARIES ${Trilinos_LIBRARIES} ${Trilinos_TPL_LIBRARIES})
