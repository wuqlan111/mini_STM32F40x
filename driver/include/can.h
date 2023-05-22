
#ifndef  STM32_CAN_H
#define  STM32_CAN_H

#include  <stdint.h>

#define  FILTER_BANK_NUMBER       28
#define  MAX_DATA_LEN       8




enum {
    CAN1 = 0,
    CAN2,
    CAN_MAX_ID = CAN2,
};


enum {

    TX_MAINBOX0 = 0,
    TX_MAINBOX1,
    TX_MAINBOX2,
    MAILBOX_MAX_ID = TX_MAINBOX2,
};

enum {

    RX_FIFO0 = 0,
    RX_FIFO1,
    FIFO_MAX_ID = RX_FIFO1,
};


enum  {
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






#endif

