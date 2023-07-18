
#ifndef  __CONSOLE_H
#define  __CONSOLE_H

#include  <stdint.h>
#include  "util.h"




int32_t  console_init(void);


int32_t  console_fmt_out(char * fmt, ...);


int32_t  console_recv_data(uint8_t * buf, uint32_t len,  uint32_t * recv_len);









#endif



