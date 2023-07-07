
#ifndef  ARCH_GCC_ATRRIBUTE_H
#define  ARCH_GCC_ATRRIBUTE_H

#include  <stdint.h>

#define ATTRIBUTE_PACK         __attribute__((packed))
#define ATTRIBUTE_ALIGN(n)     __attribute__((aligned((n))))


#define  TYPE_OFFSET(type, member)     ((uint8_t *)(&(((type *)0)->member)))
#define  container_of(pointer,  type, member)     ((type *)(((uint8_t *)pointer) - TYPE_OFFSET(type, member)))

#define __NOP()           __asm__ volatile("nop")






#endif

