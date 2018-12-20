#include <time.h>
#include <stdio.h>
#include <stdlib.h>

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
	float tot = 0;
  	float val;
  	srand(5);
	for (int i=0; i< 1000000 ; i++){
      	val = rand() % 1001; //random number from 0 to 1001
  		
  		start = clock();
  		sqrtfcn(val);
  		end = clock();
  		
  		tot += end-start;
  	}
  	printf("%f\n",tot/1000000 );
}
