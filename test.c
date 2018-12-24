#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "fixed_div_128bit.h"

int main()
{
  int64_t num = -200 * pow(2,30);
  int64_t div = 51 * pow(2,30);
  printf("%f\n",fixed_div_128(num,div)/pow(2,30));
  return 0;
}
