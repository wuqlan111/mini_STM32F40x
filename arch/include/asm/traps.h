#ifndef  ARCH_TRAPS_H
#define  ARCH_TRAPS_H

#include  "arch_regs.h"

#define  BFSR_BFARVALID_MASK     (1<<7U)
#define  BFSR_LSPERR_MASK        (1<<5U)
#define  BFSR_STKERR_MASK        (1<<4U)
#define  BFSR_UNSTKERR_MASK      (1<<3U)
#define  BFSR_IMPRECISERR_MASK   (1<<2U)
#define  BFSR_PRECISERR_MASK     (2U)
#define  BFSR_IBUSERR_MASK       (1U)

#define  UFSR_DIVBYZERO_MASK     (1<<9U)
#define  UFSR_UNALIGNED_MASK     (1<<8U)
#define  UFSR_NOCP_MASK          (1<<3U)
#define  UFSR_INVPC_MASK         (1<<2U)
#define  UFSR_INVSTATE_MASK      (2U)
#define  UFSR_UNDEFINSTR_MASK    (1U)


#define  HFSR_DEBUGEVT_MASK      (1<<31U)
#define  HFSR_FORCED_MASK        (1<<30U)
#define  HFSR_VECTTBL_MASK       (2U)


static inline  uint32_t  get_bus_fault_addr(void)
{
    return  REG32_READ(SCB_BFAR_REG_ADDR);
}

static inline  uint32_t  get_bus_fault_info(void)
{
    uint32_t  val  =  REG32_READ(SCB_CFSR_REG_ADDR) >> 8;
    return  (val & 0xff);
}

static inline  uint32_t  get_usage_fault_info(void)
{
    uint32_t  val  =  REG32_READ(SCB_CFSR_REG_ADDR) >> 16;
    return  (val & 0xffff);
}


static inline  uint32_t  get_hard_fault_info(void)
{
    return  REG32_READ(SCB_HFSR_REG_ADDR);
}




#endif

