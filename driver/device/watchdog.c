
#include  <stdlib.h>

#include  "watchdog.h"

#define  IWDG_KR_KEY            0xffff          // Key value
#define  IWDG_PR_PR             0x7             // prescaler divider
#define  IWDG_RLR_RL            0xfff           // watchdog counter reload value

#define  IWDG_SR_RVU            0x2             // watchdog counter reload value update
#define  IWDG_SR_PVU            0x1             // watchdog prescaler value update


#define  WWDG_CR_WDGA           (1<<7)              // watchdog enable
#define  WWDG_CR_T              0x7f                // 7-bit counter

#define  WWDG_CFR_EWI             (1<<9)                // early wakeup interrupt
#define  WWDG_CFR_WDGTB             (0x3<<7)            // timer base
#define  WWDG_CFR_W                 0x7f                // 7-bit window value

#define  WWDG_SR_EWIF               0x1                  // early wakeup interrupt flag


























