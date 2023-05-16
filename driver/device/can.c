
#include  <stdlib.h>

#include  "../include/can.h"

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



#define   CAN1_REG_BASE             0x40006400u
#define   CAN2_REG_BASE             0x40006800u
#define   CAN_CONTROL_OFFSET           0
#define   CAN_MAILBOX_OFFSET           0x180
#define   CAN_FILTER_OFFSET           0x200


typedef struct can_control{

    volatile uint32_t can_mcr;
    volatile uint32_t can_msr;
    volatile uint32_t can_tsr;
    volatile uint32_t can_rf0r;
    volatile uint32_t can_rf1r;
    volatile uint32_t can_ier;
    volatile uint32_t can_esr;
    volatile uint32_t can_btr;

}can_control_t;


typedef struct mailbox_reg{

    volatile uint32_t can_tixr;
    volatile uint32_t can_tdtxr;
    volatile uint32_t can_tdlxr;
    volatile uint32_t can_tdhxr;
}mailbox_reg_t;

typedef struct fifo_reg{
    volatile uint32_t can_rixr;
    volatile uint32_t can_rdtxr;
    volatile uint32_t can_rdlxr;
    volatile uint32_t can_rdhxr;
}fifo_reg_t;


typedef struct can_mailbox{
    mailbox_reg_t mailboxs[MAILBOX_NUMBER];
    fifo_reg_t  fifos[FIFO_NUMBER];
}can_mailbox_t;


typedef struct can_filter{
    volatile uint32_t can_fmr;
    volatile uint32_t can_fm1r;
    volatile uint32_t  reserve1;
    volatile uint32_t can_fs1r;
    volatile uint32_t  reserve2;
    volatile uint32_t can_ffa1r;
    volatile uint32_t  reserve3;
    volatile uint32_t can_fa1r;
    volatile uint32_t  reserve4;
    volatile uint32_t reserves[7];
    volatile uint32_t can_firx[ 2 * FILTER_BANK_NUMBER];
}can_filter_t;


can_control_t *  const  can_controls[CAN_NUMBER] = { (can_control_t *)CAN1_REG_BASE,
                                                (can_control_t *)CAN2_REG_BASE };
can_mailbox_t *  const  can_mailboxs[CAN_NUMBER] = { (can_control_t *)(CAN1_REG_BASE + CAN_MAILBOX_OFFSET),
                                                (can_control_t *)(CAN2_REG_BASE + CAN_MAILBOX_OFFSET) };
can_filter_t  * const  can_filters = (can_filter_t *)(CAN1_REG_BASE + CAN_FILTER_OFFSET);


int32_t  enable_CAN_interrupt(uint8_t can_id,  uint32_t int_mask){

    if ( (int_mask & ~CAN_ALL_INT) || can_id > CAN2)
        return -1;
    
    can_controls[can_id]->can_ier |= int_mask;
    return 0;

}

int32_t  disable_CAN_interrupt( uint8_t can_id, uint32_t int_mask){

    if ((int_mask & ~CAN_ALL_INT) || can_id > CAN2)
        return -1;
    
    can_controls[can_id]->can_ier &= ~int_mask;
    return 0;

}


int32_t  set_fileter_mode(uint8_t bank_id, bool mask_mode){

    if (bank_id >= FILTER_BANK_NUMBER)
        return -1;
    
    can_filters->can_fmr |= CAN_FMR_FINIT;
    if (mask_mode)
        can_filters->can_fm1r &= ~(1<<bank_id);
    else
        can_filters->can_fm1r |= (1<<bank_id);
    
    can_filters->can_fmr &= ~CAN_FMR_FINIT;
    return 0;
}



int32_t  set_fileter_sacle( uint8_t bank_id, bool dual_16bit){

    if (bank_id >= FILTER_BANK_NUMBER )
        return -1;
    
    can_filters->can_fmr |= CAN_FMR_FINIT;
    if (dual_16bit)
        can_filters->can_fs1r &= ~(1<<bank_id);
    else
        can_filters->can_fs1r |= (1<<bank_id);
    
    can_filters->can_fmr &= ~ CAN_FMR_FINIT;
    
    return 0;
}


int32_t  set_fileter_fifo(uint8_t bank_id, bool assign_fifo0){

    if (bank_id >= FILTER_BANK_NUMBER)
        return -1;
    
    can_filters->can_fmr |= CAN_FMR_FINIT;
    if (assign_fifo0)
        can_filters->can_ffa1r &= ~(1<<bank_id);
    else
        can_filters->can_ffa1r |= (1<<bank_id);
    
    can_filters->can_fmr &= ~CAN_FMR_FINIT;
    
    return 0;
}


int32_t  set_fileter_activation(uint8_t bank_id, bool active){

    if (bank_id >= FILTER_BANK_NUMBER)
        return -1;
    
    can_filters->can_fmr |= CAN_FMR_FINIT;
    if (active)
        can_filters->can_fs1r |= (1<<bank_id);
    else
        can_filters->can_fs1r &=  ~(1<<bank_id);
    
    can_filters->can_fmr &= ~CAN_FMR_FINIT;
    
    return 0;
}



int32_t  set_fileter_16identifier(uint8_t bank_id, uint16_t identifier, uint8_t id_num){

    if (bank_id >= FILTER_BANK_NUMBER  ||  id_num > 3 || (can_filters->can_fs1r & (1 << bank_id)) 
        ||  !(can_filters->can_fm1r & (1 << bank_id)))
        return -1;
    
    bool hbyte = id_num & 0x1;
    uint8_t idx =  id_num>1? (bank_id << 1) + 1:(bank_id << 1);

    can_filters->can_firx[idx] &= ~(0xffff << (hbyte));
    can_filters->can_firx[idx] |= ( identifier << (hbyte));
    
    return 0;
}


int32_t  set_fileter_32identifier(uint8_t bank_id, uint32_t identifier, uint8_t id_num){

    if (bank_id >= FILTER_BANK_NUMBER  ||  id_num > 1 || !(can_filters->can_fs1r & (1 << bank_id)) 
        ||  !(can_filters->can_fm1r & (1 << bank_id)))
        return -1;
    
    uint8_t idx =  id_num? (bank_id << 1) + 1:(bank_id << 1);

    can_filters->can_firx[idx] =  identifier;
    
    return 0;
}




int32_t  set_fileter_16mask(uint8_t bank_id, uint16_t identifier,  uint16_t mask, uint8_t id_num){

    if (bank_id >= FILTER_BANK_NUMBER  ||  id_num > 1 || (can_filters->can_fs1r & (1 << bank_id)) 
        ||  (can_filters->can_fm1r & (1 << bank_id)))
        return -1;
 
    uint8_t idx =  id_num? (bank_id << 1) + 1:(bank_id << 1);
    can_filters->can_firx[idx] = ( mask << 16 ) | identifier;
    
    return 0;
}


int32_t  set_fileter_32mask(uint8_t bank_id, uint32_t identifier, uint32_t mask){

    if (bank_id >= FILTER_BANK_NUMBER  || !(can_filters->can_fs1r & (1 << bank_id)) 
        ||  (can_filters->can_fm1r & (1 << bank_id)))
        return -1;
    
    uint8_t idx =  bank_id << 1;

    can_filters->can_firx[idx] =  identifier;
    can_filters->can_firx[idx + 1] =  mask;
    
    return 0;
}




int32_t   send_can_msg( uint8_t can_id, uint8_t mailbox_id,  can_txmsg_t * txmsg)
{

    if (   can_id > CAN2  || mailbox_id > TX_MAINBOX2 || txmsg->data_len > MAX_DATA_LEN || 
      !txmsg->ext_id && ( txmsg->stid > 0x7ff) || txmsg->ext_id && ( txmsg->stid> 0x1fffffff))
        return  -1;

    while (!(can_controls[can_id]->can_tsr & (CAN_TSR_TME0 << mailbox_id)))
        ;
    
    uint32_t  data_h, data_l;

    
    data_l =  (txmsg->datas[3]<<24) | (txmsg->datas[2]<<16) | (txmsg->datas[1]<<8)|txmsg->datas[0];
    data_h =  (txmsg->datas[7]<<24) | (txmsg->datas[6]<<16) | (txmsg->datas[5]<<8)|txmsg->datas[4];


    can_mailboxs[can_id]->mailboxs[mailbox_id].can_tdlxr = data_l;
    can_mailboxs[can_id]->mailboxs[mailbox_id].can_tdhxr = data_h;

    if (txmsg->ext_id){
        can_mailboxs[can_id]->mailboxs[mailbox_id].can_tixr  |= CAN_TIxR_IDE;
        can_mailboxs[can_id]->mailboxs[mailbox_id].can_tixr  &= ~CAN_TIxR_EXID;
        can_mailboxs[can_id]->mailboxs[mailbox_id].can_tixr  |= txmsg->stid;
    }else{
        can_mailboxs[can_id]->mailboxs[mailbox_id].can_tixr &= ~CAN_TIxR_IDE;
        can_mailboxs[can_id]->mailboxs[mailbox_id].can_tixr &= ~CAN_TIxR_EXID;
        can_mailboxs[can_id]->mailboxs[mailbox_id].can_tixr |= ( txmsg->stid << 21);
    }
        

    if (txmsg->remote_frame)
        can_mailboxs[can_id]->mailboxs[mailbox_id].can_tdtxr |= CAN_TIxR_RTR;
    else
        can_mailboxs[can_id]->mailboxs[mailbox_id].can_tdtxr &= ~CAN_TIxR_RTR;
    

    can_mailboxs[can_id]->mailboxs[mailbox_id].can_tdtxr &=  ~CAN_TDTxR_DLC;
    can_mailboxs[can_id]->mailboxs[mailbox_id].can_tdtxr |=  txmsg->data_len;
    can_mailboxs[can_id]->mailboxs[mailbox_id].can_tixr |= CAN_TIxR_TXRQ;


    while (can_controls[can_id]->can_tsr & (CAN_TSR_RQCP0 << (8 * mailbox_id)))
                ;
    
    uint32_t ret =  can_controls[can_id]->can_tsr & (CAN_TSR_TXOK0 << (8 * mailbox_id))?0:-1;

    can_controls[can_id]->can_tsr |=  (CAN_TSR_TXOK0 << (8 * mailbox_id));   /*clear mailbox trans status */

    return ret;

}


int32_t   recv_can_msg( uint8_t can_id, uint8_t fifo_id, can_rxmsg_t  * rxmsg){

    if (fifo_id > RX_FIFO1 || can_id > CAN2)
        return -1;

    uint8_t  recv_len;
    uint64_t  recv_data;
    if ( fifo_id == RX_FIFO0 ){
        while (!(can_controls[can_id]->can_rf0r & CAN_RF0R_FMP0))
            ;
        
    }else{

        while (!(can_controls[can_id]->can_rf1r & CAN_RF0R_FMP0))
            ;

    }

    recv_len = can_mailboxs[can_id]->fifos[fifo_id].can_rdtxr &  CAN_RDTxR_DLC;
    rxmsg->data_len = recv_len;
    rxmsg->filter_index  =  (can_mailboxs[can_id]->fifos[fifo_id].can_rdtxr & CAN_RDTxR_FMI) >> 8;
    if (can_mailboxs[can_id]->fifos[fifo_id].can_rixr & CAN_RIxR_IDE){
        rxmsg->ext_id = true;
        rxmsg->stid = (can_mailboxs[can_id]->fifos[fifo_id].can_rixr & CAN_RIxR_EXID) >> 3;
    }else{
        rxmsg->ext_id = false;
        rxmsg->stid = (can_mailboxs[can_id]->fifos[fifo_id].can_rixr & CAN_RIxR_STID) >> 21;
    }
        
    if (can_mailboxs[can_id]->fifos[fifo_id].can_rixr & CAN_RIxR_RTR)
        rxmsg->remote_frame = true;
    else
        rxmsg->remote_frame = false;
    

    recv_data =  (can_mailboxs[can_id]->fifos[fifo_id].can_rdhxr << 32) | 
            can_mailboxs[can_id]->fifos[fifo_id].can_rdlxr;

    if ( fifo_id == RX_FIFO0 ){
        can_controls[can_id]->can_rf0r |= CAN_RF0R_RFOM0;   
    }else{
        can_controls[can_id]->can_rf1r |= CAN_RF0R_RFOM0;
    }
    
    for (uint8_t i = 0; i < recv_len; i++)
        rxmsg->datas[i] =  (recv_data >> (8 * i) & 0xff);
    

    return 0;

}







