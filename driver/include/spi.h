

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
    uint32_t   bidirectional_mode:1;
    uint32_t   bidirectional_mode_output_enable:1;
    uint32_t   hardware_crc_enable:1;
    uint32_t   no_crc_phase:1;
    uint32_t   bit16_data_frame:1;
    uint32_t   receive_only:1;
    uint32_t   software_slave_management_enable:1;
    uint32_t   lsb_transmitted_first:1;
    uint32_t   baud_rate_control:3;
    uint32_t   master_configuration:1;
    uint32_t   clock_high_idle:1;
    uint32_t   second_clock_data_capture_edge:1;
    uint32_t   spi_ti_mode:1;
    uint32_t   ss_output_enable:1;
    uint32_t   tx_buffer_dma_enable:1;
    uint32_t   rx_buffer_dma_enable:1;
} ATTRIBUTE_ALIGN(4) SPI_config_t;


typedef  struct {
    uint32_t  tx_buffer_empty_interrupt:1;
    uint32_t  rx_buffer_not_empty_interrupt:1;
    uint32_t  error_interrupt_enable:1;
}ATTRIBUTE_ALIGN(4) SPI_I2S_interrupt_mask_t;


typedef  struct {
    uint32_t   tx_buffer_dma_enable:1;
    uint32_t   rx_buffer_dma_enable:1;
    uint32_t   i2s_configuration_mode:2;
    uint32_t   long_frame_synchronization:1;
    uint32_t   i2s_standard_selection:2;
    uint32_t   steady_state_clock_high:1;
    uint32_t   data_length:2;
    uint32_t   channel_bit32_length:1;
    uint32_t   master_clock_output_enable:1;
    uint32_t   odd_factor_prescale:1;
    uint32_t   i2s_linear_prescaler:8;
} ATTRIBUTE_ALIGN(4) I2S_config_t;



int32_t   global_SPI_config(uint32_t  spi_id, SPI_config_t * config);
int32_t   SPI_interrupt_mask(uint32_t  spi_id,  SPI_I2S_interrupt_mask_t * config);

int32_t   global_I2S_config(uint32_t  i2s_id, I2S_config_t * config);
int32_t   I2S_interrupt_mask(uint32_t  i2s_id,  SPI_I2S_interrupt_mask_t * config);




#endif

