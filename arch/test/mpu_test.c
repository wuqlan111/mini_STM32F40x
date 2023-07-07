
#include  <stdint.h>
#include  <stdlib.h>
#include  <string.h>
#include  <memory.h>

#include  "mpu.h"
#include  "arch_printk.h"


static  void  printf_mpu_region_config(mpu_region_config_t * config)
{
    if (!config) {
        return;
    }

    __DBG_PRINTF_ALL("addr:\t0x%08x\n", config->base_addr);
    __DBG_PRINTF_ALL("size:\t%d\n", config->size);
    __DBG_PRINTF_ALL("sub_bits:\t0x%02x\n", config->sub_bits);
    __DBG_PRINTF_ALL("access:\t%d\t", config->access);
    __DBG_PRINTF_ALL("tex:\t%d\n", config->tex);
    __DBG_PRINTF_ALL("shareable:\t%d\n", config->shareable);
    __DBG_PRINTF_ALL("cacheable:\t%d\n", config->cacheable);
    __DBG_PRINTF_ALL("write_back:\t%d\n", config->write_back);
    __DBG_PRINTF_ALL("never_execute:\t%d\n", config->never_execute);

}


void  mpu_test(void)
{

    uint32_t  max_regions = get_mpu_max_regions();
    __DBG_PRINTF_ALL("mpu support max regions:\t%d\n", max_regions);
    /*get */

    mpu_region_config_t  region_conf =  {0};

    __DBG_PRINTF_ALL("/*******1********/\n");
    if (get_mpu_region_config(1,  &region_conf)) {
        __DBG_PRINTF_ALL("get mpu region failed!\n");
    } else {
        printf_mpu_region_config(&region_conf);
    }

    memset(&region_conf,   0,  sizeof(mpu_region_config_t));

    region_conf.access   =  0x2;
    region_conf.base_addr      =     0xf100;
    region_conf.cacheable      =     1;
    region_conf.tex            =     0x3;
    region_conf.sub_bits       =     0x2f;
    region_conf.size           =     64;

    __DBG_PRINTF_ALL("/*******2********/\n");
    if (set_mpu_region_config(1,  &region_conf)) {
        __DBG_PRINTF_ALL("set mpu region failed!\n");
    } else {
        printf_mpu_region_config(&region_conf);
    }

    memset(&region_conf,   0,  sizeof(mpu_region_config_t));

    __DBG_PRINTF_ALL("/*******3********/\n");
    if (get_mpu_region_config(1,  &region_conf)) {
        __DBG_PRINTF_ALL("get mpu region failed!\n");
    } else {
        printf_mpu_region_config(&region_conf);
    }

}



