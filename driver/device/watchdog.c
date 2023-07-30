
#include  <stdlib.h>

#include  "watchdog.h"
#include  "../include/driver_util.h"
#include  "../../subsys/include/console.h"



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


#define  INDEPENDENT_WATCHDOG_REGS_BASE                    (0x40003000u)
#define  WINDOW_WATCHDOG_REGS_BASE                        (0x40002C00u)


#define  IWDG_KR_REG_ADDR            (INDEPENDENT_WATCHDOG_REGS_BASE)
#define  IWDG_PR_REG_ADDR            (INDEPENDENT_WATCHDOG_REGS_BASE + 0x4u)
#define  IWDG_RLR_REG_ADDR           (INDEPENDENT_WATCHDOG_REGS_BASE + 0x8u)
#define  IWDG_SR_REG_ADDR            (INDEPENDENT_WATCHDOG_REGS_BASE + 0xcu)


#define  WWDG_CR_REG_ADDR             (WINDOW_WATCHDOG_REGS_BASE)
#define  WWDG_CFR_REG_ADDR            (WINDOW_WATCHDOG_REGS_BASE + 0x4u)
#define  WWDG_SR_REG_ADDR             (WINDOW_WATCHDOG_REGS_BASE + 0x8u)



int32_t   set_iwdg_prescaler_and_reload(uint32_t prescaler, uint32_t  reload)
{
    CHECK_PARAM_VALUE(prescaler,  0x7);
    CHECK_PARAM_VALUE(reload,  0xfff);

    REG32_WRITE(IWDG_KR_REG_ADDR,  0x5555);
    REG32_WRITE(IWDG_PR_REG_ADDR,  prescaler);
    REG32_WRITE(IWDG_RLR_REG_ADDR,  reload);

}


int32_t  inline  reload_iwdg_value(void)
{
    REG32_WRITE(IWDG_KR_REG_ADDR,  0xaaaa);
}


int32_t  inline  start_iwdg(void)
{
    REG32_WRITE(IWDG_KR_REG_ADDR,  0xcccc);
}




uint32_t  wwdg_reflash_load(void)
{
    uint32_t  t_count  =  REG32_READ(WWDG_CR_REG_ADDR) & WWDG_CR_T;
    uint32_t  w_count  =  REG32_READ(WWDG_CFR_REG_ADDR) & WWDG_CFR_W;

    return   w_count >= t_count;

}


int32_t  wwdg_set_load(uint32_t  value, uint32_t  is_w)
{
    uint32_t  flag =  (1 << 6) | value;
    CHECK_PARAM_VALUE(value, 0x3f);

    if (is_w) {
        REG32_UPDATE(WWDG_CFR_REG_ADDR,  flag,   WWDG_CFR_W);
    } else {
        REG32_UPDATE(WWDG_CR_REG_ADDR,  flag,   WWDG_CR_T);
    }

    return   0;

}


void  set_wwdg_enable(void)
{
    REG32_UPDATE(WWDG_CR_REG_ADDR,  1 << 7,  WWDG_CR_WDGA);
}











