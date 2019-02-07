#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "fixed_op_64bit.h"

#define SHIFT_AMOUNT 30
#define EXEC_NUM 100000

int64_t fabss(int64_t x)
{
	if (x < 0)
		return -x;
	else
		return x;
}

int64_t sqrtfcn(int64_t val) {

	int64_t x = fixed_div_64(val,10737418240,SHIFT_AMOUNT); //10*2^30
   	int64_t dx;
	int64_t diff;
   	int64_t min_tol = 10737; //0.00001 * 2^30

   	int i, flag;

   	flag = 0;
   	if (val == 0 )
      	x = 0;
   	else {
      	for (i=1;i<20;i++)
      	{
			if (!flag) {
            dx = fixed_div_64((val - (fixed_mul_64(x,x,SHIFT_AMOUNT))),(fixed_mul_64(2147483648,x,SHIFT_AMOUNT)),SHIFT_AMOUNT);
            x = x + dx;
            diff = val - (fixed_mul_64(x,x,SHIFT_AMOUNT));
            if (fabss(diff) <= min_tol)
               	flag = 1;
        }
         	else {} /* JG */
/*            	x =x; */
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
	fp = fopen ("sqrt_fixed_results.txt","w");
	int64_t val;
	srand(5);
	for (int i=0; i< EXEC_NUM ; i++){
		val = (int64_t) rand() % 1001 << SHIFT_AMOUNT; //random value between 0 and 1000

		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		sqrtfcn(val);
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);

		fprintf (fp, "%lld\n",(long long)(diff(start,end).tv_sec * pow(10,9))+(long long)diff(start,end).tv_nsec);
	}

	fclose (fp);
	return 0;
}
