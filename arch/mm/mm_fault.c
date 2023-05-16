
#include <stdio.h> 
#include "context_stack.h"
#include "irqflags.h"

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


void  do_with_exception_stack_fault(void)
{





}



void  do_with_data_access_fault(uint32_t addr)
{






}


void  do_with_instruction_fetch_fault(void)
{


}



void  do_mem_fault(context_no_fp_regs_t regs)
{
    disable_irq();
    context_no_fp_regs_t * no_fp_context = &regs;

    uint32_t  mmfalut_info = get_memory_fault_info();
    uint32_t  mmfault_addr = 0;

    if (mmfalut_info &  MMFSR_MMARVALID_MASK)
        mmfault_addr  =  get_memory_fault_addr();

    
    if ( (mmfalut_info & MMFSR_MSTKERR_MASK) || (mmfalut_info & MMFSR_MUNSTKERR_MASK) ) {
        do_with_exception_stack_fault();
    } else if (mmfalut_info & MMFSR_DACCVIOL_MASK) {
        do_with_data_access_fault(mmfault_addr);
    } else if (mmfalut_info & MMFSR_IACCVIOL_MASK) {
        do_with_instruction_fetch_fault();
    } else if (mmfalut_info & MMFSR_MLSPERR_MASK) {

    } else ;

    enable_irq();

    return;

}



