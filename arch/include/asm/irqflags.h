
#ifndef   ASM_IRQFLAGS_H
#define   ASM_IRQFLAGS_H

#include  <stdint.h>
#include  "arch_regs.h"


#define  disable_irq()    SET_PRIMASK()
#define  enable_irq()     CLEAR_PRIMASK()



static  inline  uint32_t  save_and_disable_irq(void)
{
    uint32_t  ret =  0;
    ret = read_xpsr(PRIMASK_REG);
    return ret;
}

static  inline  void restore_and_enable_irq(uint32_t flag)
{
    write_xpsr(PRIMASK_REG, flag);
}











#endif



