
#include   "../include/gpio.h"


#define PORT_MODE_MASK      0x3
#define OUTPUT_SPEED_MASK   0x3
#define PORT_PULL_TYPE_MAASK    0x3
#define ALTERNATE_PORT_MASK     0xf
#define MAX_PORT_ID         0xf

#define  GPIO_PORT_REG_STEP                          (0x400u)
#define  GPIO_PORT_REGS_BASE_ADDR                    (0x40020000u)
#define  GPIOX_MODER_REG_ADDR(port)                  (GPIO_PORT_REGS_BASE_ADDR + (port) * GPIO_PORT_REG_STEP)
#define  GPIOX_OTYPER_REG_ADDR(port)                 (GPIO_PORT_REGS_BASE_ADDR + (port) * GPIO_PORT_REG_STEP + 0x4)
#define  GPIOX_OSPEEDR_REG_ADDR(port)                (GPIO_PORT_REGS_BASE_ADDR + (port) * GPIO_PORT_REG_STEP + 0x8)
#define  GPIOX_PUPDR_REG_ADDR(port)                  (GPIO_PORT_REGS_BASE_ADDR + (port) * GPIO_PORT_REG_STEP + 0xC)
#define  GPIOX_IDR_REG_ADDR(port)                    (GPIO_PORT_REGS_BASE_ADDR + (port) * GPIO_PORT_REG_STEP + 0x10)
#define  GPIOX_ODR_REG_ADDR(port)                    (GPIO_PORT_REGS_BASE_ADDR + (port) * GPIO_PORT_REG_STEP + 0x14)
#define  GPIOX_BSRR_REG_ADDR(port)                   (GPIO_PORT_REGS_BASE_ADDR + (port) * GPIO_PORT_REG_STEP + 0x18)
#define  GPIOX_LCKR_REG_ADDR(port)                   (GPIO_PORT_REGS_BASE_ADDR + (port) * GPIO_PORT_REG_STEP + 0x1C)
#define  GPIOX_AFRL_REG_ADDR(port)                   (GPIO_PORT_REGS_BASE_ADDR + (port) * GPIO_PORT_REG_STEP + 0x20)
#define  GPIOX_AFRH_REG_ADDR(port)                   (GPIO_PORT_REGS_BASE_ADDR + (port) * GPIO_PORT_REG_STEP + 0x24)


static  int32_t  lock_or_unlock_port_config(uint32_t  port, uint32_t bit_id, uint32_t  lock)
{
    uint32_t  flag, mask;
    flag  =  mask  =  1<< 16;

    while (flag & mask) {
        flag  =  1 << 16;
        REG32_UPDATE(GPIOX_LCKR_REG_ADDR(port), flag, mask);

        flag = 0;
        REG32_UPDATE(GPIOX_LCKR_REG_ADDR(port), flag, mask);

        flag  =  1<< 16;
        REG32_UPDATE(GPIOX_LCKR_REG_ADDR(port), flag, mask);

        flag = REG32_READ(GPIOX_LCKR_REG_ADDR(port));
    }

    flag  =  lock? 1 << bit_id: 0;
    mask  =  1 << bit_id;
    REG32_UPDATE(GPIOX_LCKR_REG_ADDR(port), flag, mask);

    return  0;

}








int32_t  GPIO_port_bit_config(uint32_t port, uint32_t  bit_id,  GPIO_port_bit_config_t * config)
{
    uint32_t  flag,  mask;
    flag = mask = 0;
    if ( (port > GPIO_MAX_PORT) || !config || (bit_id >= GPIO_PORT_BIT_NUMBER)) {
        return  -1;
    }

    if (config->pull_mode > GPIO_PORT_MAX_PULL) {
        return  -1;
    }

    flag = config->io_mode <<  (2 * bit_id);
    mask = 0x3 << (2 * bit_id);
    REG32_UPDATE(GPIOX_MODER_REG_ADDR(port), flag, mask);

    flag = config->open_drain? 1 << bit_id: 0;
    mask = 1<<bit_id;
    REG32_UPDATE(GPIOX_OTYPER_REG_ADDR(port), flag, mask);

    flag  = config->speed << (2 * bit_id);
    mask = 0x3 << (2 * bit_id);
    REG32_UPDATE(GPIOX_OSPEEDR_REG_ADDR(port), flag, mask);

    flag = config->pull_mode << (2 * bit_id);
    mask = 0x3 << (2 * bit_id);
    REG32_UPDATE(GPIOX_PUPDR_REG_ADDR(port), flag, mask);

    if (bit_id > 7) {
        flag  =  config->alternate_function << (2 * (bit_id - 8));
        mask  =  0xf << (2 * (bit_id - 8));
        REG32_UPDATE(GPIOX_AFRH_REG_ADDR(port),  flag, mask);
    } else {
        flag  =  config->alternate_function << (2 * bit_id);
        mask  =  0xf << (2 * bit_id);
        REG32_UPDATE(GPIOX_AFRL_REG_ADDR(port),  flag, mask);
    }

    lock_or_unlock_port_config(port, bit_id, config->config_lock);

    return  0;

}


int32_t  get_GPIO_port_data(uint32_t  port,  uint32_t * data)
{
    if ( (port > GPIO_MAX_PORT) || !data) {
        return  -1;
    }

    *data  =  REG32_READ(GPIOX_IDR_REG_ADDR(port));
    return  0;

}



int32_t  set_GPIO_port_data(uint32_t  port, uint32_t bit_set, uint32_t bit_reset, uint32_t data)
{
    uint32_t  flag = 0;
    if ( (port >  GPIO_MAX_PORT) || (bit_reset > 0xffff) || 
                    (bit_set > 0xffff) || (data > 0xffff) ) {
        return  -1;

    }

    flag = bit_reset << 16 | bit_set;
    REG32_WRITE(GPIOX_BSRR_REG_ADDR(port),  flag);
    REG32_UPDATE(GPIOX_ODR_REG_ADDR(port),  data,  0xffff);

    return  0;
}








