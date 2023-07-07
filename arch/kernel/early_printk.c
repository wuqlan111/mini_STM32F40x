#include  <stdint.h>
#include  <string.h>
#include  <stdio.h>
#include  <stdarg.h>

#include "ring_buffer.h"
#include "arch_printk.h"

#define  EARLY_LOG_SIZE           8192
#define  MAX_INFO_LEN           128



static  uint8_t  early_log_buffer[EARLY_LOG_SIZE] = {0};

static  ring_buffer_t early_log =  {
    .head     =  0,
    .tail     =  0,
    .size     =  EARLY_LOG_SIZE,
    .buffer   =  early_log_buffer,
};


int32_t  early_printk(const char * fmt,  ...)
{
    int32_t  ret = 0;
    uint8_t buf[MAX_INFO_LEN + 1] = {0};
    if (!fmt) {
        return -1;        
    }

    va_list args;
    va_start(args, fmt);
    vsprintf(buf,  fmt, args);
    va_end(args);

    uint32_t len = strlen(buf);

    if ( (len > MAX_INFO_LEN )) {
        return -1;        
    }

    ret = write_to_ring_buffer(&early_log, buf, len + 1);

    return  ret;

}


int32_t  get_early_log(uint8_t  * out)
{
    int32_t  ret  = 0;
    uint8_t  data  =  0;
    uint32_t  len = 0;

    if (!out) {
        return  -1;        
    }

    do {

        ret = read_from_ring_buffer(&early_log, &data, 1, &len);

        if (!len || ret) {
            return  -1;
        }
    } while (!data);

    out[0] = data;

    for (int32_t i = 0; data; i++) {
        ret = read_from_ring_buffer(&early_log, &data, 1, &len);
        if (!len || ret) {
            break;
        }

        out[i+1] = data;
    }

    return  0;

}



