# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (PIC)

# serial codes
add_subdirectory (pic2)
add_subdirectory (bpic2)

## basic parallel (level 1) 
# OpenMP
add_subdirectory (mbpic2)
add_subdirectory (mpic2)
# MPI
add_subdirectory (pbpic2)
add_subdirectory (ppic2)
# SIMD
add_subdirectory (vbpic2)
add_subdirectory (vpic2)
