#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EXEC_NUM 100000

double fabs(double x)
{
   	if (x < 0)
      	return -x;
   	else
      	return x;
}

double sqrtfcn(double val)
{
   	double x = val/10;

   	double dx;

   	double diff;
   	double min_tol = 0.00001;

   	int i, flag;

   	flag = 0;
   	if (val == 0 )
      	x = 0;
  	else {
      	for (i=1;i<20;i++)
      	{
        if (!flag) {
            dx = (val - (x*x)) / (2.0 * x);
            x = x + dx;
            diff = val - (x*x);
            if (fabs(diff) <= min_tol)
               	flag = 1;
        }
        else {} /* JG */
/*            x =x; */
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
  fp = fopen ("sqrt_float_results.txt","w");
	float val;
	srand(5);
	for (int i=0; i< EXEC_NUM ; i++){
      	val = rand() % 1001; //random number from 0 to 1001

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        sqrtfcn(val);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        fprintf (fp, "%lld\n",(long long)(diff(start,end).tv_sec * pow(10,9))+(long long)diff(start,end).tv_nsec);
  }

	fclose (fp);
	return 0;
}
