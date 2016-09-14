#! /usr/bin/env bash

BUILDDIR=${1:-build}

KOKKOS=${KOKKOS:-OFF}

# Install parallel version of netcdf library...
ACCESS=`pwd`
pwd
cd TPL/netcdf
wget https://github.com/Unidata/netcdf-c/archive/v4.4.0.tar.gz
tar -xzvf v4.4.0.tar.gz
cd netcdf-c-4.4.0
CC=mpicc ./configure --prefix=$ACCESS --enable-netcdf4 --disable-v2 --disable-fsync --disable-dap && make && sudo make install

cd $ACCESS
pwd

cd TPL/cgns
git clone https://github.com/cgns/CGNS
cd CGNS
mkdir build
cd build
MPI=ON sh ../../runconfigure.sh
make && sudo make install

cd $ACCESS
pwd

mpiexec --version
mpiexec --help

MPI_EXEC=`which mpiexec`
MPI_BIN=`dirname "${MPI_EXEC}"`

mkdir $BUILDDIR && cd $BUILDDIR

CUDA_PATH=${CUDA_ROOT} #Set this to the appropriate path

### Set to ON for CUDA compile; otherwise OFF (default)
CUDA="OFF"

echo "KOKKOS = ${KOKKOS}"

if [ "$KOKKOS" == "ON" ]
then
  if [ "$CUDA" == "ON" ]
  then
    export CUDA_MANAGED_FORCE_DEVICE_ALLOC=1
    KOKKOS_SYMBOLS="-DTPL_ENABLE_CUDA:Bool=ON -DCUDA_TOOLKIT_ROOT_DIR:PATH=${CUDA_PATH} -DTPL_ENABLE_Pthread:Bool=OFF"
  else
    unset CUDA_MANAGED_FORCE_DEVICE_ALLOC
    KOKKOS_SYMBOLS="-DSEACASProj_ENABLE_OpenMP:Bool=ON -DTPL_ENABLE_Pthread:Bool=OFF"
  fi
else
  KOKKOS_SYMBOLS="-D SEACASProj_ENABLE_Kokkos:BOOL=OFF"
fi


cmake \
  -DTPL_ENABLE_MPI=ON \
  -DCMAKE_CXX_COMPILER:FILEPATH=mpicxx \
  -DCMAKE_C_COMPILER:FILEPATH=mpicc \
  -DCMAKE_Fortran_COMPILER:FILEPATH=mpif77 \
  -DBUILD_SHARED_LIBS:BOOL=ON \
  -DCMAKE_CXX_FLAGS="-Wall -pedantic" \
  -DCMAKE_C_FLAGS="-Wall -pedantic" \
  -DNetCDF_DIR:PATH=${ACCESS} \
  -DHDF5_ROOT:PATH=/usr/ \
  -DSEACASProj_ENABLE_ALL_PACKAGES:BOOL=ON \
  -DSEACASProj_ENABLE_SECONDARY_TESTED_CODE:BOOL=ON \
  -DSEACASProj_ENABLE_TESTS:BOOL=ON \
  -DSEACASProj_USE_GNUINSTALLDIRS:BOOL=ON \
  ${KOKKOS_SYMBOLS} \
  -DTPL_ENABLE_CGNS:BOOL=ON \
  -DCGNS_ROOT:PATH="/" \
  -DTPL_ENABLE_Matio:BOOL=ON \
  -DTPL_ENABLE_METIS:BOOL=OFF \
  -DTPL_ENABLE_ParMETIS:BOOL=OFF \
  -DTPL_ENABLE_Netcdf:BOOL=ON \
  -DTPL_ENABLE_Pamgen:BOOL=OFF \
  -DTPL_ENABLE_X11:BOOL=ON \
  -DTPL_ENABLE_Zlib:BOOL=ON \
  -DZoltan_ENABLE_TESTS:BOOL=OFF \
  -DMPI_BIN_DIR:PATH=${MPI_BIN} \
  ../

make -j2

cd $ACCESS
