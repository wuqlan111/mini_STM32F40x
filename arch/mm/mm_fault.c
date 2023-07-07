
#include <stdlib.h> 
#include "context_stack.h"
#include "irqflags.h"
#include "arch_printk.h"
#include "traps.h"

#define  MMFSR_MMARVALID_MASK       (0x1<<7U)
#define  MMFSR_MLSPERR_MASK         (0x1<<5U)
#define  MMFSR_MSTKERR_MASK         (0x1<<4U)
#define  MMFSR_MUNSTKERR_MASK       (0x1<<3U)
#define  MMFSR_DACCVIOL_MASK        (0x1<<1U)
#define  MMFSR_IACCVIOL_MASK        (0x1U)


static inline uint32_t get_memory_fault_addr(void)
{
    return  REG32_READ(SCB_MMFAR_REG_ADDR);
}

static  inline  uint32_t  get_memory_fault_info(void)
{
    return  REG32_READ(SCB_CFSR_REG_ADDR) & 0xff;
}


void  do_mem_fault(context_exception_no_fp_regs_t * regs)
{
    disable_irq();
    record_exception_occur_counter(MEMORY_FAULT_EXCEPTION_NUMBER);

    uint32_t  mmfalut_info = get_memory_fault_info();
    uint32_t  mmfault_addr = 0;

    if (mmfalut_info &  MMFSR_MMARVALID_MASK) {
        mmfault_addr  =  get_memory_fault_addr();        
    }
    
    if ( (mmfalut_info & MMFSR_MSTKERR_MASK) || (mmfalut_info & MMFSR_MUNSTKERR_MASK) ) {
        __DBG_PRINTF_ALL("memory fault when entry or return exception!\n");
    } else if (mmfalut_info & MMFSR_DACCVIOL_MASK) {
        __DBG_PRINTF_ALL("data access fault at addr 0x%08x!\n", mmfault_addr);
    } else if (mmfalut_info & MMFSR_IACCVIOL_MASK) {
        __DBG_PRINTF_ALL("instruction  occur!\n");
    } else if (mmfalut_info & MMFSR_MLSPERR_MASK) {

    }

    enable_irq();

    return;

}



