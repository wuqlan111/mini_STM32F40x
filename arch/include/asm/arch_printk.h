
#ifndef  ARCH_PRINTK_H
#define  ARCH_PRINTK_H

#include  <stdint.h>

#ifdef DEBUG
#define  __DBG_PRINTF_ALL(fmt, ...)     early_printk("<DEBUG>[%s:%d]:\t%s", __FILE__, __LINE__, fmt, ...)
#define  __DBG_PRINTF(fmt, ...)         early_printk(fmt, ...)
#else
#define  __DBG_PRINTF_ALL(fmt, ...)
#define  __DBG_PRINTF(fmt, ...)
#endif

int32_t  early_printk(const char * fmt,  ...);
int32_t  get_early_log(char * out);







#endif

