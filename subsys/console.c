
#include  <memory.h>
#include  <string.h>
#include  <stdarg.h>

#include  "usart.h"
#include  "include/console.h"


#define   CONSOLE_USART_BUFFER        (0x1000u)
#define   CONSOLE_USART_ID            USART1
#define   CONSOLE_USART_BAUD_RATE          (115200)
#define   CONSOLE_USART_TIMEOUT           (0x100u)


uint8_t   console_tx_buffer[CONSOLE_USART_BUFFER] = {0};
uint8_t   console_rx_buffer[CONSOLE_USART_BUFFER] = {0};



int32_t  console_init(void)
{
    int32_t   ret  =  0;
    usart_cfg_t  cfg  =  {0};

    cfg.buffer_cfg.rx_buffer  =  console_rx_buffer;
    cfg.buffer_cfg.rx_sz      =  CONSOLE_USART_BUFFER;
    cfg.buffer_cfg.tx_buffer  =  console_tx_buffer;
    cfg.buffer_cfg.tx_sz      =  CONSOLE_USART_BUFFER;

    cfg.user_cfg.baud_rate    =  CONSOLE_USART_BAUD_RATE;
    cfg.user_cfg.data_len     =  USART_DATA_8;
    cfg.user_cfg.parity       =  USART_PARITY_ODD;
    cfg.user_cfg.stop_bits    =  USART_STOP_1_0;
    cfg.user_cfg.timeout      =  CONSOLE_USART_TIMEOUT;

    ret  =   usart_init(CONSOLE_USART_ID,  &cfg);

    return  ret;

}



int32_t  console_fmt_out(char * fmt, ...)
{

    int32_t  ret = 0;

    if (!fmt) {
        return -1;        
    }

    va_list args;
    va_start(args, fmt);
    vsprintf(console_tx_buffer,  fmt, args);
    va_end(args);





    return  ret;

}













