
#include  <memory.h>
#include  <stdlib.h>
#include  "../include/ADC.h"
#include  "util.h"

#define   ADC_REG_BASE    (0x40012000u)
#define   ADC_REGS_STEP         (0x100u)       
#define   ADC_COMMON_OFFSET         (0x300)

#define   ADC_SR_REG_ADDR(n)        (ADC_REG_BASE + ADC_REGS_STEP * (n))
#define   ADC_CR1_REG_ADDR(n)       (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x4)
#define   ADC_CR2_REG_ADDR(n)       (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x8)
#define   ADC_SMPR1_REG_ADDR(n)     (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0xc)
#define   ADC_SMPR2_REG_ADDR(n)     (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x10)
#define   ADC_JOFR1_REG_ADDR(n)     (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x14)
#define   ADC_JOFR2_REG_ADDR(n)     (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x18)
#define   ADC_JOFR3_REG_ADDR(n)     (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x1c)
#define   ADC_JOFR4_REG_ADDR(n)     (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x20)
#define   ADC_HTR_REG_ADDR(n)       (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x24)
#define   ADC_LTR_REG_ADDR(n)       (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x28)
#define   ADC_SQR1_REG_ADDR(n)      (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x2c)
#define   ADC_SQR2_REG_ADDR(n)      (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x30)
#define   ADC_SQR3_REG_ADDR(n)      (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x34)
#define   ADC_JSQR_REG_ADDR(n)      (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x38)
#define   ADC_JDR1_REG_ADDR(n)      (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x3c)
#define   ADC_JDR2_REG_ADDR(n)      (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x40)
#define   ADC_JDR3_REG_ADDR(n)      (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x44)
#define   ADC_JDR4_REG_ADDR(n)      (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x48)
#define   ADC_DR_REG_ADDR(n)        (ADC_REG_BASE + ADC_REGS_STEP * (n) + 0x4c)

#define   ADC_CSR_REG_ADDR          (ADC_REG_BASE + ADC_COMMON_OFFSET)
#define   ADC_CCR_REG_ADDR          (ADC_REG_BASE + ADC_COMMON_OFFSET + 0x4)
#define   ADC_CDR_REG_ADDR          (ADC_REG_BASE + ADC_COMMON_OFFSET + 0x8)



#define  ADC_SR_OVERRUN     (1<<5)      // overrun occurred
#define  ADC_SR_START     (1<<4)      // regular channel conversion started
#define  ADC_SR_JSTRT    0x8         // injected group conversion started
#define  ADC_SR_JEOC     0x4     // injected channel end of conversion
#define  ADC_SR_EOC     0x2     // conversion complete or sequence of conversions complete
#define  ADC_SR_AWD     0x1     // analog watchdog event occurred


#define  ADC_CR1_OVRIE      (1<<26)         // enable overrun interrupt
#define  ADC_CR1_RES        (0x3<<24)       // the resolution of the conversion
#define  ADC_CR1_AWDEN      (1<<23)         // enable analog watchdog 
#define  ADC_CR1_JAWDEN         (1<<22)        // enable analog watchdog on injected channels
#define  ADC_CR1_DISCNUM        (0x7<<13)       // discontinuous mode channel count
#define  ADC_CR1_JDISCEN        (1<<12)         // enable discontinuous mode on injected channels 
#define  ADC_CR1_DISCEN         (1<<11)         // nable discontinuous mode on regular channels
#define  ADC_CR1_JAUTO          (1<<10)         // enable automatic injected group conversion 
#define  ADC_CR1_AWDSGL         (1<<9)          // enable analog watchdog on a single channel
#define  ADC_CR1_SCAN           (1<<8)          // enable scan mode 
#define  ADC_CR1_JEOCIE         (1<<7)          // enable JEOC interrupt 
#define  ADC_CR1_AWDIE          (1<<6)          // enable analog watchdog interrupt 
#define  ADC_CR1_EOCIE          (1<<5)          // enable EOC interrupt 
#define  ADC_CR1_AWDCH          0x1f            // analog watchdog channel select bits


#define  ADC_CR2_SWSTART        (1<<30)         // start conversion of regular channels
#define  ADC_CR2_EXTEN          (0x3<<28)       // select the external trigger polarity and enable
#define  ADC_CR2_EXTSEL         (0xf<<24)        // select external event for regular group
#define  ADC_CR2_JSWSTART          (1<<22)      // start conversion of injected channels
#define  ADC_CR2_JEXTEN             (0x3<<20)       // select the external trigger polarity and enable for injected channels
#define  ADC_CR2_JEXTSEL            (0xf<<16)       // select external event for injected group
#define  ADC_CR2_ALIGN             (1<<11)          //  data left alignment
#define  ADC_CR2_EOCS           (1<<10)             // end of conversion selection
#define  ADC_CR2_DDS            (1<<9)              // DMA disable
#define  ADC_CR2_DMA            (1<<8)              // enable DMA mode
#define  ADC_CR2_CONT           0x2                 // continuous conversion mode
#define  ADC_CR2_ADON           0x1                 // enable ADC


#define ADC_SMPR1_SMPTIME        0x7         // channel x sampling time selection



#define ADC_JOFR_JOFFSET     0xfff              //  data offset for injected channel
#define  ADC_HTR_HT         0xfff     // analog watchdog higher threshold
#define  ADC_LTR_LT         0xfff     // analog watchdog lower threshold

#define ADC_SQR1_L          (0xf<<20)       // regular channel sequence length
#define ADC_SQR1_SQ13       0x1f      // 13th conversion in regular sequence

#define  ADC_JSQR_JL        (0x3<<20)           // injected sequence length
#define  ADC_JSQR_JSQ4      (0x1f<<15)          // 4th conversion in injected sequence
#define  ADC_JSQR_JSQ3      (0x1f<<10)          // 3rd conversion in injected sequence
#define  ADC_JSQR_JSQ2      (0x1f<<5)          // 2nd conversion in injected sequence
#define  ADC_JSQR_JSQ1      0x1f         // 1st conversion in injected sequence


#define ADC_JDR_JDATA    0xffff         // injected data

#define ADC_DR_DATA         0xffff         // regular data


#define  ADC_CSR_OVR1           (1<<5)              // overrun flag of ADC1
#define  ADC_CSR_STRT1          (1<<4)              // regular channel Start flag of ADC1
#define  ADC_CSR_JSTRT1            0x8              // injected channel Start flag of ADC1
#define  ADC_CSR_JEOC1              0x4             // injected channel end of conversion of ADC1
#define  ADC_CSR_EOC1              0x2              // end of conversion of ADC1
#define  ADC_CSR_AWD1               0x1             // analog watchdog flag of ADC1


#define  ADC_CCR_TSVREFE         (1<<23)        // enable temperature sensor and VREFINT channel 
#define  ADC_CCR_VBATE          (1<<22)         // enable VBAT channel
#define  ADC_CCR_ADCPRE         (0x3<<16)          // select the frequency of the clock to the ADC
#define  ADC_CCR_DMA            (0x3<<14)       // DMA mode for multi ADC mode
#define  ADC_CCR_DDS            (1<<13)         // DMA disable selection
#define  ADC_CCR_DELAY          (0xf<<8)        // delay between 2 sampling phases
#define  ADC_CCR_MULTI          0x1f            // multi ADC mode selection



#define  ADC_CDR_DATA1          0xffff0000              // 2nd data item of a pair of regular conversions
#define  ADC_CDR_DATA2          0xffff              // 1st data item of a pair of regular conversions








int32_t init_ADCx_config(uint32_t  adc,  ADCx_config_t * init_info)
{
    uint32_t  flag, mask;
    if (!ADC_ID_VALID(adc) || !init_info) {
        return  -1;
    }

    REG32_WRITE(ADC_HTR_REG_ADDR(adc), init_info->watchdog_higher_thresold & 0xfff);
    REG32_WRITE(ADC_LTR_REG_ADDR(adc), init_info->watchdog_lower_thresold & 0xfff);

    if (init_info->interrupt_watchdog_enbale)
        flag = ADC_CR1_AWDIE;
    if (init_info->interrupt_overrun_enbale)
        flag |= ADC_CR1_OVRIE;
    if (init_info->interrupt_eoc_enable)
        flag |= ADC_CR1_EOCIE;
    
    flag |= init_info->adc_resolution << 24;
    if (!init_info->watchdog_all_channel)
        flag  |=  ADC_CR1_AWDSGL;
    
    flag |= init_info->watchdog_channel_select;
    mask =  ADC_CR1_AWDIE | ADC_CR1_OVRIE | ADC_CR1_RES | ADC_CR1_EOCIE |
                ADC_CR1_AWDSGL | ADC_CR1_AWDCH;
    
    REG32_UPDATE(ADC_CR1_REG_ADDR(adc), flag, mask);

    if (init_info->left_align)
        flag = ADC_CR2_ALIGN;
    if (init_info->enable_continue)
        flag |= ADC_CR2_CONT;

    mask  =  ADC_CR2_ALIGN | ADC_CR2_CONT;
    REG32_UPDATE(ADC_CR2_REG_ADDR(adc), flag,  mask);
    return  0;

}


int32_t init_ADCx_regular_group_config(uint32_t  adc,  ADCx_regular_group_config_t *  config)
{
    uint32_t  flag, mask;
    if (!ADC_ID_VALID(adc) || !config) {
        return  -1;
    }

    if (config->enable_watchdog)
        flag = ADC_CR1_AWDEN;

    flag |= config->discontinuous_channel_count << 13;
    if (config->discontinuous_mode_enable)
        flag |= ADC_CR1_DISCEN;
    mask = ADC_CR1_AWDEN | ADC_CR1_DISCNUM | ADC_CR1_DISCEN;
    REG32_UPDATE(ADC_CR1_REG_ADDR(adc), flag, mask);

    flag = config->external_trigger_polarity << 28;
    flag |= config->external_event_select << 24;
    mask  =  ADC_CR2_EXTEN | ADC_CR2_EXTSEL;
    REG32_UPDATE(ADC_CR2_REG_ADDR(adc),  flag,  mask);
    return  0;

}


int32_t init_ADCx_inject_group_config(uint32_t  adc,   ADCx_inject_group_config_t * config)
{
    uint32_t  flag, mask;
    if (!ADC_ID_VALID(adc) || !config) {
        return  -1;
    }

    if (config->enable_watchdog)
        flag |= ADC_CR1_JAWDEN;
    if (config->discontinuous_mode_enable)
        flag |=  ADC_CR1_JDISCEN;
    if (config->jeoc_interrupt_enable)
        flag |= ADC_CR1_JEOCIE;
    if (config->automatic_injected_enable)
        flag |= ADC_CR1_JAUTO;
    mask =  ADC_CR1_JAWDEN | ADC_CR1_JDISCEN | ADC_CR1_JEOCIE | ADC_CR1_JAUTO;
    REG32_UPDATE(ADC_CR1_REG_ADDR(adc), flag,  mask);

    flag = config->external_trigger_polarity << 20;
    flag |= config->external_event_select << 16;
    mask  =  ADC_CR2_JEXTEN | ADC_CR2_JEXTSEL;
    REG32_UPDATE(ADC_CR2_REG_ADDR(adc),  flag,  mask);
    return  0;

}

static inline uint32_t  get_ADCx_regular_sequence(uint32_t adc)
{
    return  (REG32_READ(ADC_SQR1_REG_ADDR(adc)) >> 20) & 0xf;
}


static inline uint32_t  get_ADCx_injected_sequence(uint32_t adc)
{
    return  (REG32_READ(ADC_JSQR_REG_ADDR(adc)) >> 20) & 0x3;
}


static int32_t alloc_regular_sequence(uint32_t adc, uint32_t channel, uint32_t sample_time)
{
    uint32_t  len = get_ADCx_regular_sequence(adc);
    if (len == 0xf ) {
        return -1;
    }

    uint32_t  flag, mask;
    if (len  < 5) {
        flag  =  channel << ( (len + 1) * 5 );
        mask  =  0x1f  <<  ( (len + 1) * 5 );
        REG32_UPDATE(ADC_SQR3_REG_ADDR(adc), flag, mask);
    } else if (len < 11) {
        flag  = channel << ((len - 5) * 5);
        mask  = 0x1f << ((len - 5) * 5);
        REG32_UPDATE(ADC_SQR2_REG_ADDR(adc), flag, mask);
    } else {
        flag  =  channel  << ((len - 11) * 5);
        mask  = 0x1f << ((len - 11) * 5);
        REG32_UPDATE(ADC_SQR1_REG_ADDR(adc), flag,  mask);
    }

    if (channel < 10) {
        flag  =  sample_time << (3 * channel);
        mask  =  0x7 << (3 * channel);
        REG32_UPDATE(ADC_SMPR2_REG_ADDR(adc), flag,  mask);
    } else {
        flag  =  sample_time << (3 * (channel - 10) );
        mask  =  0x7 << (3 * (channel - 10) );
        REG32_UPDATE(ADC_SMPR2_REG_ADDR(adc), flag,  mask);
    }

    flag  = (len + 1) << 20;
    mask  = 0xf << 20;
    REG32_UPDATE(ADC_SQR1_REG_ADDR(adc), flag, mask);
    return  0;
}



static int32_t alloc_injected_sequence(uint32_t adc, uint32_t channel)
{
    uint32_t  len = get_ADCx_injected_sequence(adc);
    if (len == 0x3 ) {
        return -1;
    }

    uint32_t  flag, mask;
    flag  =  channel << ((len + 1) * 5);
    mask  =  0x1f <<  ((len + 1) * 5);
    REG32_UPDATE(ADC_JSQR_REG_ADDR(adc), flag,  mask);

    flag  = (len + 1) << 20;
    mask  = 0x3 << 20;
    REG32_UPDATE(ADC_JSQR_REG_ADDR(adc), flag, mask);
    return  0;
}



int32_t init_ADCx_channel_config(uint32_t  adc,  ADCx_channel_config_t *  config)
{
    uint32_t  flag, mask;
    if (!ADC_ID_VALID(adc) || !config) {
        return  -1;
    }

    if (config->channel_select > MAX_ADC_CHANNEL_ID) {
        return -1;
    }

    if (config->sample_time > 0x7) {
        return -1;
    }


    if (config->regular_group) {
        if (alloc_regular_sequence(adc, config->channel_select, config->sample_time))
            return  -1;
    } else {
        if (alloc_injected_sequence(adc, config->channel_select))
            return  -1;
    }

    return  0;

}


int32_t  start_ADCx_group_conversion(uint32_t adc, uint32_t is_regular)
{
    uint32_t  flag, mask;
    if (adc > ADC_ID_MAX)
        return  -1;
    
    if (is_regular) {
        flag  =  ADC_CR2_SWSTART;
        mask  =  ADC_CR2_SWSTART;
    } else {
        flag  =  ADC_CR2_JSWSTART;
        mask  =  ADC_CR2_JSWSTART;
    }
    REG32_UPDATE(ADC_CR2_REG_ADDR(adc), flag,  mask);
    return  0;
}


int32_t  reset_ADCx_group_conversion(uint32_t adc, uint32_t is_regular)
{
    uint32_t  flag, mask;
    if (adc > ADC_ID_MAX)
        return  -1;
    
    flag = 0;
    if (is_regular) {
        mask  =  ADC_CR2_SWSTART;
    } else {
        mask  =  ADC_CR2_JSWSTART;
    }
    REG32_UPDATE(ADC_CR2_REG_ADDR(adc), flag,  mask);
    return  0;
}







