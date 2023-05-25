

#ifndef  STM32_DAC_H
#define  STM32_DAC_H

#include  <stdint.h>
#include  "util.h"

#define MAX_AMPLITUDE_MASKBIT       12


enum  {
    DAC_CHANNEL1 = 0,
    DAC_CHANNEL2,
    DAC_MAX_CHANNEL = DAC_CHANNEL2,
};


enum {
    DISABLE_WAVE_GENERATION = 0,
    ENABLE_NOISE_WAVE,
    ENABLE_TRUANGLE_WAVE,
    DAC_MAX_WAVE =  ENABLE_TRUANGLE_WAVE,
};


enum {
    TIMER6_TRGO_EVENT = 0,
    TIMER8_TRGO_EVENT,
    TIMER7_TRGO_EVENT,
    TIMER5_TRGO_EVENT,
    TIMER2_TRGO_EVENT,
    TIMER4_TRGO_EVENT,
    EXTERNAL_LINE9_EVENT,
    SOFTWARE_TRG_EVENT,
    DAC_MAX_TRIGGER_EVENT =  SOFTWARE_TRG_EVENT,
};


enum {
    BIT12_LEFT_ALIGN = 0,
    BIT12_RIGHT_ALIGN,
    BIT8_RIGHT_ALIGN,
    DAC_MAX_DATA_ALIGN  =  BIT8_RIGHT_ALIGN,
};


typedef struct {
    uint32_t  dma_underrun_interrupt_enable:1;
    uint32_t  dma_enable:1;
    uint32_t  mask_selector:4;
    uint32_t  wave_generation:2;
    uint32_t  trigger_selector:3;
    uint32_t  trigger_enable:1;
    uint32_t  output_buffer_enable:1;
} ATTRIBUTE_ALIGN(4) DAC_channel_config_t;


int32_t DAC_channel_config(uint32_t channel_id, DAC_channel_config_t *  config);
int32_t enable_or_disable_DAC_channel(uint32_t channel_id, uint32_t enable);
int32_t set_channel_data(uint32_t channel_id,  uint32_t data, uint32_t data_align_type);
int32_t get_channel_outdata(uint32_t channel_id, uint32_t * data);
int32_t set_dualchannel_data(uint32_t channel_id,  uint32_t data, uint32_t data_align_type);
int32_t DAC_software_trigger(uint32_t channel_id, uint32_t trigger);



#endif


