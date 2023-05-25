

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

#define  DAC_REG_BASE             (0x40007400u)
#define  DAC_CR_REG_ADDR                  (DAC_REG_BASE)
#define  DAC_SWTRIGR_REG_ADDR             (DAC_REG_BASE + 0x4)
#define  DAC_DHR12RX_REG_ADDR(channel)             (DAC_REG_BASE + 0x8  + (channel) * 12)
#define  DAC_DHR12LX_REG_ADDR(channel)             (DAC_REG_BASE + 0xc  + (channel) * 12)
#define  DAC_DHR8RX_REG_ADDR(channel)              (DAC_REG_BASE + 0x10 + (channel) * 12)
#define  DAC_DHR12RD_REG_ADDR             (DAC_REG_BASE + 0x20)
#define  DAC_DHR12LD_REG_ADDR             (DAC_REG_BASE + 0x24)
#define  DAC_DHR8RD_REG_ADDR              (DAC_REG_BASE + 0x28)
#define  DAC_DORX_REG_ADDR(channel)       (DAC_REG_BASE + 0x2c + (channel) * 4)
#define  DAC_SR_REG_ADDR                  (DAC_REG_BASE + 0x34)


int32_t DAC_channel_config(uint32_t channel_id, DAC_channel_config_t *  config)
{
    uint32_t  flag, mask;
    flag = mask = 0;
    if (channel_id > DAC_MAX_CHANNEL || !config) {
        return -1;        
    }

    if (config->dma_underrun_interrupt_enable) {
        flag = 1<<13;
    }
    
    if (config->dma_enable) {
        flag |= ( 1 << 12);
    }

    flag |= (config->mask_selector << 8);
    flag |= (config->wave_generation << 6);
    flag |= (config->trigger_selector << 3);

    if (config->trigger_enable) {
        flag |= (1<<2);
    }

    if (config->output_buffer_enable) {
        flag |= 0x2;
    }

    mask = 0x3ffe;

    if (channel_id == DAC_CHANNEL2) {
        flag <<= 16;
        mask <<= 16;
    }

    REG32_UPDATE(DAC_CR_REG_ADDR, flag, mask);

    return 0;

}



int32_t  enable_or_disable_DAC_channel(uint32_t channel_id, uint32_t enable)
{
    uint32_t flag, mask;
    flag = mask = 0;
    if (channel_id > DAC_MAX_CHANNEL) {
        return -1;        
    }

    flag = enable? 1: 0;
    mask = 0x1;

    if (channel_id == DAC_CHANNEL2) {
        flag <<= 16;
        mask <<= 16;
    }

    REG32_UPDATE(DAC_CR_REG_ADDR, flag,  mask);
    
    return 0;
}


int32_t set_channel_data(uint32_t channel_id,  uint32_t data, uint32_t data_align_type)
{

    if ( (channel_id > DAC_MAX_CHANNEL) || (data > 0xfff) 
                || (data_align_type > DAC_MAX_DATA_ALIGN)) {
        return -1;        
    }

    if ((data_align_type == BIT8_RIGHT_ALIGN ) && (data > 0xff)) {
        return -1;
    }

    switch (data_align_type)
    {
    case  BIT12_LEFT_ALIGN:
        REG32_WRITE(DAC_DHR12LX_REG_ADDR(channel_id),  (data & 0xfff)<<4);
        break;

    case BIT12_RIGHT_ALIGN:
        REG32_WRITE(DAC_DHR12RX_REG_ADDR(channel_id),  data & 0xfff);
        break;

    case BIT8_RIGHT_ALIGN:
        REG32_WRITE(DAC_DHR8RX_REG_ADDR(channel_id),  data & 0xff);
        break;
    
    }

    return 0;

}

int32_t get_channel_outdata(uint32_t channel_id, uint32_t * data)
{
    uint32_t  val = 0;
    if ( (channel_id > DAC_MAX_CHANNEL)  || !data) {
        return -1;        
    }

    *data  =  REG32_READ(DAC_DORX_REG_ADDR(channel_id));
    return  0;

}



int32_t set_dualchannel_data(uint32_t channel_id,  uint32_t data, uint32_t data_align_type)
{

    if ( (channel_id > DAC_MAX_CHANNEL) || (data > 0xfff)  
                || (data_align_type > DAC_MAX_DATA_ALIGN) ) {
            return -1;
    }

    if ((data_align_type == BIT8_RIGHT_ALIGN) && (data  >  0xff)) {
        return  -1;
    }

    return 0;

}


int32_t DAC_software_trigger(uint32_t channel_id, uint32_t trigger)
{
    uint32_t  flag, mask;
    if (channel_id > DAC_MAX_CHANNEL) {
        return -1;        
    }

    flag  =  trigger? 1:  0;
    mask  = 0x1;

    if (channel_id  == DAC_CHANNEL2) {
        flag <<= 1;
        mask <<= 1;
    }

    REG32_UPDATE(DAC_SWTRIGR_REG_ADDR, flag,  mask);
    return 0;

}





