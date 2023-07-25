
#include  <memory.h>
#include  <string.h>
#include  <stdarg.h>

#include  "usart.h"
#include  "../driver/include/gpio.h"
#include  "../driver/include/system_rcc.h"
#include  "include/console.h"


#define   CONSOLE_USART_BUFFER        (0x1000u)
#define   CONSOLE_USART_ID            USART1
#define   CONSOLE_USART_BAUD_RATE          (115200)
#define   CONSOLE_USART_TIMEOUT           (0x100u)


static  uint8_t   console_tx_buffer[CONSOLE_USART_BUFFER] = {0};
static  uint8_t   console_rx_buffer[CONSOLE_USART_BUFFER] = {0};


int32_t  console_init(void)
{
    int32_t   ret  =  0;
    usart_cfg_t  cfg  =  {0};

    /*enable gpio clk*/
    ret  =  rcc_module_set_op(RCC_MODULE_GPIOA,  RCC_CLK_ENABLE);
    if (ret) {
        return   -1;
    }


    /*init usart1  rx gpio pin function*/
    GPIO_port_bit_config_t gpio_cfg = {0};
    gpio_cfg.pin   = GPIO_PORT_PIN9;
    gpio_cfg.io_mode   =  GPIO_PORT_ALTERNATE_MODE;
    gpio_cfg.speed   =  GPIO_SPEED_2MHZ;
    gpio_cfg.open_drain  =  0;

    if (GPIO_port_bit_config(GPIO_PORTA, &gpio_cfg)) {
        return  -1;
    }

    if (set_GPIO_port_alternate_function(GPIO_PORTA, GPIO_PORT_PIN9,  CONSOLE_USART_ID)) {
        return  -1;
    }

    /*init usart1  tx gpio pin function*/
    gpio_cfg.pin   = GPIO_PORT_PIN10;
    gpio_cfg.io_mode   =  GPIO_PORT_ALTERNATE_MODE;
    gpio_cfg.speed   =  GPIO_SPEED_2MHZ;
    gpio_cfg.open_drain  =  0;

    if (GPIO_port_bit_config(GPIO_PORTA, &gpio_cfg)) {
        return  -1;
    }

    if (set_GPIO_port_alternate_function(GPIO_PORTA, GPIO_PORT_PIN10,  CONSOLE_USART_ID)) {
        return  -1;
    }

    /*enable usart1 clk*/
    ret  =  rcc_module_set_op(RCC_MODULE_USART1,  RCC_CLK_ENABLE);
    if (ret) {
        return   -1;
    }

    cfg.buffer_cfg.rx_buffer  =  console_rx_buffer;
    cfg.buffer_cfg.rx_sz      =  CONSOLE_USART_BUFFER;
    cfg.buffer_cfg.tx_buffer  =  console_tx_buffer;
    cfg.buffer_cfg.tx_sz      =  CONSOLE_USART_BUFFER;

    cfg.user_cfg.baud_rate    =  CONSOLE_USART_BAUD_RATE;
    cfg.user_cfg.data_len     =  USART_DATA_8;
    cfg.user_cfg.parity       =  USART_PARITY_NONE;
    cfg.user_cfg.stop_bits    =  USART_STOP_1_0;
    cfg.user_cfg.timeout      =  CONSOLE_USART_TIMEOUT;


    ret  =   usart_init(CONSOLE_USART_ID,  &cfg);

    return  ret;

}



int32_t  console_fmt_out(char * fmt, ...)
{

    int32_t  ret = 0;
    int32_t  len =  0;

    if (!fmt) {
        return -1;        
    }

    va_list args;
    va_start(args, fmt);
    len = vsprintf(console_tx_buffer,  fmt, args);
    va_end(args);

    if (len <= 0) {
        return  -1;
    }

    console_tx_buffer[len] = '\r';
    console_tx_buffer[len + 1]  =  '\n';

    ret  =  usart_send_data(CONSOLE_USART_ID,  len + 2);

    return  ret;

}



int32_t  console_recv_data(uint8_t * buf, uint32_t len,  uint32_t * recv_len)
{
    int32_t   ret  =   0;

    if (!buf || !recv_len || !len ) {
        return  -1;
    }

    *recv_len  = 0;
    ret   =  usart_recv_data(CONSOLE_USART_ID,  len,  recv_len);

    if (!ret) {
        memcpy(buf,   console_rx_buffer,  *recv_len );
    }

    return  ret;

}





