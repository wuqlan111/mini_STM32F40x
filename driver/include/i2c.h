


#ifndef STM32_I2C_H
#define STM32_I2C_H

#include  <stdlib.h>
#include  <stdint.h>

#include  "util.h"

#define I2C_SMODE_FREQ   100
#define I2C_SMODE_TIME   10000
#define I2C_FMODE_FREQ   400
#define I2C_FMODE_TIME   2500
#define  T_PCLK1         125     // 125ns
#define  I2C_MAX_CLOCK_FREQUENCY         (50u)       // max i2c clock 50 MHz
#define  I2C_MIN_CLOCK_FREQUENCY         (2u)       // min i2c clock 2 MHz

enum {

    I2C_DEV0 = 0,
    I2C_DEV1,
    I2C_DEV2,
    I2C_MAX_DEV = I2C_DEV2,
};


enum  {

    SLAVE_TRANS = 0,
    SLAVE_RECV,
    MASTER_TRANS,
    MASTER_RECV

};

typedef  struct {

    uint32_t  SMBus_alert:1;
    uint32_t  packet_error_check:1;
    uint32_t  acknowledge_enable:1;
    uint32_t  clock_stretch_disable:1;
    uint32_t  general_call_enable:1;
    uint32_t  pec_enable:1;
    uint32_t  arp_enable:1;
    uint32_t  SMBus_host:1;
    uint32_t  SMBus_mode:1;
    uint32_t  DMA_request_enable:1;
    uint32_t  buffer_interrupt_enable:1;
    uint32_t  event_interrupt_enable:1;
    uint32_t  error_interrupt_enable:1;
    uint32_t  clock_frequency:6;

} ATTRIBUTE_ALIGN(4) I2C_config_t;


typedef struct {
    uint32_t  slave_address_10bit:1;
    uint32_t  address:10;
} ATTRIBUTE_ALIGN(4) I2C_address_t;






#endif


