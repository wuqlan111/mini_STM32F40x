
#include  <stdlib.h>
#include  <stdbool.h>

#include  "../include/usart.h"


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

static  uint32_t  usart_regs_base_addr[] = {0x40011000,  0x40004400,  0x40004800,  0x40004C00,  
                    0x40005000, 0x40011400,  0x40007800,  0x40007C00 };


#define USART_SR_REG_ADDR(usart)                     (usart_regs_base_addr[usart])
#define USART_DR_REG_ADDR(usart)                     (usart_regs_base_addr[usart] + 0x4)
#define USART_BRR_REG_ADDR(usart)                    (usart_regs_base_addr[usart] + 0x8)
#define USART_CR1_REG_ADDR(usart)                    (usart_regs_base_addr[usart] + 0xC)
#define USART_CR2_REG_ADDR(usart)                    (usart_regs_base_addr[usart] + 0x10)
#define USART_CR3_REG_ADDR(usart)                    (usart_regs_base_addr[usart] + 0x14)
#define USART_GTPR_REG_ADDR(usart)                   (usart_regs_base_addr[usart] + 0x18)



int32_t  global_USART_config(uint32_t  usart_id,  USART_config_t  * config)
{
    if ( (usart_id > USART_MAX_ID ) ||  !config) {
        return  -1;
    }




    return  0;

}





int32_t  global_USART_interrupt(uint32_t  usart_id,  USART_interrupt_config_t * config)
{
    uint32_t  flag,  mask;
    flag = mask = 0;
    if ( (usart_id > USART_MAX_ID ) ||  !config) {
        return  -1;
    }

    if (config->pe_interrupt_enable) {
        flag = 1 << 8;
    }

    if (config->txe_interrupt_enable) {
        flag |= 1 << 7;
    }

    if (config->complete_interrupt_enable) {
        flag |= 1 << 6;
    }

    if (config->rxne_interrupt_enable) {
        flag  |=  1 << 5;
    }

    if (config->idle_interrupt_enable) {
        flag |=  1 << 4;
    }

    mask =  0x1f0;

    REG32_UPDATE(USART_CR1_REG_ADDR(usart_id),  flag,  mask);

    if (config->cts_interrupt_enable) {
        flag  =  1 << 10;
    }

    if (config->error_interrupt_enable) {
        flag  |=  0x1;
    }

    mask  =  ( 1<< 10) | 0x1;

    REG32_UPDATE(USART_CR3_REG_ADDR(usart_id), flag,  mask);

    return  0;


}



