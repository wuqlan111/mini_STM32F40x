
#ifndef STM32_GPIO_H
#define STM32_GPIO_H

#include  <stdlib.h>
#include  <stdint.h>
#include  "util.h"

#define  GPIO_PORT_BIT_NUMBER     16
#define  GPIO_PORT_AF_NUMBER      16


enum  {
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
};


enum {

    GPIO_PORT_INPUT_MODE = 0,
    GPIO_PORT_OUTPUT_MODE,
    GPIO_PORT_ALTERNATE_MODE,
    GPIO_PORT_ANALOG_MODE,
    GPIO_PORT_MAX_MODE  = GPIO_PORT_ANALOG_MODE,

};


enum {

    GPIO_OUTPUT_LOW_SPEED = 0,
    GPIO_OUTPUT_LMEDIUM_SPEED,
    GPIO_OUTPUT_HIGH_SPEED,
    GPIO_OUTPUT_HIGHEST_SPEED,
    GPIO_OUTPUT_MAX_SPEED = GPIO_OUTPUT_HIGHEST_SPEED,

};

enum {

    GPIO_PORT_NO_PULL = 0,
    GPIO_PORT_PULL_UP,
    GPIO_PORT_PULL_DOWN,
    GPIO_PORT_MAX_PULL =  GPIO_PORT_PULL_DOWN,

};


typedef  struct {
    uint32_t  pin:4;
    uint32_t  io_mode:2;
    uint32_t  open_drain:1;
    uint32_t  speed:2;
    uint32_t  pull_mode:2;
    uint32_t  config_lock:1;
    uint32_t  alternate_function:4;
}ATTRIBUTE_ALIGN(4) GPIO_port_bit_config_t;

int32_t  GPIO_port_bit_config(uint32_t port, uint32_t  bit_id,  GPIO_port_bit_config_t * config);
int32_t  get_GPIO_port_data(uint32_t  port,  uint32_t * data);
int32_t  set_GPIO_port_data(uint32_t  port, uint32_t bit_set, uint32_t bit_reset, uint32_t data);


#endif

