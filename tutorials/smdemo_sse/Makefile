# Makefile for SSE test program

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

SSEOBJS = ssemain.o dtimer.o

# Linkage rules

all: sse

sse: cssetest fssetest

#SSE
cssetest : cssetest.o $(SSEOBJS)
	$(CC) $(CCOPTS) $(LOPTS) -o cssetest cssetest.o \
      $(SSEOBJS)

fssetest : fssetest.o $(SSEOBJS)
	$(FC90) $(OPTS90) $(LOPTS) -o fssetest fssetest.o \
      $(SSEOBJS)

# Compilation rules

dtimer.o : dtimer.c
	$(CC) $(CCOPTS) -c dtimer.c

#SSE
ssemain.o : ssemain.c
	$(CC) $(CCOPTS) -o ssemain.o -c ssemain.c

cssetest.o : cssetest.c
	$(CC) $(CCOPTS) -c cssetest.c

fssetest.o : fssetest.f90
	$(FC90) $(OPTS90) -c fssetest.f90

clean:
	rm -f *.o *.mod

clobber: clean
	rm -f *ssetest
