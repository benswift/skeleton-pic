cmake_minimum_required (VERSION 3.0)

project(skeleton_PIC)

# MPI required for all sub-projects
find_package(MPI REQUIRED)

add_library(pic2 SHARED
  pic2/dtimer.c
  pic2/push2.c
  pic2/pic2.c
  pic2/ompi_comm_addr.c)

target_include_directories(pic2 PRIVATE ${MPI_C_INCLUDE_PATH})  
target_link_libraries(pic2 PRIVATE ${MPI_C_LIBRARIES})  

install(TARGETS pic2
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib)
