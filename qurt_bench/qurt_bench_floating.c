#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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


int main()
{

  clock_t start, end;
  int clock_cycles [EXEC_NUM];
  srand(5);
  for (int i = 0; i < EXEC_NUM; i++)
  {
    a[0]= (rand() % 100 - 50);
    a[1]= (rand() % 100 - 50);
    a[2]= (rand() % 100 - 50);
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
