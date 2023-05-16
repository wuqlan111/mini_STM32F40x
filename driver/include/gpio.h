
#ifndef STM32_GPIO_H
#define STM32_GPIO_H

#include  <stdlib.h>
#include  <stdint.h>


#define OUTPUT_PUSH_PULL      0
#define OUTPUT_OPEN_DRIAN     1

#define  IO_PINS_NUMBER       16
#define  GPIO_PORT_AF_NUMBER      16


enum  gpio_port{
    GPIO_PORTA = 0,
    GPIO_PORTB,
    GPIO_PORTC,
    GPIO_PORTD,
    GPIO_PORTE,
    GPIO_PORTF,
    GPIO_PORTG,
    GPIO_PORTH,
    GPIO_PORTI,
    GPIO_PORT_NUMBER
};


enum port_mode{

    PORT_INPUT_MODE = 0,
    PORT_OUTPUT_MODE,
    PORT_ALTERNATE_MODE,
    PORT_ANALOG_MODE

};


enum output_speed{

    OUTPUT_LOW_SPEED = 0,
    OUTPUT_LMEDIUM_SPEED,
    OUTPUT_HIGH_SPEED,
    OUTPUT_HIGHEST_SPEED

};

enum pull_type{

    PORT_NO_PULL = 0,
    PORT_PULL_UP,
    PORT_PULL_DOWN,
    PORT_PULL_RESERVED

};


typedef struct gpio_register{

    uint32_t port;
    void * gpio_regs;

}gpio_register_t;




int32_t  get_pin_input(uint32_t port,  uint32_t pin);
int32_t get_pin_output(uint32_t port,  uint32_t pin);
int32_t set_pin_output(uint32_t port,  uint32_t pin, uint32_t data);





#endif

