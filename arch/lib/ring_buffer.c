
#include  <stdlib.h>
#include  <string.h>
#include  <memory.h>

#include  "ring_buffer.h"


static  uint32_t  check_ring_buffer_valid(ring_buffer_t * buffer)
{
    uint32_t  valid  =   1;
    if (!buffer || !buffer->buffer || !buffer->size || 
            (buffer->head > buffer->tail ) ) {
        valid  =  0;
    }

    return  valid;
}


int32_t  get_ring_buffer_data_len(ring_buffer_t * buffer, uint32_t  * len)
{
    if (  !check_ring_buffer_valid(buffer)  || !len) {
        return  -1;
    }

    *len  =  buffer->tail - buffer->head;

    return   0;

}


void  clean_ring_buffer_data(ring_buffer_t * buffer)
{
    if (!check_ring_buffer_valid(buffer)) {
        return;
    }

    memset(buffer->buffer, 0,  buffer->size);
    buffer->head  =  buffer->tail  =  0;

}


int32_t  write_to_ring_buffer(ring_buffer_t * buffer, uint8_t * data, uint32_t len)
{
    uint32_t  head_pos,  tail_pos, tail_res;
    head_pos   =  tail_pos  =  tail_res = 0;

    if ( !check_ring_buffer_valid(buffer) || !data || !len) {
        return  -1;
    }

    if ( (buffer->size + buffer->head - buffer->tail)  < len ) {
        return  -1;
    }

    head_pos   =  buffer->head % buffer->size;
    tail_pos   =  buffer->tail % buffer->size;
    tail_res   =  buffer->size - tail_pos;

    if ( (head_pos >=  tail_pos)  || (tail_res >= len)) {
        memcpy(&buffer->buffer[tail_pos], data,  len);
    } else {
        memcpy(&buffer->buffer[tail_pos], data,  tail_res);
        memcpy(&buffer->buffer[0], data + tail_res, len - tail_res);
    }

    buffer->tail += len;

    if (buffer->tail  < buffer->head) {
        buffer->tail  =  (buffer->tail % buffer->size)  +  buffer->size;
        buffer->head  =  buffer->head % buffer->size;
    }

    return  0;

}


int32_t  read_from_ring_buffer(ring_buffer_t * buffer, uint8_t * data, uint32_t size, uint32_t * len)
{
    uint32_t  head_pos,  tail_pos, head_res, ret_count;
    head_pos   =  tail_pos  =  head_res  =  ret_count = 0;

    if ( !check_ring_buffer_valid(buffer) || !data || !size  || !len) {
        return  -1;
    }

    if ( buffer->tail == buffer->head ) {
        *len  =  0;
        return  0;
    }

    if ( (buffer->tail - buffer->head) >=   size) {
        ret_count  =  size;
    } else {
        ret_count  =  buffer->tail - buffer->head;
    }

    *len    =  ret_count;

    head_pos   =  buffer->head % buffer->size;
    tail_pos   =  buffer->tail % buffer->size;
    head_res   =  buffer->size - head_pos;

    if ( (head_pos <  tail_pos)  || (head_res >= ret_count)) {
        memcpy(data,  &buffer->buffer[head_pos], ret_count);
    } else {
        memcpy(data,   &buffer->buffer[head_pos],   head_res);
        memcpy(data + head_res,   &buffer->buffer[0],  ret_count - head_res);
    }

    buffer->head += ret_count;

    return  0;

}



