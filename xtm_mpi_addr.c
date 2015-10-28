#include <mpi.h>
#include <stdio.h>

// datatypes
void* xtm_mpi_datatype_null = MPI_DATATYPE_NULL;
void* xtm_mpi_char = MPI_CHAR;
void* xtm_mpi_signed_char = MPI_SIGNED_CHAR;
void* xtm_mpi_unsigned_char = MPI_UNSIGNED_CHAR;
void* xtm_mpi_byte = MPI_BYTE;
void* xtm_mpi_short = MPI_SHORT;
void* xtm_mpi_unsigned_short = MPI_UNSIGNED_SHORT;
void* xtm_mpi_int = MPI_INT;
void* xtm_mpi_unsigned = MPI_UNSIGNED;
void* xtm_mpi_long = MPI_LONG;
void* xtm_mpi_unsigned_long = MPI_UNSIGNED_LONG;
void* xtm_mpi_long_long_int = MPI_LONG_LONG_INT;
void* xtm_mpi_unsigned_long_long = MPI_UNSIGNED_LONG_LONG;
void* xtm_mpi_float = MPI_FLOAT;
void* xtm_mpi_double = MPI_DOUBLE;
void* xtm_mpi_long_double = MPI_LONG_DOUBLE;
void* xtm_mpi_wchar = MPI_WCHAR;
void* xtm_mpi_packed = MPI_PACKED;

// C++ / C99 datatypes
// void* xtm_mpi_c_bool = MPI_C_BOOL;
// void* xtm_mpi_cxx_bool = MPI_CXX_BOOL;

// Complex datatypes for C (base types), C++, and fortran
void* xtm_mpi_c_float_complex = MPI_C_FLOAT_COMPLEX;
void* xtm_mpi_c_complex = MPI_C_COMPLEX;
void* xtm_mpi_c_double_complex = MPI_C_DOUBLE_COMPLEX;
void* xtm_mpi_c_long_double_complex = MPI_C_LONG_DOUBLE_COMPLEX;

// communicators
void* xtm_mpi_comm_world = (void *)MPI_COMM_WORLD;
void* xtm_mpi_comm_self = (void *)MPI_COMM_SELF;
void* xtm_mpi_comm_null = (void *)MPI_COMM_NULL;
