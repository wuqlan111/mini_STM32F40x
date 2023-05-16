

#ifndef  STM32_DAC_H
#define  STM32_DAC_H

#include  <stdint.h>
#include  <stdbool.h>

#define MAX_AMPLITUDE_MASKBIT       12



enum  dac_channel{
    DAC_CHANNEL1 = 0,
    DAC_CHANNEL2,
    DAC_CHANNEL_NUMBER
};


enum wave_generation_mode{
    DISABLE_WAVE_GENERATION = 0,
    ENABLE_NOISE_WAVE,
    ENABLE_TRUANGLE_WAVE
};


enum DAC_channel_trigger{
    TIMER6_TRGO_EVENT = 0,
    TIMER8_TRGO_EVENT,
    TIMER7_TRGO_EVENT,
    TIMER5_TRGO_EVENT,
    TIMER2_TRGO_EVENT,
    TIMER4_TRGO_EVENT,
    EXTERNAL_LINE9_EVENT,
    SOFTWARE_TRG_EVENT
};


enum  data_align_mode{
    BIT12_LEFT_ALIGN = 0,
    BIT12_RIGHT_ALIGN,
    BIT8_RIGHT_ALIGN
};


typedef struct DAC_init{
    bool enable_underrun_int;
    bool enable_DMA;
    bool  enable_trigger;
    bool enable_obuffer;
    uint8_t  amplitude_maskbit;
    uint8_t  wave_generation_mode;
    uint8_t  channel_trigger;
}DAC_init_t;




int32_t DAC_channel_init(uint8_t channel_id, DAC_init_t *  dac_inits);
int32_t  enable_DAC_channel(uint8_t channel_id, bool enable);
int32_t set_channel_data(uint8_t channel_id,  uint16_t data, uint8_t data_align_type);
int16_t get_channel_outdata(uint8_t channel_id);
int32_t set_dualchannel_data(uint8_t channel_id,  uint16_t data, uint8_t data_align_type);
int32_t DAC_software_trigger(uint8_t channel_id, bool trigger);
int32_t DAC_software_dualtrigger(bool trigger);



#endif


