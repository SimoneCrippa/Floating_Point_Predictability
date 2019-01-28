#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define EXEC_NUM 100000

double a[3], x1[2], x2[2];
int flag;

int  qurt();


double qurt_fabs(double n)
{
	double f;

	if (n >= 0) f = n;
	else f = -n;
	return f;
}

double qurt_sqrt(val)
double val;
{
	double x = val/10;

	double dx;

  	double diff;
  	double min_tol = 0.00001;

  	int i, flag;

  	flag = 0;
  	if (val == 0 ) x = 0;
  	else {
    	for (i=1;i<20;i++)
      	{
			if (!flag) {
	  			dx = (val - (x*x)) / (2.0 * x);
	  			x = x + dx;
	  			diff = val - (x*x);
	  			if (qurt_fabs(diff) <= min_tol) flag = 1;
			}
			else {} /* JG */
					/*	  x =x; */
		}
  }
  return (x);
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
  	fp = fopen ("qurt_floating_results.txt","w");
	srand(5);
	for (int i=0; i< EXEC_NUM ; i++)
  	{
    	a[0]= (rand() % 100 - 50);
    	a[1]= (rand() % 100 - 50);
    	a[2]= (rand() % 100 - 50);

    	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    	qurt();
    	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    	fprintf (fp, "%lld\n",(long long)(diff(start,end).tv_sec * pow(10,9))+(long long)diff(start,end).tv_nsec);

  	}
 	fclose(fp);
  	return 0;
}

int  qurt()
{
	double  d, w1, w2;

	if(a[0] == 0.0) return(999);
	d = a[1]*a[1] - 4 * a[0] * a[2];
	w1 = 2.0 * a[0];
	w2 = qurt_sqrt(qurt_fabs(d));
	if(d > 0.0)
	{
		flag = 1;
		x1[0] = (-a[1] + w2) / w1;
		x1[1] = 0.0;
		x2[0] = (-a[1] - w2) / w1;
		x2[1] = 0.0;
		return(0);
	}
	else if(d == 0.0)
	{
		flag = 0;
		x1[0] = -a[1] / w1;
		x1[1] = 0.0;
		x2[0] = x1[0];
		x2[1] = 0.0;
		return(0);
	}
	else
	{
		flag = -1;
		w2 /= w1;
		x1[0] = -a[1] / w1;
		x1[1] = w2;
		x2[0] = x1[0];
		x2[1] = -w2;
		return(0);
	}
}
