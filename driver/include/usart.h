
#ifndef  STM32_USART_H
#define  STM32_USART_H

#include  <stdint.h>

#include  "util.h"

enum {
    USART1 = 0,
    USART2,
    USART3,
    USART4,
    USART5,
    USART6,
    USART7,
    USART8,
    USART_MAX_ID  =  USART8,
};


typedef  struct {
    uint32_t  oversampling_by8:1;
    uint32_t  data_bit9:1;
    uint32_t  wakeup_address_mark:1;
    uint32_t  parity_control_enabled:1;
    uint32_t  odd_parity:1;
    uint32_t  lin_mode_enable:1;
    uint32_t  stop_bits:2;
    uint32_t  ck_pin_enable:1;
    uint32_t  second_clock_data_capture:1;
    uint32_t  last_data_bit_clk_output:1;
    uint32_t  bit11_breakdetection:1;
    uint32_t  one_sample_bit:1;
    uint32_t  cts_enable:1;
    uint32_t  rts_enable:1;
    uint32_t  dma_transmitter_enable:1;
    uint32_t  dma_receiver_enable:1;
    uint32_t  smartcard_mode_enable:1;
    uint32_t  smartcard_nack_enable:1;
    uint32_t  half_duplex_mode_enable:1;

} ATTRIBUTE_ALIGN(4) USART_config_t;

typedef  struct {
    uint32_t  pe_interrupt_enable:1;
    uint32_t  txe_interrupt_enable:1;
    uint32_t  complete_interrupt_enable:1;
    uint32_t  rxne_interrupt_enable:1;
    uint32_t  idle_interrupt_enable:1;
    uint32_t  cts_interrupt_enable:1;
    uint32_t  error_interrupt_enable:1;
} ATTRIBUTE_ALIGN(4)  USART_interrupt_config_t;


int32_t  global_USART_config(uint32_t  usart_id,  USART_config_t  * config);

int32_t  global_USART_interrupt(uint32_t  usart_id,  USART_interrupt_config_t * config);

#endif

