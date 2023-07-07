
#include  <stdint.h>
#include  <stdio.h>
#include  <string.h>

#include  "arch_regs.h"
#include  "context_stack.h"
#include  "traps.h"
#include  "arch_config.h"
#include  "arch_printk.h"
#include  "irqflags.h"


#define  MEMORY_FAULT_PRIORITY     0
#define  BUS_FAULT_PRIORITY     0
#define  USAGE_FAULT_PRIORITY     0
#define  SV_CALL_PRIORITY     1
#define  DEBUG_MONITOR_PRIORITY    2
#define  PEND_SV_PRIORITY    3
#define  SYSTICK_PRIORITY     4

#define  EXPTION_PRIORITY_FLAG(priority)       ((priority & 0xff) << (8 - ARCH_EXCEPTION_PRIORITY_BITS))

static  uint32_t  excetion_counter[ARCH_MAX_SYSTEM_EXCETION + 1] = {0};

void  reset_init_exceptions(void)
{
    uint32_t  flag, mask, val;
    
    SET_FAULTMASK();
    /*set exception group priority*/
    val   =  7 - GROUP_EXCEPTION_PRIORITY_BIT;
    flag   =   (0x5fa << 16) | (val << 8);
    mask   =   (0xffff << 16) |  (0x7 << 8);
    REG32_UPDATE(SCB_AIRCR_REG_ADDR,  flag,  mask);

    /*set exception priority*/
    flag  =  ( EXPTION_PRIORITY_FLAG(USAGE_FAULT_PRIORITY) << 16) | 
             ( EXPTION_PRIORITY_FLAG(BUS_FAULT_PRIORITY) << 8) 
            | EXPTION_PRIORITY_FLAG(MEMORY_FAULT_PRIORITY);
    REG32_WRITE(SCB_SHPR1_REG_ADDR,  flag);

    /*set svcall priority*/
    flag  =  EXPTION_PRIORITY_FLAG(SV_CALL_PRIORITY)  << 24;
    REG32_WRITE(SCB_SHPR2_REG_ADDR,  flag);

    /*set priority*/
    flag =  (EXPTION_PRIORITY_FLAG(SYSTICK_PRIORITY) << 24) | 
            (EXPTION_PRIORITY_FLAG(PEND_SV_PRIORITY) << 16) |
            EXPTION_PRIORITY_FLAG(DEBUG_MONITOR_PRIORITY);
    REG32_WRITE(SCB_SHPR3_REG_ADDR,  flag);

    /*enable memory, bus and usage fault exception*/
    flag  =  0x7 << 16;
    REG32_UPDATE(SCB_SHCSR_REG_ADDR,  flag,  mask);

    CLEAR_FAULTMASK();


}


void  record_exception_occur_counter(uint32_t  exception)
{
    if (exception > ARCH_MAX_SYSTEM_EXCETION) {
        return;
    }

    excetion_counter[exception]++;
}




void  do_NMI(context_exception_no_fp_regs_t * regs)
{

    record_exception_occur_counter(NMI_EXCEPTION_NUMBER);

}


void  do_bus_fault(context_exception_no_fp_regs_t * regs)
{
    uint32_t  fault_info =  get_bus_fault_info();
    uint32_t  fault_addr = 0;

    record_exception_occur_counter(BUS_FAULT_EXCEPTION_NUMBER);
    if (fault_info & BFSR_BFARVALID_MASK) {
        fault_addr  =  get_bus_fault_addr();
    }

    if (fault_info & ( BFSR_STKERR_MASK | BFSR_UNSTKERR_MASK) ) {
        /*stack error*/
        __DBG_PRINTF_ALL("bus fault occured when entry or return!\n");
    } else if (fault_info & BFSR_IBUSERR_MASK) {
        __DBG_PRINTF_ALL("bus fault occured on an instruction prefetch!\n");
    } else if (fault_info & BFSR_PRECISERR_MASK) {
        __DBG_PRINTF_ALL("bus fault occured at addr 0x%08x on a precise data access!\n", fault_addr);
    } else if (fault_info & BFSR_IMPRECISERR_MASK) {
        __DBG_PRINTF_ALL("bus fault occured on a imprecise data access!\n");
    }


    return;
}


void  do_usage_fault(context_exception_no_fp_regs_t * regs)
{
    uint32_t  fault_info  = get_usage_fault_info();

    record_exception_occur_counter(USAGE_FAULT_EXCEPTION_NUMBER);

    if (fault_info & UFSR_NOCP_MASK) {
        __DBG_PRINTF_ALL("attempt to access a coprocessor that does not exist!\n");
    } else if (fault_info & UFSR_UNDEFINSTR_MASK) {
        __DBG_PRINTF_ALL("attempt to execute an unknown instruction!\n");
    } else if (fault_info & UFSR_INVSTATE_MASK) {
        
        __DBG_PRINTF_ALL("attempts to execute in an invalid EPSR state!\n");
    } else if (fault_info & UFSR_INVPC_MASK) {
        __DBG_PRINTF_ALL("failure of the integrity checks for exception returns!\n");
    } else if (fault_info & UFSR_UNALIGNED_MASK) {
        __DBG_PRINTF_ALL("attempt to access a non-word aligned location!\n");
    } else if (fault_info & UFSR_DIVBYZERO_MASK) {
        __DBG_PRINTF_ALL("attempt to execute SDIV or UDIV with a divisor of 0!\n");
    }

    return;

}


void  do_svcall(context_exception_no_fp_regs_t * regs)
{
    record_exception_occur_counter(SVCALL_EXCEPTION_NUMBER);

    if (!regs) {
        return;
    }

    int32_t  ret  =  {0};
    uint16_t * svc_instruction = (uint16_t *)(((uint8_t *)regs->common_regs.ret_addr) - 2);
    uint32_t  svc_number   =  *svc_instruction & 0xff;
    uint32_t * r0_addr  =  &regs->common_regs.r0;
    void * svc_func  = NULL;

    if (get_svcall_func(svc_number, &svc_func)) {
        __DBG_PRINTF_ALL("get svcall func failed!\n");
        return;
    }

    uintptr_t  func  =  (uintptr_t)svc_func;

    __asm__  volatile("mov r0, %0\n"
                    "mov  r1, %1\n"
                    "mov  r2, %2\n"
                    "mov  r3, %3"::"r"(regs->common_regs.r0),"r"(regs->common_regs.r1),
                        "r"(regs->common_regs.r2), "r"(regs->common_regs.r3):);

    /*save lr*/
    __asm__  volatile("push  {lr}");

    /*set new lr = pc + 8, but bit0 must set 1 for THUMB state*/
    __asm__  volatile("add lr, pc, #9":::);
    __asm__  volatile ("mov pc, %0"::"r"(func):);
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __asm__  volatile("pop {lr}");

    __asm__  volatile("mov  %0,  r0":"=r"(ret)::);
    regs->common_regs.r0   =  ret;
    return;
}




void  do_debug(context_exception_no_fp_regs_t * regs)
{
    record_exception_occur_counter(DEBUG_EXCEPTION_NUMBER);

}

void  do_pendsv(context_exception_no_fp_regs_t * regs)
{
    record_exception_occur_counter(PENDSV_EXCEPTION_NUMBER);

}


void do_hard_fault(context_exception_no_fp_regs_t * regs)
{
    uint32_t  flag, other_fault_escalat;
    uint32_t  cur_info  = get_cur_fault_info();
    uint32_t  hard_info  =  get_hard_fault_info();

    flag  =   other_fault_escalat  =  0;

    record_exception_occur_counter(HARD_FAULT_EXCEPTION_NUMBER);

    if (hard_info & (1 << 31)) {
        __DBG_PRINTF_ALL("hard fault occured on a debug event!\n");
    } else  if (hard_info &  0x2) {
        __DBG_PRINTF_ALL("vector table read fault occurred!\n");
    } else if (hard_info & (1 << 30)) {
        other_fault_escalat   =  1;
        __DBG_PRINTF_ALL("escalate a configurable-priority exception to HardFault!\n");
    }

    flag  =  cur_info >>  16;
    if (flag) {
        record_exception_occur_counter(USAGE_FAULT_EXCEPTION_NUMBER);
        __DBG_PRINTF_ALL("usage fault escalated, flag 0x%04x!", flag);
    }

    flag  =  (cur_info >> 8) & 0xff;
    if (flag) {
        record_exception_occur_counter(BUS_FAULT_EXCEPTION_NUMBER);
        __DBG_PRINTF_ALL("bus fault escalated, flag 0x%02x!", flag);
    }

    flag  =  cur_info & 0xff;
    if (flag) {
        record_exception_occur_counter(MEMORY_FAULT_EXCEPTION_NUMBER);
        __DBG_PRINTF_ALL("memory fault escalated, flag 0x%02x!", flag);
    }


    return;

}





