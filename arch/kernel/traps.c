
#include  <stdint.h>
#include  <stdio.h>
#include  <string.h>

#include "arch_regs.h"
#include "asm/context_stack.h"
#include "asm/traps.h"


void  do_reset()
{


}


void  do_NMI()
{



}


void  do_bus_fault(context_no_fp_regs_t regs)
{
    uint32_t  fault_info =  get_bus_fault_info();
    uint32_t  fault_addr = 0;

    if (fault_info & BFSR_BFARVALID_MASK) {
        fault_addr  =  get_bus_fault_addr();
    }

    if (fault_info & ( BFSR_STKERR_MASK | BFSR_UNSTKERR_MASK) ) {
        /*stack error*/
    } else if (fault_info & BFSR_IBUSERR_MASK) {

    } else if (fault_info & BFSR_PRECISERR_MASK) {

    } else if (fault_info & BFSR_IMPRECISERR_MASK) {

    }


    return;
}


void  do_usage_fault()
{
    uint32_t  fault_info  = get_usage_fault_info();

    if (fault_info & UFSR_NOCP_MASK) {
            ;
    } else if (fault_info & UFSR_UNDEFINSTR_MASK) {
        ;
    } else if (fault_info & UFSR_INVSTATE_MASK) {
        ;
    } else if (fault_info & UFSR_INVPC_MASK) {
        ;
    } else if (fault_info & UFSR_UNALIGNED_MASK) {
        ;
    } else if (fault_info & UFSR_DIVBYZERO_MASK) {
        ;
    }

    return;

}


void  do_svcall()
{


}

void  do_debug()
{


}

void  do_pendsv()
{


}








