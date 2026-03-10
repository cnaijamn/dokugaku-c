/*
/usr/local/share/doc/spblas/blas-report.pdf
P.110 : "Sparse Matrices: Inserting List of Entries"
P.115 : "C exaple: sparse matrix/vector multiplication"
*/
#include <stdio.h>
#include <spblas/blas_sparse.h>

/*
4x4 matrix
A :=  1.1    0    0    0
        0  2.2    0  2.4
        0    0  3.3    0
      4.1    0    0  4.4

y := Ax
*/

int
main(void)
{
	const int N  = 4;
	const int nz = 6;
	double val[] = { 1.1, 2.2, 2.4, 3.3, 4.1, 4.4 }; // 要素の値
	int   indx[] = {   0,   1,   1,   2,   3,   3 }; // val[i]が該当する行位置
	int   jndx[] = {   0,   1,   3,   2,   0,   3 }; // val[i]が該当する列位置
	double   x[] = { 1.0, 1.0, 1.0, 1.0 };
	double   y[] = { 0.0, 0.0, 0.0, 0.0 };

	blas_sparse_matrix A; // Sparse matrix handle (int)
	int i;
	double alpha = 1.0;

	/*-----------------------------------*/
	/* Step 1: Create Sparse BLAS Handle */
	/*-----------------------------------*/

	A = BLAS_duscr_begin(N, N);

	/*------------------------*/
	/* Step 2: insert entries */
	/*------------------------*/

	for (i = 0; i < nz; i++)
		BLAS_duscr_insert_entry(A, val[i], indx[i], jndx[i]);

	/*------------------------------------------------*/
	/* Step 3: Complete construction of sparse matrix */
	/*------------------------------------------------*/

	BLAS_duscr_end(A);

	/*-----------------------------------------------*/
	/* Step 4: Compute Matrix vector product y = A*x */
	/*-----------------------------------------------*/

	BLAS_dusmv(blas_no_trans, alpha, A, x, 1, y, 1);

	for (i = 0; i < N; i++)
		printf("%f ", y[i]);
	putchar('\n');
	// 1.100000 4.600000 3.300000 8.500000

	/*-------------------------------*/
	/* Step 5: Release Matrix Handle */
	/*-------------------------------*/

	BLAS_usds(A);

	return 0;
}
