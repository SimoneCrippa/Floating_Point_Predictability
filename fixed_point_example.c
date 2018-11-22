#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define SHIFT_AMOUNT 30

int64_t fixed_mul_30(int64_t x, int64_t y)
	{
		x = x >> SHIFT_AMOUNT;
		return (x * y);
	}

int64_t fixed_div_30(int64_t x, int64_t y)
  {
    //ex x=50 y=80 50 * 2^SHIFT_AMOUNT * 2^SHIFT_AMOUNT / 80 * 2^SHIFT_AMOUNT = 50/80 * 2^SHIFT_AMOUNT
		return ((((__int128)x << SHIFT_AMOUNT) / y));
  }

void main(){
	int64_t scaling_factor = pow(2,30);

	int64_t fixed_point_value1 = (int64_t) 230 << SHIFT_AMOUNT;
	int64_t fixed_point_value2 = (int64_t) 80 << SHIFT_AMOUNT;

	float floating_point_value1 = ((float)fixed_mul_30(fixed_point_value1, fixed_point_value2))/scaling_factor;
	float floating_point_value2 = ((float)fixed_div_30(fixed_point_value1, fixed_point_value2))/scaling_factor;
	float floating_point_value3 = ((float)(fixed_point_value1 + fixed_point_value2))/scaling_factor;
	float floating_point_value4 = ((float)(fixed_point_value1 - fixed_point_value2))/scaling_factor;

	printf("%f\n%f\n%f\n%f\n",floating_point_value1,floating_point_value2,floating_point_value3,floating_point_value4);

}
