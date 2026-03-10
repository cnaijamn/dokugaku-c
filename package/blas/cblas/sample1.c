#include <stdio.h>
#include <cblas.h>

int
main(void)
{
	puts("### 内積 xT･y");
	{
		double x[] = {1.0, 2.0, 3.0, 4.0, 5.0};
		double y[] = {6.0, 7.0, 8.0, 9.0, 0.0};
		double d   = cblas_ddot(5, x, 1, y, 1);
		printf("%f\n", d); // 80.000000
	}

	puts("### l1ノルム l2ノルム");
	{
		double x[] = {1.0, -2.0, 3.0, -4.0, 5.0};
		double n1  = cblas_dasum(5, x, 1);
		double n2  = cblas_dnrm2(5, x, 1);
		printf("%f %f\n", n1, n2); // 15.000000 7.416198
	}

	puts("### ベクトルと行列の演算 y = αAx + βy");
	{
		double A[] = { 1.0,  2.0,  3.0,  4.0,
			       5.0,  6.0,  7.0,  8.0,
			       9.0, 10.0, 11.0, 12.0};
		double x[] = {10.0, 20.0, 30.0, 40.0};
		double y[] = {50.0, 60.0, 70.0};
		double alpha = 2.0, beta = 3.0;

		cblas_dgemv(
		    CblasRowMajor, CblasNoTrans, 3, 4,
		    alpha,
		    A, 4,
		    x, 1,
		    beta,
		    y, 1
		);
		for (int i = 0; i < 3; i++)
			printf("%f ", y[i]);
		// 750.000000 1580.000000 2410.000000
		putchar('\n');
	}

	puts("### 行列同士の演算 C = αAB + βC");
	{
		double A[6] = {1.0, 2.0,
			       3.0, 4.0,
			       5.0, 6.0};
		double B[8] = {1.0, 2.0, 3.0, 4.0,
			       5.0, 6.0, 7.0, 8.0};
		double C[12];
		double alpha = 1.0, beta = 0.0;

		cblas_dgemm(
		    CblasRowMajor, CblasNoTrans, CblasNoTrans, 3, 4, 2,
		    alpha,
		    A, 2,
		    B, 4,
		    beta,
		    C, 4
		);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++)
				printf("%f ", C[i * 4 + j]);
			putchar('\n');
		}
		// 11.000000 14.000000 17.000000 20.000000
		// 23.000000 30.000000 37.000000 44.000000
		// 35.000000 46.000000 57.000000 68.000000
	}

	return (0);
}
