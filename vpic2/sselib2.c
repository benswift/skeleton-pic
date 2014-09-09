/* SSE2 utility Library */
/* written by Viktor K. Decyk, UCLA and Ricardo Fonseca, ISCTE */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <complex.h>
#include <xmmintrin.h>
#include "sselib2.h"

/* Prototypes for Fortran function called by C */

void getf2cptr_(unsigned long *carrayref, float *carray, int *nx,
                int *ny);

void getf3cptr_(unsigned long *carrayref, float *carray, int *nx,
                int *ny, int *nz);

void getc2cptr_(unsigned long *carrayref, float complex *carray,
                int *nx, int *ny);

void geti1cptr_(unsigned long *carrayref, int *carray, int *nx);

/*--------------------------------------------------------------------*/
void sse_fallocate(float **s_f, int nsize, int *irc) {
/* allocate aligned float memory on SSE return pointer to C */
/* size is padded to be a multiple of the alignment length */
/* local data */
/* NV = vector length for 32 bit data */
#define NV             4
   int ns;
   void *sptr = NULL;
   ns = NV*((nsize - 1)/NV + 1);
   sptr = _mm_malloc(ns*sizeof(float),4*NV);
   if (sptr==NULL) {
      printf("_mm_malloc float Error,len=%d\n",ns);
      *irc = 1;
   }
   *s_f = (float *)sptr;
   return;
#undef NV
}

/*--------------------------------------------------------------------*/
void sse_callocate(float complex **s_c, int nsize, int *irc) {
/* allocate aligned float complex memory on SSE return pointer to C */
/* size is padded to be a multiple of the alignment length          */
/* local data */
/* NV = vector length for 64 bit data */
#define NV             2
   int ns;
   void *sptr = NULL;
   ns = NV*((nsize - 1)/NV + 1);
   sptr = _mm_malloc(ns*sizeof(float complex),8*NV);
   if (sptr==NULL) {
      printf("_mm_malloc float complex Error,len=%d\n",ns);
      *irc = 1;
   }
   *s_c = (float complex *)sptr;
   return;
#undef NV
}

/*--------------------------------------------------------------------*/
void sse_iallocate(int **s_i, int nsize, int *irc) {
/* allocate aligned int memory on SSE, return pointer to C */
/* size is padded to be a multiple of the alignment length */
/* local data */
/* NV = vector length for 32 bit data */
#define NV             4
   int ns;
   void *sptr = NULL;
   ns = NV*((nsize - 1)/NV + 1);
   sptr = _mm_malloc(ns*sizeof(int),4*NV);
   if (sptr==NULL) {
      printf("_mm_malloc int Error,len=%d\n",ns);
      *irc = 1;
   }
   *s_i = (int *)sptr;
   return;
#undef NV
}

/*--------------------------------------------------------------------*/
void sse_deallocate(void *s_d) {
/* deallocate aligned memory on SSE */
   _mm_free(s_d);
   return;
}

/*--------------------------------------------------------------------*/
void csse2iscan2(int *isdata, int nths) {
/* performs local prefix reduction of integer data shared by threads */
/* using binary tree method. */
/* requires SSE2, isdata needs to be 16 byte aligned */
/* local data */
   int j, ns, isum, ist;
   __m128i v_m1, v_m2, v_it, v_is, v_ioff;
   ns = 4*(nths/4);
   v_m1 = _mm_set_epi32(0,-1,0,-1);
   v_m2 = _mm_set_epi32(0,-1,-1,0);
   isum = 0;
   v_ioff = _mm_set1_epi32(isum);
/* vector loop over elements in blocks of 4 */
   for (j = 0; j < ns; j+=4) {
/* load data */
      v_it = _mm_load_si128((__m128i *)&isdata[j]);
/* first pass */
      v_is = _mm_slli_si128(_mm_and_si128(v_it,v_m1),4);
      v_it = _mm_add_epi32(v_is,v_it);
/* second pass */
      v_is = _mm_shuffle_epi32(v_it,212);
      v_is = _mm_slli_si128(_mm_and_si128(v_is,v_m2),4);
      v_it = _mm_add_epi32(v_is,v_it);
/* add offset */
      v_it = _mm_add_epi32(v_it,v_ioff);
/* next offset */
      v_ioff = _mm_shuffle_epi32(v_it,255);
/* write data */
      _mm_store_si128((__m128i *)&isdata[j],v_it);
   }
   if (ns > 0)
      isum = isdata[ns-1];
/* loop over remaining elements */
   for (j = ns; j < nths; j++) {
      ist = isdata[j];
      isum += ist;
      isdata[j] = isum;
   }
   return;
}

/* Interfaces to Fortran */

/*--------------------------------------------------------------------*/
void sse_f2allocatex_(unsigned long *sp_f, int *nx, int *ny, int *nd,
                      int *irc) {
/* allocate aligned 2d real memory, assign data   */
/* pointer to Fortran pointer object sp_f         */
/* nd = (1,2) = (default,double precision)        */
/* This procedure needs an interface in Fortran90 */
/* interface                                        */
/*    subroutine sse_f2allocatex(sp_f,nx,ny,nd,irc) */
/*    implicit none                                 */
/*    integer :: nx, ny, nd, irc                    */
/*    real, dimension(:,:), pointer :: sp_f         */
/*    end subroutine                                */
/* end interface                                    */
/* local data */
   int nsize;
   float *fptr;
   nsize = (*nx)*(*ny);
   if ((*nd >= 0) && (*nd <= 2))
      nsize = (*nd)*nsize;
   sse_fallocate(&fptr,nsize,irc);
/* set reference to C data in real Fortran pointer object */
   getf2cptr_(sp_f,fptr,nx,ny);
   return;
}

/*--------------------------------------------------------------------*/
void sse_f3allocatex_(unsigned long *sp_f, int *nx, int *ny, int *nz,
                      int *nd, int *irc) {
/* allocate aligned 3d real memory, assign data   */
/* pointer to Fortran pointer object sp_f         */
/* nd = (1,2) = (default,double precision)        */
/* This procedure needs an interface in Fortran90 */
/* interface                                           */
/*    subroutine sse_f3allocatex(sp_f,nx,ny,nz,nd,irc) */
/*    implicit none                                    */
/*    integer :: nx, ny, nz, nd, irc                   */
/*    real, dimension(:,:,:), pointer :: sp_f          */
/*    end subroutine                                   */
/* end interface                                       */
/* local data */
   int nsize;
   float *fptr;
   nsize = (*nx)*(*ny)*(*nz);
   if ((*nd >= 0) && (*nd <= 2))
      nsize = (*nd)*nsize;
   sse_fallocate(&fptr,nsize,irc);
/* set reference to C data in real Fortran pointer object */
   getf3cptr_(sp_f,fptr,nx,ny,nz);
   return;
}

/*--------------------------------------------------------------------*/
void sse_c2allocatex_(unsigned long *sp_c, int *nx, int *ny,  int *nd,
                      int *irc) {
/* allocate aligned 2d complex memory, assign data */
/* pointer to Fortran pointer object sp_c          */
/* nd = (1,2) = (default,double precision)         */
/* This procedure needs an interface in Fortran90  */
/* interface                                        */
/*    subroutine sse_c2allocatex(sp_c,nx,ny,nd,irc) */
/*    implicit none                                 */
/*    integer :: nx, ny, nd, irc                    */
/*    complex, dimension(:,:), pointer :: sp_c      */
/*    end subroutine                                */
/* end interface                                    */
/* local data */
   int nsize;
   float complex *cptr;
   nsize = (*nx)*(*ny);
   if ((*nd >= 0) && (*nd <= 2))
      nsize = (*nd)*nsize;
   sse_callocate(&cptr,nsize,irc);
/* set reference to C data in real Fortran pointer object */
   getc2cptr_(sp_c,cptr,nx,ny);
   return;
}

/*--------------------------------------------------------------------*/
void sse_i1allocatex_(unsigned long *sp_i, int *nx,  int *nd,
                      int *irc) {
/* allocate aligned 1d integer memory, assign data */
/* pointer to Fortran pointer object sp_i          */ 
/* This procedure needs an interface in Fortran90  */
/* nd = (1,2) = (default,double precision)         */
/* interface                                     */
/*    subroutine sse_i1allocatex(sp_i,nx,nd,irc) */
/*    implicit none                              */
/*    integer :: nx, nd, irc                     */
/*    real, dimension(:), pointer :: sp_i        */
/*    end subroutine                             */
/* end interface                                 */
/* local data */
   int nsize;
   int *iptr;
   nsize = *nx;
   if ((*nd >= 0) && (*nd <= 2))
      nsize = (*nd)*nsize;
   sse_iallocate(&iptr,nsize,irc);
/* set reference to C data in integer Fortran pointer object */
   geti1cptr_(sp_i,iptr,nx);
   return;
}

/*--------------------------------------------------------------------*/
void sse_deallocate_(void *sp_d) {
/* pointer in Fortran should also be nullified */
   sse_deallocate(sp_d);
   return;
}

/*--------------------------------------------------------------------*/
void csse2iscan2_(int *isdata, int *nths) {
   csse2iscan2(isdata,*nths);
   return;
}

void fcopyin_(float *f, float *g, int *n) {
   int j;
   for (j = 0; j < *n; j++) {
      f[j] = g[j];
   }
   return;
}

