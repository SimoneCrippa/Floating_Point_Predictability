#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;
#define M 7
#define NSTACK 50
#define SHIFT_AMOUNT 14

volatile float arr_float[20] = {
  5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
  10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 88.88
};

int64_t arr[20];

void fillarray()
{
  for(int i = 0; i < 20; i++)
      arr[i] = arr_float[i] * pow(2,SHIFT_AMOUNT);
}

int istack[100];

void sort(unsigned long n)
{
	unsigned long i,ir=n,j,k,l=1;
	int jstack=0;
	int flag;
	int64_t a,temp;

	flag = 0;
	while (1) {
		if (ir-l < M) {
			for (j=l+1;j<=ir;j++) {
				a=arr[j];
				for (i=j-1;i>=l;i--) {
					if (arr[i] <= a) break;
					arr[i+1]=arr[i];
				}
				arr[i+1]=a;
			}
			if (jstack == 0) break;
			ir=istack[jstack--];
			l=istack[jstack--];
		} else {
			k=(l+ir) >> 1;
			SWAP(arr[k],arr[l+1])
			if (arr[l] > arr[ir]) {
				SWAP(arr[l],arr[ir])
			}
			if (arr[l+1] > arr[ir]) {
				SWAP(arr[l+1],arr[ir])
			}
			if (arr[l] > arr[l+1]) {
				SWAP(arr[l],arr[l+1])
			}
			i=l+1;
			j=ir;
			a=arr[l+1];
			for (;;) {
				i++; while (arr[i] < a) i++;
				j--; while (arr[j] > a) j--;
				if (j < i) break;
				SWAP(arr[i],arr[j]);
			}
			arr[l+1]=arr[j];
			arr[j]=a;
			jstack += 2;

			if (ir-i+1 >= j-l) {
				istack[jstack]=ir;
				istack[jstack-1]=i;
				ir=j-1;
			} else {
				istack[jstack]=j-1;
				istack[jstack-1]=l;
				l=i;
			}
		}
	}
}

int main(void)
{
  fillarray();
  clock_t start,end;
  float tot = 0;
  for(int i = 0; i < 1000000; i++)
  {
    start = clock();

    sort(19);
    end = clock();

    tot += end - start;
  }
  printf("Time elapsed: %f\n",tot/1000000);
  return 0;
}
