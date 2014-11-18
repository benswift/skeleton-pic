!-----------------------------------------------------------------------
      program omptest
! OpenMP vector add test program
! written by Viktor K. Decyk, UCLA
! nx = size of array, nthreads = number of threads
!     use omp_lib
      implicit none
      integer :: nx = 1048576, nthreads = 1
      integer :: j, irc
      real :: time = 0.0
      real :: eps, epsmax
      double precision :: dtime
      real, dimension(:), pointer :: a, b, c, d
      integer, dimension(4) :: itime
      real, dimension(:), pointer :: p_a, p_b, p_c
!
! initialize Host data
      allocate(a(nx),b(nx),c(nx),d(nx))
      do j = 1, nx
         b(j) = j
         c(j) = 2*j
      enddo
      a = 0.0; d = -1.0
! set up openmp
      call init_omp(0)
!     call setnthsize(nthreads)
! allocate data for openmp
      allocate(p_a(nx),p_b(nx),p_c(nx))
!
! First execute on Host in Fortran: a = b + c
      call dtimer(dtime,itime,-1)
      call fadd(a,b,c,nx)
      call dtimer(dtime,itime,1)
      write (*,*) 'Fortran add time=', real(dtime)
! Copy data for openmp
      call dtimer(dtime,itime,-1)
      p_b = b
      p_c = c
      call dtimer(dtime,itime,1)
      time = time + real(dtime)
      write (*,*) 'Copyin time=', real(dtime)
! Execute with openmp: g_a = g_b + g_c
      call dtimer(dtime,itime,-1)
      call mpadd(p_a,p_b,p_c,nx)
      call dtimer(dtime,itime,1)
      time = time + real(dtime)
      write (*,*) 'openmp add time=', real(dtime)
! Copy data from openmp: d = g_a
      call dtimer(dtime,itime,-1)
      d = p_a
      call dtimer(dtime,itime,1)
      time = time + real(dtime)
      write (*,*) 'Copyout time=', real(dtime)
      write (*,*) 'Total openmp time=',time
!
! Check for correctness: compare a and d
      epsmax = 0.0
      do j = 1, nx
         eps = abs(a(j)-d(j))
         if (eps > epsmax) epsmax = eps
      enddo
      write (*,*) 'maximum difference = ', epsmax
!
! deallocate memory for openmp
      deallocate(p_a,p_b,p_c)
! deallocate Host memory
      deallocate(a,b,c,d)
!
      end program
!
      subroutine fadd(a,b,c,nx)
      integer :: nx
      real, dimension(nx) :: a, b, c
      integer :: j
      do j = 1, nx
         a(j) = b(j) + c(j)
      enddo
      end subroutine
      
