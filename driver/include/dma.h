
#ifndef  STM32_DMA_H
#define  STM32_DMA_H

#include  <stdint.h>
#include  "util.h"

#define  DMA_STREAM_NUMBER      8
#define  DMA_MAX_CHANNEL_NUMBER       8


enum {
    DMA1 = 0,
    DMA2,
    DMA_MAX_ID  =  DMA2,
};


enum {
    DMA_SINGLE_TRANSFER = 0,
    DMA_INCR4_TRANSFER,
    DMA_INCR8_TRANSFER,
    DMA_INCR16_TRANSFER,
    DMA_MAX_TRANSFER  =  DMA_INCR16_TRANSFER,
};

enum {
    DMA_LOW_PRIORITY = 0,
    DMA_Medium_PRIORITY,
    DMA_High_PRIORITY,
    DMA_VERY_HIGH_PRIORITY,
    DMA_MAX_PRIORITY  =  DMA_VERY_HIGH_PRIORITY,
};

enum {
    DMA_DATA_SIZE_BYTE = 0,
    DMA_DATA_SIZE_HALF_WORD,
    DMA_DATA_SIZE_WORD,
    DMA_DATA_MAX_SIZE = DMA_DATA_SIZE_WORD,
};

enum {
    DMA_PERIPHERAL_TO_MEMORY  = 0,
    DMA_MEMORY_TO_PERIPHERAL,
    DMA_MEMORY_TO_MEMORY,
    DMA_TRANSFER_MAX_DIRECTION = DMA_MEMORY_TO_MEMORY,
};


typedef struct {
    uint32_t  channel:3;
    uint32_t  memory_burst:2;
    uint32_t  peripheral_burst:2;
    uint32_t  memory0:1;
    uint32_t  double_buffer_mode:1;
    uint32_t  priority:2;
    


}DMA_stream_config_t;





#endif


