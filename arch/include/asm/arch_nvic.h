
#ifndef  ARCH_NVIC_H
#define  ARCH_NVIC_H

#include  <stdint.h>

#include  "arch_regs.h"

static  inline  uint32_t  get_max_interrupt()
{
    return  (REG32_READ(ICTR_REG_ADDR) + 1) << 5;
}


static  inline int32_t is_interrupt_enable(uint32_t  irq)
{
    uint32_t  max_number = get_max_interrupt();
    if (max_number < irq)
        return  -1;

    uint32_t enable = REG32_READ(NVIC_ISER_REG_ADDR(irq>>5));
    uint32_t offset = irq & 0x1f;
    return  (enable & (1 << offset));
}

static  inline void enable_or_disable_interrupt(uint32_t  irq, uint32_t is_enable)
{
    uint32_t  max_number = get_max_interrupt();
    if (max_number < irq)
        return;

    uint32_t offset = irq & 0x1f;
    if (is_enable) {
        REG32_UPDATE(NVIC_ISER_REG_ADDR(irq>>5), 1<<offset,  1<<offset);        
    } else {
        REG32_UPDATE(NVIC_ICER_REG_ADDR(irq>>5), 1<<offset,  1<<offset);
    }
}


static  inline int32_t is_interrupt_pending(uint32_t  irq)
{
    uint32_t  max_number = get_max_interrupt();
    if (max_number < irq)
        return  -1;

    uint32_t pending = REG32_READ(NVIC_ISPR_REG_ADDR(irq>>5));
    uint32_t offset = irq & 0x1f;
    return  (pending & (1 << offset));
}

static  inline void suspend_or_resume_interrupt(uint32_t  irq, uint32_t is_suspend)
{
    uint32_t  max_number = get_max_interrupt();
    if (max_number < irq)
        return;

    uint32_t offset = irq & 0x1f;
    if (is_suspend) {
        REG32_UPDATE(NVIC_ISPR_REG_ADDR(irq>>5), 1<<offset,  1<<offset);        
    } else {
        REG32_UPDATE(NVIC_ICPR_REG_ADDR(irq>>5), 1<<offset,  1<<offset);
    }
}

static  inline int32_t is_interrupt_active(uint32_t  irq)
{
    uint32_t  max_number = get_max_interrupt();
    if (max_number < irq)
        return  -1;

    uint32_t active = REG32_READ(NVIC_IABR_REG_ADDR(irq>>5));
    uint32_t offset = irq & 0x1f;
    return  (active & (1 << offset));
}

static  inline int32_t get_interrupt_priority(uint32_t  irq)
{
    uint32_t  max_number = get_max_interrupt();
    if (max_number < irq)
        return  -1;

    uint32_t offset  = irq & 0x3;
    uint32_t priority  =  REG32_READ(NVIC_IPR_REG_ADDR(irq >> 2));

    return  ((priority >>  (offset << 3)) & 0xff);

}


static  inline int32_t set_interrupt_priority(uint32_t  irq,  uint32_t priority)
{
    uint32_t  max_number = get_max_interrupt();
    if ( (max_number < irq )||  (priority  >  0xff))
        return  -1;

    uint32_t offset  = irq & 0x3;
    REG32_UPDATE(NVIC_IPR_REG_ADDR(irq >> 2), priority << (offset<<3), (0xff)<<(offset<<3));

    return  0;

}






#endif

