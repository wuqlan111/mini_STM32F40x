
#include  <stdint.h>
#include  <stdio.h>
#include  <string.h>

#include  "traps.h"
#include  "arch_config.h"
#include  "arch_printk.h"

static  int32_t  svcall_func1(uint32_t  a,  uint32_t b);


static  void *  svcall_funcyions[] = {(void *)svcall_func1, 0};



static  int32_t  svcall_func1(uint32_t  a,  uint32_t b)
{
    return  (a + b);
}


int32_t  get_svcall_func(uint32_t  svcall_number,  void ** func)
{
    if (svcall_number > 0xff) {
        __DBG_PRINTF_ALL("ERROR! svcall number %d invalid!", svcall_number);
        return   -1;
    }

    if (!func) {
        __DBG_PRINTF_ALL("ERROR! func is null!");
        return   -1;
    }

    *func  =  svcall_funcyions[svcall_number];

    return  0;

}













