
#include  <stdlib.h>
#include  "../include/dma.h"


typedef struct  dma_interrupt{

    volatile  uint32_t  dma_lisr;
    volatile  uint32_t  dma_hisr;
    volatile  uint32_t  dma_lifcr;
    volatile  uint32_t  dma_hifcr;

}dma_interrupt_t;


typedef struct  dma_stream{

    volatile  uint32_t  dma_sxcr;
    volatile  uint32_t  dma_sxndtr;
    volatile  uint32_t  dma_sxpar;
    volatile  uint32_t  dma_sxm0ar;
    volatile  uint32_t  dma_sxm1ar;
    volatile  uint32_t  dma_sxfcr;

}dma_stream_t;

dma_interrupt_t * const dma_interrupt_control;
dma_stream_t * const dma_all_stream[DMA_STREAM_NUMBER];


int32_t  get_stream_interrupt(uint8_t stream_idx){

    int32_t  int_status = 0, reg_value;

    if (stream_idx > MAX_DMA_STREAM_ID)
        return -1;
    
    reg_value = stream_idx > 3?dma_interrupt_control->dma_hisr:dma_interrupt_control->dma_lisr;

    switch (stream_idx & 0x4)
    {
    case   0:
        int_status = reg_value & 0x3f;
        break;
    
    case   1:
        int_status = (reg_value >> 6) & 0x3f;
        break;

    case   2:
        int_status = (reg_value >> 16) & 0x3f;
        break;


    case   3:
        int_status = (reg_value >> 22) & 0x3f;
        break;

    }

    return  int_status;


}



int32_t  clear_stream_interrupt(uint8_t stream_idx,  uint32_t int_mask){

    int32_t  int_clear = 0, reg_value;

    if (stream_idx > MAX_DMA_STREAM_ID  ||   (int_mask & ~DMA_ALLC_INT))
        return -1;
    

    switch (stream_idx & 0x4){

    case   0:
        int_clear = int_mask;
        break;
    
    case   1:
        int_clear = int_mask << 6;
        break;

    case   2:
        int_clear = int_mask << 16;
        break;

    case   3:
        int_clear = int_mask << 22;
        break;

    }


    if (stream_idx > 3)
        dma_interrupt_control->dma_lifcr |= int_clear;
    else
        dma_interrupt_control->dma_hifcr |= int_clear;

    return  0;

}




inline int32_t  enable_stream_interrupt( uint8_t stream_idx,  uint32_t  int_mask){

    if (stream_idx > MAX_DMA_STREAM_ID  ||  (int_mask & ~DMA_ALL_INTERRUPTE))
        return -1;


    dma_all_stream[stream_idx]->dma_sxcr |= (int_mask & 0xf);
    
    dma_all_stream[stream_idx]->dma_sxfcr |= (int_mask & 0xf0);

    return 0;

}


inline int32_t  disable_stream_interrupt( uint8_t stream_idx,  uint32_t int_mask){

    if (stream_idx > MAX_DMA_STREAM_ID  ||  (int_mask & ~DMA_ALL_INTERRUPTE))
        return -1;


    dma_all_stream[stream_idx]->dma_sxcr &= ~(int_mask & 0xf);
    
    dma_all_stream[stream_idx]->dma_sxfcr &= ~(int_mask & 0xf0);

    return 0;

}








