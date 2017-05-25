#!/usr/bin/env bash

rm -rf CMakeFiles
rm CMakeCache.txt

cmake \
      -DCMAKE_INSTALL_PREFIX=$HOME/Desktop/tadiga \
      -DCMAKE_BUILD_TYPE:STRING=Debug \
      -DBUILD_Trilinos:BOOL=ON \
      -DMPI_CXX_COMPILER:FILEPATH=/usr/local/openmpi/bin/mpicxx \
      -DMPI_C_COMPILER:FILEPATH=/usr/local/openmpi/bin/mpicc \
      -DCOVERAGE:BOOL=ON \
      ..

      #-DTrilinos_DIR:PATH=/Users/john/projects/TaDIgA/build/trilinos-build/lib/cmake/Trilinos \


