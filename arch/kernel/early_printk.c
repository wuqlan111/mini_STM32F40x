#include  <stdint.h>
#include  <string.h>
#include  <stdio.h>

#include "asm/arch_printk.h"

#define  EARLY_LOG_SIZE           8192
#define  MAX_INFO_LEN           128

char  early_log_buffer[EARLY_LOG_SIZE] = {0};
static  uint32_t  head = 0;
static  uint32_t  tail = 0;


int32_t  early_printk(const char * fmt,  ...)
{
    char buf[MAX_INFO_LEN + 1] = {0};
    if (!fmt)
        return -1;

    va_list args;
    va_start(args, fmt);
    vsprintf(buf,  fmt, args);

    uint32_t len = strlen(buf);

    if ( (len > 128 ) || (tail + len > EARLY_LOG_SIZE -1))
        return -1;

    memcpy(early_log_buffer[tail], buf, len);
    early_log_buffer[tail+len - 1] = '\0';
    tail+=len;

    return  0;

}


int32_t  get_early_log(char * out)
{
    if (!out)
        return  -1;

    if (head  ==  tail)
        return  -1;

    uint32_t  len = strlen(&early_log_buffer[head]);
    
    memcpy(out,  &early_log_buffer[head], len);
    head+=len + 1;
    return  0;

}



