
#ifndef STM32_GPIO_H
#define STM32_GPIO_H

#include  <stdlib.h>
#include  <stdint.h>
#include  "util.h"

#define  GPIO_PORT_BIT_NUMBER     16
#define  GPIO_PORT_AF_NUMBER      16


typedef enum  {
    GPIO_PORTA = 0,
    GPIO_PORTB,
    GPIO_PORTC,
    GPIO_PORTD,
    GPIO_PORTE,
    GPIO_PORTF,
    GPIO_PORTG,
    GPIO_PORTH,
    GPIO_PORTI,
    GPIO_PORTJ,
    GPIO_PORTK,
    GPIO_MAX_PORT  =  GPIO_PORTK,
} gpio_port_e;


typedef enum  {
    GPIO_PORT_PIN0 = 0,
    GPIO_PORT_PIN1,
    GPIO_PORT_PIN2,
    GPIO_PORT_PIN3,
    GPIO_PORT_PIN4,
    GPIO_PORT_PIN5,
    GPIO_PORT_PIN6,
    GPIO_PORT_PIN7,
    GPIO_PORT_PIN8,
    GPIO_PORT_PIN9,
    GPIO_PORT_PIN10,
    GPIO_PORT_PIN11,
    GPIO_PORT_PIN12,
    GPIO_PORT_PIN13,
    GPIO_PORT_PIN14,
    GPIO_PORT_PIN15,
    GPIO_PORT_MAX_PIN  =  GPIO_PORT_PIN15,
} gpio_port_pin_e;


typedef enum {
    GPIO_PORT_INPUT_MODE = 0,
    GPIO_PORT_OUTPUT_MODE,
    GPIO_PORT_ALTERNATE_MODE,
    GPIO_PORT_ANALOG_MODE,
    GPIO_PORT_MAX_MODE  = GPIO_PORT_ANALOG_MODE,
} gpio_port_direction_e;

typedef enum {
    GPIO_PORT_OUTPUT_PP  =  0,
    GPIO_PORT_OUTPUT_OP,
    GPIO_PORT_MAX_OUTPUT_TYPE = GPIO_PORT_OUTPUT_OP,
} gpio_port_output_type_e;


typedef enum {
    GPIO_OUTPUT_LOW_SPEED = 0,
    GPIO_OUTPUT_MEDIUM_SPEED,
    GPIO_OUTPUT_HIGH_SPEED,
    GPIO_OUTPUT_HIGHEST_SPEED,
    GPIO_OUTPUT_MAX_SPEED = GPIO_OUTPUT_HIGHEST_SPEED,
} gpio_port_speed_e;

#define  GPIO_SPEED_2MHZ        GPIO_OUTPUT_LOW_SPEED   
#define  GPIO_SPEED_25MHZ       GPIO_OUTPUT_MEDIUM_SPEED 
#define  GPIO_SPEED_50MHZ       GPIO_OUTPUT_HIGH_SPEED 
#define  GPIO_SPEED_100MHZ      GPIO_OUTPUT_HIGHEST_SPEED


typedef enum {
    GPIO_PORT_NO_PULL = 0,
    GPIO_PORT_PULL_UP,
    GPIO_PORT_PULL_DOWN,
    GPIO_PORT_MAX_PULL =  GPIO_PORT_PULL_DOWN,
} gpio_push_up_down_e;


typedef enum {
    GPIO_PORT_AF0   =  0,
    GPIO_PORT_AF1,
    GPIO_PORT_AF2,
    GPIO_PORT_AF3,
    GPIO_PORT_AF4,
    GPIO_PORT_AF5,
    GPIO_PORT_AF6,
    GPIO_PORT_AF7,
    GPIO_PORT_AF8,
    GPIO_PORT_AF9,
    GPIO_PORT_AF10,
    GPIO_PORT_AF11,
    GPIO_PORT_AF12,
    GPIO_PORT_AF13,
    GPIO_PORT_AF14,
    GPIO_PORT_AF15,
    GPIO_PORT_MAX_AF  =  GPIO_PORT_AF15,
} gpio_alternate_function_e;

#define  GPIO_AF_SYSTEM      GPIO_PORT_AF0
#define  GPIO_AF_TIM1        GPIO_PORT_AF1
#define  GPIO_AF_TIM2        GPIO_PORT_AF1
#define  GPIO_AF_TIM3        GPIO_PORT_AF2
#define  GPIO_AF_TIM4        GPIO_PORT_AF2
#define  GPIO_AF_TIM5        GPIO_PORT_AF2
#define  GPIO_AF_TIM8        GPIO_PORT_AF3
#define  GPIO_AF_TIM9        GPIO_PORT_AF3
#define  GPIO_AF_TIM10       GPIO_PORT_AF3
#define  GPIO_AF_TIM11       GPIO_PORT_AF3
#define  GPIO_AF_I2CX        GPIO_PORT_AF4
#define  GPIO_AF_SPI1        GPIO_PORT_AF5
#define  GPIO_AF_SPI2        GPIO_PORT_AF5
#define  GPIO_AF_SPI3        GPIO_PORT_AF6
#define  GPIO_AF_USART1        GPIO_PORT_AF7
#define  GPIO_AF_USART2        GPIO_PORT_AF7
#define  GPIO_AF_USART3        GPIO_PORT_AF7
#define  GPIO_AF_USART4        GPIO_PORT_AF8
#define  GPIO_AF_USART5        GPIO_PORT_AF8
#define  GPIO_AF_USART6        GPIO_PORT_AF8
#define  GPIO_AF_CANX          GPIO_PORT_AF9
#define  GPIO_AF_TIM12         GPIO_PORT_AF9
#define  GPIO_AF_TIM13         GPIO_PORT_AF9
#define  GPIO_AF_TIM14         GPIO_PORT_AF9
#define  GPIO_AF_OTG_HS        GPIO_PORT_AF10
#define  GPIO_AF_OTG_FS        GPIO_PORT_AF10
#define  GPIO_AF_ETH           GPIO_PORT_AF11
#define  GPIO_AF_FSMC          GPIO_PORT_AF12
#define  GPIO_AF_SDIO          GPIO_PORT_AF12
#define  GPIO_AF_DCMI          GPIO_PORT_AF13
#define  GPIO_AF_EVENTOUT      GPIO_PORT_AF15


typedef  struct {
    uint32_t  pin:4;
    uint32_t  io_mode:2;
    uint32_t  open_drain:1;
    uint32_t  speed:2;
    uint32_t  pull_mode:2;
}ATTRIBUTE_ALIGN(4) GPIO_port_bit_config_t;

int32_t  GPIO_port_bit_config(uint32_t port, GPIO_port_bit_config_t * config);
int32_t  get_GPIO_port_data(uint32_t  port,  uint32_t * data);



#endif

