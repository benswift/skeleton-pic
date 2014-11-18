/* SSE vector add test program */
/* written by Viktor K. Decyk, UCLA and Ricardo Fonseca, IST */

#include <stdlib.h>
#include <stdio.h>
#include <xmmintrin.h>

static int nblock_size = 4;

/*--------------------------------------------------------------------*/
void setgbsize(int nblock) {
   nblock_size = nblock;
   return;
}

/*--------------------------------------------------------------------*/
void g_fallocate(float **g_f, int nsize, int *irc) {
/* allocate aligned float memory on SSE, return pointer to C */
   float *gptr;
   gptr = _mm_malloc(nsize*sizeof(float),16);
   if (gptr==NULL) {
      printf("_mm_malloc float Error,l=%d\n",nsize);
      *irc = 1;
   }
   *g_f = gptr;
   return;
}

/*--------------------------------------------------------------------*/
void g_deallocate(float **g_f) {
/* deallocate global memory on GPU, return pointer to C */
   _mm_free(*g_f);
   *g_f = NULL;
   return;
}

/*--------------------------------------------------------------------*/
void copyin_gmemptr(float *f, float *g_f, int nsize) {
/* copy float array from main memory to aligned SSE memory */
   int i;
   __m128 vf;
   for (i = 0; i < nsize; i+=4) {
      vf = _mm_loadu_ps(&f[i]);
     _mm_store_ps(&g_f[i],vf);
   }
   return;
}

/*--------------------------------------------------------------------*/
void copyout_gmemptr(float *f, float *g_f, int nsize) {
/* copy float array from aligned SSE memory to main memory */
   int i;
   __m128 vf;
   for (i = 0; i < nsize; i+=4) {
      vf = _mm_load_ps(&g_f[i]);
     _mm_storeu_ps(&f[i],vf);
   }
   return;
}

/*--------------------------------------------------------------------*/
void ssadd(float g_a[], float g_b[], float g_c[], int nx) {
   int i;
    __m128 va, vb, vc;
   for (i = 0; i < nx; i+=4) {
      vb = _mm_load_ps(&g_b[i]);
      vc = _mm_load_ps(&g_c[i]);
      va = _mm_add_ps(vb,vc);
     _mm_store_ps(&g_a[i],va);
   }
   return;
}

/* Interfaces to Fortran */

/*--------------------------------------------------------------------*/
void setgbsize_(int *nblock) {
   setgbsize(*nblock);
   return;
}

/*--------------------------------------------------------------------*/
void g_fallocate_(unsigned long *gp_f, int *nsize, int *irc) {
/* allocate aligned float memory on SSE, return pointer to Fortran */
   float *fptr;
   g_fallocate(&fptr,*nsize,irc);
   *gp_f = (long )fptr;
   return;
}

/*--------------------------------------------------------------------*/
void g_deallocate_(unsigned long *gp_f) {
/* deallocate aligned memory on SSE, return pointer to Fortran */
   float *f;
   f = (float *)*gp_f;
   g_deallocate(&f);
   *gp_f = 0;
   return;
}

/*--------------------------------------------------------------------*/
void copyin_gmemptr_(float *f, unsigned long *gp_f,
                                int *nsize) {
/* copy float array from main memory to aligned SSE memory */
   float *g_f;
   g_f = (float *)*gp_f;
   copyin_gmemptr(f,g_f,*nsize);
   return;
}

/*--------------------------------------------------------------------*/
void copyout_gmemptr_(float *f, unsigned long *gp_f,
                                 int *nsize) {
/* copy float array from aligned SSE memory to main memory */
   float *g_f;
   g_f = (float *)*gp_f;
   copyout_gmemptr(f,g_f,*nsize);
   return;
}

/*--------------------------------------------------------------------*/
void ssadd_(unsigned long *gp_a, unsigned long *gp_b,
           unsigned long *gp_c, int *nx) {
/* Vector Add Interface for Fortran */
   float *g_a, *g_b, *g_c;
   g_a = (float *)*gp_a;
   g_b = (float *)*gp_b;
   g_c = (float *)*gp_c;
   ssadd(g_a,g_b,g_c,*nx);
}

