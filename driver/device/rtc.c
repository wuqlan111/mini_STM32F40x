
#include <stdlib.h>
#include  "../include/rtc.h"

#define  RTC_TR_PM              (1<<22)                 // PM notation
#define  RTC_TR_HT              (0x3<<20)               // hour tens in BCD format
#define  RTC_TR_HU              (0xf<<16)               // hour units in BCD format
#define  RTC_TR_MNT             (0x7<<12)               // min tens in BCD format
#define  RTC_TR_MNU             (0xf<<8)                // min units in BCD format
#define  RTC_TR_ST              (0x7<<4)                // second tens in BCD format
#define  RTC_TR_SU              0xf                     // second units in BCD format


#define  RTC_DR_YT          (0xf<<20)               // year tens in BCD format
#define  RTC_DR_YU          (0xf<<16)               // year units in BCD format
#define  RTC_DR_WDU         (0x7<<13)               // week day units
#define  RTC_DR_MT          (1<<12)                 // month tens in BCD format
#define  RTC_DR_MU          (0xf<<8)                // month units in BCD format
#define  RTC_DR_DT          0x30                    // date tens in BCD format
#define  RTC_DR_DU            0xf                   // date units in BCD format  



#define  RTC_CR_COE             (1<<23)             // calibration output enable
#define  RTC_CR_OSEL            (0x3<<21)           // output selection
#define  RTC_CR_POL             (1<<20)             // output polarity
#define  RTC_CR_COSEL           (1<<19)             // calibration output selection
#define  RTC_CR_BKP             (1<<18)             // backup
#define  RTC_CR_SUB1H           (1<<17)             // subtract 1 hour
#define  RTC_CR_ADD1H           (1<<16)             // add 1 hour
#define  RTC_CR_TSIE            (1<<15)             // timestamp interrupt enable
#define  RTC_CR_WUTIE           (1<<14)             // wakeup timer interrupt enable
#define  RTC_CR_ALRBIE          (1<<13)              // alarm B interrupt enable
#define  RTC_CR_ALRAIE          (1<<12)             // alarm A interrupt enable
#define  RTC_CR_TSE             (1<<11)             // time stamp enable
#define  RTC_CR_WUTE            (1<<10)             // wakeup timer enable
#define  RTC_CR_ALRBE           (1<<9)              // alarm B enable
#define  RTC_CR_ALRAE           (1<<8)              // alarm A enable
#define  RTC_CR_DCE             (1<<7)              // coarse digital calibration enable
#define  RTC_CR_FMT             (1<<6)              // AM/PM hour format
#define  RTC_CR_BYPSHAD         (1<<5)              // bypass the shadow registers
#define  RTC_CR_REFCKON         (1<<4)              // reference clock detection enable
#define  RTC_CR_TSEDGE          0x8                 // timestamp event active edge
#define  RTC_CR_WUCKSEL           0x7               // wakeup clock selection
#define  RTC_ALL_INTERRUPT              0xf000


#define RTC_ISR_RECALPF         (1<<16)             // recalibration pending Flag
#define RTC_ISR_TAMP2F          (1<<14)             // TAMPER2 detection flag
#define RTC_ISR_TAMP1F          (1<<13)             // tamper detection flag
#define RTC_ISR_TSOVF           (1<<12)             // timestamp overflow flag
#define RTC_ISR_TSF             (1<<11)             // timestamp flag
#define RTC_ISR_WUTF            (1<<10)             // wakeup timer flag
#define RTC_ISR_ALRBF           (1<<9)              // alarm B flag
#define RTC_ISR_ALRAF           (1<<8)              // alarm A flag
#define RTC_ISR_INIT            (1<<7)              // initialization mode
#define RTC_ISR_INITF           (1<<6)              // initialization flag
#define RTC_ISR_RSF             (1<<5)              // registers synchronization flag
#define RTC_ISR_INITS           (1<<4)              // initialization status flag
#define RTC_ISR_SHPF            0x8                 // shift operation pending
#define RTC_ISR_WUTWF           0x4                 // wakeup timer write flag
#define RTC_ISR_ALRBWF          0x2                 // alarm B update allowed
#define RTC_ISR_ALRAWF          0x1                 // alarm A update allowed


#define  RTC_PRER_PREDIV_A          (0x7f<<16)              // asynchronous prescaler factor
#define  RTC_PRER_PREDIV_S          0x7fff              // synchronous prescaler factor
#define  RTC_WUTR_WUT           0xffff                  // wakeup auto-reload value bits


#define RTC_CALIBR_DCS          (1<<7)                  // digital calibration sign
#define RTC_CALIBR_DC           (0x1f)                  // digital calibration

#define  RTC_ALRMAR_MSK4            (1<<31u)                // alarm A date mask
#define  RTC_ALRMAR_WDSEL           (1<<30)                 // week day selection
#define  RTC_ALRMAR_DT              (0x3<<28)               // date tens in BCD format
#define  RTC_ALRMAR_DU              (0xf<<24)               // date units or day in BCD format
#define  RTC_ALRMAR_MSK3            (1<<23)             // alarm A hours mask
#define  RTC_ALRMAR_PM              (1<<22)             // AM/PM notation
#define  RTC_ALRMAR_HT              (0x3<<20)              // hour tens in BCD format
#define  RTC_ALRMAR_HU              (0xf<<16)                   // hour units in BCD format
#define  RTC_ALRMAR_MSK2            (1<<15)                     // alarm A minutes mask
#define  RTC_ALRMAR_MNT                (0x7<<12)                // minute tens in BCD format
#define  RTC_ALRMAR_MNU                (0xf<<8)                // minute units in BCD format
#define  RTC_ALRMAR_MSK1                (1<<7)                  // alarm A seconds mask
#define  RTC_ALRMAR_ST                  (0x7<<4)                // second tens in BCD format
#define  RTC_ALRMAR_SU                  0xf                     // second units in BCD format


#define  RTC_WPR_KEY                0xff                    // write protection key
#define  RTC_SSR_SS                 0xffff                  // sub second value

#define  RTC_SHIFTR_ADD1S           (1<<31u)                // add one second
#define  RTC_SHIFTR_SUBFS           0x7fff                  // subtract a fraction of a second
#define  RTC_SHIFTR_


#define  RTC_TSTR_PM            (1<<22)                     // PM hour format
#define  RTC_TSTR_HT            (0x3<<20)                   // hour tens in BCD format
#define  RTC_TSTR_HU            (0xf<<16)                   // hour units in BCD format
#define  RTC_TSTR_MNT           (0x7<<12)                   // minute tens in BCD format
#define  RTC_TSTR_MNU           (0xf<<8)                    // minute units in BCD format
#define  RTC_TSTR_ST            (0x7<<4)                    // second tens in BCD format
#define  RTC_TSTR_SU            0xf                         // second units in BCD format


#define  RTC_TSDR_WDU           (0x3<<13)                   // week day units
#define  RTC_TSDR_MT               (1<<12)                  // month tens in BCD format
#define  RTC_TSDR_MU                (0xf<<8)                // month units in BCD format
#define  RTC_TSDR_DT               (0x3<<4)                 // date tens in BCD format
#define  RTC_TSDR_DU               0xf                      // date units in BCD format


#define  RTC_TSSSR_SS           0xffff                  // sub second value

#define  RTC_CALR_CALP              (1<<15)                 // increase frequency of RTC by 488.5 ppm
#define  RTC_CALR_CALW8             (1<<14)                 // use an 8-second calibration cycle period
#define  RTC_CALR_CALW16            (1<<13)                 // use a 16-second calibration cycle period
#define  RTC_CALR_CALM                 0x1ff                 // calibration minus


#define  RTC_REGS_BASE_ADDR                (0x40002800u)
#define  RTC_TR_REG_ADDR                   (RTC_REGS_BASE_ADDR)
#define  RTC_DR_REG_ADDR                   (RTC_REGS_BASE_ADDR + 0x4)
#define  RTC_CR_REG_ADDR                   (RTC_REGS_BASE_ADDR + 0x8)
#define  RTC_ISR_REG_ADDR                  (RTC_REGS_BASE_ADDR + 0xC)
#define  RTC_PRER_REG_ADDR                 (RTC_REGS_BASE_ADDR + 0x10)
#define  RTC_WUTR_REG_ADDR                 (RTC_REGS_BASE_ADDR + 0x14)
#define  RTC_CALIBR_REG_ADDR               (RTC_REGS_BASE_ADDR + 0x18)
#define  RTC_ALRMAR_REG_ADDR               (RTC_REGS_BASE_ADDR + 0x1C)
#define  RTC_ALRMBR_REG_ADDR               (RTC_REGS_BASE_ADDR + 0x20)
#define  RTC_WPR_REG_ADDR                  (RTC_REGS_BASE_ADDR + 0x24)
#define  RTC_SSR_REG_ADDR                  (RTC_REGS_BASE_ADDR + 0x28)
#define  RTC_SHIFTR_REG_ADDR               (RTC_REGS_BASE_ADDR + 0x2C)
#define  RTC_TSTR_REG_ADDR                 (RTC_REGS_BASE_ADDR + 0x30)
#define  RTC_TSSSR_REG_ADDR                (RTC_REGS_BASE_ADDR + 0x38)
#define  RTC_CALR_REG_ADDR                 (RTC_REGS_BASE_ADDR + 0x3C)
#define  RTC_TAFCR_REG_ADDR                (RTC_REGS_BASE_ADDR + 0x40)
#define  RTC_ALRMASSR_REG_ADDR             (RTC_REGS_BASE_ADDR + 0x44)
#define  RTC_ALRMBSSR_REG_ADDR             (RTC_REGS_BASE_ADDR + 0x48)
#define  RTC_BKPXR_REG_ADDR(bkp)           (RTC_REGS_BASE_ADDR + 0x50 + (bkp) * 0x4)


int32_t  RTC_init_config(RTC_config_t * config)
{
    uint32_t  flag,  mask;
    flag = mask = 0;
    if (!config) {
        return  -1;
    }

    if (config->calibration_output_enable) {
        flag |= 1 << 23;
    }

    flag |=  config->output_selection << 21;

    if (config->alarm_output_low) {
        flag |=  1 << 20;
    }

    if (config->calibration_output_1HZ) {
        flag |=  1 << 19;
    }

    if ( config->timestamp_interrupt_enable) {
        flag |= 1 << 15;
    }

    if (config->wakeup_interrupt_enable) {
        flag |= 1 << 14;
    }

    if (config->alarmB_interrupt_enable) {
        flag |= 1 << 13;
    }

    if (config->alarmA_interrupt_enable) {
        flag |= 1 << 12;
    }

    if (config->timestamp_enable) {
        flag |= 1 << 11;
    }

    if (config->wakeup_timer_enable) {
        flag |= 1 << 10;
    }

    if (config->alarmB_enable) {
        flag |= 1 << 9;
    }

    if (config->alarmA_enable) {
        flag |= 1 << 8;
    }

    if (config->digital_calibration_enable) {
        flag  |= 1 << 7;
    }

    if (config->PM_AM_format) {
        flag |=  1 << 6;
    }

    if (config->bypass_shadow_register) {
        flag |= 1 << 5;
    }

    if (config->reference_clock_enable) {
        flag |= 1 << 4;
    }

    if (config->timestamp_event_active_fall) {
        flag |= 1 << 3;
    }

    flag  |=  config->wakeup_clock_selection;
    mask  =   0xf8ffff;


    REG32_UPDATE(RTC_CR_REG_ADDR, flag,  mask);
    return  0;

}











