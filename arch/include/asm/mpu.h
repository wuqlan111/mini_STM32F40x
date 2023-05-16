
#ifndef  ARCH_MPU_H
#define  ARCH_MPU_H

#include  <stdint.h>

#include  "arch_regs.h"


static  inline int32_t get_mpu_max_regions(void)
{
    uint32_t  val = REG32_READ(MPU_TYPE_REG_ADDR);
    return  (val >> 8) & 0xff;
} 


static inline void enable_or_disable_default_map(uint32_t enable)
{
    uint32_t  flag =  enable? 1<<2:0;
    REG32_UPDATE(MPU_CTRL_REG_ADDR, flag,  1 << 2);

}

static inline void enable_or_disable_mpu_handler(uint32_t enable)
{
    uint32_t  flag =  enable? 1<<1:0;
    REG32_UPDATE(MPU_CTRL_REG_ADDR, flag,  1 << 1);
}


static inline void enable_or_disable_mpu(uint32_t enable)
{
    uint32_t  flag =  enable? 1:0;
    REG32_UPDATE(MPU_CTRL_REG_ADDR, flag,  1);
}






#endif


