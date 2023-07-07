
#include  <stdio.h>
#include  <stdint.h>
#include  <memory.h>

#include  "arch_printk.h"

typedef  void (* func_call)(void);


static  void  invalid_data_access(uint32_t is_write)
{
    uint32_t  * addr  =  (uint32_t *)0x081000123;
    uint32_t  value  =  0;

    if (is_write) {
        __DBG_PRINTF_ALL("write to addr--%p\n", addr);
        *addr   =   0x11223344;
    } else {
        value   =  *addr;
        __DBG_PRINTF_ALL("read from addr--%p,\tvalue--0x%08x\n", addr,  value);
    }

    __DBG_PRINTF_ALL("memory data access\n");

}



static  void  invalid_execuate_instruction()
{
    uint32_t  value  =  0;    
    func_call  func  = (func_call ) ((uint32_t)&value | 0x1);

    func();

    __DBG_PRINTF_ALL("in\n");

}



void  test_mm_fault(void)
{
    invalid_data_access(1);
    invalid_data_access(0);

    invalid_execuate_instruction();

}












