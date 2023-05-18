
#ifndef  STM32_ADC_H
#define  STM32_ADC_H

#include  <stdint.h>
#include  "util.h"

#define  MAX_ADC_CHANNEL_ID     18
#define  MAX_ADC_EXT_CHANNEL_ID     15



typedef enum {
    BIT12_15CYCLE = 0,
    BIT10_13CYCLE,
    BIT8_11CYCLE,
    BIT6_9CYCLE,
    ADC_RESOLUTION_MAX  =  BIT6_9CYCLE,
}ADC_resolution_t;

typedef enum {
    ADC1 =0,
    ADC2,
    ADC3,
    ADC_ID_MAX  =  ADC3,
}ADC_id_t;


typedef enum{

    TRIGGER_DETECT_DISABLE = 0,
    TRIGGER_DETECT_RISE,
    TRIGGER_DETECT_FALL,
    TRIGGER_DETECT_BOTH,
    TRIGGER_DETECT_MAX  =  TRIGGER_DETECT_BOTH,
}external_trigger_polarity_t;


typedef enum {

    T1_CC1_EVENT = 0,
    T1_CC2_EVENT,
    T1_CC3_EVENT,
    T2_CC2_EVENT,
    T2_CC3_EVENT,
    T2_CC4_EVENT,
    T2_TRGO1_EVENT,
    T3_CC1_EVENT,
    T3_TRGO_EVENT,
    T4_CC4_EVENT,
    T5_CC1_EVENT,
    T5_CC2_EVENT,
    T5_CC3_EVENT,
    T8_CC1_EVENT,
    T8_TRGO_EVENT,
    EXTI_LINE11,
    REGYLAR_EXTERNAL_EVENT_MAX  =  EXTI_LINE11,

}regular_external_event_t;


typedef enum {

    T1_CC4_EVENT = 0,
    T1_TRGO_EVENT,
    T2_CC1_EVENT,
    T2_TRGO2_EVENT,
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
    EXTI_LINE15,
    INJEXTED_EXTERNAL_EVENT_MAX = EXTI_LINE15,

}injected_external_event_t;


typedef enum {

    SAMPLE_3_CYCLE = 0,
    SAMPLE_15_CYCLE,
    SAMPLE_28_CYCLE,
    SAMPLE_56_CYCLE,
    SAMPLE_84_CYCLE,
    SAMPLE_112_CYCLE,
    SAMPLE_144_CYCLE,
    SAMPLE_480_CYCLE,
    SAMPLIE_TIME_MAX_CYCLE  = SAMPLE_480_CYCLE,

}sampling_time_t;


typedef enum {

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
    TRIPLE_ALTERNATE_ONLY = 25,
    NULTI_ADC_MODE_MAX =  TRIPLE_ALTERNATE_ONLY,

}multi_adc_mode_t;


typedef struct {
    uint16_t  watchdog_higher_thresold;
    uint16_t  watchdog_lower_thresold;    
    uint8_t  interrupt_eoc_enable;
    uint8_t  interrupt_watchdog_enbale;
    uint8_t  interrupt_overrun_enbale;
    uint8_t  adc_resolution;
    uint8_t  watchdog_all_channel;
    uint8_t  watchdog_channel_select;
    uint8_t  left_align;
    uint8_t  enable_continue;
}ATTRIBUTE_PACKED ADCx_config_t;

typedef struct {
    uint8_t  enable_watchdog;
    uint8_t  discontinuous_channel_count;
    uint8_t  discontinuous_mode_enable;
    uint8_t  external_trigger_polarity;
    uint8_t  external_event_select;
} ATTRIBUTE_PACKED ADCx_regular_group_config_t;

typedef struct {
    uint8_t  enable_watchdog;
    uint8_t  discontinuous_mode_enable;
    uint8_t  automatic_injected_enable;
    uint8_t  jeoc_interrupt_enable;
    uint8_t  external_trigger_polarity;
    uint8_t  external_event_select;
    uint8_t  injected_sequence_length;
} ATTRIBUTE_PACKED ADCx_inject_group_config_t;

typedef struct {
    uint8_t  channel_select;
    uint8_t  sample_time;
    uint8_t  sequence_number;
    uint8_t  regular_group;

} ATTRIBUTE_PACKED ADCx_channel_config_t;



#define  ADC_ID_VALID(adc)  ( ((adc) <= ADC_ID_MAX) && ((adc) > 0))




int32_t init_ADCx_config(uint32_t  adc,  ADCx_config_t * init_info);
int32_t init_ADCx_regular_group_config(uint32_t  adc,  ADCx_regular_group_config_t *  config);
int32_t init_ADCx_inject_group_config(uint32_t  adc,   ADCx_inject_group_config_t *  config);
int32_t init_ADCx_channel_config(uint32_t  adc,  ADCx_channel_config_t *  config);









#endif

