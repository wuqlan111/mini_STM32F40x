
#include  <stdio.h>
#include  <stdint.h>

#include  "arch_printk.h"
#include  "console.h"



int  main(void)
{

    int32_t  ret  =  0;
    
    console_init();

    while(1) {

        for (int32_t i  =  0; i < 12000; i++);

        console_fmt_out("hello world! \r\n");
    };

    return  0;
}





