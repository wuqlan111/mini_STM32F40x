
#include  <stdlib.h>
#include  <stdbool.h>

#include  "../include/usart.h"


typedef struct usart_control{

    volatile  uint32_t  usart_sr;
    volatile  uint32_t  usart_dr;
    volatile  uint32_t  usart_brr;
    volatile  uint32_t  usart_cr1;
    volatile  uint32_t  usart_cr2;
    volatile  uint32_t  usart_cr3;
    volatile  uint32_t  usart_gtpr;
    
}usart_control_t;











