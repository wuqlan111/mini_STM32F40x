
#ifndef   RING_BUFFER_H
#define   RING_BUFFER_H

#include  <stdint.h>

#include "gcc_type.h"

typedef struct {
    uint32_t  head;
    uint32_t  tail;
    const  uint32_t  size;
    uint8_t  *  const  buffer;
}ATTRIBUTE_ALIGN(4)  ring_buffer_t;


int32_t  get_ring_buffer_data_len(ring_buffer_t * buffer, uint32_t  * len);
void  clean_ring_buffer_data(ring_buffer_t * buffer);
int32_t  write_to_ring_buffer(ring_buffer_t * buffer, uint8_t * data, uint32_t len);
int32_t  read_from_ring_buffer(ring_buffer_t * buffer, uint8_t * data, uint32_t size, uint32_t * len);




#endif


