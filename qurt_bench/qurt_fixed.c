#include <stdint.h>
#include "fixed_op_64bit.h"

#define SHIFT_AMOUNT 30

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
	a[0] =  (int64_t)1 << SHIFT_AMOUNT;
	a[1] =  (int64_t)-3 << SHIFT_AMOUNT;
	a[2] =  (int64_t)2 << SHIFT_AMOUNT;

	qurt();


  a[0] =  (int64_t)1 << SHIFT_AMOUNT;
	a[1] =  (int64_t)-2 << SHIFT_AMOUNT;
	a[2] =  (int64_t)1 << SHIFT_AMOUNT;

  qurt();


  a[0] =  (int64_t)1 << SHIFT_AMOUNT;
	a[1] =  (int64_t)-4 << SHIFT_AMOUNT;
	a[2] =  (int64_t)8 << SHIFT_AMOUNT;

  qurt();
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
