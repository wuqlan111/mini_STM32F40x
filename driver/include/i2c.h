


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

typedef  enum {

    I2C_DEV0 = 0,
    I2C_DEV1,
    I2C_DEV2,
    I2C_MAX_DEV = I2C_DEV2,
} i2c_dev_e;


typedef  enum  {
    SLAVE_TRANS = 0,
    SLAVE_RECV,
    MASTER_TRANS,
    MASTER_RECV
} i2c_dev_mode_e;

typedef  struct {
    uint32_t  acknowledge_enable:1;
    uint32_t  clock_stretch_disable:1;
    uint32_t  general_call_enable:1;
    uint32_t  pec_enable:1;
    uint32_t  arp_enable:1;
    uint32_t  fm_mode:1;
    uint32_t  fm_tlow_thigh_2:1;
} ATTRIBUTE_ALIGN(4) I2C_config_t;


typedef struct {
    uint32_t  slave_address_10bit:1;
    uint32_t  address1:10;
    uint32_t  address2:10;
    uint32_t  dual_address_mode:1;
} ATTRIBUTE_ALIGN(4) I2C_address_t;


typedef struct {
    uint32_t  pclk_freq:6;       //MHz
    uint32_t  scl_freq:10;      //KHz
    uint32_t  trise_time:10;    //ns
} ATTRIBUTE_ALIGN(4) I2C_transfer_time_t;


int32_t  I2C_dev_init(i2c_dev_e  i2c_dev, I2C_config_t * config);
int32_t  enable_or_disable_I2C(i2c_dev_e i2c_dev, uint32_t enable);
int32_t  set_I2C_slave_address(i2c_dev_e  i2c_dev, I2C_address_t * config);
int32_t  set_I2C_transfer_time(i2c_dev_e  i2c_dev, I2C_transfer_time_t * config);
int32_t  I2C_send_data(i2c_dev_e  i2c_dev,  uint8_t * data,  uint32_t len);
int32_t  I2C_recv_data(i2c_dev_e  i2c_dev,  uint8_t * data,  uint32_t len,  uint32_t * recv_len);


#endif


