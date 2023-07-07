
#ifndef  ARCH_MATH_UTIL_H
#define  ARCH_MATH_UTIL_H

#include  <stdint.h>


static  inline  uint32_t  is_powers_of_2(uint32_t  value)
{
    return   !((value - 1) & value);
}



int32_t  get_low_bit_zero(uint32_t value,  uint32_t * bit_pos);
int32_t  get_low_bit_no_zero(uint32_t value, uint32_t * bit_pos);
int32_t  get_high_bit_zero(uint32_t value,  uint32_t * bit_pos);
int32_t  get_high_bit_no_zero(uint32_t value, uint32_t * bit_pos);
int32_t  math_clog2(uint32_t value,  uint32_t * log2);









#endif

