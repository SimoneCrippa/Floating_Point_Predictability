#include <time.h>
#include <stdio.h>
#include <stdlib.h>

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

void main(){
	clock_t start, end;
  int clock_cycles [EXEC_NUM];
  float val;
  srand(5);
	for (int i=0; i< EXEC_NUM ; i++){
      val = rand() % 1001; //random number from 0 to 1001

  		start = clock();
  		sqrtfcn(val);
  		end = clock();

  		clock_cycles[i] = end-start;
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
}
