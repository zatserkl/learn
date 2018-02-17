*
* Main program to test DROOT
* May 8, 2011
*
* optic> gfortran droot.f
* optic> ./a.out
*  Enter a, b, c
* 1 -3 2
*  a =    1.0000000000000000       b =   -3.0000000000000000       c =    2.0000000000000000     
*  x1 =    1.0000000000000000       x2 =    2.0000000000000000       iflag =            0
*

* Tests from Chapter 2.6 of
* George E. Forsythe and Michael A. Malcolm and Cleve B. Moler, Computer Methods for Mathematical Computations
*
* From http://www.math.niu.edu/~rusin/known-math/99/root_finding
* For a very clear discussion of root-finding written by authors who _are_
* numerical analysis experts, see
* 
* @book
* 	{
* 	Forsythe-Malcolm-Moler,
* 	author = "George E. Forsythe and Michael A. Malcolm
* 		  and Cleve B. Moler",
* 	title = "Computer Methods for Mathematical Computations",
* 	publisher = "Prentice-Hall",
* 	address = "Englewood Cliffs",
* 	year = 1977,
* 	isbn = "0-13-165332-6",
* 	}
* 
* An additional benefit of Forsythe/Malcolm/Moler's book and software
* is that unlike the Numerical Recipes software, the FMM software is
* freely available from Netlib
*    http://www.netlib.org/fmm		# double precision
*    http://www.netlib.org/sfmm		# single precision
* and may be (legally) freely redistributed along with your own code.

* optic> ./a.out
*  Enter a, b, c
* 1 -4 3.9999999
*  a =    1.0000000000000000       b =   -4.0000000000000000       c =    3.9999999000000002     
*  x1 =    1.9996837722342420       x2 =    2.0003162277657580       iflag =            0
* optic> 
* optic> ./a.out
*  Enter a, b, c
* 1e-30 -1e30 1e30
*  a =   1.00000000000000008E-030  b =  -1.00000000000000002E+030  c =   1.00000000000000002E+030
*  x1 =    1.0000000000000000       x2 =   9.99999999999999949E+059  iflag =            0
* optic> 
* optic> ./a.out
*  Enter a, b, c
* 6e30 5e30 -4e30
*  a =   5.99999999999999956E+030  b =   4.99999999999999982E+030  c =  -4.00000000000000008E+030
*  x1 =   0.50000000000000000       x2 =   -1.3333333333333335       iflag =            0
* optic> 
* optic> ./a.out
*  Enter a, b, c
* 1 -1e5 1
*  a =    1.0000000000000000       b =   -100000.00000000000       c =    1.0000000000000000     
*  x1 =   1.00000000010000011E-005  x2 =    99999.999989999982       iflag =            0

      double precision a, b, c, x1, x2
      integer iflag
      print*, 'Enter a, b, c'
      read*, a, b, c
      print*, 'a = ', a, ' b = ', b, ' c = ', c
      iflag = 0
      call DROOT(a, b, c, x1, x2, iflag)
      print*, 'x1 = ', x1, ' x2 = ', x2, ' iflag = ', iflag
      end

*                                         @METAGS DROOT
*                                         06-02-98 03:47am
*--------------- DROOT ---------------
*
      subroutine DROOT(a,b,c,x1,x2,ierr)
*
*     For square equation a*x**2 + b*x + c = 0
*     calculates REAL roots.F
*     For COMPLEX returns in x1 real part and in x2 imaginary part
*     of root -b/(2*a) + i*sqrt(-D)/(2*a)
*     To preserve computer accuracy use formula x1 = 2*c/(-b-sqrt(D))
*     Error flags:
*      0: normal
*      1: any roots: a=b=c=0
*      2: complex roots
*     -1: no roots: a=b=0, c<>0
*
      double precision a,b,c,x1,x2
      integer ierr
      double precision D

      x1 = 0.d0
      x2 = 0.d0
      ierr = 0

*      print*, a,b,c
*      call WAIT('DROOT: a,b,c')
      if (a .EQ. 0d0) then
         if (b.EQ.0d0) then
            if (c.EQ.0.d0) then
*               print*, 'DROOT: Any roots: a=b=c=0'
               ierr = 1
            else
               print*, 'DROOT ERROR: No roots: a=b=0, c<>0'
               ierr = -1
            endif
            RETURN
         endif
         x1 = -c/b
         x2 = x1
         RETURN
      endif

      D = b**2 - 4d0*a*c
*      print*, 'D =', D
*      call WAIT('DROOT: D')
      if (D .LT. 0.d0) then
*         print*, 'DROOT: Complex roots'
         x1 = -b/(2.d0*a)
         x2 = sqrt(-D)/(2.d0*a)
         ierr = 2
         RETURN
      elseif (D .EQ. 0.d0) then
         x1 = -b/(2.d0*a)
         x2 = x1
         RETURN
      endif

      if (b .GT. 0.d0) then
*        .. compute "minus" root
         x1 = 2.d0*c/(-b - sqrt(D))
      else
*        .. compute "plus" root
         x1 = 2.d0*c/(-b + sqrt(D))
      endif

*     .. use Viete formulae for the other root
      if (x1 .NE. 0.d0) then
*        .. to preserve computer accuracy
         x2 =  (c/a) / x1
      else
         x2 = -(b/a) - x1
      endif
      END

*                                         @METAGS WAIT
*                                         11-15-96 09:45pm
*--------------- WAIT ---------------
*
      SUBROUTINE WAIT(mess)
      character mess*(*), ch*1
      if ((LEN(mess).GT.0) .AND. (mess.NE.' ')) print*, mess
      print*, '<CR>=Continue, Q=Quit'
      read 1, ch
      if ((ch.EQ.'q') .OR. (ch.EQ.'Q')) STOP
      RETURN
    1 FORMAT(A)
      END
