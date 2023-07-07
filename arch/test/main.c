
#include  <stdio.h>
#include  <stdint.h>

#include  "arch_printk.h"


extern  void  test_mm_fault(void);
extern  int32_t  svcall_test(uint32_t  param1,  uint32_t param2,  
            uint32_t param3,  uint32_t  param4);

int  main(void)
{

    int32_t  ret  =  0;
    ret = svcall_test(12,1,123,1234);

    __DBG_PRINTF_ALL("svcall ret: %d\n",  ret);
    while(1) ;

    return  0;
}





