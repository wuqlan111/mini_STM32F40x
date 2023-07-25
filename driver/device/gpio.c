
#include  <stdint.h>
#include  <string.h>
#include  <memory.h>
#include  <stdlib.h>

#include   "../include/gpio.h"
#include   "../include/driver_util.h"

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


int32_t  lock_or_unlock_port_config(uint32_t  port, uint32_t bit_id, uint32_t  lock)
{
    uint32_t  flag, mask;
    flag  =  mask  =  1<< 16;

    CHECK_PARAM_VALUE(port,  GPIO_MAX_PORT);
    CHECK_PARAM_VALUE(bit_id,  GPIO_PORT_MAX_PIN);

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



int32_t  GPIO_port_bit_config(uint32_t port, GPIO_port_bit_config_t * config)
{
    uint32_t  flag,  mask;
    flag = mask = 0;

    CHECK_PARAM_NULL(config);
    CHECK_PARAM_VALUE(port,  GPIO_MAX_PORT);
    CHECK_PARAM_VALUE(config->pull_mode,  GPIO_PORT_MAX_PULL);

    uint32_t  bit_id  = config->pin;
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

    return  0;

}


int32_t  get_GPIO_port_data(uint32_t  port,  uint32_t * data)
{

    CHECK_PARAM_NULL(data);
    CHECK_PARAM_VALUE(port,  MAX_PORT_ID);

    *data  =  REG32_READ(GPIOX_IDR_REG_ADDR(port));
    return  0;

}



int32_t  set_GPIO_port_data(uint32_t  port, uint32_t bit_set, uint32_t bit_reset, uint32_t data)
{
    uint32_t  flag = 0;

    CHECK_PARAM_VALUE(port,  GPIO_MAX_PORT);
    CHECK_PARAM_VALUE(bit_set,  0xffff);
    CHECK_PARAM_VALUE(bit_reset,  0xffff);
    CHECK_PARAM_VALUE(data,  0xffff);

    flag = bit_reset << 16 | bit_set;
    REG32_WRITE(GPIOX_BSRR_REG_ADDR(port),  flag);
    REG32_UPDATE(GPIOX_ODR_REG_ADDR(port),  data,  0xffff);

    return  0;
}



int32_t  set_GPIO_port_alternate_function(uint32_t  port,  uint32_t  pin,  uint32_t af)
{
    int32_t  ret  =  0;
    uint32_t  flag,  mask,  reg ;
    flag  =  mask  =   reg = 0;

    CHECK_PARAM_VALUE(port,  GPIO_MAX_PORT);
    CHECK_PARAM_VALUE(pin,   GPIO_PORT_MAX_PIN);
    CHECK_PARAM_VALUE(af,    GPIO_PORT_MAX_AF);

    reg  =  pin > GPIO_PORT_PIN7? GPIOX_AFRH_REG_ADDR(port):  GPIOX_AFRL_REG_ADDR(port);

    uint32_t  shift   =   pin > GPIO_PORT_PIN7? pin -  GPIO_PORT_PIN8: pin - GPIO_PORT_PIN0;

    flag  =  af << shift;
    mask  =  0xf << shift;

    REG32_UPDATE(reg,  flag,  mask);

    return   ret;

}



