
#include <stdint.h>

#include  "arch_regs.h"
#include  "mpu.h"


#define  MIN_REGION_SIZE     32

int32_t  get_region_base_addr(uint32_t region, uint32_t * addr)
{
    uint32_t  max_region =  get_mpu_max_regions();
    if ( (region >= max_region) || !addr)
        return  -1;

    REG32_WRITE(MPU_RNR_REG_ADDR,  region);
    uint32_t  val = REG32_READ(MPU_RBAR_REG_ADDR);
    *addr =  val & 0xfffffe0;

    return 0;
}


int32_t  set_region_base_addr(uint32_t region, uint32_t addr)
{
    uint32_t  max_region =  get_mpu_max_regions();
    if ( (region >= max_region) || (addr & 0x1f))
        return  -1;

    REG32_WRITE(MPU_RBAR_REG_ADDR,  addr);
    REG32_WRITE(MPU_RNR_REG_ADDR,   region);

    return 0;
}

int32_t  set_region_size(uint32_t region, uint32_t size)
{
    uint32_t  max_region =  get_mpu_max_regions();
    if ( (region >= max_region) || (size < 4) || (size > 0x1f))
        return  -1;

    REG32_WRITE(MPU_RNR_REG_ADDR,  region);
    REG32_UPDATE(MPU_RNR_REG_ADDR,  size << 1, 0x3e);
    REG32_WRITE(MPU_RNR_REG_ADDR,  region);

    return 0;
}

int32_t  enable_or_disable_region(uint32_t region, uint32_t enable)
{
    uint32_t  max_region =  get_mpu_max_regions();
    if ( (region >= max_region) )
        return  -1;

    uint32_t flag = enable? 0x1: 0;
    REG32_WRITE(MPU_RNR_REG_ADDR,  region);
    REG32_UPDATE(MPU_RNR_REG_ADDR,  flag, 0x1);
    REG32_WRITE(MPU_RNR_REG_ADDR,  region);

    return 0;
}


int32_t  enable_or_disable_subregison(uint32_t region, uint32_t sub_bits, uint32_t enable)
{
    uint32_t  max_region =  get_mpu_max_regions();
    if ( (region >= max_region) ||  (sub_bits & 0xffffff00) )
        return  -1;

    uint32_t flag = enable? sub_bits << 8: (~sub_bits & 0xff) << 8;
    REG32_WRITE(MPU_RNR_REG_ADDR,  region);
    REG32_UPDATE(MPU_RNR_REG_ADDR,  flag, 0xff00);
    REG32_WRITE(MPU_RNR_REG_ADDR,  region);

    return 0;
}






