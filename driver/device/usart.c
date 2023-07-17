
#include  <stdlib.h>
#include  <stdbool.h>

#include  "../include/usart.h"
#include  "../include/driver_util.h"


#define  USART_SR_CTS              (1<<9)           // the CTS status line change
#define  USART_SR_LBD              (1<<8)           // LIN break detection flag
#define  USART_SR_TXE              (1<<7)           // transmit data register empty
#define  USART_SR_TC               (1<<6)           // transmission complete
#define  USART_SR_RXNE             (1<<5)           // read data register not empty
#define  USART_SR_IDLE             (1<<4)           // IDLE line detected
#define  USART_SR_ORE              0x8              // overrun error
#define  USART_SR_NF               0x4              // noise detected flag
#define  USART_SR_FE               0x2              // detecte framing error or break character
#define  USART_SR_PE               0x1              // parity error


#define  USART_DR_DR               0xff



#define  USART_BRR_DIV_MANTISSA             0xffff0             // mantissa of USARTDIV
#define  USART_BRR_DIV_FRACTION             0xf                 // fraction of USARTDIV


#define  USART_CR1_OVER8              (1<<15)                   // oversampling mode by 8
#define  USART_CR1_UE                 (1<<14)                   // USART enable
#define  USART_CR1_M                  (1<<12)                   // 10 bit word length
#define  USART_CR1_WAKE               (1<<11)                   // wakeup method by address Mark
#define  USART_CR1_PCE                (1<<10)                   // parity control enable
#define  USART_CR1_PS                 (1<<9)                    // odd parity selection
#define  USART_CR1_PEIE               (1<<8)                    // PE interrupt enable
#define  USART_CR1_TXEIE              (1<<7)                    // TXE interrupt enable
#define  USART_CR1_TCIE               (1<<6)                    // transmission complete interrupt enable
#define  USART_CR1_RXNEIE             (1<<5)                    // RXNE interrupt enable
#define  USART_CR1_IDLEIE             (1<<4)                    // IDLE interrupt enable
#define  USART_CR1_TE                  0x8                      // transmitter enable
#define  USART_CR1_RE                  0x4                      // receiver enable
#define  USART_CR1_RWU                 0x2                      // receiver wakeup
#define  USART_CR1_SBK                 0x1                      // send break


#define  USART_CR2_LINEN               (1<<14)                  // LIN mode enable
#define  USART_CR2_STOP                (0x3<<12)                // STOP bits
#define  USART_CR2_CLKEN               (1<<11)                  // clock enable
#define  USART_CR2_CPOL                (1<<10)                  // clock polarity
#define  USART_CR2_CPHA                (1<<9)                   // clock phase
#define  USART_CR2_LBCL                (1<<8)                   // last bit clock pulse
#define  USART_CR2_LBDIE               (1<<6)                   // LIN break detection interrupt enable
#define  USART_CR2_LBDL                (1<<5)                   // 11-bit break detection
#define  USART_CR2_ADD                 0xf                      // address of the USART node


#define  USART_CR3_ONEBIT                   (1<<11)                 // one sample bit method enable
#define  USART_CR3_CTSIE                    (1<<10)                 // CTS interrupt enable
#define  USART_CR3_CTSE                     (1<<9)                  // CTS enable
#define  USART_CR3_RTSE                     (1<<8)                  // RTS enable
#define  USART_CR3_DMAT                     (1<<7)                  // DMA enable transmitter
#define  USART_CR3_DMAR                     (1<<6)                  // DMA enable receiver
#define  USART_CR3_SCEN                     (1<<5)                  // smartcard Mode enable
#define  USART_CR3_NACK                     (1<<4)                  // smartcard NACK enable
#define  USART_CR3_HDSEL                    0x8                     // Half-duplex selection
#define  USART_CR3_IRLP                     0x4                     // IrDA low-power
#define  USART_CR3_IREN                     0x2                     // IrDA mode enable
#define  USART_CR3_EIE                      0x1                     // error interrupt enable


#define  USART_GTPR_GT                      0xff00                      // guard time value
#define  USART_GTPR_PSC                     0xff                        // prescaler value


#define USART_SR_REG_ADDR(usart)                     (usart_regs_base_addr[usart])
#define USART_DR_REG_ADDR(usart)                     (usart_regs_base_addr[usart] + 0x4)
#define USART_BRR_REG_ADDR(usart)                    (usart_regs_base_addr[usart] + 0x8)
#define USART_CR1_REG_ADDR(usart)                    (usart_regs_base_addr[usart] + 0xC)
#define USART_CR2_REG_ADDR(usart)                    (usart_regs_base_addr[usart] + 0x10)
#define USART_CR3_REG_ADDR(usart)                    (usart_regs_base_addr[usart] + 0x14)
#define USART_GTPR_REG_ADDR(usart)                   (usart_regs_base_addr[usart] + 0x18)


typedef  struct {
    uint32_t  timeout;
    uint8_t  * rx_buffer;
    uint32_t  rx_sz;
    uint8_t  * tx_buffer;
    uint32_t  tx_sz;
} ATTRIBUTE_PACKED usart_internal_cfg_t;

static  usart_internal_cfg_t  usart_dev_cfg[USART_MAX_ID + 1] = {0};

static  uint32_t  usart_regs_base_addr[] = {0x40011000,  0x40004400,  0x40004800,  0x40004C00,  
                    0x40005000, 0x40011400,  0x40007800,  0x40007C00 };


static  int32_t  check_usart_user_cfg(usart_user_cfg_t * user_cfg)
{
    CHECK_PARAM_NULL(user_cfg);

    CHECK_PARAM_VALUE(user_cfg->data_len,   USART_MAX_DATA_LEN);
    CHECK_PARAM_VALUE(user_cfg->parity,     USART_MAX_PARITY);
    CHECK_PARAM_VALUE(user_cfg->stop_bits,  USART_MAX_STOP_BIT);
    CHECK_PARAM_VALUE(user_cfg->timeout,    USART_MAX_TIMEOUT);

    if ((user_cfg->data_len == USART_DATA_7) && (user_cfg->parity == USART_PARITY_NONE)) {
        return   -1;
    }

    if ((user_cfg->data_len == USART_DATA_9) && (user_cfg->parity != USART_PARITY_NONE)) {
        return   -1;
    }

    return  0;

}


static  int32_t  check_usart_buffer_cfg(usart_buffer_cfg_t * buffer_cfg)
{
    CHECK_PARAM_NULL(buffer_cfg);

    if ((!buffer_cfg->rx_buffer && buffer_cfg->rx_sz) || 
                        (buffer_cfg->rx_buffer && !buffer_cfg->rx_sz)) {
        return  -1;
    }

    if ((!buffer_cfg->tx_buffer && buffer_cfg->tx_sz) || 
                        (buffer_cfg->tx_buffer && !buffer_cfg->tx_sz)) {
        return  -1;
    }

    return  0;

}


static  int32_t   set_usart_baud_rate(usart_dev_e  usart,  uint32_t  baud_rate)
{
    
}


int32_t   usart_init(usart_dev_e  usart,  usart_cfg_t * cfg)
{
    uint32_t  flag, mask;
    flag  =  mask  =  0;
    CHECK_PARAM_VALUE(usart, USART_MAX_ID);
    CHECK_PARAM_NULL(cfg);

    if (check_usart_user_cfg((&cfg->user_cfg))) {
        return  -1;
    }

    if (check_usart_buffer_cfg(&cfg->buffer_cfg)) {
        return  -1;
    }

    if (cfg->user_cfg.parity == USART_PARITY_EVEN) {
        flag  =  USART_CR1_PCE;
    } else if (cfg->user_cfg.parity == USART_PARITY_ODD) {
        flag  =  USART_CR1_PCE | USART_CR1_PS;
    }

    if ((cfg->user_cfg.data_len  ==  USART_DATA_8) && (flag & USART_CR1_PCE)) {
        flag |=  USART_CR1_M;
    }

    if (cfg->user_cfg.data_len ==  USART_DATA_9) {
        flag |=  USART_CR1_M;
    }

    REG32_WRITE(USART_CR1_REG_ADDR(usart),  flag);

    switch (cfg->user_cfg.stop_bits) {
        case  USART_STOP_0_5:
            flag  =  1 << 12;
            break;
        
        case  USART_STOP_1_0:
            flag  = 0;
            break;

        case  USART_STOP_1_5:
            flag  = 3 << 12;
            break;

        case  USART_STOP_2_0:
            flag  =  2  << 12;
            break;
    }

    REG32_WRITE(USART_CR2_REG_ADDR(usart),  flag);

    REG32_WRITE(USART_CR3_REG_ADDR(usart),  0);


    usart_dev_cfg[usart].rx_buffer   =  cfg->buffer_cfg.rx_buffer;
    usart_dev_cfg[usart].rx_sz       =  cfg->buffer_cfg.rx_sz;
    usart_dev_cfg[usart].tx_buffer   =  cfg->buffer_cfg.tx_buffer;
    usart_dev_cfg[usart].tx_sz       =  cfg->buffer_cfg.tx_sz;
    usart_dev_cfg[usart].timeout     =  cfg->user_cfg.timeout;

    return   0;

}

static  void  wait_usart_sr_flag(usart_dev_e  usart,  uint32_t  flag,  uint32_t * is_timeout)
{
    uint32_t  timeout  =  usart_dev_cfg[usart].timeout;
    uint32_t  tmp  =  0;

    *is_timeout  =  1;

    while (timeout) {
        tmp  =   REG32_READ(USART_SR_REG_ADDR(usart));
        if (tmp & flag) {
            *is_timeout  =  0;
            break;
        }
        timeout--;
    }

}



static  int32_t  usart_poll_send(usart_dev_e  usart,  uint32_t  len)
{
    uint32_t  flag, mask,  is_timeout;
    int32_t   ret =  0;
    uint8_t * tx_data   =   usart_dev_cfg->tx_buffer;
    flag = mask  =  is_timeout = 0;

    flag  =  mask  =  USART_CR1_UE | USART_CR1_TE;

    REG32_UPDATE(USART_CR1_REG_ADDR(usart),  flag, mask);


    for (int32_t i  =  0;  i < len; i++) {
        wait_usart_sr_flag(usart,  USART_SR_TXE, &is_timeout);

        if (is_timeout) {
            return  -1;
        }

        REG32_WRITE(USART_DR_REG_ADDR(usart),  tx_data[i]);

    }

    wait_usart_sr_flag(usart,  USART_SR_TC, &is_timeout);

    if (is_timeout) {
        ret =  -1;
    }

    REG32_UPDATE(USART_CR1_REG_ADDR(usart),  0, mask);

    return   ret;

}



static  int32_t  usart_poll_recv(usart_dev_e  usart,  uint32_t  len,  uint32_t * recv_len)
{
    uint32_t  flag, mask,  is_timeout;
    int32_t   ret =  0;
    uint8_t * rx_data   =   usart_dev_cfg->rx_buffer;
    flag = mask  =  is_timeout = 0;

    flag  =  mask  =  USART_CR1_UE | USART_CR1_RE;

    REG32_UPDATE(USART_CR1_REG_ADDR(usart),  flag, mask);


    for (int32_t i  =  0;  i < len; i++) {
        wait_usart_sr_flag(usart,  USART_SR_RXNE, &is_timeout);

        if (is_timeout) {
            *recv_len  =  i;
            break;
        }

        rx_data[i]  =  REG32_READ(USART_DR_REG_ADDR(usart)) & 0xff;

    }

    if (!is_timeout) {
        *recv_len  =  len;
    }

    REG32_UPDATE(USART_CR1_REG_ADDR(usart),  0, mask);

    return   ret;

}





int32_t   usart_send_data(usart_dev_e  usart,  uint32_t  len)
{
    int32_t  ret  =  0;
    CHECK_PARAM_VALUE(usart,  USART_MAX_ID);

    if (!len || (len > usart_dev_cfg[usart].tx_sz)) {
        return  -1;
    }

    CHECK_PARAM_NULL(usart_dev_cfg[usart].tx_buffer);

    ret =  usart_poll_send(usart,  len);

    return  ret;

}



int32_t   usart_recv_data(usart_dev_e  usart,  uint32_t  len, uint32_t * recv_len)
{

    int32_t  ret  =  0;
    CHECK_PARAM_VALUE(usart,  USART_MAX_ID);
    CHECK_PARAM_NULL(recv_len);

    if (!len || (len > usart_dev_cfg[usart].rx_sz)) {
        return  -1;
    }

    CHECK_PARAM_NULL(usart_dev_cfg[usart].rx_buffer);

    ret =  usart_poll_recv(usart,  len,  recv_len);

    return  ret;

}








