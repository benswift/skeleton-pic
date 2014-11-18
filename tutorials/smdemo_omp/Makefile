# Makefile for OpenMP test program

# Makefile gfortran compiler with MacOS X

CARBON = /System/Library/Frameworks/Carbon.framework/Carbon

#FC90 = gfortran
#CC = gcc

#OPTS90 = -O3
#CCOPTS = -O3

# Makefile gfortran compiler with Linux

FC90 = gfortran
CC = gcc

OPTS90 = -O3
CCOPTS = -O3

#

OMPOBJS = compmain.o dtimer.o

FOMPOBJS = fompmain.o dtimer.o

# Linkage rules

all: openmp

openmp: comptest fomptest

#OPENMP
comptest : comptest.o $(OMPOBJS)
	$(CC) $(CCOPTS) $(LOPTS) -o comptest comptest.o \
      $(OMPOBJS) -lgomp

fomptest : fomptest.o $(FOMPOBJS)
	$(FC90) $(OPTS90) $(LOPTS) -o fomptest fomptest.o \
      $(FOMPOBJS) -lgomp

# Compilation rules

dtimer.o : dtimer.c
	$(CC) $(CCOPTS) -c dtimer.c

#OPENMP
compmain.o : ompmain.c
	$(CC) $(CCOPTS) -o compmain.o -fopenmp -c ompmain.c

fompmain.o : ompmain.f
	$(FC90) $(OPTS90) -o fompmain.o -fopenmp -c ompmain.f

comptest.o : comptest.c
	$(CC) $(CCOPTS) -fopenmp -c comptest.c

fomptest.o : fomptest.f90
	$(FC90) $(OPTS90) -fopenmp -c fomptest.f90

clean:
	rm -f *.o *.mod

clobber: clean
	rm -f *omptest
