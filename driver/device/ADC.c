
#include  <stdlib.h>
#include  "../include/ADC.h"


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


#define   ADC_REG_BASE    0x40012000u
#define   ADC1_REG_OFFSET        0
#define   ADC2_REG_OFFSET        0x100
#define   ADC3_REG_OFFSET        0x200
#define   ADC_COMMON_OFFSET         0x300

typedef struct ADC_reg{

    volatile  uint32_t  adc_sr;
    volatile  uint32_t  adc_cr1;
    volatile  uint32_t  adc_cr2;
    volatile  uint32_t  adc_smpr1;
    volatile  uint32_t  adc_smpr2;
    volatile  uint32_t  adc_jofr1;
    volatile  uint32_t  adc_jofr2;
    volatile  uint32_t  adc_jofr3;
    volatile  uint32_t  adc_jofr4;
    volatile  uint32_t  adc_htr;
    volatile  uint32_t  adc_ltr;
    volatile  uint32_t  adc_sqr1;
    volatile  uint32_t  adc_sqr2;
    volatile  uint32_t  adc_sqr3;
    volatile  uint32_t  adc_jsqr;
    volatile  uint32_t  adc_jdr1;
    volatile  uint32_t  adc_jdr2;
    volatile  uint32_t  adc_jdr3;
    volatile  uint32_t  adc_jdr4;
    volatile  uint32_t  adc_dr;

}ADC_reg_t;


typedef struct ADC_creg{

    volatile  uint32_t  adc_csr;
    volatile  uint32_t  adc_ccr;
    volatile  uint32_t  adc_cdr;

}ADC_creg_t;


ADC_reg_t * const ALL_ADCs[ADC_NUMBER] = {  (ADC_reg_t *)(ADC1_REG_OFFSET + ADC1_REG_OFFSET),
                                            (ADC_reg_t *)(ADC1_REG_OFFSET + ADC2_REG_OFFSET),
                                            (ADC_reg_t *)(ADC1_REG_OFFSET + ADC3_REG_OFFSET) };
ADC_creg_t * const ADC_cregs = (ADC_creg_t *)(ADC1_REG_OFFSET + ADC_COMMON_OFFSET);


int32_t set_ADC_multimode(uint8_t multi_mode){

    if ( multi_mode > ADC_CCR_MULTI )
        return -1;
    
    ADC_cregs->adc_ccr &= ~ADC_CCR_MULTI;
    ADC_cregs->adc_ccr |= multi_mode;

    return 0;

}


int32_t enable_ADC_interrupt(uint8_t adc_id ,uint32_t int_mask){

    uint32_t all_int_mask = ADC_OVERRUN_INT | ADC_JEOC_INT | ADC_WATCHDOG_INT | ADC_EOC_INT;

    if ((int_mask & ~all_int_mask) || adc_id >ADC3)
        return -1;
    
    ALL_ADCs[adc_id]->adc_cr1 |= int_mask;

    return -1;

}


int32_t disable_ADC_interrupt( uint8_t adc_id, uint32_t int_mask){

    uint32_t all_int_mask = ADC_CR1_OVRIE | ADC_CR1_JDISCEN | ADC_CR1_AWDIE | ADC_CR1_EOCIE;

    if ((int_mask &  ~all_int_mask)  || adc_id > ADC3)
        return -1;
    
    ALL_ADCs[adc_id]->adc_cr1 &= ~int_mask;

    return -1;


}


int32_t set_ADC_resolution( uint8_t adc_id, uint8_t adc_resolution){


    if ( adc_resolution > BIT6_9CYCLE || adc_id > ADC3)
        return -1;
    
    ALL_ADCs[adc_id]->adc_cr1 &= ~ADC_CR1_RES;
    ALL_ADCs[adc_id]->adc_cr1 |= (adc_resolution << 24);
    return -1;

}


int32_t  set_ADC_sample_time( uint8_t adc_id, uint8_t channel_id, uint8_t sample_time){

    if ( adc_id > ADC3 || sample_time > SAMPLE_480_CYCLE || channel_id > MAX_ADC_CHANNEL_ID)
        return -1;
    
    if (channel_id > 9)
    {
        ALL_ADCs[adc_id]->adc_smpr1 &= ~(0x7<<(channel_id - 10));
        ALL_ADCs[adc_id]->adc_smpr1 |= (sample_time<<(channel_id - 10));
    }else{

        ALL_ADCs[adc_id]->adc_smpr1 &= ~(0x7<<channel_id);
        ALL_ADCs[adc_id]->adc_smpr1 |= (sample_time<<channel_id );
    }
    
    return 0;

}


int32_t  set_ADC_inject_offset( uint8_t adc_id, uint8_t inject_channel_idx ,uint16_t  sub_raw_offset){

    if ( adc_id > ADC3 ||sub_raw_offset > ADC_JOFR_JOFFSET  ||  inject_channel_idx > 3)
        return  -1;

    switch (inject_channel_idx)
    {
    case 0:
        ALL_ADCs[adc_id]->adc_jofr1 &= ~ADC_JOFR_JOFFSET;
        ALL_ADCs[adc_id]->adc_jofr1 |= sub_raw_offset;
        break;
    case 1:
        ALL_ADCs[adc_id]->adc_jofr2 &= ~ADC_JOFR_JOFFSET;
        ALL_ADCs[adc_id]->adc_jofr2 |= sub_raw_offset;
        break;

    case 2:
        ALL_ADCs[adc_id]->adc_jofr3 &= ~ADC_JOFR_JOFFSET;
        ALL_ADCs[adc_id]->adc_jofr3 |= sub_raw_offset;
        break;

    case 3:
        ALL_ADCs[adc_id]->adc_jofr4 &= ~ADC_JOFR_JOFFSET;
        ALL_ADCs[adc_id]->adc_jofr4 |= sub_raw_offset;
        break;

    default:
        break;
    }
    
    return 0;

}



int32_t set_ADC_wdg_HTR( uint8_t adc_id, uint16_t  wdg_htr){

    if (wdg_htr > ADC_HTR_HT || adc_id > ADC3)
        return -1;    

    ALL_ADCs[adc_id]->adc_htr =  wdg_htr;
    return 0;

}


int32_t set_ADC_wdg_LTR( uint8_t adc_id, uint16_t  wdg_ltr){

    if (wdg_ltr > ADC_HTR_HT || adc_id > ADC3 )
        return -1;    

    ALL_ADCs[adc_id]->adc_ltr =  wdg_ltr;
    return 0;

}



int32_t set_ADC_discnum( uint8_t adc_id, uint8_t channel_num){

    if ( channel_num > 7 || adc_id > ADC3 )
        return -1;    

    ALL_ADCs[adc_id]->adc_cr1 &= ~ADC_CR1_DISCNUM;
    ALL_ADCs[adc_id]->adc_cr1 |= (channel_num << 13);
    return 0;

}



int32_t set_ADC_wdg_channel( uint8_t adc_id, uint8_t channel_id){

    if ( channel_id > MAX_ADC_CHANNEL_ID || adc_id > ADC3 )
        return -1;    

    ALL_ADCs[adc_id]->adc_cr1 &= ~ADC_CR1_AWDCH;
    ALL_ADCs[adc_id]->adc_cr1 |= (channel_id);
    return 0;

}


int32_t set_ADC_regular_trigger( uint8_t adc_id, uint8_t trigger_type, uint8_t ext_event){

    if (  adc_id > ADC3 || trigger_type > TRIGGER_DETECT_BOTH || ext_event > EXTI_LINE11)
        return -1;    

    ALL_ADCs[adc_id]->adc_cr2 &= ~ADC_CR2_EXTEN;
    ALL_ADCs[adc_id]->adc_cr2 |= (trigger_type << 28);
    ALL_ADCs[adc_id]->adc_cr2 &= ~ADC_CR2_EXTSEL;
    ALL_ADCs[adc_id]->adc_cr2 |= (ext_event << 24);
    return 0;

}

int32_t set_ADC_inject_trigger( uint8_t adc_id, uint8_t trigger_type, uint8_t ext_event){

    if (  adc_id > ADC3 || trigger_type > TRIGGER_DETECT_BOTH || ext_event > EXTI_LINE15)
        return -1;    

    ALL_ADCs[adc_id]->adc_cr2 &= ~ADC_CR2_JEXTEN;
    ALL_ADCs[adc_id]->adc_cr2 |= (trigger_type << 20);
    ALL_ADCs[adc_id]->adc_cr2 &= ~ADC_CR2_JEXTSEL;
    ALL_ADCs[adc_id]->adc_cr2 |= (ext_event << 16);
    return 0;

}



int32_t set_ADC_regular_order( uint8_t adc_id, uint8_t channel_id, uint8_t order){

    if (  adc_id > ADC3 || channel_id > MAX_ADC_CHANNEL_ID || !order || order > 16)
        return -1;    

    if (order > 12){
        ALL_ADCs[adc_id]->adc_sqr1 &= ~(ADC_SQR1_SQ13<<(order - 13));
        ALL_ADCs[adc_id]->adc_sqr1 |= (channel_id << (order - 13));
    }else if (order > 6){
        ALL_ADCs[adc_id]->adc_sqr1 &= ~(ADC_SQR1_SQ13<<(order - 7));
        ALL_ADCs[adc_id]->adc_sqr1 |= (channel_id << (order - 7));
    }else{
        ALL_ADCs[adc_id]->adc_sqr1 &= ~(ADC_SQR1_SQ13<<(order - 1));
        ALL_ADCs[adc_id]->adc_sqr1 |= (channel_id << (order - 1));
    }

    return 0;

}

int32_t set_ADC_inject_order( uint8_t adc_id, uint8_t channel_id, uint8_t order){

    if (  adc_id > ADC3 || channel_id > MAX_ADC_CHANNEL_ID || !order || order > 4)
        return -1;    

    ALL_ADCs[adc_id]->adc_jsqr &= ~(ADC_SQR1_SQ13<<(order - 1));
    ALL_ADCs[adc_id]->adc_jsqr |= (channel_id << (order - 1));

    return 0;

}


int32_t enable_ADC(uint8_t adc_id){

    if (adc_id > ADC3)
        return -1;
    ALL_ADCs[adc_id]->adc_cr2 |= ADC_CR2_ADON;
    return 0;

}

int32_t disable_ADC(uint8_t adc_id){

    if (adc_id > ADC3)
        return -1;
    ALL_ADCs[adc_id]->adc_cr2 &= ~ADC_CR2_ADON;
    return 0;

}


int32_t enable_discontiouns_mode(uint8_t adc_id, bool inject_group){

    if (adc_id > ADC3)
        return -1;
    
    if (inject_group)
        ALL_ADCs[adc_id]->adc_cr1 |= ADC_CR1_JDISCEN;
    else
        ALL_ADCs[adc_id]->adc_cr1 |= ADC_CR1_DISCEN;

    return 0;

}

int32_t disable_discontiouns_mode(uint8_t adc_id, bool inject_group){

    if (adc_id > ADC3)
        return -1;
    
    if (inject_group)
        ALL_ADCs[adc_id]->adc_cr1 &= ~ADC_CR1_JDISCEN;
    else
        ALL_ADCs[adc_id]->adc_cr1 &=  ~ADC_CR1_DISCEN;

    return 0;

}


int32_t  enable_ADC_wdg(uint8_t adc_id, bool inject_group, uint8_t channel_id){

    if (adc_id > ADC3 || channel_id  > MAX_ADC_CHANNEL_ID)
        return -1;
    
    ALL_ADCs[adc_id]->adc_cr1 &= ~ ADC_CR1_AWDCH;
    ALL_ADCs[adc_id]->adc_cr1 |= channel_id;
    if (inject_group)
        ALL_ADCs[adc_id]->adc_cr1 |=  ADC_CR1_JAWDEN;
    else
        ALL_ADCs[adc_id]->adc_cr1 |=  ADC_CR1_AWDEN;
    
    return 0;

}

int32_t  disable_ADC_wdg(uint8_t adc_id, bool inject_group){

    if (adc_id > ADC3)
        return -1;

    if (inject_group)
        ALL_ADCs[adc_id]->adc_cr1 &=   ~ADC_CR1_JAWDEN;
    else
        ALL_ADCs[adc_id]->adc_cr1 &=  ~ADC_CR1_AWDEN;
    
    return 0;

}


int16_t  get_regular_data(uint8_t  adc_id){

    if (adc_id > ADC3)
        return -1;
    
    while (!(ALL_ADCs[adc_id]->adc_sr & ADC_SR_EOC))
        ;
    
    uint16_t adc_data = ALL_ADCs[adc_id]->adc_dr & ADC_DR_DATA;
    ALL_ADCs[adc_id]->adc_sr &= ~ADC_SR_EOC;

    return adc_data;

}


int16_t  get_inject_data(uint8_t  adc_id, uint8_t jsq_num){

    if (adc_id > ADC3 || jsq_num > 4 || !jsq_num )
        return -1;
    
    while (!(ALL_ADCs[adc_id]->adc_sr & ADC_SR_JEOC))
        ;

    uint16_t adc_data;
    switch (jsq_num)
    {
    case 1:
        adc_data = ALL_ADCs[adc_id]->adc_jdr1 & ADC_JDR_JDATA;
        break;
    case 2:
        adc_data = ALL_ADCs[adc_id]->adc_jdr2 & ADC_JDR_JDATA;
        break;
    case 3:
        adc_data = ALL_ADCs[adc_id]->adc_jdr3 & ADC_JDR_JDATA;
        break;
    case 4:
        adc_data = ALL_ADCs[adc_id]->adc_jdr4 & ADC_JDR_JDATA;
        break;
    }

    ALL_ADCs[adc_id]->adc_sr &= ~ADC_SR_JEOC;
    return adc_data;

}



int32_t  get_multiadc_data(bool dual_mode){

    uint32_t eoc_flag = dual_mode?(3 << 1 | 3 << 9):(3 << 1 | 3 << 9 | 3 << 17);

    //
    
    uint32_t mutlti_data =  ADC_cregs->adc_cdr;
    ADC_cregs->adc_csr &= ~ eoc_flag;

    return mutlti_data;

}

