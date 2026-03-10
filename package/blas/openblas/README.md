OpenBLAS
========
- Optimized BLAS library based on GotoBLAS2
- http://www.openmathlib.org/OpenBLAS/
- https://github.com/OpenMathLib/OpenBLAS

Install
-------
`% sudo pkg install openblas`

Compile
-------
```sh
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
	libopenblas.so.0 => /usr/local/lib/libopenblas.so.0 (0x27dbc1c00000)
	libomp.so => /usr/lib/libomp.so (0x27dbc4823000)
	libc.so.7 => /lib/libc.so.7 (0x27dbc59ef000)
	libthr.so.3 => /lib/libthr.so.3 (0x27dbc6044000)
	libgfortran.so.5 => /usr/local/lib/gcc14/libgfortran.so.5 (0x27dbc7400000)
	libm.so.5 => /lib/libm.so.5 (0x27dbc698b000)
	libsys.so.7 => /lib/libsys.so.7 (0x27dbc781e000)
	libquadmath.so.0 => /usr/local/lib/gcc14/libquadmath.so.0 (0x27dbc8aaa000)
	libgcc_s.so.1 => /usr/local/lib/gcc14/libgcc_s.so.1 (0x27dbc914e000)
	[vdso] (0x27dbc0efc000)
```

REPL (with Cling)
-----------------
```sh
% sudo pkg install cling
% rehash
% cling `pkgconf --cflags --libs openblas`
****************** CLING ******************
* Type C++ code and press enter to run it *
*             Type .q to exit             *
*******************************************
[cling]$ #include <cblas.h>
[cling]$ int M = 2, N = 2, K = 3;
[cling]$ float m1[] = { 1,2,3, 4,5,6 };
[cling]$ float m2[] = { 1,2, 3,4, 5,6 };
[cling]$ float m3[] = { 0,0, 0,0 };
[cling]$ float alpha = 1.0, beta = 0.0;
[cling]$ cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, m1, K, m2, N, beta, m3, 2);
[cling]$ m3
(float[4]) { 22.0000f, 28.0000f, 49.0000f, 64.0000f }
[cling]$
```
