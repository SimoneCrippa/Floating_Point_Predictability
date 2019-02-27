#include <stdio.h>
#include <time.h>
#include <math.h>

#define EXEC_NUM 100000

int minver(int row, int col, double eps);
int  mmul(int  row_a, int col_a, int row_b, int col_b);

static double  a[3][3] = {
  {3.0, -6.0,  7.0},
  {9.0,  0.0, -5.0},
  {5.0, -8.0,  6.0},
};
double  b[3][3], c[3][3], aa[3][3], a_i[3][3], e[3][3], det;


double minver_fabs(double n)
{
	double f;

	if (n >= 0) f = n;
	else f = -n;
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
  	struct timespec start0,end0,start1,end1;
  	FILE * fp;
  	fp = fopen ("minver_floating_results.txt","w");

	for (int k=0; k< EXEC_NUM ; k++){
		int i, j;
		double eps;

		eps = 1.0e-6;

		for(i = 0; i < 3; i++)
	  		for(j = 0; j < 3; j++)
	    		aa[i][j] = a[i][j];

		clock_gettime(CLOCK_MONOTONIC_RAW, &start0);
		minver(3, 3, eps);
		clock_gettime(CLOCK_MONOTONIC_RAW, &end0);

		for(i = 0; i < 3; i++)
	  		for(j = 0; j < 3; j++)
	    		a_i[i][j] = a[i][j];

		clock_gettime(CLOCK_MONOTONIC_RAW, &start1);
		mmul(3, 3, 3, 3);
		clock_gettime(CLOCK_MONOTONIC_RAW, &end1);

    	fprintf (fp, "%lld\n",(long long)(diff(start0,end0).tv_sec * pow(10,9))+(long long)diff(start0,end0).tv_nsec
    	+ (long long)(diff(start1,end1).tv_sec * pow(10,9))+(long long)diff(start1,end1).tv_nsec);
	}

  	fclose (fp);
  	return 0;
}


int  mmul(int row_a, int col_a, int row_b, int col_b)
{
	int i, j, k, row_c, col_c;
	double w;

	row_c = row_a;
	col_c = col_b;

	if(row_c < 1 || row_b < 1 || col_c < 1 || col_a != row_b) return(999);
	for(i = 0; i < row_c; i++)
	{
		for(j = 0; j < col_c; j++)
		{
			w = 0.0;
			for(k = 0; k < row_b; k++)
				w += a[i][k] * b[k][j];
			c[i][j] = w;
		}
	}
	 return(0);

}


int minver(int row, int col, double eps)
{

	int work[500], i, j, k, r, iw, s, t, u, v;
	double w, wmax, pivot, api, w1;

	if(row < 2 || row > 500 || eps <= 0.0) return(999);
	w1 = 1.0;
	for(i = 0; i < row; i++)
		work[i] = i;
	for(k = 0; k < row; k++)
	{
		wmax = 0.0;
	    for(i = k; i < row; i++)
		{
			w = minver_fabs(a[i][k]);
			if(w > wmax)
		  	{
		    	wmax = w;
		    	r = i;
		  	}
		}
	    pivot = a[r][k];
	    api = minver_fabs(pivot);
	    if(api <= eps)
	    {
			det = w1;
			return(1);
		}
	    w1 *= pivot;
	    u = k * col;
	    v = r * col;
	    if(r != k)
		{
			w1 = -w;
			iw = work[k];
			work[k] = work[r];
			work[r] = iw;
			for(j = 0; j < row; j++)
		  	{
		    	s = u + j;
		    	t = v + j;
		    	w = a[k][j];
		    	a[k][j] = a[r][j];
		    	a[r][j] = w;
		  	}
		}
	    for(i = 0; i < row; i++)
			a[k][i] /= pivot;
	    for(i = 0; i < row; i++)
		{
			if(i != k)
			{
				v = i * col;
		    	s = v + k;
		    	w = a[i][k];
		    	if(w != 0.0)
				{
					for(j = 0; j < row; j++)
						if(j != k) a[i][j] -= w * a[k][j];
					a[i][k] = -w / pivot;
				}
			}
		}
	    a[k][k] = 1.0 / pivot;
	}
	for(i = 0; i < row; i++)
	{
		while(1)
		{
			k = work[i];
			if(k == i) break;
			iw = work[k];
			work[k] = work[i];
			work[i] = iw;
			for(j = 0; j < row; j++)
			{
				u = j * col;
		    	s = u + i;
		    	t = u + k;
		    	w = a[k][i];
		    	a[k][i] = a[k][k];
		    	a[k][k] = w;
		  	}
		}
	}
	det = w1;
	return(0);

}
