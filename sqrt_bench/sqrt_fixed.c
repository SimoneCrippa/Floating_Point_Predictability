/*
#include <stdio.h>
#include <stdint.h>
#include <math.h>
*/

#define SHIFT_AMOUNT 30

int64_t fixed_mul_30(int64_t x, int64_t y)
	{
		x = x >> SHIFT_AMOUNT;
		return (x * y);
	}

int64_t fixed_div_30(int64_t x, int64_t y)
  {
		return ((((__int128)x << SHIFT_AMOUNT) / y));
  }
  
int64_t fabss(int64_t x)
{
   	if (x < 0)
      	return -x;
   	else
      	return x;
}

int64_t sqrtfcn(int64_t val, int64_t x, int64_t min_tol, int64_t val2)
{
   	//_int128 x = val/10;

   	int64_t dx;

   	int64_t diff;
   	//int64_t min_tol = 0.00001;

   	int i, flag;

   	flag = 0;
   	if (val == 0 )
      	x = 0;
   	else {
      	for (i=1;i<20;i++)
      	{
         	if (!flag) {
            dx = fixed_div_30((val - (fixed_mul_30(x,x))),(fixed_mul_30(val2,x)));
            x = x + dx;
            diff = val - (fixed_mul_30(x,x));
            if (fabss(diff) <= min_tol)
               	flag = 1;
        }
         	else {} /* JG */
/*            	x =x; */
      	}
   }
   	return (x);
}

/*
void main()
{
  	int64_t val = (int64_t) 10 << SHIFT_AMOUNT;
  	int64_t x = fixed_div_30(val,(int64_t) 10 << SHIFT_AMOUNT);
  	int64_t min_tol = (int64_t)(0.00001 * pow(2,30));
  	int64_t val2 = (int64_t) 2 << SHIFT_AMOUNT;
  	double res = ((double)sqrtfcn(val,x,min_tol,val2))/pow(2,30);
  	printf("%f\n",res);
  
}
*/