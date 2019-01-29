#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

float selectt(unsigned long k, unsigned long n);

#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;
#define EXEC_NUM 100000

float arr[20];

void fillarray()
{
	for (int i = 0; i < 20; i++)
		arr[i] = (rand() % 100000) / 100;
}
//selectt instead of select since there is a conflict with a primitive in Linux
float selectt(unsigned long k, unsigned long n)
{
	unsigned long   i, ir, j, l, mid;
	float           a, temp;
	int             flag, flag2;

	l = 0;
	ir = n - 1;
	flag = 0;
	while (!flag) {
		if (ir <= l + 1) {
			if (ir == l + 1) {
				if (arr[ir] < arr[l]) {
					SWAP(arr[l], arr[ir])
				}
			}
			flag = 1;
		} else if (!flag) {
			mid = (l + ir) >> 1;
			SWAP(arr[mid], arr[l + 1])
			if (arr[l + 1] > arr[ir]) {
				SWAP(arr[l + 1], arr[ir])
			}
			if (arr[l] > arr[ir]) {
				SWAP(arr[l], arr[ir])
			}
			if (arr[l + 1] > arr[l]) {
				SWAP(arr[l + 1], arr[l])
			}
			i = l + 1;
			j = ir;
			a = arr[l];
			flag2 = 0;
			while (!flag2) {
				i++;
				while (arr[i] < a)
					i++;
				j--;
				while (arr[j] > a)
					j--;
				if (j < i)
					flag2 = 1;
				if (!flag2) {
					SWAP(arr[i], arr[j])
				}
			}
			arr[l] = arr[j];
			arr[j] = a;
			if (j >= k)
				ir = j - 1;
			if (j <= k)
				l = i;
		}
	}
	return arr[k];
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
	fp = fopen ("select_floating_results.txt","w");
	unsigned long val;
	srand(5);
	for (int i=0; i< EXEC_NUM ; i++){
		fillarray();
		val = rand() % 21;	//random value between 0 and 20

		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		selectt(val,20);
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		
		fprintf (fp, "%lld\n",(long long)(diff(start,end).tv_sec * pow(10,9))+(long long)diff(start,end).tv_nsec);
	}

	fclose (fp);
	return 0;
}
