
#include  <stdlib.h>
#include  "../include/dma.h"


#define  DMA_LISR_TCIF0             (1<<5)              // stream 0 transfer complete interrupt flag
#define  DMA_LISR_HTIF0             (1<<4)              // stream 0 half transfer interrupt flag
#define  DMA_LISR_TEIF0             0x8                 // stream 0 transfer error interrupt flag
#define  DMA_LISR_DMEIF0            0x4                 // stream 0 direct mode error interrupt flag
#define  DMA_LISR_FEIF0             0x1                 // stream 0 FIFO error interrupt flag 

#define  DMA_LIFCR_CTCIF0           (1<<5)                     // stream 0 clear transfer complete interrupt flag 
#define  DMA_LIFCR_CHTIF0           (1<<4)                     // stream 0 clear half transfer interrupt flag
#define  DMA_LIFCR_CTEIF0           0x8                        // stream x clear transfer error interrupt flag
#define  DMA_LIFCR_CDMEIF0          0x4                      // stream x clear direct mode error interrupt flag
#define  DMA_LIFCR_CFEIF0           0x1                     //  stream x clear FIFO error interrupt flag
#define  DMA_ALLC_INT               0x3d

#define  DMA_SxCR_CHSEL         (0x7<<25)                   // Channel selection
#define  DMA_SxCR_MBURST        (0x3<<23)                   // memory burst transfer configuration
#define  DMA_SxCR_PBURST        (0x3<<21)                   // peripheral burst transfer configuration
#define  DMA_SxCR_CT            (1<<19)                     // current target memory is memory 1
#define  DMA_SxCR_DBM           (1<<18)                     // double buffer mode
#define  DMA_SxCR_PL            (0x3<<16)                   // priority level
#define  DMA_SxCR_PINCOS            (1<<15)                 // peripheral increment offset size
#define  DMA_SxCR_MSIZE             (0x3<<13)                   // memory data size
#define  DMA_SxCR_PSIZE             (0x3<<11)                   // peripheral data size
#define  DMA_SxCR_MINC              (1<<10)                     // memory increment mode
#define  DMA_SxCR_PINC              (1<<9)                      // peripheral increment mode
#define  DMA_SxCR_CIRC              (1<<8)                      // circular mode enable
#define  DMA_SxCR_DIR               (0x3<<6)                    // data transfer direction
#define  DMA_SxCR_PFCTRL            (1<<5)                      // the peripheral is the flow controller
#define  DMA_SxCR_TCIE              (1<<4)                         // transfer complete interrupt enable
#define  DMA_SxCR_HTIE              0x8                         // half transfer interrupt enable
#define  DMA_SxCR_TEIE              0x4                         // transfer error interrupt enable
#define  DMA_SxCR_DMEIE             0x2                         // direct mode error interrupt enable
#define  DMA_SxCR_EN                0x1                         // stream enabled
#define  DMA_ALL_INTERRUPTE        0x8e

#define  DMA_SxNDTR_NDT            0xffff                   // number of data items to transfer
#define  DMA_SxPAR_PAR          0xffffffff              // peripheral address
#define  DMA_SxM0AR_M0A         0xffffffff              // memory 0 address
#define  DMA_SxM1AR_M1A         0xffffffff              // memory 1 address


#define  DMA_SxFCR_FEIE             (1<<7)              // FIFO error interrupt enable
#define  DMA_SxFCR_FS               0x38                // FIFO status
#define  DMA_SxFCR_DMDIS            0x4                 // direct mode disable
#define  DMA_SxFCR_FTH              0x3                 // FIFO threshold selection

#define  DMA_REGS_STEP               (0x400u)
#define  DMA_REG_BASE_ADDR           (0x40026000u)

#define  DMA_LISR_REG_ADDR(dma)                (DMA_REG_BASE_ADDR + (dma) * DMA_REGS_STEP )
#define  DMA_HISR_REG_ADDR(dma)                (DMA_REG_BASE_ADDR + (dma) * DMA_REGS_STEP + 0x4u)
#define  DMA_LIFCR_REG_ADDR(dma)               (DMA_REG_BASE_ADDR + (dma) * DMA_REGS_STEP + 0x8u)
#define  DMA_HIFCR_REG_ADDR(dma)               (DMA_REG_BASE_ADDR + (dma) * DMA_REGS_STEP + 0xCu)
#define  DMA_STREAM_REGS_BASE_ADDR(dma)        (DMA_REG_BASE_ADDR + (dma) * DMA_REGS_STEP + 0x10u)
#define  DMA_SXCR_REG_ADDR(dma, stream)        (DMA_STREAM_REGS_BASE_ADDR(dma) + 0x18 * (stream))
#define  DMA_SXNDTR_REG_ADDR(dma, stream)      (DMA_STREAM_REGS_BASE_ADDR(dma) + 0x18 * (stream) + 0x4u)
#define  DMA_SXPAR_REG_ADDR(dma, stream)       (DMA_STREAM_REGS_BASE_ADDR(dma) + 0x18 * (stream) + 0x8u)
#define  DMA_SXM0AR_REG_ADDR(dma, stream)      (DMA_STREAM_REGS_BASE_ADDR(dma) + 0x18 * (stream) + 0xCu)
#define  DMA_SXM1AR_REG_ADDR(dma, stream)      (DMA_STREAM_REGS_BASE_ADDR(dma) + 0x18 * (stream) + 0x10u)
#define  DMA_SXFCR_REG_ADDR(dma, stream)       (DMA_STREAM_REGS_BASE_ADDR(dma) + 0x18 * (stream) + 0x14u)


int32_t  DMA_steam_config(uint32_t dma_id, uint32_t  stream_id, DMA_stream_config_t * config)
{

    uint32_t  flag, mask;
    flag = mask = 0;
    if ( (dma_id > DMA_MAX_ID) || (stream_id >= DMA_STREAM_NUMBER) || !config) {
        return  -1;
    }

    if ( (config->memory_data_size > DMA_DATA_MAX_SIZE) || 
                (config->peripheral_data_size > DMA_DATA_MAX_SIZE)) {
        return  -1;

    }

    if (config->data_transfer_direction >  DMA_TRANSFER_MAX_DIRECTION) {
        return  -1;
    }

    flag  |=  config->channel << 25;
    flag  |=  config->memory_burst << 23;
    flag  |=  config->peripheral_burst  << 21;
    flag  |=  config->priority << 16;
    flag  |=  config->memory_data_size  << 13;
    flag  |=  config->peripheral_data_size  << 13;
    flag  |=  config->data_transfer_direction << 6;

    if (!config->memory0) {
        flag  |=  1<<19;
    }

    if (config->double_buffer_mode) {
        flag |=  1<<18;
    }

    if (config->memory_incr_fixed) {
        flag |= 1<<10;
    }    

    if (config->peripheral_incr_fixed) {
        flag  |= 1<<15;
    }

    if (config->circular_mode) {
        flag  |=  1<<8;
    }

    if (config->peripheral_flow_controller) {
        flag |= 1<<5;
    }

    if (config->transfer_complete_interrupt_enable) {
        flag |= 1<<4;
    }

    if (config->half_transfer_interrupt_enable) {
        flag  |=  1<<3;
    }

    if (config->transfer_error_interrupt_enable) {
        flag |=  1<<2;
    }

    if (config->direct_error_interrupt_enable) {
        flag |=  0x2;
    }

    mask  =  0xfeffffe;

    REG32_UPDATE(DMA_SXCR_REG_ADDR(dma_id, stream_id),  flag,  mask);
    return  0;
}



int32_t  DMA_fifo_config(uint32_t dma_id, uint32_t  stream_id, DMA_fifo_config_t * config)
{
    uint32_t  flag, mask;
    flag = mask = 0;
    if ( (dma_id > DMA_MAX_ID) || (stream_id >= DMA_STREAM_NUMBER) || !config) {
        return  -1;
    }

    flag  |= config->fifo_threshold;

    if (config->fifo_error_interrupt_enable) {
        flag |= 1<<7;
    }

    if (config->direct_mode_disable) {
        flag |=  1<<2;
    }

    mask = 0x87;

    REG32_UPDATE(DMA_SXFCR_REG_ADDR(dma_id, stream_id), flag, mask);
    return 0;

}



int32_t  enable_or_disable_DMA_stream(uint32_t dma_id, uint32_t  stream_id, uint32_t enable)
{
    uint32_t  flag = 0;
    if ( (dma_id > DMA_MAX_ID) || (stream_id >= DMA_STREAM_NUMBER)) {
        return  -1;
    }

    flag = enable? 0x1: 0;
    REG32_UPDATE(DMA_SXCR_REG_ADDR(dma_id, stream_id), flag,  0x1);
    return  0;

}










