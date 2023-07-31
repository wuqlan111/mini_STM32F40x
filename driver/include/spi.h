

#ifndef  STM32_SPI_H
#define  STM32_SPI_H

#include  <stdint.h>

#include  "util.h"

typedef  enum  {
    SPI1 = 0,
    SPI2,
    SPI3,
    SPI4,
    SPI5,
    SPI6,
    SPI_MAX_ID  =  SPI6,
} spi_dev_e;


typedef  struct {
    uint32_t   bidirectional_mode:1;
    uint32_t   bidirectional_mode_output_enable:1;
    uint32_t   hardware_crc_enable:1;
    uint32_t   bit16_data_frame:1;
    uint32_t   receive_only:1;
    uint32_t   lsb_transmitted_first:1;
    uint32_t   master_configuration:1;
    uint32_t   clock_high_idle:1;
    uint32_t   second_clock_data_capture_edge:1;
    uint32_t   ss_output_enable:1;
} ATTRIBUTE_ALIGN(4) SPI_config_t;




int32_t   SPI_init(spi_dev_e  spi_id, SPI_config_t * config);

int32_t  enable_or_disable(spi_dev_e  spi_id,  uint32_t  enable);

int32_t  set_SPI_baud_rate(spi_dev_e  spi_id, uint32_t  baud_rate);


#endif

