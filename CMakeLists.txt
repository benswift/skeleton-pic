cmake_minimum_required (VERSION 3.0)

project(skeleton_PIC)

option(OPENMP "build the OpenMP libraries" OFF)

if(OPENMP)
  find_package(OpenMP REQUIRED)
endif()

# MPI required for all sub-projects
find_package(MPI REQUIRED)

########################
# here are the targets #
########################

# pic2

add_library(pic2 SHARED
  pic2/dtimer.c
  pic2/push2.c
  pic2/pic2.c)

install(TARGETS pic2
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib)

# bpic2

add_library(bpic2 SHARED
  bpic2/dtimer.c
  bpic2/bpush2.c
  bpic2/bpic2.c)

install(TARGETS bpic2
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib)

# bpic3

# add_library(bpic3 SHARED
#   bpic3/dtimer.c
#   bpic3/bpush3.c
#   bpic3/bpic3.c)

# install(TARGETS bpic3
#   LIBRARY DESTINATION lib
#   RUNTIME DESTINATION lib)

# # mbpic2

# add_library(mbpic2 SHARED
#   mbpic2/dtimer.c
#   mbpic2/mbpush2.c
#   mbpic2/omplib.c
#   mbpic2/mbpic2.c)

# target_compile_options(mbpic2 PRIVATE ${OpenMP_C_FLAGS})  

# install(TARGETS mbpic2
#   LIBRARY DESTINATION lib
#   RUNTIME DESTINATION lib)

# # mpbpic2

# add_library(mpbpic2 SHARED
#   mpbpic2/dtimer.c
#   mpbpic2/mpbpush2.c
#   mpbpic2/omplib.c
#   mpbpic2/mpbpic2.c
#   xtm_mpi_addr.c)

# target_compile_options(mbpic2 PRIVATE ${OpenMP_C_FLAGS})  
# target_include_directories(mpbpic2 PRIVATE ${MPI_C_INCLUDE_PATH})  
# target_link_libraries(mpbpic2 PRIVATE ${MPI_C_LIBRARIES})  

# install(TARGETS mpbpic2
#   LIBRARY DESTINATION lib
#   RUNTIME DESTINATION lib)

# # mpic2

# add_library(mpic2 SHARED
#   mpic2/dtimer.c
#   mpic2/mpush2.c
#   mpic2/omplib.c
#   mpic2/mpic2.c)

# target_compile_options(mbpic2 PRIVATE ${OpenMP_C_FLAGS})  

# install(TARGETS mpic2
#   LIBRARY DESTINATION lib
#   RUNTIME DESTINATION lib)

# mppic2

# for mppic2, need to specify an openmp-enabled compiler through the CC/CXX variables, e.g.

# GCC

# CC=/usr/local/Cellar/gcc/5.2.0/bin/gcc-5 CXX=/usr/local/Cellar/gcc/5.2.0/bin/g++-5 cmake .. && make mppic2

# Clang

# CC=clang-omp CXX=clang-omp++ cmake .. && make mppic2

if(OPENMP)

  add_library(mppic2 SHARED
    mppic2/dtimer.c
    mppic2/mppic2.c
    mppic2/mpplib2.c
    mppic2/mppush2.c
    mppic2/omplib.c
    # mppic2/ppic2.c
    # mppic2/ppush2.c
    xtm_mpi_addr.c)

  # MPI
  target_include_directories(mppic2 PRIVATE ${MPI_C_INCLUDE_PATH})
  target_link_libraries(mppic2 PRIVATE ${MPI_C_LIBRARIES})

  # OpenMP
  target_compile_options(mppic2 PRIVATE ${OpenMP_C_FLAGS})
  target_link_libraries(mppic2 PRIVATE iomp5) # if using clang/libiomp
  # target_link_libraries(mppic2 PRIVATE gomp) # if using clang/libiomp

  install(TARGETS mppic2
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION lib)

endif()

# pbpic2

add_library(pbpic2 SHARED
  pbpic2/dtimer.c
  pbpic2/pbpush2.c
  pbpic2/pbpic2.c
  pbpic2/pplib2.c
  xtm_mpi_addr.c)

target_include_directories(pbpic2 PRIVATE ${MPI_C_INCLUDE_PATH})
target_link_libraries(pbpic2 PRIVATE ${MPI_C_LIBRARIES})

install(TARGETS pbpic2
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib)

add_executable(cpbpic2
  pbpic2/dtimer.c
  pbpic2/pbpush2.c
  pbpic2/pbpic2.c
  pbpic2/pplib2.c
  xtm_mpi_addr.c)

target_include_directories(cpbpic2 PRIVATE ${MPI_C_INCLUDE_PATH})
target_link_libraries(cpbpic2 PRIVATE ${MPI_C_LIBRARIES})

install(TARGETS cpbpic2
  RUNTIME DESTINATION bin)

# pic3

# add_library(pic3 SHARED
#   pic3/dtimer.c
#   pic3/push3.c
#   pic3/pic3.c
#   xtm_mpi_addr.c)

# target_include_directories(pic3 PRIVATE ${MPI_C_INCLUDE_PATH})  
# target_link_libraries(pic3 PRIVATE ${MPI_C_LIBRARIES})  

# install(TARGETS pic3
#   LIBRARY DESTINATION lib
#   RUNTIME DESTINATION lib)

# ppic2

add_library(ppic2 SHARED
  ppic2/dtimer.c
  ppic2/ppush2.c
  ppic2/ppic2.c
  ppic2/pplib2.c
  xtm_mpi_addr.c)

target_include_directories(ppic2 PRIVATE ${MPI_C_INCLUDE_PATH})  
target_link_libraries(ppic2 PRIVATE ${MPI_C_LIBRARIES})  

install(TARGETS ppic2
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib)

# vbpic2

add_library(vbpic2 SHARED
  vbpic2/dtimer.c
  vbpic2/vbpush2.c
  vbpic2/vbpic2.c
  vbpic2/sselib2.c
  vbpic2/ssebpush2.c)

# target_include_directories(vbpic2 PRIVATE ${MPI_C_INCLUDE_PATH})  
# target_link_libraries(vbpic2 PRIVATE ${MPI_C_LIBRARIES})  

install(TARGETS vbpic2
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib)

# vpic2

add_library(vpic2 SHARED
  vpic2/dtimer.c
  vpic2/vpush2.c
  vpic2/vpic2.c
  vpic2/sselib2.c
  vpic2/ssepush2.c)

# target_include_directories(vpic2 PRIVATE ${MPI_C_INCLUDE_PATH})  
# target_link_libraries(vpic2 PRIVATE ${MPI_C_LIBRARIES})  

install(TARGETS vpic2
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib)
