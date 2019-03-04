#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "fixed_op_64bit.h"

#define SHIFT_AMOUNT 30

int main(){
	int64_t scaling_factor = pow(2,SHIFT_AMOUNT);

	int64_t fixed_point_value1 = (int64_t)(230.52111 * scaling_factor);
	int64_t fixed_point_value2 = (int64_t)(80.12111 * scaling_factor);

	double floating_point_value1 = ((double)fixed_mul_64(fixed_point_value1, fixed_point_value2, SHIFT_AMOUNT))/scaling_factor;
	double floating_point_value2 = ((double)fixed_div_64(fixed_point_value1, fixed_point_value2, SHIFT_AMOUNT))/scaling_factor;
	double floating_point_value3 = ((double)(fixed_point_value1 + fixed_point_value2))/scaling_factor;
	double floating_point_value4 = ((double)(fixed_point_value1 - fixed_point_value2))/scaling_factor;

	printf("multiplication: %.10f\ndivision: %.10f\nsum: %.10f\nsubtraction: %.10f\n",floating_point_value1,floating_point_value2,floating_point_value3,floating_point_value4);
	return 0;
}
