
#include  <stdio.h>
#include  <stdint.h>

#include  "arch_printk.h"
#include  "console.h"



int  main(void)
{

    int32_t  ret  =  0;
    
    console_init();

    set_system_log_level(LOG_LEVEL_DEBUG);

    while(1) {

        for (int32_t i  =  0; i < 12000; i++);

        DEBUG_PRINTF_DEBUG("hello world!");
    };

    return  0;
}





