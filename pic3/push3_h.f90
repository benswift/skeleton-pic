!-----------------------------------------------------------------------
! Interface file for push3.f
      module push3_h
      implicit none
!
      interface
         subroutine DISTR3(part,vtx,vty,vtz,vdx,vdy,vdz,npx,npy,npz,    &
     &idimp,nop,nx,ny,nz,ipbc)
         implicit none
         integer :: npx, npy, npz, idimp, nop, nx, ny, nz, ipbc
         real :: vtx, vty, vtz, vdx, vdy, vdz
         real, dimension(idimp,nop) :: part
         end subroutine
      end interface
!
      interface
         subroutine GPUSH3L(part,fxyz,qbm,dt,ek,idimp,nop,nx,ny,nz,nxv, &
     &nyv,nzv,ipbc)
         implicit none
         integer :: idimp, nop, nx, ny, nz, nxv, nyv, nzv, ipbc
         real :: qbm, dt, ek
         real, dimension(idimp,nop) :: part
         real, dimension(3,nxv,nyv,nzv) :: fxyz
         end subroutine
      end interface
!
      interface
         subroutine GPOST3L(part,q,qm,nop,idimp,nxv,nyv,nzv)
         implicit none
         integer :: nop, idimp, nxv, nyv, nzv
         real :: qm
         real, dimension(idimp,nop) :: part
         real, dimension(nxv,nyv,nzv) :: q
         end subroutine
      end interface
!
      interface
         subroutine DSORTP3YZL(parta,partb,npic,idimp,nop,ny1,nyz1)
         implicit none
         integer :: idimp, nop, ny1, nyz1
         real, dimension(idimp,nop) :: parta, partb
         integer, dimension(nyz1) :: npic
         end subroutine
      end interface
!
      interface
         subroutine CGUARD3L(fxyz,nx,ny,nz,nxe,nye,nze)
         implicit none
         integer :: nx, ny, nz, nxe, nye, nze
         real, dimension(3,nxe,nye,nze) :: fxyz
         end subroutine
      end interface
!
      interface
         subroutine AGUARD3L(q,nx,ny,nz,nxe,nye,nze)
         implicit none
         integer :: nx, ny, nz, nxe, nye, nze
         real, dimension(nxe,nye,nze) :: q
         end subroutine
      end interface
!
      interface
         subroutine POIS33(q,fxyz,isign,ffc,ax,ay,az,affp,we,nx,ny,nz,  &
     &nxvh,nyv,nzv,nxhd,nyhd,nzhd)
         implicit none
         integer :: isign, nx, ny, nz, nxvh, nyv, nzv, nxhd, nyhd, nzhd
         real :: ax, ay, az, affp, we
         real, dimension(2*nxvh,nyv,nzv) :: q
         real, dimension(3,2*nxvh,nyv,nzv) :: fxyz
         complex, dimension(nxhd,nyhd,nzhd) :: ffc
         end subroutine
      end interface
!
      interface
         subroutine WFFT3RINIT(mixup,sct,indx,indy,indz,nxhyzd,nxyzhd)
         implicit none
         integer :: indx, indy, indz, nxhyzd, nxyzhd
         integer, dimension(nxhyzd) :: mixup
         complex, dimension(nxyzhd) :: sct
         end subroutine
      end interface
!
      interface
         subroutine WFFT3RX(f,isign,mixup,sct,indx,indy,indz,nxhd,nyd,  &
     &nzd,nxhyzd,nxyzhd)
         implicit none
         integer :: isign, indx, indy, indz, nxhd, nyd, nzd
         integer :: nxhyzd, nxyzhd
         real, dimension(2*nxhd,nyd,nzd) :: f
         integer, dimension(nxhyzd) :: mixup
         complex, dimension(nxyzhd) :: sct
         end subroutine
      end interface
!
      interface
         subroutine WFFT3R3(f,isign,mixup,sct,indx,indy,indz,nxhd,nyd,  &
     &nzd,nxhyzd,nxyzhd)
         implicit none
         integer :: isign, indx, indy, indz, nxhd, nyd, nzd
         integer :: nxhyzd, nxyzhd
         real, dimension(3,2*nxhd,nyd,nzd) :: f
         integer, dimension(nxhyzd) :: mixup
         complex, dimension(nxyzhd) :: sct
         end subroutine
      end interface
!
      interface
          subroutine FFT3RXY(f,isign,mixup,sct,indx,indy,indz,nzi,nzp,  &
     &nxhd,nyd,nzd,nxhyzd,nxyzhd)
         implicit none
         integer :: isign, indx, indy, indz, nzi, nzp, nxhd, nyd, nzd
         integer :: nxhyzd, nxyzhd
         real, dimension(2*nxhd,nyd,nzd) :: f
         integer, dimension(nxhyzd) :: mixup
         complex, dimension(nxyzhd) :: sct
         end subroutine
      end interface
!
      interface
         subroutine FFT3RXZ(f,isign,mixup,sct,indx,indy,indz,nyi,nyp,   &
     &nxhd,nyd,nzd,nxhyzd,nxyzhd)
         implicit none
         integer :: isign, indx, indy, indz, nyi, nyp, nxhd, nyd, nzd
         integer :: nxhyzd, nxyzhd
         real, dimension(2*nxhd,nyd,nzd) :: f
         integer, dimension(nxhyzd) :: mixup
         complex, dimension(nxyzhd) :: sct
         end subroutine
      end interface
!
      interface
         subroutine FFT3R3XY(f,isign,mixup,sct,indx,indy,indz,nzi,nzp,  &
     &nxhd,nyd,nzd,nxhyzd,nxyzhd)
         implicit none
         integer :: isign, indx, indy, indz, nzi, nzp, nxhd, nyd, nzd
         integer :: nxhyzd, nxyzhd
         real, dimension(3,2*nxhd,nyd,nzd) :: f
         integer, dimension(nxhyzd) :: mixup
         complex, dimension(nxyzhd) :: sct
         end subroutine
      end interface
!
      interface
         subroutine FFT3R3Z(f,isign,mixup,sct,indx,indy,indz,nyi,nyp,   &
     &nxhd,nyd,nzd,nxhyzd,nxyzhd)
         implicit none
         integer :: isign, indx, indy, indz, nyi, nyp, nxhd, nyd, nzd
         integer :: nxhyzd, nxyzhd
         real, dimension(3,2*nxhd,nyd,nzd) :: f
         integer, dimension(nxhyzd) :: mixup
         complex, dimension(nxyzhd) :: sct
         end subroutine
      end interface
!
      interface
         function ranorm()
         implicit none
         double precision :: ranorm
         end function
      end interface
!
      interface
         function randum()
         implicit none
         double precision :: randum
         end function
      end interface
!
      end module
