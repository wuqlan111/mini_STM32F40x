
#include  <stdlib.h>

#include  "random_number_generator.h"

#define  RNG_CR_INTERRUPT_ENABLE                   (1<<3u)
#define  RNG_CR_RNGEN                              (1<<2u)

#define  RNG_SR_SEED_ERROR                         (1<<6u)
#define  RNG_SR_CLOCK_ERROR                        (1<<5u)
#define  RNG_SR_SEED_ERROR_CURRENT                 (1<<2u)
#define  RNG_SR_CLOCK_ERROR_CURRENT                (0x2u)
#define  RNG_SR_DATA_READY                         (0x1u)

#define  RNG_REGS_BASE_ADDR                      (0x50060800u)
#define  RNG_CR_REG_ADDR                         (RNG_REGS_BASE_ADDR)
#define  RNG_SR_REG_ADDR                         (RNG_REGS_BASE_ADDR + 0x4)
#define  RNG_DR_REG_ADDR                         (RNG_REGS_BASE_ADDR + 0x8)


int32_t  get_random_number(uint32_t * random)
{
    uint32_t  flag,  mask;
    flag  =  mask  = 0;
    if (!random) {
        return  -1;
    }

    REG32_UPDATE(RNG_CR_REG_ADDR,  0x4,  0x4);

    REG32_WAIT(RNG_SR_REG_ADDR,  0x1,  0x1);

    *random  =  REG32_READ(RNG_DR_REG_ADDR);

    return  0;

}



