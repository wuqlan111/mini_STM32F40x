
#ifndef  __CONSOLE_H
#define  __CONSOLE_H

#include  <stdint.h>
#include  <stdio.h>
#include  "util.h"

typedef  enum {
    LOG_LEVEL_DEBUG  =  0,
    LOG_LEVEL_INFO,
    LOG_LEVEL_NOTICE,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
}  system_log_level_e;


int32_t  console_init(void);


int32_t  console_fmt_out(char * fmt, ...);


int32_t  console_recv_data(uint8_t * buf, uint32_t len,  uint32_t * recv_len);

void   __debug_printf(uint32_t level, char * fmt, ...);

void  set_system_log_level(uint32_t level);


#define  DEBUG_PRINTF_DEBUG(fmt, ...)     __debug_printf(LOG_LEVEL_DEBUG, "[DEBUG]%s:%u - " fmt "\r\n",  \
                                                __FILE__,  __LINE__, ##__VA_ARGS__)
#define  DEBUG_PRINTF_INFO(fmt, ...)      __debug_printf(LOG_LEVEL_INFO, "[INFO]%s:%u - " fmt "\r\n",   \
                                                __FILE__, __LINE__, ##__VA_ARGS__)
#define  DEBUG_PRINTF_NOTICE(fmt, ...)    __debug_printf(LOG_LEVEL_NOTICE, "[NOTICE]%s:%u - " fmt "\r\n",   \
                                                __FILE__, __LINE__, ##__VA_ARGS__)
#define  DEBUG_PRINTF_WARN(fmt, ...)      __debug_printf(LOG_LEVEL_WARN, "[WARN]%s:%u - " fmt "\r\n",   \
                                                __FILE__, __LINE__, ##__VA_ARGS__)
#define  DEBUG_PRINTF_ERROR(fmt, ...)      __debug_printf(LOG_LEVEL_ERROR, "[ERROR]%s:%u - " fmt "\r\n",  \
                                                __FILE__, __LINE__, ##__VA_ARGS__)
#define  DEBUG_PRINTF_FATAL(fmt, ...)      __debug_printf(LOG_LEVEL_FATAL, "[FATAL]%s:%u - " fmt "\r\n",  \
                                                __FILE__, __LINE__, ##__VA_ARGS__)






#endif



