#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "fixed_op_64bit.h"

#define SHIFT_AMOUNT 30
#define EXEC_NUM 100000

int64_t a[50][50], b[50], x[50];

int ludcmp( /* int nmax, */ int n, int64_t eps);

static int64_t fab(int64_t n)
{
	int64_t f;

	if (n >= 0)
		f = n;
	else
		f = -n;
	return f;
}

struct timespec diff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}

int main()
{
	struct timespec start,end;
	FILE * fp;
	fp = fopen ("ludcmp_fixed_results.txt","w");
	int i, j;
	srand(5);
	int64_t eps;
  	int64_t w;
	eps = 1074; //1.0 * 10^-6 * 2^30

	for (int k=0; k< EXEC_NUM ; k++){
   		int n = (rand()%50)+1; /*, nmax = 50*/
   		for (i = 0; i <= n; i++) {
			w = 0;
			for (j = 0; j <= n; j++) {
				a[i][j] = ((int64_t)(i + j + 2)) << SHIFT_AMOUNT;
				if (i == j)
					a[i][j] = fixed_mul_64(a[i][j],10737418240,SHIFT_AMOUNT);		//10 shifted by SHIFT_AMOUNT
				w += a[i][j];
			}
			b[i] = w;
			}

		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		ludcmp( /* nmax, */ n, eps);
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);

		fprintf (fp, "%lld\n",(long long)(diff(start,end).tv_sec * pow(10,9))+(long long)diff(start,end).tv_nsec);
	}
	fclose (fp);
	return 0;
}

int ludcmp( /* int nmax, */ int n, int64_t eps)
{

	int i, j, k;
	int64_t w, y[100];

	if (n > 99 || eps <= 0)
		return (999);
	for (i = 0; i < n; i++) {
		//		printf("A[i][i]: %lld eps:%lld\n",a[i][i],eps);
		if (fab(a[i][i]) <= eps)
			return (1);
		for (j = i + 1; j <= n; j++) {
			w = a[j][i];
			if (i != 0)
				for (k = 0; k < i; k++)
          			w -= fixed_mul_64(a[j][k],a[k][i],SHIFT_AMOUNT);
				a[j][i] = fixed_div_64(w,a[i][i],SHIFT_AMOUNT);
		}
		for (j = i + 1; j <= n; j++) {
			w = a[i + 1][j];
			for (k = 0; k <= i; k++)
				w -= fixed_mul_64(a[i + 1][k],a[k][j],SHIFT_AMOUNT);
			a[i + 1][j] = w;
		}
	}
	y[0] = b[0];
	for (i = 1; i <= n; i++) {
		w = b[i];
		for (j = 0; j < i; j++)
			w -= fixed_mul_64(a[i][j],y[j],SHIFT_AMOUNT);
		y[i] = w;
	}
	x[n] = fixed_div_64(y[n],a[n][n],SHIFT_AMOUNT);
	for (i = n - 1; i >= 0; i--) {
		w = y[i];
		for (j = i + 1; j <= n; j++)
			w -= fixed_mul_64(a[i][j],x[j],SHIFT_AMOUNT);
		x[i] = fixed_div_64(w,a[i][i],SHIFT_AMOUNT);
	}
	return (0);

}
