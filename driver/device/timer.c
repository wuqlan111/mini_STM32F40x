
#include  <stdlib.h>

#include  "timer.h"



#define  TIMx_CR1_ARPE              (1<<7)                  // Auto-reload preload enable
#define  TIMx_CR1_OPM               0x8                     // one-pulse mode
#define  TIMx_CR1_URS               0x4                     // update request source
#define  TIMx_CR1_UDIS              0x2                     // update disable
#define  TIMx_CR1_CEN               0x1                     // counter enable


#define  TIMx_CR2_MMS               (0x7<<4)                // master mode selection

#define  TIMx_DIER_UDE              (1<<8)                  // update DMA request enable
#define  TIMx_DIER_UIE              0x1                     // update interrupt enable

#define  TIMx_SR_UIF            0x1                 // update interrupt flag
#define  TIMx_EGR_UG            0x1                 // update generation
#define  TIMx_CNT_CNT           0xffff              // counter value
#define  TIMx_PSC_PSC           0xffff              // prescaler value
#define  TIMx_ARR_ARR          0xffff           // auto-reload value















