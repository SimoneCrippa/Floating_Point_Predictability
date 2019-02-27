/*
#include <stdio.h>
#include <math.h>
*/
#include <stdint.h>
#include "fixed_op_64bit.h"

#define SHIFT_AMOUNT 30

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
