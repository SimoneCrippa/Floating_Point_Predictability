#include <stdio.h>
#include <stdint.h>
#include <math.h>


int64_t divisione(int64_t value_int, int64_t b_int)
{	
	int positive = 0;
	if(value_int >= 0){
		if(b_int >= 0){
			positive = 1;
			}
		else{
			positive = 0;
			b_int = -b_int;
			}
		}
	else{
		value_int = -value_int;
		if(b_int >= 0){
			positive = 0;
			}
		else{
			positive = 1;
			b_int = -b_int;
			}
		}

	uint64_t value = value_int;
	uint64_t b = b_int;
		
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
      if(rem >= b)
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

    rem -= b;
    rem -= (1 - carry);
    carry = 1;
    temp_carry = q >> 63;
    q <<= 1;
    q |= carry;
    carry = temp_carry;
  }
  
  if(positive)
  	return q;
  else{
  	int64_t q_int64 = q;
  	return -q_int64;
  }
}


int main(){
	int64_t value = (int64_t)(-200*pow(2,30));
	int64_t b =  (int64_t)51 << 30;
	double res = ((double)divisione(value, b))/pow(2,30);
	printf("%f\n",res);
	return 0;


}