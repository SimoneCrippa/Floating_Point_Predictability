#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "fixed_op_64bit.h"

#define SHIFT_AMOUNT 30
#define EXEC_NUM 100000

int64_t a[3], x1[2], x2[2];
int flag;

int  qurt();


int64_t qurt_fabs(int64_t n)
{
  int64_t f;

  if (n >= 0) f = n;
  else f = -n;
  return f;
}

int64_t qurt_sqrt(val)
int64_t val;
{
  int64_t x = fixed_div_64(val,(int64_t)10 << SHIFT_AMOUNT);

  int64_t dx;

  int64_t diff;
  int64_t min_tol = 10737; //0.00001 * 2^30

  int i, flag;

  flag = 0;
  if (val == 0 ) x = 0;
  else {
    for (i=1;i<20;i++)
      {
	if (!flag) {
	  dx = fixed_div_64((val - fixed_mul_64(x,x)),(fixed_mul_64(2 << SHIFT_AMOUNT,x)));
	  x = x + dx;
	  diff = val - fixed_mul_64(x,x);
	  if (qurt_fabs(diff) <= min_tol) flag = 1;
	}
	else {} /* JG */
/*	  x =x; */
      }
  }
  return (x);
}


int main()
{
  clock_t start, end;
  int clock_cycles [EXEC_NUM];
  srand(5);
  for (int i = 0; i < EXEC_NUM; i++)
  {
    a[0]= (rand() % 100 - 50) << SHIFT_AMOUNT;
    a[1]= (rand() % 100 - 50) << SHIFT_AMOUNT;
    a[2]= (rand() % 100 - 50) << SHIFT_AMOUNT;
    start = clock();
    qurt();
    end = clock();
    clock_cycles[i] = end - start;
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

int  qurt()
{
	int64_t  d, w1, w2;

	if(a[0] == 0.0) return(999);
	d = fixed_mul_64(a[1],a[1]) - (fixed_mul_64(fixed_mul_64((int64_t)4 << SHIFT_AMOUNT,a[0]),a[2]));
	w1 = fixed_mul_64(2 << SHIFT_AMOUNT,a[0]);
	w2 = qurt_sqrt(qurt_fabs(d));
	if(d > 0.0)
	{
		 flag = 1;
		 x1[0] = fixed_div_64((-a[1] + w2),w1);
		 x1[1] = 0.0;
		 x2[0] = fixed_div_64((-a[1] - w2),w1);
		 x2[1] = 0.0;
		 return(0);
	}
	else if(d == 0.0)
	{
		 flag = 0;
		 x1[0] = fixed_div_64(-a[1],w1);
		 x1[1] = 0.0;
		 x2[0] = x1[0];
		 x2[1] = 0.0;
		 return(0);
	}
	else
	{
		 flag = -1;
		 w2 = fixed_div_64(w2,w1);
		 x1[0] = fixed_div_64(-a[1],w1);
		 x1[1] = w2;
		 x2[0] = x1[0];
		 x2[1] = -w2;
		 return(0);
	}
}
