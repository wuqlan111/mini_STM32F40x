


#ifndef STM32_I2C_H
#define STM32_I2C_H

#include  <stdlib.h>
#include  <stdint.h>

#include  "util.h"


#define T_PCLK1         125     // 125ns


enum i2c_dev{

    I2C_DEV0 = 0,
    I2C_DEV1,
    I2C_DEV2,
    I2C_DEV_NUMBER
};


enum  i2c_mode{

    SLAVE_TRANS = 0,
    SLAVE_RECV,
    MASTER_TRANS,
    MASTER_RECV

};


#define I2C_SMODE_FREQ   100
#define I2C_SMODE_TIME   10000
#define I2C_FMODE_FREQ   400
#define I2C_FMODE_TIME   2500


#endif



