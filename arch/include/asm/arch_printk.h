
#ifndef  ARCH_PRINTK_H
#define  ARCH_PRINTK_H

#include  <stdint.h>

#ifdef DEBUG
#define  __DBG_PRINTF_ALL(fmt, ...)     early_printk("<DEBUG>[%s:%d]:\t" fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define  __DBG_PRINTF(fmt, ...)         early_printk(fmt, ##__VA_ARGS__)
#else
#define  __DBG_PRINTF_ALL(fmt, ...)
#define  __DBG_PRINTF(fmt, ...)
#endif

int32_t  early_printk(const char * fmt,  ...);
int32_t  get_early_log(uint8_t * out);




#endif

