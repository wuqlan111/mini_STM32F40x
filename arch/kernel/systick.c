
#include  <stdint.h>
#include  <stdio.h>
#include  <string.h>

#include  "arch_regs.h"
#include  "arch_systick.h"
#include  "context_stack.h"
#include  "traps.h"
#include  "arch_config.h"
#include  "arch_printk.h"
#include  "irqflags.h"

#define  ARCH_SYSTICK_COUNTER          (0x100)


void  arch_systick_init(void)
{

    uint32_t  flag,  mask  =  0;
    flag  =  ARCH_SYSTICK_COUNTER & 0xffffff;
    REG32_WRITE(SYSTICK_RVR_REG_ADDR,  flag);

    flag  =  0x7;
    REG32_WRITE(SYSTICK_CSR_REG_ADDR,  flag);

}



void  do_systick(context_exception_no_fp_regs_t * regs)
{
    record_exception_occur_counter(SYSTICK_EXCEPTION_NUMBER);

    __DBG_PRINTF_ALL("systick occur!");


}





