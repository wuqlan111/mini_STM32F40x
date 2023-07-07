
#include  <stdio.h>
#include  <stdint.h>
#include  <memory.h>

#include  "arch_printk.h"


void  test_early_printk(void)
{

    int32_t  ret   =  0;
    uint8_t  buf[130]  =  {0};

    for (int32_t i = 0; i < 4; i++) {
        __DBG_PRINTF_ALL("/********%d****/\n", i);
    }
    
    
    while(!ret) {
        ret = get_early_log(buf);
        memset(buf,  0,   130);
    }

}





