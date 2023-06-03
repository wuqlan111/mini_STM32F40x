
#include <stdlib.h>

#include "sdio.h"


#define  SDIO_POWER_PWRCTRL        0x3              // power supply control bits


#define  SDIO_CLKCR_HWFC_EN             (1<<14)             // HW flow control enable
#define  SDIO_CLKCR_NEGEDGE             (1<<13)             // SDIO_CK dephasing selection bit
#define  SDIO_CLKCR_WIDBUS              (0x3<<11)           // wide bus mode enable bit
#define  SDIO_CLKCR_BYPASS              (1<<10)             // clock divider bypass enable bi
#define  SDIO_CLKCR_PWRSAV              (1<<9)              // power saving configuration bit
#define  SDIO_CLKCR_CLKEN               (1<<8)              // clock enable bit
#define  SDIO_CLKCR_CLKDIV              0xff                // clock divide factor


#define  SDIO_ARG_CMDARG        0xffffffff      // command argument


#define  SDIO_CMD_ATACMD                (1<<14)                 // CE-ATA command
#define  SDIO_CMD_NIEN                  (1<<13)                 // not interrupt enable
#define  SDIO_CMD_ENCMD                 (1<<12)                    // enable CMD completion
#define  SDIO_CMD_SDIOSPEND             (1<<11)                     // SD I/O suspend command
#define  SDIO_CMD_CPSMEN                (1<<10)                     // command path state machine enable
#define  SDIO_CMD_WAITPEND              (1<<9)                  // CPSM waits for ends of data transfer
#define  SDIO_CMD_WAITINT                  (1<<8)               // CPSM waits for interrupt request
#define  SDIO_CMD_WAITRESP              (0x3<<6)                // wait for response bits
#define  SDIO_CMD_CMDINDEX              0x3f                    // command index


#define  SDIO_RESPCMD_RESPCMD          0x3f             // response command index

#define  SDIO_DCTRL_SDIOEN              (1<<11)             // SD I/O enable functions
#define  SDIO_DCTRL_RWMOD               (1<<10)             // read wait mode
#define  SDIO_DCTRL_RWSTOP              (1<<9)              // read wait stop
#define  SDIO_DCTRL_RWSTART             (1<<8)              // read wait start
#define  SDIO_DCTRL_DBLOCKSIZE          0xf0                // data block size
#define  SDIO_DCTRL_DMAEN               0X8                 // DMA enable bit
#define  SDIO_DCTRL_DTMODE              0X4                 // Stream or SDIO multibyte data transfer
#define  SDIO_DCTRL_DTDIR               0X2                 // from card to controller
#define  SDIO_DCTRL_DTEN                0x1                 // data transfer enabled bit


#define  SDIO_DCOUNT_DATACOUNT              0x1ffffff              // data count value

#define  SDIO_STA_CEATAEND              (1<<23)                 // CE-ATA command completion signal received for CMD61
#define  SDIO_STA_SDIOIT                (1<<22)                 // SDIO interrupt received
#define  SDIO_STA_RXDAVL                (1<<21)                 // data available in receive FIFO
#define  SDIO_STA_TXDAVL                (1<<20)                 // data available in transmit FIFO
#define  SDIO_STA_RXFIFOE               (1<<19)                 // receive FIFO empty
#define  SDIO_STA_TXFIFOE               (1<<18)                 // transmit FIFO empty
#define  SDIO_STA_RXFIFOF               (1<<17)                 // receive FIFO full
#define  SDIO_STA_TXFIFOF               (1<<16)                 // transmit FIFO full
#define  SDIO_STA_RXFIFOHF              (1<<15)                 // receive FIFO half full
#define  SDIO_STA_TXFIFOHE              (1<<14)                 // transmit FIFO half empty
#define  SDIO_STA_RXACT                 (1<<13)                 // data receive in progress
#define  SDIO_STA_TXACT                 (1<<12)                 // data transmit in progress
#define  SDIO_STA_CMDACT                (1<<11)                 // command transfer in progress
#define  SDIO_STA_DBCKEND               (1<<10)                 // data block sent/received
#define  SDIO_STA_STBITERR              (1<<9)                  // start bit not detected
#define  SDIO_STA_DATAEND               (1<<8)                  // data end
#define  SDIO_STA_CMDSENT               (1<<7)                     // command sent
#define  SDIO_STA_CMDREND               (1<<6)                  // command response received
#define  SDIO_STA_RXOVERR               (1<<5)                  // received FIFO overrun error
#define  SDIO_STA_TXUNDERR              (1<<4)                  // transmit FIFO underrun error
#define  SDIO_STA_DTIMEOUT              0x8                     // data timeout
#define  SDIO_STA_CTIMEOUT              0x4                     // command response timeout
#define  SDIO_STA_DCRCFAIL              0x2                     // CRC check failed
#define  SDIO_STA_CCRCFAIL              0x1                      // command response received (CRC check failed)



#define  SDIO_FIFOCNT_FIFOCOUNT              0xffffff                   // number of words to be written to or read from the FIFO


#define  SDIO_REGS_BASE_ADDR              (0x40012C00u)

#define  SDIO_POWER_REG_ADDR              (SDIO_REGS_BASE_ADDR)
#define  SDIO_CLKCR_REG_ADDR              (SDIO_REGS_BASE_ADDR + 0x4)
#define  SDIO_ARG_REG_ADDR                (SDIO_REGS_BASE_ADDR + 0x8)
#define  SDIO_CMD_REG_ADDR                (SDIO_REGS_BASE_ADDR + 0xC)
#define  SDIO_RESPCMD_REG_ADDR            (SDIO_REGS_BASE_ADDR + 0x10)
#define  SDIO_RESPX_REG_ADDR(resp)        (SDIO_REGS_BASE_ADDR + 0x14 + (resp) * 0x4)
#define  SDIO_DTIMER_REG_ADDR             (SDIO_REGS_BASE_ADDR + 0x24)
#define  SDIO_DLEN_REG_ADDR               (SDIO_REGS_BASE_ADDR + 0x28)
#define  SDIO_DCTRL_REG_ADDR              (SDIO_REGS_BASE_ADDR + 0x2C)
#define  SDIO_DCOUNT_REG_ADDR             (SDIO_REGS_BASE_ADDR + 0x30)
#define  SDIO_STA_REG_ADDR                (SDIO_REGS_BASE_ADDR + 0x34)
#define  SDIO_ICR_REG_ADDR                (SDIO_REGS_BASE_ADDR + 0x38)
#define  SDIO_MASK_REG_ADDR               (SDIO_REGS_BASE_ADDR + 0x3C)
#define  SDIO_FIFOCNT_REG_ADDR            (SDIO_REGS_BASE_ADDR + 0x48)
#define  SDIO_FIFO_REG_ADDR               (SDIO_REGS_BASE_ADDR + 0x80)




int32_t  global_SDIO_config(SDIO_config_t * config)
{
    uint32_t  flag, mask;
    flag = mask = 0;
    if (!config || (config->wide_bus_mode > SDIO_MAX_BUS_MODE)) {
        return  -1;
    }

    if (config->hw_flow_control_enable) {
        flag  |=  1 << 14;
    }

    if (config->output_clock_fall_edge) {
        flag  |=  1 << 13;
    }

    flag |= config->wide_bus_mode << 11;

    if (config->output_clock_bypass_divider) {
        flag |=  1 << 10;
    }

    if (!config->output_clock_always) {
        flag |= 1 << 9;
    }

    if (config->output_clock_enable) {
        flag |=  1  << 8;
    }

    flag |=  config->output_clock_divide;
    mask  =  0x7fff;

    REG32_UPDATE(SDIO_CLKCR_REG_ADDR, flag,  mask);

    REG32_WRITE(SDIO_DTIMER_REG_ADDR, config->data_timeout_period);

    return  0;

}




int32_t  global_SDIO_interrupt_config(SDIO_interrupt_mask_t * config)
{
    uint32_t  flag,  mask;
    flag =  mask  =  0;
    if (!config) {
        return  -1;
    }

    if (config->ceata_completion_interrupt) {
        flag |=  1 << 23;
    }

    if (config->sdio_mode_interrupt) {
        flag |=  1 << 22;
    }

    if (config->rx_fifo_avalible_interrupt) {
        flag |=  1 << 21;
    }

    if (config->tx_fifo_avalible_interrupt) {
        flag |=  1 << 20;
    }

    if (config->rx_fifo_full_interrupt) {
        flag |=  1 << 19;
    }

    if (config->tx_fifo_full_interrupt) {
        flag |=  1 << 18;
    }



    mask  =  0xffffff;
    REG32_UPDATE(SDIO_MASK_REG_ADDR,  flag,  mask);
    return  0;

}



