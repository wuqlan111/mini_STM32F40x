
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
#define  DMA_SXCR_REG_ADDR(dma, stream)        (DMA_STREAM_REGS_BASE_ADDR(dma) + 0x18 * (steam))
#define  DMA_SXNDTR_REG_ADDR(dma, stream)      (DMA_STREAM_REGS_BASE_ADDR(dma) + 0x18 * (steam) + 0x4u)
#define  DMA_SXPAR_REG_ADDR(dma, stream)       (DMA_STREAM_REGS_BASE_ADDR(dma) + 0x18 * (steam) + 0x8u)
#define  DMA_SXM0AR_REG_ADDR(dma, stream)      (DMA_STREAM_REGS_BASE_ADDR(dma) + 0x18 * (steam) + 0xCu)
#define  DMA_SXM1AR_REG_ADDR(dma, stream)      (DMA_STREAM_REGS_BASE_ADDR(dma) + 0x18 * (steam) + 0x10u)
#define  DMA_SXFCR_REG_ADDR(dma, stream)       (DMA_STREAM_REGS_BASE_ADDR(dma) + 0x18 * (steam) + 0x14u)


int32_t  get_stream_interrupt(uint8_t stream_idx){

    int32_t  int_status = 0, reg_value;

    if (stream_idx > MAX_DMA_STREAM_ID)
        return -1;
    
    reg_value = stream_idx > 3?dma_interrupt_control->dma_hisr:dma_interrupt_control->dma_lisr;

    switch (stream_idx & 0x4)
    {
    case   0:
        int_status = reg_value & 0x3f;
        break;
    
    case   1:
        int_status = (reg_value >> 6) & 0x3f;
        break;

    case   2:
        int_status = (reg_value >> 16) & 0x3f;
        break;


    case   3:
        int_status = (reg_value >> 22) & 0x3f;
        break;

    }

    return  int_status;


}



int32_t  clear_stream_interrupt(uint8_t stream_idx,  uint32_t int_mask){

    int32_t  int_clear = 0, reg_value;

    if (stream_idx > MAX_DMA_STREAM_ID  ||   (int_mask & ~DMA_ALLC_INT))
        return -1;
    

    switch (stream_idx & 0x4){

    case   0:
        int_clear = int_mask;
        break;
    
    case   1:
        int_clear = int_mask << 6;
        break;

    case   2:
        int_clear = int_mask << 16;
        break;

    case   3:
        int_clear = int_mask << 22;
        break;

    }


    if (stream_idx > 3)
        dma_interrupt_control->dma_lifcr |= int_clear;
    else
        dma_interrupt_control->dma_hifcr |= int_clear;

    return  0;

}




inline int32_t  enable_stream_interrupt( uint8_t stream_idx,  uint32_t  int_mask){

    if (stream_idx > MAX_DMA_STREAM_ID  ||  (int_mask & ~DMA_ALL_INTERRUPTE))
        return -1;


    dma_all_stream[stream_idx]->dma_sxcr |= (int_mask & 0xf);
    
    dma_all_stream[stream_idx]->dma_sxfcr |= (int_mask & 0xf0);

    return 0;

}


inline int32_t  disable_stream_interrupt( uint8_t stream_idx,  uint32_t int_mask){

    if (stream_idx > MAX_DMA_STREAM_ID  ||  (int_mask & ~DMA_ALL_INTERRUPTE))
        return -1;


    dma_all_stream[stream_idx]->dma_sxcr &= ~(int_mask & 0xf);
    
    dma_all_stream[stream_idx]->dma_sxfcr &= ~(int_mask & 0xf0);

    return 0;

}








