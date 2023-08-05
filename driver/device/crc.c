
#include <stdlib.h>

#include  "../include/driver_util.h"
#include  "../include/crc.h"
#include  "../../subsys/include/console.h"

#define  CRC_REGS_BASE_ADDR                        (0x40023000u)
#define  CRC_DR_REG_ADDR                           (CRC_REGS_BASE_ADDR)
#define  CRC_IDR_REG_ADDR                          (CRC_REGS_BASE_ADDR + 0x4)
#define  CRC_CR_REG_ADDR                           (CRC_REGS_BASE_ADDR + 0x8)

#define  WAIT_CRC_TIMEOUT                 12000


static  int32_t  wait_crc32_complete(uint32_t value,  uint32_t  timesout)
{
    uint32_t   tmp  =  0;
    const  uint32_t   timeout_vld =  timesout ?  1:  0;

    do {
        tmp  =   REG32_READ(CRC_DR_REG_ADDR);

        if (tmp !=  value) {
            DEBUG_PRINTF_INFO("wait crc32 complete failed successful!");
            return   0;
        }

        timesout   =   timesout? timesout - 1: 0;

        if (timeout_vld && !timesout) {
            break;
        }
    } while(1);

    DEBUG_PRINTF_ERROR("wait crc32 complete failed!");

    return  -1;

}


int32_t  get_crc32_of_data(uint8_t * data,  uint32_t  len,   uint32_t * crc)
{
    CHECK_PARAM_NULL(crc);
    CHECK_PARAM_NULL(data);

    if (!len || (len & 0x3)) {
        DEBUG_PRINTF_ERROR("len[%u] invalid!",  len);
        return  -1;
    }

    *crc  =  0;
    REG32_WRITE(CRC_CR_REG_ADDR,  0x1);

    DEBUG_PRINTF_DEBUG("crc_data:\t%p,\tlen:\t%u!", data,  len);

    uint32_t * val32  =  (uint32_t *)data;
    uint32_t  times  =  len >> 2;

    for (uint32_t i  =  0; i < times;  i++) {

        REG32_WRITE(CRC_DR_REG_ADDR,  val32[i]);

        if (wait_crc32_complete(val32[i],   WAIT_CRC_TIMEOUT)) {
            return   -1;
        }
    }

    *crc  =  REG32_READ(CRC_IDR_REG_ADDR);

    return   0;

}








