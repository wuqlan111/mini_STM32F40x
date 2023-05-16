
#include   "../include/gpio.h"


#define PORT_MODE_MASK      0x3
#define OUTPUT_SPEED_MASK   0x3
#define PORT_PULL_TYPE_MAASK    0x3
#define ALTERNATE_PORT_MASK     0xf
#define MAX_PORT_ID         0xf


typedef struct gpio_reg{

    uint32_t  gpio_mode;
    uint32_t  gpio_otype;
    uint32_t  gpio_ospeed;
    uint32_t  gpio_pupd;
    uint32_t  gpio_input;
    uint32_t  gpio_output;
    uint32_t  gpio_bset;
    uint32_t  gpio_lock;
    uint32_t  gpio_afrl;
    uint32_t  gpio_afrh;

}gpio_reg_t;


gpio_reg_t  *  gpio_ports[GPIO_PORT_NUMBER];




static int32_t  register_gpio_port(gpio_register_t *  new_port){

    uint32_t  reg_base = (uint32_t)new_port->gpio_regs, port_idx = new_port->port;

    if(port_idx >= GPIO_PORT_NUMBER  ||  gpio_ports[port_idx] || reg_base & 0x3 )
        return -1;

    gpio_ports[port_idx] =  (gpio_reg_t *)new_port->gpio_regs;

    return 0;

}


static  int32_t get_port_mode(uint32_t port,  uint32_t port_af){

    if (port >= GPIO_PORT_NUMBER || port_af >= GPIO_PORT_AF_NUMBER)
            return -1;

    gpio_reg_t * gpio_reg =  gpio_ports[port];

    uint32_t reg_val =  ((gpio_reg->gpio_mode)>>(port_af + 1)) & 0x3;

    return reg_val;

}


static int32_t set_port_mode(uint32_t port,  uint32_t port_af, uint32_t mode){

    if (port >= GPIO_PORT_NUMBER || port_af >= GPIO_PORT_AF_NUMBER || mode > PORT_ANALOG_MODE)
            return -1;

    gpio_reg_t * gpio_reg =  gpio_ports[port];

    uint32_t reg_val =  gpio_reg->gpio_mode;

    reg_val &=  ~(0x3<<port_af);
    reg_val |= (mode << port_af);

    gpio_reg->gpio_mode = reg_val;

    return 0;

}




static int32_t get_port_otype(uint32_t port,  uint32_t port_af){

    if (port >= GPIO_PORT_NUMBER || port_af >= GPIO_PORT_AF_NUMBER)
            return -1;

    gpio_reg_t * gpio_reg =  gpio_ports[port];

    uint32_t reg_val =  ((gpio_reg->gpio_otype)>>port_af ) & 0x1;

    return reg_val;

}


static int32_t set_port_otype(uint32_t port,  uint32_t port_af, uint32_t otype){

    if (port >= GPIO_PORT_NUMBER || port_af >= GPIO_PORT_AF_NUMBER || otype > 1)
            return -1;

    gpio_reg_t * gpio_reg =  gpio_ports[port];

    uint32_t reg_val =  gpio_reg->gpio_otype;

    reg_val &=  ~(0x1<<port_af);
    reg_val |= (otype << port_af);

    gpio_reg->gpio_mode = reg_val;

    return 0;

}



static int32_t get_port_pupd(uint32_t port,  uint32_t port_af){

    if (port >= GPIO_PORT_NUMBER || port_af >= GPIO_PORT_AF_NUMBER)
            return -1;

    gpio_reg_t * gpio_reg =  gpio_ports[port];

    uint32_t reg_val =  ((gpio_reg->gpio_otype)>>port_af ) & 0x1;

    return reg_val;

}


static int32_t set_port_pupd(uint32_t port,  uint32_t port_af, uint32_t pupd){

    if (port >= GPIO_PORT_NUMBER || port_af >= GPIO_PORT_AF_NUMBER || pupd > PORT_PULL_RESERVED)
        return -1;

    gpio_reg_t * gpio_reg =  gpio_ports[port];

    uint32_t reg_val =  gpio_reg->gpio_pupd;

    reg_val &=  ~(0x3<<port_af);
    reg_val |= (pupd << port_af);

    gpio_reg->gpio_mode = reg_val;

    return 0;

}




static int32_t get_port_input(uint32_t port,  uint32_t port_af){

    if (port >= GPIO_PORT_NUMBER || port_af >= GPIO_PORT_AF_NUMBER )
        return -1;

    gpio_reg_t * gpio_reg =  gpio_ports[port];

    uint32_t reg_val =  ((gpio_reg->gpio_input) >> port_af) & 0x1;

    return reg_val;

}


static int32_t get_port_output(uint32_t port,  uint32_t port_af){

    if (port >= GPIO_PORT_NUMBER || port_af >= GPIO_PORT_AF_NUMBER )
        return -1;

    gpio_reg_t * gpio_reg =  gpio_ports[port];

    uint32_t reg_val =  ((gpio_reg->gpio_output) >> port_af) & 0x1;

    return reg_val;

}


static int32_t set_port_output(uint32_t port,  uint32_t port_af,  uint32_t data){

    uint32_t reg_val;
    if (port >= GPIO_PORT_NUMBER || port_af >= GPIO_PORT_AF_NUMBER )
        return -1;

    gpio_reg_t * gpio_reg =  gpio_ports[port];
    reg_val =  gpio_reg->gpio_output;

    reg_val &=  ~(1<<port_af);
    reg_val |=  (data << port_af);
    gpio_reg->gpio_output = reg_val;

    return 0;

}


static int32_t set_config_lock(uint32_t port,  uint32_t port_af){

    if (port >= GPIO_PORT_NUMBER || port_af >= GPIO_PORT_AF_NUMBER )
        return -1;

    gpio_reg_t * gpio_reg =  gpio_ports[port];

    uint32_t reg_val = gpio_reg->gpio_lock;

    reg_val |= ( 1 << 16 | 1 << port_af);
    gpio_reg->gpio_lock =  reg_val;

    reg_val =  gpio_reg->gpio_lock;
    reg_val &= ~(1<<16);
    gpio_reg->gpio_lock = reg_val;

    reg_val = gpio_reg->gpio_lock;
    reg_val |= (1<<16);


    reg_val = gpio_reg->gpio_lock;

    return  reg_val & (1 << 16)?0:-1;

}




static int32_t get_pin_port(uint32_t port,  uint32_t pin){

    uint32_t reg_val;

    if (port >= GPIO_PORT_NUMBER || pin >= IO_PINS_NUMBER)
        return -1;

    gpio_reg_t * gpio_reg =  gpio_ports[port];
    reg_val =  (pin < 7)?gpio_reg->gpio_afrl:gpio_reg->gpio_afrh;

    reg_val >>= (pin & 0x7);

    reg_val &= 0xf;

    return reg_val;

}



static int32_t set_pin_port(uint32_t port,  uint32_t port_af,  uint32_t pin){

    uint32_t reg_val;

    if (port >= GPIO_PORT_NUMBER || port_af >= GPIO_PORT_AF_NUMBER || pin >= IO_PINS_NUMBER)
        return -1;

    gpio_reg_t * gpio_reg =  gpio_ports[port];

    reg_val = pin < 7? gpio_reg->gpio_afrl: gpio_reg->gpio_afrh;
    reg_val &= ~(0xf<<(pin & 0x7));
    reg_val |=  (port_af << (pin & 0x7));

    if (pin < 7)
        gpio_reg->gpio_afrl = reg_val;
    else
        gpio_reg->gpio_afrh = reg_val;

    return 0;
}







int32_t  get_pin_input(uint32_t port,  uint32_t pin){

    int32_t port_af =  get_pin_data(port, pin);

    if (port_af <  0)
        return -1;
    

    uint32_t reg_val = get_port_input(port, port_af);

    return reg_val;

}



int32_t get_pin_output(uint32_t port,  uint32_t pin){


    int32_t port_af =  get_pin_data(port, pin);

    if (port_af <  0)
        return -1;
    

    uint32_t reg_val = get_port_output(port, port_af);

    return reg_val;


}

int32_t set_pin_output(uint32_t port,  uint32_t pin, uint32_t data){


    int32_t port_af =  get_pin_data(port, pin);

    if (port_af <  0)
        return -1;
    

    uint32_t reg_val = set_port_output(port, port_af, data);

    return reg_val;

}






