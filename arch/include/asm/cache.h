
#ifndef   ASM_ARCH_CACHE_H
#define   ASM_ARCH_CACHE_H

#include  <stdint.h>

#include  "arch_regs.h"

#define  CTYPE_NO_CACHE     0
#define  CTYPE_INSTRUCTION_CACHE        (1u)
#define  CTYPE_DATA_CACHE          (2u)
#define  CTYPE_SEPARETE_CACHE      (3u)
#define  CTYPE_UNIFIED_CACHE       (4u)


#define get_cache_type(level)    ( (REG32_READ(ID_CLIDR_REG_ADDR) >> ((level) - 1)) & 0x7)

#define  CCR_IC_ENABLE_BIT   (17U)
#define  CCR_DC_ENABLE_BIT   (16U)


static  inline  void  enable_or_disable_icache(uint32_t enable)
{
    uint32_t flag = enable ? 1<<CCR_IC_ENABLE_BIT: 0;
    REG32_UPDATE(SCB_CCR_REG_ADDR, flag, 1 << CCR_IC_ENABLE_BIT);
}

static  inline  void  enable_or_disable_dcache(uint32_t enable)
{
    uint32_t flag = enable ? 1<<CCR_DC_ENABLE_BIT: 0;
    REG32_UPDATE(SCB_CCR_REG_ADDR, flag, 1 << CCR_DC_ENABLE_BIT);
}






#endif



