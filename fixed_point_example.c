#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "fixed_op_64bit.h"

#define SHIFT_AMOUNT 30

int main(){
	int64_t scaling_factor = pow(2,SHIFT_AMOUNT);

	int64_t fixed_point_value1 = (int64_t) 230 << SHIFT_AMOUNT;
	int64_t fixed_point_value2 = (int64_t) 80 << SHIFT_AMOUNT;

	float floating_point_value1 = ((float)fixed_mul_64(fixed_point_value1, fixed_point_value2, SHIFT_AMOUNT))/scaling_factor;
	float floating_point_value2 = ((float)fixed_div_64(fixed_point_value1, fixed_point_value2, SHIFT_AMOUNT))/scaling_factor;
	float floating_point_value3 = ((float)(fixed_point_value1 + fixed_point_value2))/scaling_factor;
	float floating_point_value4 = ((float)(fixed_point_value1 - fixed_point_value2))/scaling_factor;

	printf("moltiplicazione: %f\ndivisione: %f\nsomma: %f\ndifferenza: %f\n",floating_point_value1,floating_point_value2,floating_point_value3,floating_point_value4);
	return 0;
}
