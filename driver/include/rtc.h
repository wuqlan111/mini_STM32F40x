

#ifndef  STM32_RTC_H
#define  STM32_RTC_H

#include  <stdint.h>

#include  "util.h"



enum {
    RTC_OUTPUT_DISABLE = 0,
    RTC_ALARMA_OUTPUT,
    RTC_ALARMB_OUTPUT,
    RTC_WAKEUP_OUTPUT,
    RTC_MAX_OUTPUT  =  RTC_WAKEUP_OUTPUT,
};



enum {

    RTC_WAKEUP_CLOCK_16 = 0,
    RTC_WAKEUP_CLOCK_8,
    RTC_WAKEUP_CLOCK_4,
    RTC_WAKEUP_CLOCK_2,
    RTC_WACKUP_MAX_CLOCK = RTC_WAKEUP_CLOCK_2,
};







typedef struct {
    uint32_t  calibration_output_enable:1;
    uint32_t  output_selection:2;
    uint32_t  output_polarity:1;
    uint32_t  calibration_output_1HZ:1;
    uint32_t  backup:1;
    uint32_t  timestamp_interrupt_enable:1;
    uint32_t  wakeup_interrupt_enable:1;
    uint32_t  alarmB_interrupt_enable:1;
    uint32_t  alarmA_interrupt_enable:1;
    uint32_t  time_stamp_enable:1;
    uint32_t  wakeup_timer_enable:1;
    uint32_t  alarmB_enable:1;
    uint32_t  alarmA_enable:1;
    uint32_t  digital_calibration_enable:1;
    uint32_t  PM_AM_format:1;
    uint32_t  bypass_shadow_register:1;
    uint32_t  reference_clock_enable:1;
    uint32_t  timestamp_event_active_fall:1;
    uint32_t  wakeup_clock_selection:2;
} ATTRIBUTE_ALIGN(4)  RTC_config_t;



int32_t  RTC_init_config(RTC_config_t * config);









#endif

