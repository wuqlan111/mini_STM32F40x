
#include  <stdint.h>
#include  <stdlib.h>
#include  <string.h>
#include  <memory.h>

#include  "math_util.h"

int32_t  get_low_bit_zero(uint32_t value,  uint32_t * bit_pos)
{
    if ( (value ==  0xffffffff ) || !bit_pos) {
        return  -1;
    }

    for (int32_t i = 0;  i < 32; i++) {
        if ( ! (value & ( 1 << i)) ) {
            *bit_pos  =  i;
            break;
        }
    }

    return  0;

}


int32_t  get_low_bit_no_zero(uint32_t value, uint32_t * bit_pos)
{
    if ( !value || !bit_pos) {
        return  -1;
    }

    for (int32_t i = 0;  i < 32; i++) {
        if ( value & ( 1 << i) ) {
            *bit_pos  =  i;
            break;
        }
    }

    return  0;

}


int32_t  get_high_bit_zero(uint32_t value,  uint32_t * bit_pos)
{
    if ( (value ==  0xffffffff ) || !bit_pos) {
        return  -1;
    }

    for (int32_t i = 31;  i >= 0; i--) {
        if ( ! (value & ( 1 << i)) ) {
            *bit_pos  =  i;
            break;
        }
    }

    return  0;

}


int32_t  get_high_bit_no_zero(uint32_t value, uint32_t * bit_pos)
{
    if ( !value || !bit_pos) {
        return  -1;
    }

    for (int32_t i = 31;  i >=0; i--) {
        if ( value & ( 1 << i) ) {
            *bit_pos  =  i;
            break;
        }
    }

    return  0;

}



int32_t  math_clog2(uint32_t value,  uint32_t * log2)
{
    uint32_t  bit_pos = 0;
    if (!value || !log2) {
        return  -1;
    }

    if (get_high_bit_no_zero(value, &bit_pos)) {
        return  -1;
    }

    if (value & ((1 << bit_pos) - 1) ) {
        bit_pos++;
    }

    *log2  =   bit_pos;

    return   0;

}




