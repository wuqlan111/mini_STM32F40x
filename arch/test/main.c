
#include  <stdio.h>
#include  <stdint.h>

#include  "arch_printk.h"
#include  "console.h"



int  main(void)
{

    int32_t  ret  =  0;
    
    console_init();

    console_fmt_out("hello world! \r\n");


    while(1) ;

    return  0;
}





