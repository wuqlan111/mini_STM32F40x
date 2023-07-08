
#ifndef  STM32_CAN_H
#define  STM32_CAN_H

#include  <stdint.h>
#include  "util.h"

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


typedef union {
    struct {
        uint16_t  debug_freeze:1;
        uint16_t  time_trigger_mode:1;
        uint16_t  auto_bus_off:1;
        uint16_t  auto_wakeup:1;
        uint16_t  auto_retrans:1;
        uint16_t  rx_fifo_lock_mode:1;
        uint16_t  tx_fifo_priority_identifier:1;
    };

    uint16_t  val;

} ATTRIBUTE_ALIGN(4) can_config_t;

typedef union {
    struct {
        uint16_t  sleep_interrupt_enable:1;
        uint16_t  wakeup_interrupt_enable:1;
        uint16_t  error_interrupt_enable:1;
        uint16_t  last_error_interrupt_enable:1;
        uint16_t  bus_off_interrupt_enable:1;
        uint16_t  error_passive_interrupt_enable:1;
        uint16_t  error_warning_interrupt_enable:1;
        uint16_t  tx_empty_interrupt_enable:1;
    };

    uint16_t  val;
} ATTRIBUTE_ALIGN(4) can_global_interrupt_config_t;


typedef union {
    struct  {
        uint16_t  fifo_full_interrupt_enable:1;
        uint16_t  fifo_pending_interrupt_enable:1;
        uint16_t  fifo_overrun_interrupt_enable:1;
        uint16_t  rx_fifo;
    };
    uint32_t  val;
} ATTRIBUTE_ALIGN(4) can_rxfifo_interrupt_config_t;

typedef  struct {
    uint32_t filter0;
    uint32_t filter1;
    uint32_t  bank:6;
    uint32_t  mask_mode:1;
    uint32_t  scale_32bit:1;
    uint32_t  assign_fifo0:1;
} ATTRIBUTE_ALIGN(4) can_filter_config_t;






typedef  struct {
    uint32_t  stid;
    uint32_t  std_identifier:1;
    uint32_t  data_frame:1;
    uint32_t  data_len: 4;
    uint32_t  trans_time:1;
    uint32_t  time_stamp:16;
    uint8_t   data[8];
} ATTRIBUTE_ALIGN(4) can_txmsg_t;

typedef struct {
    uint32_t  stid;
    uint32_t  std_identifier:1;
    uint32_t  data_frame:1;
    uint32_t  data_len: 4;
    uint32_t  filter_index:8;
    uint32_t  time_stamp:16;
    uint8_t  data[8];
} ATTRIBUTE_ALIGN(4) can_rxmsg_t;

int32_t  can_global_init(uint32_t  can_id, can_config_t * config);
int32_t  can_set_global_interrupt(uint32_t  can_id,  can_global_interrupt_config_t * config);
int32_t  can_set_rxfifo_interrupt(uint32_t  can_id,  can_rxfifo_interrupt_config_t * config);
inline  void  reset_can_master(uint32_t can_id);
inline  void  enter_or_exit_sleep_mode(uint32_t can_id, uint32_t enter);
inline  void  enter_or_exit_initialization_mode(uint32_t can_id, uint32_t enter);
int32_t  set_filter_bank(uint32_t can_id,  can_filter_config_t * config);
int32_t  enable_or_disable_filter(uint32_t bank_id, uint32_t  enable);
int32_t  send_can_message(uint32_t can_id, uint32_t mailbox_id, can_txmsg_t * msg);
int32_t  read_can_message(uint32_t can_id, uint32_t mailbox_id, can_rxmsg_t * msg);

#endif

