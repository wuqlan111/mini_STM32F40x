
#ifndef  ARCH_MPU_H
#define  ARCH_MPU_H

#include  <stdint.h>

#include  "arch_regs.h"
#include  "gcc_type.h"

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

static inline void enable_or_disable_mpu_exception_occur(uint32_t enable)
{
    uint32_t  flag =  enable? 1<<1:0;
    REG32_UPDATE(MPU_CTRL_REG_ADDR, flag,  1 << 1);
}


static inline void enable_or_disable_mpu(uint32_t enable)
{
    uint32_t  flag =  enable? 1:0;
    REG32_UPDATE(MPU_CTRL_REG_ADDR, flag,  1);
}


typedef  struct {
    uint32_t  base_addr;
    uint32_t  size;
    uint32_t  never_execute:1;
    uint32_t  access:3;
    uint32_t  tex:3;
    uint32_t  shareable:1;
    uint32_t  cacheable:1;
    uint32_t  write_back:1;
    uint32_t  sub_bits:8;
}ATTRIBUTE_ALIGN(4) mpu_region_config_t;


int32_t  enable_or_disable_region(uint32_t region, uint32_t enable);
int32_t  set_mpu_region_config(uint32_t  region,  mpu_region_config_t * config);
int32_t  get_mpu_region_config(uint32_t  region,  mpu_region_config_t * config);


#endif


