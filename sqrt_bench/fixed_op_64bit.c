#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define SHIFT_AMOUNT 30

int64_t fixed_div_64(int64_t value, int64_t div)
{
	// sign handling and converting to unsigned int
	int positive = 0;
	if(value >= 0)
	{
		if(div >= 0)
			positive = 1;
		else
			div = (uint64_t)-div;
	}
	else
	{
		value = (uint64_t)-value;
		if(div < 0)
		{
			positive = 1;
			div = (uint64_t)-div;
		}
	}

	/* unsigned 64-bit division algorithm
	available at
	https://codereview.stackexchange.com/questions/67962/mostly-portable-128-by-64-bit-division */
  	// numerator
	uint64_t a_lo;
	uint64_t a_hi;

	a_lo = (value & (uint64_t)0b1111111111111111111111111111111111) << 30;

	a_hi = ((value & ((uint64_t)0b111111111111111111111111111111 << 34) ) >> 34 );

	// quotient
	uint64_t q = a_lo << 1;

	// remainder
	uint64_t rem = a_hi;

	uint64_t carry = a_lo >> 63;
	uint64_t temp_carry = 0;
	int i;

	for(i = 0; i < 64; i++)
	{
    	temp_carry = rem >> 63;
    	rem <<= 1;
    	rem |= carry;
    	carry = temp_carry;

    	if(carry == 0)
    	{
			if(rem >= div)
			{
				carry = 1;
			}
			else
			{
				temp_carry = q >> 63;
				q <<= 1;
				q |= carry;
				carry = temp_carry;
				continue;
			}
		}

   		rem -= div;
    	rem -= (1 - carry);
    	carry = 1;
    	temp_carry = q >> 63;
    	q <<= 1;
    	q |= carry;
    	carry = temp_carry;
	}

	if(positive)
		return (int64_t)q;
	else
		return (int64_t)-q;
}

int64_t fixed_mul_64(int64_t x, int64_t y)
{
	x = x >> SHIFT_AMOUNT;
	return (x * y);
}
