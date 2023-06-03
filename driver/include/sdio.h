

#ifndef  STM32_SDIO_H
#define  STM32_SDIO_H

#include  <stdint.h>
#include  "util.h"

enum {
    SDIO_CLOCK_POWER_OFF  =  0,
    SDIO_CLOCK_POWER_UP  =  2,
    SDIO_CLOCK_POWER_ON,
};

enum {
    SDIO_DEFAULT_BUS_MODE  =  0,
    SDIO_4BIT_BUS_MODE,
    SDIO_8BIT_BUS_MODE,
    SDIO_MAX_BUS_MODE  =  SDIO_8BIT_BUS_MODE,
};


enum {
    SDIO_NO_RESPONSE  =  0,
    SDIO_SHORT_RESPONSE,
    SDIO_LONG_RESPONSE  = 3,
};


typedef struct {
    uint32_t  hw_flow_control_enable:1;
    uint32_t  output_clock_fall_edge:1;
    uint32_t  wide_bus_mode:2;
    uint32_t  output_clock_bypass_divider:1;
    uint32_t  output_clock_always:1;
    uint32_t  output_clock_enable:1;
    uint32_t  output_clock_divide:8;
    uint32_t  data_timeout_period;
} ATTRIBUTE_ALIGN(4) SDIO_config_t;



typedef struct {
    uint32_t  ceata_completion_interrupt:1;
    uint32_t  sdio_mode_interrupt:1;
    uint32_t  rx_fifo_avalible_interrupt:1;
    uint32_t  tx_fifo_avalible_interrupt:1;
    uint32_t  rx_fifo_empty_interrupt:1;
    uint32_t  tx_fifo_empty_interrupt:1;
    uint32_t  rx_fifo_full_interrupt:1;
    uint32_t  tx_fifo_full_interrupt:1;
    uint32_t  rx_fifo_half_full_interrupt:1;
    uint32_t  data_receive_acting_interrupt:1;
    uint32_t  data_transmit_acting_interrupt:1;
    uint32_t  command_acting_interrupt:1;
    uint32_t  data_block_end_interrupt:1;
    uint32_t  start_bit_error_interrupt:1;
    uint32_t  data_end_interrupt:1;
    uint32_t  command_sent_interrupt:1;
    uint32_t  command_response_received_interrupt:1;
    uint32_t  rx_fifo_overrun_error_interrupt:1;
    uint32_t  tx_fifo_overrun_error_interrupt:1;
    uint32_t  data_timeout_interrupt:1;
    uint32_t  command_timeout_interrupt:1;
    uint32_t  data_crc_fail_interrupt:1;
    uint32_t  command_crc_fail_interrupt:1;

} ATTRIBUTE_ALIGN(4) SDIO_interrupt_mask_t;


int32_t  global_SDIO_config(SDIO_config_t * config);
int32_t  global_SDIO_interrupt_config(SDIO_interrupt_mask_t * config);






#endif

