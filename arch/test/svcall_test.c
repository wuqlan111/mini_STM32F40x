
#include  <stdint.h>
#include  <stdlib.h>
#include  <string.h>
#include  <memory.h>

#include  "mpu.h"
#include  "arch_printk.h"



int32_t  svcall_test(uint32_t  param1,  uint32_t param2,  
            uint32_t param3,  uint32_t  param4)
{

    int32_t   ret  =  0;
    __asm__ volatile("mov r0, %0\n"
                    "mov r1, %1\n"
                    "mov r2, %2\n"
                    "mov r3, %3": : "r"(param1),  "r"(param2), 
                    "r"(param2),  "r"(param3):);
    __asm__  volatile("svc 0");

    __asm__  volatile("mov %0, r0":"=r"(ret)::);

    return  ret;
    
}








