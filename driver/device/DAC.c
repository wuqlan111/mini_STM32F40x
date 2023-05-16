

#include  <stdlib.h>
#include  "../include/DAC.h"



#define DAC_CR_DMAUDRIE1            (1<<13)                 // DAC channel1 DMA Underrun Interrupt enable
#define DAC_CR_DMAEN1               (1<<12)                 // DAC channel1 DMA enable
#define DAC_CR_MAMP1                (0xf<<8)                // DAC channel1 mask selector
#define DAC_CR_WAVE1                (0x3<<6)                // DAC channel1 noise wave generation enable
#define DAC_CR_TSEL1                (0x7<<3)                // DAC channel1 trigger selection
#define DAC_CR_TEN1                 0x4                        // DAC channel1 trigger enable
#define DAC_CR_BOFF1                0x2                     // DAC channel1 output buffer disable
#define DAC_CR_EN1                  0x1                     // 1: DAC channel1 enable



#define  DAC_SWTRIGR_SWTRIG2        0x2             // enable DAC channel2 software trigger
#define  DAC_SWTRIGR_SWTRIG1        0x1             // enable DAC channel1 software trigger

#define  DAC_DHR12Rx_DACDHR           0xfff           // DAC channelx 12-bit right-aligned data
#define  DAC_DHR12Lx_DACDHR           0xfff0          // DAC channelx 12-bit left-aligned data
#define  DAC_DHR8Rx_DACDHR           0xff                 // DAC channelx 8-bit right-aligned data


#define  DAC_DHR12RD_DACC1DHR             0xfff                 // DAC channel1 12-bit right-aligned data
#define  DAC_DHR12LD_DACC1DHR           0xffff0                 // DAC channel1 12-bit left-aligned data
#define  DAC_DHR8RD_DACC1DHR            0xff                    // DAC channel1 8-bit right-aligned data


#define  DAC_DORx_DACDOR          0xfff                   // DAC channelx data output


#define  DAC_SR_DMAUDR2            (1<<29)                  // DAC channel2 DMA underrun flag
#define  DAC_SR_DMAUDR1             (1<<13)                 // DAC channel1 DMA underrun flag

#define DAC_REG_BASE             0x40007400u

typedef struct dac_dhr{

    volatile uint32_t dac_dhr12rx;
    volatile uint32_t dac_dhr12lx;
    volatile uint32_t dac_dhr8rx;

}dac_dhr_t;


typedef struct dac_control{
    volatile  uint32_t dac_cr;
    volatile  uint32_t dac_swtrigr;
    dac_dhr_t  dac_dhrs[DAC_CHANNEL_NUMBER];
    volatile  uint32_t  dac_dhr12rd;
    volatile  uint32_t  dac_dhr12ld;
    volatile  uint32_t  dac_dhr8rd;
    volatile  uint32_t  dac_dors[DAC_CHANNEL_NUMBER];
    volatile  uint32_t  dac_sr;

}dac_control_t;


dac_control_t * const dac_controls = (dac_control_t *)DAC_REG_BASE;



int32_t DAC_channel_init(uint8_t channel_id, DAC_init_t *  dac_inits){

    if (channel_id > DAC_CHANNEL2 || !dac_inits || dac_inits->wave_generation_mode > ENABLE_TRUANGLE_WAVE
          ||  dac_inits->amplitude_maskbit > MAX_AMPLITUDE_MASKBIT 
          || dac_inits->channel_trigger > SOFTWARE_TRG_EVENT)
        return -1;
    
    if (dac_inits->enable_underrun_int)
        dac_controls->dac_cr |= (DAC_CR_DMAUDRIE1 << (16 * channel_id));
    else
        dac_controls->dac_cr &= ~(DAC_CR_DMAUDRIE1 << (16 * channel_id));

    if (dac_inits->enable_DMA)
        dac_controls->dac_cr |= (DAC_CR_DMAEN1 << (16 * channel_id));
    else
        dac_controls->dac_cr &= ~(DAC_CR_DMAEN1 << (16 * channel_id));

    if (dac_inits->enable_trigger){
        
        dac_controls->dac_cr |= (DAC_CR_TEN1<< (16 * channel_id));
        dac_controls->dac_cr &= ~(DAC_CR_TSEL1<< (16 * channel_id));
        dac_controls->dac_cr |= (dac_inits->channel_trigger<< (16 * channel_id));

    }else
        dac_controls->dac_cr &= ~(DAC_CR_TEN1 << (16 * channel_id));

    if (dac_inits->wave_generation_mode != DISABLE_WAVE_GENERATION){

        if (!dac_inits->amplitude_maskbit)
            return -1;   
        dac_controls->dac_cr &= ~(DAC_CR_WAVE1 << (16 * channel_id));
        dac_controls->dac_cr |= (dac_inits->wave_generation_mode << (16 * channel_id));
        dac_controls->dac_cr &= ~(DAC_CR_MAMP1 << (16 * channel_id));
        dac_controls->dac_cr |= ((dac_inits->amplitude_maskbit -1)<< (16 * channel_id));

    }else
        dac_controls->dac_cr &= ~(DAC_CR_WAVE1 << (16 * channel_id));

    if (dac_inits->enable_obuffer)
        dac_controls->dac_cr &= ~(DAC_CR_BOFF1 << (16 * channel_id));
    else
        dac_controls->dac_cr |=  (DAC_CR_BOFF1 << (16 * channel_id));
    
    return 0;

}



int32_t  enable_DAC_channel(uint8_t channel_id, bool enable){

    if (channel_id > DAC_CHANNEL2)
        return -1;
    
    if (enable)
        dac_controls->dac_cr |= (DAC_CR_EN1 << (16 * channel_id));
    else
        dac_controls->dac_cr &= ~(DAC_CR_EN1<< (16 * channel_id));
    
    return 0;
}


int32_t set_channel_data(uint8_t channel_id,  uint16_t data, uint8_t data_align_type){

    if (channel_id > DAC_CHANNEL2 || data > 0xfff  || data_align_type > BIT8_RIGHT_ALIGN)
            return -1;
    
    dac_controls->dac_dhrs[channel_id].dac_dhr12lx &= ~ DAC_DHR12Lx_DACDHR;
    dac_controls->dac_dhrs[channel_id].dac_dhr12rx &= ~DAC_DHR12Rx_DACDHR;
    dac_controls->dac_dhrs[channel_id].dac_dhr8rx &=  ~DAC_DHR8Rx_DACDHR;

    switch (data_align_type)
    {
    case  BIT12_LEFT_ALIGN:
        dac_controls->dac_dhrs[channel_id].dac_dhr12lx |= (data<<4);
        break;

    case BIT12_RIGHT_ALIGN:
        dac_controls->dac_dhrs[channel_id].dac_dhr12rx |= data;
        break;

    case BIT8_RIGHT_ALIGN:
        if (data > 0xff)
            return -1;
        dac_controls->dac_dhrs[channel_id].dac_dhr8rx |= data;
        break;
    
    }

    return 0;

}

int16_t get_channel_outdata(uint8_t channel_id){

    if (channel_id > DAC_CHANNEL2 )
        return -1;

    int16_t ret = dac_controls->dac_dors[channel_id] & 0xfff;

    return ret;

}



int32_t set_dualchannel_data(uint8_t channel_id,  uint16_t data, uint8_t data_align_type){

    if (channel_id > DAC_CHANNEL2 || data > 0xfff  || data_align_type > BIT8_RIGHT_ALIGN)
            return -1;
    
    dac_controls->dac_dhr12ld &= ~(DAC_DHR12LD_DACC1DHR << (16 * channel_id));
    dac_controls->dac_dhr12rd &= ~(DAC_DHR12RD_DACC1DHR << (16 * channel_id));
    dac_controls->dac_dhr8rd &= ~(DAC_DHR8RD_DACC1DHR << (16 * channel_id));

    switch (data_align_type)
    {
    case  BIT12_LEFT_ALIGN:
        dac_controls->dac_dhr12ld |= (data << (16 * channel_id + 4));
        break;

    case BIT12_RIGHT_ALIGN:
        dac_controls->dac_dhr12rd |= (data << (16 * channel_id));
        break;

    case BIT8_RIGHT_ALIGN:
        if (data > 0xff)
            return -1;
       dac_controls->dac_dhr8rd |= (data << (8 * channel_id));
        break;
    
    }

    return 0;

}


int32_t DAC_software_trigger(uint8_t channel_id, bool trigger){

    if (channel_id > DAC_CHANNEL2)
        return -1;

    if (trigger)
        dac_controls->dac_swtrigr |= (1 << channel_id);
    else
        dac_controls->dac_swtrigr &= ~(1 << channel_id);
    
    return 0;

}


int32_t DAC_software_dualtrigger(bool trigger){

    if (trigger)
        dac_controls->dac_swtrigr |= 0x3;
    else
        dac_controls->dac_swtrigr &= ~0x3;
    
    return 0;

}




