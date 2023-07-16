
#ifndef  STM32_USART_H
#define  STM32_USART_H

#include  <stdint.h>

#include  "util.h"

typedef  enum {
    USART1 = 0,
    USART2,
    USART3,
    USART4,
    USART5,
    USART6,
    USART7,
    USART8,
    USART_MAX_ID  =  USART8,
} usart_dev_e;

typedef enum {
    USART_DATA_8 = 0,
    USART_DATA_9,
    USART_MAX_DATA_LEN  =  USART_DATA_9,
} usart_data_len_e;

typedef enum {
    USART_STOP_0_5 = 0,
    USART_STOP_1_0,
    USART_STOP_1_5,
    USART_STOP_2_0,
    USART_MAX_STOP_BIT  =  USART_STOP_2_0,
} usart_stop_bits_e;


typedef enum {
    USART_PARITY_NONE =  0,
    USART_PARITY_ODD,
    USART_PARITY_EVEN,
    USART_MAX_PARITY  =  USART_PARITY_EVEN,
} usart_parity_e;


typedef  struct {
    
} usart_user_cfg_t;







int32_t  global_USART_config(uint32_t  usart_id,  USART_config_t  * config);

int32_t  global_USART_interrupt(uint32_t  usart_id,  USART_interrupt_config_t * config);

#endif

