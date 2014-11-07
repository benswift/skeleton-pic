# Parallel Plasma PIC Codes

by Viktor K. Decyk

copyright 1994-2013, regents of the university of california


Skeleton Particle-in-Cell (PIC) Codes: These skeleton codes contain
the critical algorithms used in various PIC codes, but do not contain
the wide range of inputs, diagnostics, and outputs normally found in
such codes. Their main purpose is to teach students how such codes are
structured. They can also be used for benchmarking purposes and as a
starting point in evaluating new computer architectures and languages.
Most of the examples are in Fortran and C.

## Basic Serial Codes:

1. 2D Serial Electrostatic Spectral code (pic2)

2. 2-1/2D Serial Electromagnetic Spectral code (bpic2)

## Basic Parallel Codes - Level 1

These families of codes illustrate how to implement PIC codes with one
level of parallelism.

### OpenMP

The first family uses a tiling technique designed for shared memory
processors with OpenMP:

1. 2D Parallel Electrostatic Spectral code (mpic2)

2. 2-1/2D Parallel Electromagnetic Spectral code (mbpic2)

### MPI

The second family uses domain decomposition designed for distributed
memory processors with MPI:

1. 2D Parallel Electrostatic Spectral code (ppic2)

2. 2-1/2D Parallel Electromagnetic Spectral code (pbpic2)

### SIMD

The third family uses SIMD vectorization with either compiler
directives or SSE intrinsics:

1. 2D Parallel Electrostatic Spectral code (vpic2)

2. 2-1/2D Parallel Electromagnetic Spectral code (vbpic2)

## Basic Parallel Codes - Level 2

These families of codes illustrate how to implement PIC codes with two
levels of parallelism.

### GPU (CUDA C)

The first family uses CUDA C on the NVIDIA GPU, with a tiling
technique for each thread block, and with SIMD vectorization within a
block.

1. 2D Parallel Electrostatic Spectral code (gpupic2)

2. 2-1/2D Parallel Electromagnetic Spectral code (gpubpic2)

### GPU (CUDA Fortran)

The second family uses CUDA Fortran on the NVIDIA GPU, with a tiling
technique for each thread block, and with SIMD vectorization within a
block.

1. 2D Parallel Electrostatic Spectral code (gpufpic2)

2. 2-1/2D Parallel Electromagnetic Spectral code (gpufbpic2)

### MPI + OpenMP

The third family uses a hybrid MPI/OpenMP scheme, with a tiling
technique on each shared memory multi-core node using OpenMP, and
domain decomposition connecting such nodes.

1. 2D Parallel Electrostatic Spectral code (mppic2)

2. 2-1/2D Parallel Electromagnetic Spectral code (mpbpic2)

## Basic Parallel Codes - Level 3

These families of codes illustrate how to implement PIC codes with
three levels of parallelism.

### GPU (CUDA C) + MPI

The first family uses CUDA C on the NVIDIA GPU, with a tiling
technique for each thread block, SIMD vectorization within a block,
and domain decomposition with MPI between GPUs.

1. 2D Parallel Electrostatic Spectral code (gpuppic2)

2. 2-1/2D Parallel Electromagnetic Spectral code (gpupbpic2)

### GPU (CUDA Fortran) + MPI

The second family uses CUDA Fortran on the NVIDIA GPU, with a tiling
technique for each thread block, SIMD vectorization within a block,
and domain decomposition with MPI between GPUs.

1. 2D Parallel Electrostatic Spectral code (gpufppic2)

2. 2-1/2D Parallel Electromagnetic Spectral code (gpufpbpic2)

## Want to contact developer?

Send mail to Viktor Decyk - decyk@physics.ucla.edu 

## Licence

Copyright (c) 2013, Regents of the University of California
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

   Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
   Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
   
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
