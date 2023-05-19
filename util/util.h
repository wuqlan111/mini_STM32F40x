#ifndef  STM32F40x_UTIL_H
#define  STM32F40x_UTIL_H

#include <stdint.h>

#define  REGISTER_OPS(width, type)      \
static inline void REG##width##_WRITE(uint32_t  addr, uint##width##_t val)    \
{                                                       \
    volatile uint##width##_t *  p = ( volatile uint##width##_t *)addr;        \
    * p = val;                                      \
}                                                   \
static inline uint##width##_t REG##width##_READ(uint32_t  addr)    \
{                                                       \
    volatile uint##width##_t *  p = ( volatile uint##width##_t *)addr;        \
    return *p;                                     \
}                                                   \
static inline void REG##width##_UPDATE(uint32_t  addr, uint##width##_t val, uint##width##_t mask)    \
{                                                       \
    volatile uint##width##_t *  p = ( volatile uint##width##_t *)addr;        \
    uint##width##_t tmp = *p;                                  \
    tmp &= ~mask;                                   \
    tmp |= (val & mask);                            \
    * p = val;                                      \
}                                                   \


REGISTER_OPS(8, uint8_t)
REGISTER_OPS(16, uint16_t)
REGISTER_OPS(32, uint32_t)


#define  ATTRIBUTE_PACKED     __attribute__((packed))
#define  ATTRIBUTE_ALIGN(align)     __attribute__((aligned(align)))


#endif

