
#include <stdlib.h>
#include <stdbool.h>
#include  "../include/rtc.h"



typedef struct rtc_reg{

    volatile  uint32_t  rtc_tr;
    volatile  uint32_t  rtc_dr;
    volatile  uint32_t  rtc_cr;
    volatile  uint32_t  rtc_isr;
    volatile  uint32_t  rtc_prer;
    volatile  uint32_t  rtc_wutr;
    volatile  uint32_t  rtc_calibr;
    volatile  uint32_t  rtc_alrmar;
    volatile  uint32_t  rtc_alrmbr;
    volatile  uint32_t  rtc_wpr;
    volatile  uint32_t  rtc_ssr;
    volatile  uint32_t  rtc_shiftr;
    volatile  uint32_t  rtc_tstr;
    volatile  uint32_t  rtc_tsdr;
    volatile  uint32_t  rtc_tsssr;
    volatile  uint32_t  rtc_calr;
    volatile  uint32_t  rtc_tafcr;
    volatile  uint32_t  rtc_alrmassr;
    volatile  uint32_t  rtc_alrmbssr;
    volatile  uint32_t  rtc_bkpxr[20];

}rtc_reg_t;

rtc_reg_t * rtc_control;



int32_t  set_RTC_time(uint8_t hours, uint8_t minutes, uint8_t seconds, bool pm_format){

    if (hours > 23 || minutes > 59 || seconds > 59 || !(rtc_control->rtc_isr & RTC_ISR_INITF))
        return -1;
    

    if (pm_format){
       if (!hours)
            hours = 12;
        else
            hours =  hours > 12? (hours -12):hours;
    }
    

    uint32_t hours_ten = hours / 10;
    uint32_t hours_unit = hours % 10;
    uint32_t minutes_ten = minutes / 10;
    uint32_t minutes_unit = minutes % 10;
    uint32_t seconds_ten = seconds / 10;
    uint32_t seconds_unit = seconds % 10;

    rtc_control->rtc_tr = (pm_format << 22 |  hours_ten << 20 | hours_unit << 16 | minutes_ten << 12
                        | minutes_unit << 8 | seconds_ten << 4 | seconds_unit );

    return 0;

}


int32_t  set_RTC_date(uint8_t years, uint8_t months, uint8_t days, uint8_t week_day){

    if (years > 99 || months > 12 || days > 31 || week_day >7 || !(rtc_control->rtc_isr & RTC_ISR_INITF))
        return -1;
    

    uint32_t years_ten = years / 10;
    uint32_t years_unit = years % 10;
    uint32_t months_ten = months / 10;
    uint32_t months_unit = months % 10;
    uint32_t days_ten =  days / 10;
    uint32_t days_unit = days % 10;

    rtc_control->rtc_tr = ( years_ten << 20 | years_unit << 16 |   week_day << 13 | months_ten << 12
                        | months_unit << 8 | days_ten << 4 | days_unit );

    return 0;

}


inline int32_t  enable_RTC_interrupt(uint32_t int_mask){

    if ( int_mask & ~RTC_ALL_INTERRUPT)
        return -1;
    
    rtc_control->rtc_cr &= ~RTC_ALL_INTERRUPT;
    rtc_control->rtc_cr |= int_mask;

    return 0;

}


inline int32_t  disable_RTC_interrupt(uint32_t int_mask){

    if ( int_mask & ~RTC_ALL_INTERRUPT)
        return -1;

    rtc_control->rtc_cr &= ~int_mask;


    return 0;

}








