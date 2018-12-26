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

int main(void)
{
	int clock_cycles[EXEC_NUM];
	int i, j;
	srand(5);
	int64_t eps;
  	int64_t w;
  	clock_t start,end;
  	float tot = 0.0;
	eps = 1.0e-6 * pow(2,30);

  	for (int k=0; k< EXEC_NUM ; k++){
   		int n = (rand()%50)+1; /*, nmax = 50*/
   		for (i = 0; i <= n; i++) {
			w = 0;
			for (j = 0; j <= n; j++) {
				a[i][j] = (i + 1) + (j + 1);
				if (i == j)
					a[i][j] *= 10737418240;		//10 shifted by SHIFT_AMOUNT
				w += a[i][j];
			}
			b[i] = w;
		}
   		
   		start = clock();
    	ludcmp( /* nmax, */ n, eps);
    	end = clock();
		
    	clock_cycles[k]=end-start;
	}
	
	int first = 0,second = 0,third = 0;
	for (int i = 0; i < EXEC_NUM ; i ++)
  	{
		if (clock_cycles[i] > first)	
		{
			third = second;
        	second = first;
        	first = clock_cycles[i];
      	}
      	else if (clock_cycles[i] > second)
      	{
        	third = second;
        	second = clock_cycles[i];
      	}
      	else if (clock_cycles[i] > third)
        	third = clock_cycles[i];
  	}
	
	printf("Three WCET are: %d %d %d\n", first, second, third);
  	return 0;
}

int ludcmp( /* int nmax, */ int n, int64_t eps)
{

	int i, j, k;
	int64_t w, y[100];

	if (n > 99 || eps <= 0)	
		return (999);
	for (i = 0; i < n; i++) {
		if (fab(a[i][i]) <= eps)
			return (1);
		for (j = i + 1; j <= n; j++) {
			w = a[j][i];
			if (i != 0)
				for (k = 0; k < i; k++)
          			w -= fixed_mul_64(a[j][k],a[k][i]);
				a[j][i] = fixed_div_64(w,a[i][i]);
		}
		for (j = i + 1; j <= n; j++) {
			w = a[i + 1][j];
			for (k = 0; k <= i; k++)
				w -= fixed_mul_64(a[i + 1][k],a[k][j]);
			a[i + 1][j] = w;
		}
	}
	y[0] = b[0];
	for (i = 1; i <= n; i++) {
		w = b[i];
		for (j = 0; j < i; j++)
			w -= fixed_mul_64(a[i][j],y[j]);
		y[i] = w;
	}
	x[n] = fixed_div_64(y[n],a[n][n]);
	for (i = n - 1; i >= 0; i--) {
		w = y[i];
		for (j = i + 1; j <= n; j++)
			w -= fixed_mul_64(a[i][j],x[j]);
		x[i] = fixed_div_64(w,a[i][i]);
	}
	return (0);

}
