
#include  <stdlib.h>
#include  <memory.h>

#include  "../include/can.h"
#include  "util.h"

#define  CAN_MCR_DBF        (1<<16)         // CAN transmission frozen during debug
#define  CAN_MCR_RESET      (1<<15)         // force a master reset of the bxCAN
#define  CAN_MCR_TTCM        (1<<7)         // enable time triggered communication mode 
#define  CAN_MCR_ABOM       (1<<6)          // Bus-Off state is left automatically by hardware
#define  CAN_MCR_AWUM       (1<<5)          // sleep mode is left automatically by hardware
#define  CAN_MCR_NART       (1<<4)          // transmit message only once
#define  CAN_MCR_RFLM       0x8             // receive FIFO locked against overrun
#define  CAN_MCR_TXFP       0x4             // priority driven by the request order
#define  CAN_MCR_SLEEP      0x2             // sleep mode request
#define  CAN_MCR_INRQ       0x1             // initialization request


#define  CAN_MSR_RX         (1<<11)         // CAN Rx signal
#define  CAN_MSR_SAMP       (1<<10)         // last sample point
#define  CAN_MSR_RXM        (1<<9)          // receive mode
#define  CAN_MSR_TXM           (1<<8)           // the CAN hardware is currently transmitter
#define  CAN_MSR_SLAKI          (1<<4)          // sleep acknowledge interrupt
#define  CAN_MSR_WKUI          0x8              // wakeup interrupt
#define  CAN_MSR_ERRI       0x4             // error interrupt
#define  CAN_MSR_SLAK       0x2            // sleep acknowl
#define  CAN_MSR_INAK          0x1          // initialization acknowledgeedge


#define  CAN_TSR_LOW2       (1<<31u)        // lowest priority flag for mailbox 2
#define  CAN_TSR_LOW1       (1<<30)         // lowest priority flag for mailbox 1
#define  CAN_TSR_LOW0       (1<<29)         // lowest priority flag for mailbox 0
#define  CAN_TSR_TME2       (1<<28)         // transmit mailbox 2 empty
#define  CAN_TSR_TME1       (1<<27)         // transmit mailbox 1 empty
#define  CAN_TSR_TME0       (1<<26)         // transmit mailbox 0 empty
#define  CAN_TSR_CODE       (0x3<<24)           // mailbox code

#define  CAN_TSR_ABRQ0          (1<<7)              // abort request for mailbox0
#define  CAN_TSR_TERR0          0x8                 // transmission error of mailbox0
#define  CAN_TSR_ALST0          0x4                 // arbitration lost for mailbox0
#define  CAN_TSR_TXOK0          0x2                 // transmission OK of mailbox0
#define  CAN_TSR_RQCP0          0x1                 // request completed mailbox0

#define  CAN_RF0R_RFOM0        (1<<5)           // release FIFO 0 output mailbox
#define  CAN_RF0R_FOVR0         (1<<4)          // FIFO 0 overrun
#define  CAN_RF0R_FULL0         0x8             // FIFO 0 full
#define  CAN_RF0R_FMP0          0x3             // FIFO 0 message pending

#define  CAN_IER_SLKIE          (1<<17u)
#define  CAN_IER_WKUIE          (1<<16u)
#define  CAN_IER_ERRIE          (1<<15u)
#define  CAN_IER_LECIE          (1<<11u)
#define  CAN_IER_BOFIE          (1<<10u)
#define  CAN_IER_EPVIE          (1<<9u)
#define  CAN_IER_EWGIE          (1<<8u)
#define  CAN_IER_TMEIE          (0x1u)


#define  CAN_ESR_REC           (0xff<<24)           // receive error counter
#define  CAN_ESR_TEC            (0xff<<16)          // least significant byte of the 9-bit transmit error counter
#define  CAN_ESR_LEC            (0x7<<4)            // last error code
#define  CAN_ESR_BOFF           0x4             // Bus-off flag
#define  CAN_ESR_EPVF           0x2             // error passive flag
#define  CAN_ESR_EWGF           0x1         // error warning flag


#define  CAN_BTR_SILM       (1<<31u)             // silent mode
#define  CAN_BTR_LBKM       (1<<30)             // enable loop back mode 
#define  CAN_BTR_SJW        (0x3<<24)           // resynchronization jump width
#define  CAN_BTR_TS2        (0x7<<20)           // time segment 2
#define  CAN_BTR_TS1        (0xf<<16)           // time segment 1
#define  CAN_BTR_BRP        (0x3ff)                 // baud rate prescaler


#define  CAN_TIxR_STID         (0x7ff<<21u)         // standard identifier or extended identifier
#define  CAN_TIxR_EXID          (0x1fffffff<<3)        // extended identifier
#define  CAN_TIxR_IDE       0x4                 // identifier extension
#define  CAN_TIxR_RTR       0x2             // remote transmission request
#define  CAN_TIxR_TXRQ      0x1             // transmit mailbox request
#define  CAN_TDTxR_TIME         (0xffff<<16u)            // message time stamp
#define  CAN_TDTxR_TGT          (1<<8)                  // transmit global time
#define  CAN_TDTxR_DLC          0x7                     // data length code
#define CAN_TDLxR_DATA0         0xff        // data byte 0
#define CAN_TDHxR_DATA4         0xff        // data byte 4


#define CAN_RIxR_STID           (0x7ff<<21u)            // standard identifier or extended identifier
#define CAN_RIxR_EXID           (0x3ffff<<3)            // extended identifier
#define CAN_RIxR_IDE            0x4                 // identifier extension
#define CAN_RIxR_RTR            0x2                 // remote transmission request
#define CAN_RDTxR_TIME          (0xffff<<16u)           // message time stamp
#define CAN_RDTxR_FMI           0xff00                  // filter match index
#define CAN_RDTxR_DLC           0xf                 // data length code
#define  CAN_RDLxR_DATA0        0xff                // data Byte 0
#define  CAN_RDHxR_DATA4        0xff                // data Byte 4



#define  CAN_FMR_CAN2SB         (0x3f<<8)           // CAN2 start bank
#define  CAN_FMR_FINIT          0x1             // filter init mode
#define  CAN_FM1R_FBM0          0x1             // filter bank in identifier list mode
#define  CAN_FS1R_FSC0      0x1             // single 32-bit scale configuratio
#define  CAN_FFA1R_FFA0     0x1                     // filter assigned to FIFO 1
#define  CAN_FA1R_FACT0       0x1               //  filter 0 is active
#define  CAN_FIRx_FB0           0x1             // recessive bit is expected or identifier must match


#define  CAN_REGS_BASE             (0x40006400u)
#define  CAN_REGS_STEP             (0x400u)

#define  CAN_MCR_REG_ADDR(n)         (CAN_REGS_BASE + CAN_REGS_STEP * (n))
#define  CAN_MSR_REG_ADDR(n)         (CAN_REGS_BASE + CAN_REGS_STEP * (n) +  0x4)
#define  CAN_TSR_REG_ADDR(n)         (CAN_REGS_BASE + CAN_REGS_STEP * (n) +  0x8)
#define  CAN_RF0R_REG_ADDR(n)        (CAN_REGS_BASE + CAN_REGS_STEP * (n) +  0xc)
#define  CAN_RF1R_REG_ADDR(n)        (CAN_REGS_BASE + CAN_REGS_STEP * (n) +  0x10)
#define  CAN_IER_REG_ADDR(n)         (CAN_REGS_BASE + CAN_REGS_STEP * (n) +  0x14)
#define  CAN_ESR_REG_ADDR(n)         (CAN_REGS_BASE + CAN_REGS_STEP * (n) +  0x18)
#define  CAN_BTR_REG_ADDR(n)         (CAN_REGS_BASE + CAN_REGS_STEP * (n) +  0x1c)

#define  MAILBOX_REGS_STEP               (0x10u)
#define  CAN_TIXR_REG_ADDR(n, mailbox)         (CAN_REGS_BASE + CAN_REGS_STEP * (n) + MAILBOX_REGS_STEP *(mailbox) + 0x180)
#define  CAN_TDTXR_REG_ADDR(n, mailbox)        (CAN_REGS_BASE + CAN_REGS_STEP * (n) + MAILBOX_REGS_STEP *(mailbox) + 0x184)
#define  CAN_TDLXR_REG_ADDR(n, mailbox)        (CAN_REGS_BASE + CAN_REGS_STEP * (n) + MAILBOX_REGS_STEP *(mailbox) + 0x188)
#define  CAN_TDHXR_REG_ADDR(n, mailbox)        (CAN_REGS_BASE + CAN_REGS_STEP * (n) + MAILBOX_REGS_STEP *(mailbox) + 0x18c)

#define  FIFO_REGS_STEP               (0x10u)
#define  CAN_RIXR_REG_ADDR(n, fifo)         (CAN_REGS_BASE + CAN_REGS_STEP * (n) + FIFO_REGS_STEP *(fifo) + 0x1b0)
#define  CAN_RDTXR_REG_ADDR(n, fifo)        (CAN_REGS_BASE + CAN_REGS_STEP * (n) + FIFO_REGS_STEP *(fifo) + 0x1b4)
#define  CAN_RDLXR_REG_ADDR(n, fifo)        (CAN_REGS_BASE + CAN_REGS_STEP * (n) + FIFO_REGS_STEP *(fifo) + 0x1b8)
#define  CAN_RDHXR_REG_ADDR(n, fifo)        (CAN_REGS_BASE + CAN_REGS_STEP * (n) + FIFO_REGS_STEP *(fifo) + 0x1bc)


#define  CAN_FMR_REG_ADDR               (CAN_REGS_BASE + 0x200)
#define  CAN_FM1R_REG_ADDR              (CAN_REGS_BASE + 0x204)
#define  CAN_FS1R_REG_ADDR              (CAN_REGS_BASE + 0x20c)
#define  CAN_FFA1R_REG_ADDR             (CAN_REGS_BASE + 0x214)
#define  CAN_FA1R_REG_ADDR              (CAN_REGS_BASE + 0x21c)
#define  CAN_FXR1_REG_ADDR(filter)      (CAN_REGS_BASE  +  (filter) * 0x8 + 0x240)
#define  CAN_FXR2_REG_ADDR(filter)      (CAN_REGS_BASE  +  (filter) * 0x8 + 0x244)


int32_t  can_global_init(uint32_t  can_id, can_config_t * config)
{
    uint32_t  flag, mask;
    flag  =  mask = 0;
    if ((can_id > CAN_MAX_ID ) || !config)
        return -1;
    
    if (config->debug_freeze) {
        flag |= CAN_MCR_DBF;
    }

    if (config->time_trigger_mode) {
        flag |= CAN_MCR_TTCM;
    }

    if (config->auto_bus_off) {
        flag |= CAN_MCR_ABOM;
    }

    if (config->auto_wakeup) {
        flag |= CAN_MCR_AWUM;
    }

    if (!config->auto_retrans) {
        flag |=  CAN_MCR_NART;
    }

    if (config->rx_fifo_lock_mode) {
        flag |= CAN_MCR_RFLM;
    }

    if (!config->tx_fifo_priority_identifier) {
        flag |= CAN_MCR_TXFP;
    }

    mask =  CAN_MCR_DBF | CAN_MCR_TTCM | CAN_MCR_ABOM | CAN_MCR_AWUM 
                | CAN_MCR_NART | CAN_MCR_RFLM | CAN_MCR_TXFP;

    REG32_UPDATE(CAN_MCR_REG_ADDR(can_id), flag,  mask);

    return  0;

}




int32_t  can_set_global_interrupt(uint32_t  can_id,  can_global_interrupt_config_t * config)
{
    uint32_t  flag, mask;
    flag  =  mask = 0;
    if ((can_id > CAN_MAX_ID ) || !config)
        return -1;
    
    if (config->sleep_interrupt_enable) {
        flag |= CAN_IER_SLKIE;
    }

    if (config->wakeup_interrupt_enable) {
        flag |= CAN_IER_WKUIE;
    }

    if (config->error_interrupt_enable) {
        flag |= CAN_IER_ERRIE;
    }

    if (config->last_error_interrupt_enable) {
        flag  |=  CAN_IER_LECIE;
    }

    if (config->bus_off_interrupt_enable) {
        flag |=  CAN_IER_BOFIE;
    }

    if (config->error_passive_interrupt_enable) {
        flag |= CAN_IER_EPVIE;
    }

    if (config->error_warning_interrupt_enable) {
        flag |= CAN_IER_EWGIE;
    }

    if (config->tx_empty_interrupt_enable) {
        flag |= CAN_IER_TMEIE;
    }

    mask = (0x7 << 15) | (0xf << 8) | 0x1;

    REG32_UPDATE(CAN_IER_REG_ADDR(can_id), flag,  mask);
    return  0;

}





int32_t  can_set_rxfifo_interrupt(uint32_t  can_id,  can_rxfifo_interrupt_config_t * config)
{
    uint32_t  flag, mask;
    flag  =  mask = 0;
    if ((can_id > CAN_MAX_ID ) || !config || (config->rx_fifo > FIFO_MAX_ID))
        return -1;


    if (config->fifo_overrun_interrupt_enable) {
        flag |= 1<<2;
    }

    if (config->fifo_full_interrupt_enable) {
        flag  |= 1<<1;
    }

    if (config->fifo_pending_interrupt_enable) {
        flag |= 0x1;
    }

    flag  =  config->rx_fifo  ==  RX_FIFO0? flag << 1: flag << 4;
    mask  =  config->rx_fifo  ==  RX_FIFO0? 0x7 << 1:  0x7 << 4;
    REG32_UPDATE(CAN_IER_REG_ADDR(can_id),  flag,  mask);

    return  0;

}


inline  void  reset_can_master(uint32_t can_id)
{
    if (can_id > CAN_MAX_ID ) {
        return;
    }
    REG32_UPDATE(CAN_MCR_REG_ADDR(can_id), CAN_MCR_RESET,  CAN_MCR_RESET);
}



inline  void  enter_or_exit_sleep_mode(uint32_t can_id,  uint32_t  enter)
{
    uint32_t  flag = 0;
    if (can_id > CAN_MAX_ID ) {
        return;
    }

    flag  =  enter ? 0x2:  0;
    REG32_UPDATE(CAN_MCR_REG_ADDR(can_id), flag, 0x2);

}


inline  void  enter_or_exit_initialization_mode(uint32_t can_id, uint32_t enter)
{
    uint32_t  flag = 0;
    if (can_id > CAN_MAX_ID ) {
        return;
    }
    flag  =  enter ? 0x1:  0;
    REG32_UPDATE(CAN_MCR_REG_ADDR(can_id), flag, 0x1);

}


int32_t  set_filter_bank(uint32_t can_id,  can_filter_config_t * config)
{
    if (can_id > CAN_MAX_ID || !config || (config->bank >= FILTER_BANK_NUMBER )) {
        return  -1;
    }

    if (config->mask_mode) {
        REG32_UPDATE(CAN_FM1R_REG_ADDR, 0,  1 << config->bank);
    } else {
        REG32_UPDATE(CAN_FM1R_REG_ADDR, 1 << config->bank,  1 << config->bank);
    }

    if (config->scale_32bit) {
        REG32_UPDATE(CAN_FM1R_REG_ADDR, 1 << config->bank, 1 << config->bank);
    } else {
        REG32_UPDATE(CAN_FM1R_REG_ADDR, 0,  1 << config->bank);
    }

    if (config->assign_fifo0) {
        REG32_UPDATE(CAN_FM1R_REG_ADDR, 0,  1 << config->bank);
    } else {
        REG32_UPDATE(CAN_FM1R_REG_ADDR, 1 << config->bank,  1 << config->bank);
    }

    REG32_WRITE(CAN_FXR1_REG_ADDR(config->bank), config->filter0);
    REG32_WRITE(CAN_FXR2_REG_ADDR(config->bank), config->filter1);

    return  0;

}


int32_t  enable_or_disable_filter(uint32_t bank_id, uint32_t  enable)
{
    uint32_t  flag = 0;
    if (bank_id >=  FILTER_BANK_NUMBER) {
        return  -1;
    }

    flag = enable? 1 << bank_id: 0;
    REG32_UPDATE(CAN_FA1R_REG_ADDR, flag,  1 << bank_id);
    return  0;
}


int32_t  send_can_message(uint32_t can_id, uint32_t mailbox_id, can_txmsg_t * msg)
{
    uint32_t  flag = 0;
    if ((can_id > CAN_MAX_ID) || (mailbox_id > MAILBOX_MAX_ID) || !msg  
            || (msg->data_len > MAX_DATA_LEN)) {
        return  -1;
    }

    flag  =  (msg->data[3] << 24) | (msg->data[2] << 16) | (msg->data[1] << 8 )| msg->data[0];
    REG32_WRITE(CAN_TDLXR_REG_ADDR(can_id, mailbox_id), flag);

    if (msg->data_len > 4) {
        flag  =  (msg->data[7] << 24) | (msg->data[6] << 16) | (msg->data[5] << 8 )| msg->data[4];
        REG32_WRITE(CAN_TDHXR_REG_ADDR(can_id, mailbox_id), flag);
    }

    flag = 0;
    if (msg->trans_time) {
        flag = (msg->time_stamp << 16) | (1 << 8) | 0x8;
    } else {
        flag = msg->data_len;
    }

    REG32_WRITE(CAN_TDTXR_REG_ADDR(can_id,  mailbox_id), flag);

    if (msg->stid) {
        flag = (msg->stid << 21) | 0x1;
    } else {
        flag = (msg->stid << 3) | (1 << 2) | 0x1;
    }

    if (!msg->data_frame) {
        flag  |= (1<<1);
    }

    REG32_WRITE(CAN_TIXR_REG_ADDR(can_id, mailbox_id), flag);

    return  0;

}


int32_t  read_can_message(uint32_t can_id, uint32_t fifo_id, can_rxmsg_t * msg)
{
    uint32_t  flag = 0;
    if ((can_id > CAN_MAX_ID) || (fifo_id > FIFO_MAX_ID) || !msg ) {
        return  -1;
    }

    memset(msg,  0,  sizeof(can_rxmsg_t));

    flag = REG32_READ(CAN_RIXR_REG_ADDR(can_id, fifo_id));

    msg->data_frame = flag & CAN_RIxR_RTR? 0: 1;
    msg->std_identifier  =  flag &  CAN_RIxR_IDE? 0: 1;
    msg->stid  =  msg->std_identifier? flag >> 21: flag >> 3;

    flag  =  REG32_READ(CAN_RDTXR_REG_ADDR(can_id, fifo_id));
    msg->time_stamp  =  flag >> 16;
    msg->filter_index  =  (flag >> 8) & 0xff;
    msg->data_len  = flag & 0xf;

    flag = REG32_READ(CAN_RDLXR_REG_ADDR(can_id, fifo_id));
    msg->data[0]  =  flag  & 0xff;
    msg->data[1]  =  (flag >> 8) & 0xff;
    msg->data[2]  =  (flag >> 16) & 0xff;
    msg->data[3]  =  flag >> 24;

    if (msg->data_len > 4) {
        flag = REG32_READ(CAN_RDHXR_REG_ADDR(can_id, fifo_id));
        msg->data[4]  =  flag  & 0xff;
        msg->data[5]  =  (flag >> 8) & 0xff;
        msg->data[6]  =  (flag >> 16) & 0xff;
        msg->data[7]  =  flag >> 24;
    }

    return  0;

}









