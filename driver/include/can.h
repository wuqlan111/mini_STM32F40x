
#ifndef  STM32_CAN_H
#define  STM32_CAN_H

#include  <stdint.h>

#include  <stdbool.h>


#define  CAN_SLKIE_INT          (1<<17)         // sleep interrupt enable
#define  CAN_WKUIE_INT          (1<<16)         // wakeup interrupt enable
#define  CAN_ERRIE_INT          (1<<15)         // error interrupt enable
#define  CAN_LECIE_INT          (1<<11)         // last error code interrupt enable
#define  CAN_BOFIE_INT          (1<<10)         // Bus-off interrupt enable
#define  CAN_EPVIE_INT          (1<<9)          // error passive interrupt enable
#define  CAN_EWGIE_INT          (1<<8)          // error warning interrupt enable
#define  CAN_FOVIE1_INT         (1<<6)          // FIFO overrun interrupt enable
#define  CAN_FFIE1_INT          (1<<5)          // FIFO full interrupt enable
#define  CAN_FMPIE1_INT         (1<<4)          // FIFO message pending interrupt enable
#define  CAN_FOVIE0_INT         0x8         // FIFO overrun interrupt enable
#define  CAN_FFIE0_INT          0x4         // FIFO full interrupt enable
#define  CAN_FMPIE0_INT         0x2         // FIFO message pending interrupt enable
#define  CAN_TMEIE_INT          0x1            // transmit mailbox empty interrupt enable
#define  CAN_ALL_INT            0x38f7f


#define FILTER_BANK_NUMBER       28

#define  MAX_DATA_LEN       8




enum  can_id{

    CAN1 = 0,
    CAN2,
    CAN_NUMBER

};


enum  tx_mailbox_id{

    TX_MAINBOX0 = 0,
    TX_MAINBOX1,
    TX_MAINBOX2,
    MAILBOX_NUMBER
};

enum  rx_fifo_id{

    RX_FIFO0 = 0,
    RX_FIFO1,
    FIFO_NUMBER
};





enum  last_error_code{

    NO_ERROR = 0,
    STUFF_ERROR,
    FORM_ERROR,
    ACKNOWLEDGMENT_ERROR,
    BIT_RECESSIVE_ERROR,
    BIT_DOMINANT_ERROR,
    CRC_ERROR,
    SET_BY_SOFTWARE
};


typedef  struct can_txmsg{
    uint32_t  stid;
    bool   ext_id;
    bool  remote_frame;
    uint8_t data_len;
    uint8_t  datas[8];

}can_txmsg_t;

typedef struct can_rxmsg{
    uint32_t  stid;
    bool   ext_id;
    bool  remote_frame;
    uint8_t data_len;
    uint8_t  datas[8];
    uint8_t  filter_index;

}can_rxmsg_t;



int32_t  enable_CAN_interrupt(uint8_t can_id,  uint32_t int_mask);
int32_t  disable_CAN_interrupt( uint8_t can_id, uint32_t int_mask);
int32_t  set_fileter_mode(uint8_t bank_id, bool mask_mode);
int32_t  set_fileter_sacle( uint8_t bank_id, bool dual_16bit);
int32_t  set_fileter_fifo(uint8_t bank_id, bool assign_fifo0);
int32_t  set_fileter_activation(uint8_t bank_id, bool active);
int32_t  set_fileter_16identifier(uint8_t bank_id, uint16_t identifier , uint8_t id_num);
int32_t  set_fileter_32identifier(uint8_t bank_id, uint32_t identifier , uint8_t id_num);
int32_t  set_fileter_16mask(uint8_t bank_id, uint16_t identifier,  uint16_t mask, uint8_t id_num);
int32_t  set_fileter_32mask(uint8_t bank_id, uint32_t identifier, uint32_t mask);
int32_t   send_can_msg( uint8_t can_id, uint8_t mailbox_id,  can_txmsg_t * txmsg);
int32_t   recv_can_msg( uint8_t can_id, uint8_t fifo_id, can_rxmsg_t * rxmsg);





#endif

