#include <stdint.h>
int32_t  select(unsigned long k, unsigned long n);

#define SHIFT_AMOUNT 14
#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;

volatile float           arr_float[20] = {
	5, 4, 10.3, 1.1, 5.7, 100, 231, 111, 49.5, 99,
	10, 150, 222.22, 101, 77, 44, 35, 20.54, 99.99, 888.88
};

int32_t	arr[20];

void fillarray()
{
	for (int i = 0; i < 20; i++)
		arr[i] = (int32_t) arr_float[i] << SHIFT_AMOUNT;
}

int32_t select(unsigned long k, unsigned long n)
{
	unsigned long i, ir, j, l, mid;
	int32_t a, temp;
	int flag, flag2;

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
	return (arr[k] >> SHIFT_AMOUNT);
}

int main()
{
	fillarray();
  	select(10, 20);
  	return 0;
}
