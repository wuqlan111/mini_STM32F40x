
#include  <stdlib.h>
#include  <string.h>
#include  <memory.h>

#include  "../include/driver_util.h"
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


#define  DMA_FIFO_SIZE            16


static  int32_t  get_dma_data_len(dma_data_size_e  dma_size,  uint32_t * bytes)
{
    CHECK_PARAM_NULL(bytes);
    CHECK_PARAM_VALUE(dma_size,   DMA_DATA_MAX_SIZE);

    *bytes  =  0;
    switch (dma_size) {
        case  DMA_DATA_SIZE_BYTE:
            * bytes  =  1;
            break;

        case  DMA_DATA_SIZE_HALF_WORD:
            * bytes  =  2;
            break;
        
        case  DMA_DATA_SIZE_WORD:
            * bytes  =  4;
            break;
    }

    return   0;

}



static  int32_t  get_dma_transfer_burst(dma_transfer_busrt_e  dma_burst,  uint32_t * burst)
{
    CHECK_PARAM_NULL(burst);
    CHECK_PARAM_VALUE(dma_burst,   DMA_MAX_TRANSFER);

    *burst  =  0;
    switch (dma_burst) {
        case  DMA_SINGLE_TRANSFER:
            * burst  =  1;
            break;

        case  DMA_INCR4_TRANSFER:
            * burst  =  4;
            break;

        case  DMA_INCR8_TRANSFER:
            * burst  =  8;
            break;

        case  DMA_INCR16_TRANSFER:
                * burst  =  16;
                break;
    }

    return   0;

}


static  int32_t  get_dma_fifo_threshold(dma_fifo_threshold_e  fifo_threshold,  uint32_t * size)
{
    CHECK_PARAM_NULL(size);
    CHECK_PARAM_VALUE(fifo_threshold,   DMA_FIFO_MAX_THRESHOLD);

    *size  =  0;
    switch (fifo_threshold) {
        case  DMA_FIFO_THRESHOLD_1_4:
            * size  =  DMA_FIFO_SIZE / 4;
            break;

        case  DMA_FIFO_THRESHOLD_2_4:
            * size  =  DMA_FIFO_SIZE / 2;
            break;

        case  DMA_FIFO_THRESHOLD_3_4:
            * size  =  DMA_FIFO_SIZE * 3 / 4;
            break;

        case  DMA_FIFO_THRESHOLD_FULL:
            * size  =  DMA_FIFO_SIZE;
            break;
    }

    return   0;

}






int32_t  DMA_steam_config(uint32_t dma_id, uint32_t  stream_id, DMA_stream_config_t * config)
{

    uint32_t  flag, mask;
    flag = mask = 0;

    CHECK_PARAM_VALUE(dma_id,  DMA_MAX_ID);
    CHECK_PARAM_VALUE(stream_id,  DMA_STREAM_NUMBER - 1);
    CHECK_PARAM_NULL(config);

    CHECK_PARAM_VALUE(config->memory_data_size,   DMA_DATA_MAX_SIZE);
    CHECK_PARAM_VALUE(config->peripheral_data_size,   DMA_DATA_MAX_SIZE);
    CHECK_PARAM_VALUE(config->data_transfer_direction,   DMA_TRANSFER_MAX_DIRECTION);


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


    mask  =  0xfefffe0;

    REG32_UPDATE(DMA_SXCR_REG_ADDR(dma_id, stream_id),  flag,  mask);
    return  0;
}



int32_t  DMA_fifo_config(uint32_t dma_id, uint32_t  stream_id, DMA_fifo_config_t * config)
{
    uint32_t  flag, mask;
    flag = mask = 0;

    CHECK_PARAM_NULL(config);
    CHECK_PARAM_VALUE(dma_id,  DMA_MAX_ID);
    CHECK_PARAM_VALUE(stream_id,  DMA_STREAM_NUMBER - 1);

    flag  =  REG32_READ(DMA_SXCR_REG_ADDR(dma_id, stream_id));

    dma_data_size_e   psize  =  (flag &  DMA_SxCR_PSIZE) >> 11;
    dma_data_size_e   msize  =  (flag &  DMA_SxCR_MSIZE) >> 13;
    dma_data_size_e   dma_size  =  config->direct_mode_disable? msize: psize;

    uint32_t  dma_data_size, dma_burst, fifo_threshold;
    dma_data_size  =  dma_size  =  fifo_threshold  =  0;
    if (get_dma_data_len(dma_size,  &dma_data_size)) {
        return  -1;
    }

    dma_transfer_busrt_e  mburst =  ( flag & DMA_SxCR_MBURST ) >> 23;
    dma_transfer_busrt_e  pburst =  ( flag & DMA_SxCR_PBURST ) >> 21;
    dma_transfer_busrt_e  burst  =  config->direct_mode_disable? mburst: pburst;

    if (get_dma_transfer_burst(burst,  &dma_burst)) {
        return  -1;
    }

    if (get_dma_fifo_threshold(config->fifo_threshold,  &fifo_threshold)) {
        return  -1;
    }

    uint32_t  burst_size_byte   =  dma_burst * dma_data_size;

    if (fifo_threshold % burst_size_byte) {
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



int32_t  DMA_data_transfer_config(uint32_t dma_id, uint32_t  stream_id, DMA_data_transfer_config_t * config)
{
    uint32_t  flag = 0;

    CHECK_PARAM_VALUE(dma_id,  DMA_MAX_ID);
    CHECK_PARAM_VALUE(stream_id,  DMA_STREAM_NUMBER - 1);
    CHECK_PARAM_NULL(config);

    CHECK_PARAM_VALUE(config->len,  0xffff);

    REG32_WRITE(DMA_SXPAR_REG_ADDR(dma_id, stream_id),   config->peripheral_addr);
    REG32_WRITE(DMA_SXM0AR_REG_ADDR(dma_id, stream_id),  config->memory0_addr);
    REG32_WRITE(DMA_SXM1AR_REG_ADDR(dma_id, stream_id),  config->memory1_addr);
    REG32_WRITE(DMA_SXNDTR_REG_ADDR(dma_id, stream_id),  config->len);

    return   0;

}



int32_t  enable_or_disable_DMA_stream(uint32_t dma_id, uint32_t  stream_id, uint32_t enable)
{
    uint32_t  flag = 0;

    CHECK_PARAM_VALUE(dma_id,  DMA_MAX_ID);
    CHECK_PARAM_VALUE(stream_id,  DMA_STREAM_NUMBER - 1);

    flag = enable? 0x1: 0;
    REG32_UPDATE(DMA_SXCR_REG_ADDR(dma_id, stream_id), flag,  0x1);

    REG32_WAIT(DMA_SXCR_REG_ADDR(dma_id, stream_id), flag,  0x1);

    return  0;

}





