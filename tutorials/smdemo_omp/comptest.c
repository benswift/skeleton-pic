#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "ompmain.h"

void cadd(float a[], float b[], float c[], int nx) {
   int j;
   for (j = 0; j < nx; j++) {
      a[j] = b[j] + c[j];
   }
   return;
}

void dtimer(double *time, struct timeval *itime, int icntrl);

int main(int argc, char *argv[])
{
/* OpenMP vector add test program */
/* written by Viktor K. Decyk, UCLA */
/* nx = size of array, nthreads = number of threads */
   int nx = 1048576, nthreads = 1;
   int j;
   float time = 0.0;
   float eps, epsmax;
   double dtime;
   float *a = NULL, *b = NULL, *c = NULL, *d = NULL; 
   struct timeval itime;
   float *p_a = NULL, *p_b = NULL, *p_c = NULL; 

/* initialize Host data */
   a = (float *) malloc(nx*sizeof(float));
   b = (float *) malloc(nx*sizeof(float));
   c = (float *) malloc(nx*sizeof(float));
   d = (float *) malloc(nx*sizeof(float));
/* initialize vectors */
   for (j = 0; j < nx; j++) {
      a[j] = 0.0; b[j] = j + 1; c[j] = 2*j + 2; d[j] = -1.0;
   }
/* set up openmp */
   init_omp(0);
/* setnthsize(nthreads); */
/* allocate data on openmp */
   p_a = (float *) malloc(nx*sizeof(float));
   p_b = (float *) malloc(nx*sizeof(float));
   p_c = (float *) malloc(nx*sizeof(float));

/* First execute on Host in C: a = b + c */
   dtimer(&dtime,&itime,-1);
   cadd(a,b,c,nx);
   dtimer(&dtime,&itime,1);
   printf("C add time=%e\n",(float)dtime);
/* Copy data for openmp */
   dtimer(&dtime,&itime,-1);
   for (j = 0; j < nx; j++) {
      p_b[j] = b[j];
      p_c[j] = c[j];
   }
   dtimer(&dtime,&itime,1);
   time += (float)dtime;
   printf("Copyin time=%e\n",(float)dtime);
/* Execute with openmp: g_a = g_b + g_c */
   dtimer(&dtime,&itime,-1);
   mpadd(p_a,p_b,p_c,nx);
   dtimer(&dtime,&itime,1);
   time += (float)dtime;
   printf("openmp add time=%e\n",(float)dtime);
/* Copy data from openmp: d = g_a */
   dtimer(&dtime,&itime,-1);
   for (j = 0; j < nx; j++) {
      d[j] = p_a[j];
   }
   dtimer(&dtime,&itime,1);
   time += (float)dtime;
   printf("Copyout time=%e\n",(float)dtime);
   printf("Total openmp time=%e\n",time);

/* Check for correctness: compare a and d */
   epsmax = 0.0;
   for (j = 0; j < nx; j++) {
      eps = a[j] - d[j];
      if (eps < 0.0)
         eps = -eps;
      if (eps > epsmax)
         epsmax = eps;
   }
   printf("maximum difference = %e\n",epsmax);

/* deallocate memory for openmp */
   free(p_a);
   free(p_b);
   free(p_c);
/* deallocate Host memory */
   free(a);
   free(b);
   free(c);
   free(d);

   return 0;
}

