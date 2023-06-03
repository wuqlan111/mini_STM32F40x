

#ifndef  STM32_SPI_H
#define  STM32_SPI_H

#include  <stdint.h>

#include  "util.h"

enum  {
    SPI1 = 0,
    SPI2,
    SPI3,
    SPI4,
    SPI5,
    SPI6,
    SPI_MAX_ID  =  SPI6,
};

enum  {
    I2S1  =  0,
    I2S2,
    I2S3,
    I2S4,
    I2S_MAX_ID  =  I2S4,
};


enum {
    I2S_Slave_transmit =  0,
    I2S_SLAVE_RECEIVE,
    I2S_MASTER_TRANSMIT,
    I2S_MASTER_RECEIVE,
    I2S_MAX_MODE  =  I2S_MASTER_RECEIVE,
};

enum {
    I2S_TRANSFER_16BIT =  0,
    I2S_TRANSFER_24BIT,
    I2S_TRANSFER_32BIT,
    I2S_MAX_TRANSFER_DATA  =  I2S_TRANSFER_32BIT,
};


enum {
    I2S_PHILIPS_STANDARD  =  0,
    I2S_MSB_JUSTIFIED_STANDARD,
    I2S_LSB_JUSTIFIED_STANDARD,
    I2S_PCM_STANDARD,
    I2S_MAX_STANDARD_SELECTION   =  I2S_PCM_STANDARD,
};


typedef  struct {




} ATTRIBUTE_ALIGN(4) SPI_config_t;










#endif

