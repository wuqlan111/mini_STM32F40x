

#ifndef  STM32_ADC_H
#define  STM32_ADC_H

#include  <stdint.h>
#include  <stdbool.h>

#define  MAX_ADC_CHANNEL_ID     18
#define  MAX_ADC_EXT_CHANNEL_ID     15

#define  ADC_OVERRUN_INT    (1<<26)
#define  ADC_JEOC_INT    (1<<7)
#define  ADC_WATCHDOG_INT    (1<<6)
#define  ADC_EOC_INT    (1<<5)



typedef enum ADC_resolution{

    BIT12_15CYCLE = 0,
    BIT10_13CYCLE,
    BIT8_11CYCLE,
    BIT6_9CYCLE

}ADC_resolution_t;

typedef enum ADC_ID{
    ADC1 =0,
    ADC2,
    ADC3,
    ADC_NUMBER
}ADC_id_t;


typedef enum external_trigger_polarity{

    TRIGGER_DETECT_DISABLE = 0,
    TRIGGER_DETECT_RISE,
    TRIGGER_DETECT_FALL,
    TRIGGER_DETECT_BOTH

}external_trigger_polarity_t;


typedef enum  regular_external_event{

    T1_CC1_EVENT = 0,
    T1_CC2_EVENT,
    T1_CC3_EVENT,
    T2_CC2_EVENT,
    T2_CC3_EVENT,
    T2_CC4_EVENT,
    T2_TRGO_EVENT,
    T3_CC1_EVENT,
    T3_TRGO_EVENT,
    T4_CC4_EVENT,
    T5_CC1_EVENT,
    T5_CC2_EVENT,
    T5_CC3_EVENT,
    T8_CC1_EVENT,
    T8_TRGO_EVENT,
    EXTI_LINE11

}regular_external_event_t;


typedef enum  injected_external_event{

    T1_CC4_EVENT = 0,
    T1_TRGO_EVENT,
    T2_CC1_EVENT,
    T2_TRGO_EVENT,
    T3_CC2_EVENT,
    T3_CC4_EVENT,
    T4_CC1_EVENT,
    T4_CC2_EVENT,
    T4_CC3_EVENT,
    T4_TRGO_EVENT,
    T5_CC4_EVENT,
    T5_TRGO_EVENT,
    T8_CC2_EVENT,
    T8_CC3_EVENT,
    T8_CC4_EVENT,
    EXTI_LINE15

}injected_external_event_t;


typedef enum  sampling_time{

    SAMPLE_3_CYCLE = 0,
    SAMPLE_15_CYCLE,
    SAMPLE_28_CYCLE,
    SAMPLE_56_CYCLE,
    SAMPLE_84_CYCLE,
    SAMPLE_112_CYCLE,
    SAMPLE_144_CYCLE,
    SAMPLE_480_CYCLE

}sampling_time_t;


typedef enum  multi_adc_mode{

    INDEPENDENT_MODE = 0,
    DUAL_REGULAR_INJECTED,
    DUAL_REGULAR_ALTERNATE,
    DUAL_INJECTED_ONLY = 5,
    DUAL_REGULA_ONLY,
    DUAL_INTERLEAVED_ONLY,
    DUAL_ALTERNATE_ONLY = 9,
    TRIPLE_REGULAR_INJECTED = 17,
    TRIPLE_REGULAR_ALTERNATE,
    TRIPLE_INJECTED_ONLY = 21,
    TRIPLE_REGULA_ONLY,
    TRIPLE_INTERLEAVED_ONLY,
    TRIPLE_ALTERNATE_ONLY = 25

}multi_adc_mode_t;


int32_t set_ADC_multimode( uint8_t multi_mode);
int32_t enable_ADC_interrupt( uint8_t adc_id ,uint32_t int_mask)
int32_t set_ADC_resolution( uint8_t adc_id, uint8_t adc_resolution)
int32_t set_ADC_sample_time( uint8_t adc_id, uint8_t channel_id, uint8_t sample_time);
int32_t set_ADC_inject_offset( uint8_t adc_id, uint8_t inject_channel_idx ,uint16_t  sub_raw_offset);
int32_t set_ADC_wdg_HTR( uint8_t adc_id, uint16_t  wdg_htr);
int32_t set_ADC_wdg_LTR( uint8_t adc_id, uint16_t  wdg_ltr);
int32_t set_ADC_discnum( uint8_t adc_id, uint8_t channel_num);
int32_t set_ADC_wdg_channel( uint8_t adc_id, uint8_t channel_id);
int32_t set_ADC_regular_trigger( uint8_t adc_id, uint8_t trigger_type, uint8_t ext_event);
int32_t set_ADC_inject_trigger( uint8_t adc_id, uint8_t trigger_type, uint8_t ext_event);
int32_t set_ADC_regular_order( uint8_t adc_id, uint8_t channel_id, uint8_t order);
int32_t set_ADC_inject_order( uint8_t adc_id, uint8_t channel_id, uint8_t order);
int32_t enable_ADC(uint8_t adc_id);
int32_t disable_ADC(uint8_t adc_id);
int32_t enable_discontiouns_mode(uint8_t adc_id, bool inject_group);
int32_t disable_discontiouns_mode(uint8_t adc_id, bool inject_group);
int32_t  enable_ADC_wdg(uint8_t adc_id, bool inject_group, uint8_t channel_id);
int32_t  disable_ADC_wdg(uint8_t adc_id, bool inject_group);
int16_t  get_regular_data(uint8_t  adc_id);
int16_t  get_inject_data(uint8_t  adc_id, uint8_t jsq_num);
int32_t  get_multiadc_data(bool dual_mode);




#endif

