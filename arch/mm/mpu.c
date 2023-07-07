
#include <stdint.h>

#include  "math_util.h"
#include  "arch_regs.h"
#include  "mpu.h"


#define  MIN_REGION_SIZE     32
#define  MPU_RASR_MIN_SIZE           4

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


int32_t  set_mpu_region_config(uint32_t  region,  mpu_region_config_t * config)
{
    int32_t  ret  =  0;
    uint32_t max_region,  size;
    max_region  = size  =  0;
    max_region =  get_mpu_max_regions();

    if ( (region >= max_region) || !config || (config->base_addr & 0x1f)) {
        return  -1;        
    }

    if ( (config->size  < MIN_REGION_SIZE)  ||  !is_powers_of_2(config->size)) {
        return  -1;
    }


    if (math_clog2(config->size, &size) || (config->base_addr % config->size)) {
        return  -1;
    }

    REG32_WRITE(MPU_RBAR_REG_ADDR,  config->base_addr | (1<<4) | region);

    uint32_t  flag,  mask;
    flag  =  mask  =  0;

    flag   =   config->access  <<  24;
    flag  |=   config->tex     <<  19;
    flag  |=   config->sub_bits  << 8;
    flag  |=   (size - 1)   <<  1;

    if (config->never_execute) {
        flag  |= 1 << 28;
    }

    if (config->shareable) {
        flag  |=  1 << 18;
    }

    if (config->cacheable) {
        flag  |=  1 << 17;
    }

    if (config->write_back) {
        flag  |=  1 << 16;
    }

    mask   =   (1 << 28) | (7 << 24) | (0x3fff << 8) | (0x1f << 1);
    REG32_UPDATE(MPU_RASR_REG_ADDR,   flag,   mask);

    REG32_WRITE(MPU_RNR_REG_ADDR,  region);

    return   0;

}


int32_t  get_mpu_region_config(uint32_t  region,  mpu_region_config_t * config)
{

    int32_t  ret  =  0;
    uint32_t max_region,  flag;
    max_region  = flag  =  0;
    max_region =  get_mpu_max_regions();

    if ( (region >= max_region) || !config ) {
        return  -1;        
    }

    REG32_WRITE(MPU_RNR_REG_ADDR,  region);
    flag  =   REG32_READ(MPU_RASR_REG_ADDR);

    config->base_addr  =  REG32_READ(MPU_RBAR_REG_ADDR) & (~0x1f);
    config->never_execute    =  flag & (1<<28)? 1:  0;
    config->access     =    (flag  >>  24) &  0x7;
    config->tex        =    (flag  >>  19) &  0x7;
    config->shareable     =    flag &  (1 << 18)?  1:  0;
    config->cacheable     =    flag &  (1 << 17)?  1:  0;
    config->write_back    =    flag &  (1 << 16)?  1:  0;
    config->sub_bits      =    ( flag >> 8 ) & 0xff;
    config->size          =    0;

    uint32_t  tmp_size   =   (flag >> 1 ) & 0x1f;

    if (tmp_size >= MPU_RASR_MIN_SIZE) {
        config->size     =   1  <<  ((tmp_size) + 1);
    }
    
    return   0;

}




