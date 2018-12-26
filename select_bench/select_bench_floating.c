float select(unsigned long k, unsigned long n);
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;
#define EXEC_NUM 100000

volatile float           arr[20] = {
	5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
	10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 888.88
};

float select(unsigned long k, unsigned long n)
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

int main()
{
	clock_t start,end;
	int clock_cycles[EXEC_NUM];
	srand(5);
	for(int i = 0; i < EXEC_NUM ; i++)
	{
		unsigned long value = rand() % 21;

		start = clock();
		select(value, 20);		//random value between 0 and 20
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
