
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
    uint32_t  data_len:2;
    uint32_t  parity:2;
    uint32_t  stop_bits:2;
    uint32_t  baud_rate;
    uint32_t  timeout;
} ATTRIBUTE_ALIGN(4) usart_user_cfg_t;


typedef  struct {
    uint8_t  * rx_buffer;
    uint32_t  rx_sz;
    uint8_t  * tx_buffer;
    uint32_t  tx_size;
} ATTRIBUTE_ALIGN(4) usart_buffer_cfg_t;


typedef struct {
    usart_user_cfg_t  user_cfg;
    usart_buffer_cfg_t  buffer_cfg;
} ATTRIBUTE_ALIGN(4) usart_cfg_t;








#endif

