#import <time.h>
#import <stdio.h>
#import <stdlib.h>

float fabs(float x)
{
   if (x < 0)
      return -x;
   else
      return x;
}

float sqrtfcn(float val)
{
   float x = val/10;

   float dx;

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
	for (int i=0; i< 1000; i++){
  		start = clock();
  		sqrtfcn(rand() % 1001);		//random number from 0 to 1001
  		end = clock();
  		tot += end-start;
  	}
  	printf("%f\n",tot/1000);
}
