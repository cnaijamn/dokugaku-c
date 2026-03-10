CBLAS
=====
- Reference implementation of the C interface to the legacy Fortran BLAS
- https://www.netlib.org/blas/blast-forum/

Install
-------
`% sudo pkg install cblas`

Compile
-------
```
% make
% ./samble1
### 内積 xT･y
80.000000
### l1ノルム l2ノルム
15.000000 7.416198
### ベクトルと行列の演算 y = αAx + βy
750.000000 1580.000000 2410.000000
### 行列同士の演算 C = αAB + βC
11.000000 14.000000 17.000000 20.000000
23.000000 30.000000 37.000000 44.000000
35.000000 46.000000 57.000000 68.000000
% ldd ./sample1
./sample1:
	libcblas.so.3 => /usr/local/lib/libcblas.so.3 (0x2950631f6000)
	libc.so.7 => /lib/libc.so.7 (0x2950649f5000)
	libblas.so.3 => /usr/local/lib/libblas.so.3 (0x29506680b000)
	libgfortran.so.5 => /usr/local/lib/gcc14/libgfortran.so.5 (0x295066c00000)
	libm.so.5 => /lib/libm.so.5 (0x295065168000)
	libquadmath.so.0 => /usr/local/lib/gcc14/libquadmath.so.0 (0x295065f07000)
	libsys.so.7 => /lib/libsys.so.7 (0x295067ee9000)
	libgcc_s.so.1 => /usr/local/lib/gcc14/libgcc_s.so.1 (0x295063e9e000)
	[vdso] (0x295061fda000)
```
