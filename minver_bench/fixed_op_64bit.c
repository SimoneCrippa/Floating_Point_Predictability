#include <stdint.h>

#ifdef __SIZEOF_INT128__
int64_t fixed_div_64(int64_t x, int64_t y, int shift_amount)
{
    return ((((__int128)x << shift_amount) / y));
}

int64_t fixed_mul_64(int64_t x, int64_t y, int shift_amount)
{
	return (int64_t)((((__int128)x * (__int128)y)) >> shift_amount);
}


#else
uint64_t bitmask(int shift)
{
  uint64_t bitmask = (uint64_t)0b1111111111111111111111111111111111111111111111111111111111111111;
  bitmask = bitmask >> shift;
  return bitmask;
}

int64_t fixed_div_64(int64_t value, int64_t div, int shift_amount)
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
  uint64_t bitmask_low = bitmask(shift_amount);
  uint64_t bitmask_high = bitmask(64 - shift_amount);


	a_lo = (value & bitmask_low) << shift_amount;

	a_hi = (value & (bitmask_high << (64 - shift_amount))) >> (64 - shift_amount);

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

// https://stackoverflow.com/questions/31652875/fastest-way-to-multiply-two-64-bit-ints-to-128-bit-then-to-64-bit
void umul64wide (uint64_t a, uint64_t b, uint64_t *hi, uint64_t *lo)
{
    uint64_t a_lo = (uint64_t)(uint32_t)a;
    uint64_t a_hi = a >> 32;
    uint64_t b_lo = (uint64_t)(uint32_t)b;
    uint64_t b_hi = b >> 32;

    uint64_t p0 = a_lo * b_lo;
    uint64_t p1 = a_lo * b_hi;
    uint64_t p2 = a_hi * b_lo;
    uint64_t p3 = a_hi * b_hi;

    uint32_t cy = (uint32_t)(((p0 >> 32) + (uint32_t)p1 + (uint32_t)p2) >> 32);

    *lo = p0 + (p1 << 32) + (p2 << 32);
    *hi = p3 + (p1 >> 32) + (p2 >> 32) + cy;
}

void mul64wide (int64_t a, int64_t b, int64_t *hi, int64_t *lo)
{
    umul64wide ((uint64_t)a, (uint64_t)b, (uint64_t *)hi, (uint64_t *)lo);
    if (a < 0LL) *hi -= b;
    if (b < 0LL) *hi -= a;
}

/* compute mul_wide (a, b) >> s, for s in [0,63] */
int64_t fixed_mul_64 (int64_t a, int64_t b, int s)
{
    int64_t res;
    int64_t hi, lo;
    mul64wide (a, b, &hi, &lo);
    if (s) {
        res = ((uint64_t)hi << (64 - s)) | ((uint64_t)lo >> s);
    } else {
        res = lo;
    }
    return res;
}

#endif
