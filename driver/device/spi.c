
#include  <stdlib.h>

#include  "spi.h"

#include  "../include/driver_util.h"
#include  "../include/system_rcc.h"
#include  "math_util.h"


#define  SPI_CR1_BIDIMODE           (1<<15)                 // bidirectional data mode enable
#define  SPI_CR1_BIDIOE             (1<<14)                 // output enable in bidirectional mode
#define  SPI_CR1_CRCEN              (1<<13)                 // hardware CRC calculation enable
#define  SPI_CR1_CRCNEXT            (1<<12)                // CRC transfer next
#define  SPI_CR1_DFF                (1<<11)                // data frame format
#define  SPI_CR1_RXONLY             (1<<10)                 // receive only
#define  SPI_CR1_SSM                (1<<9)                  // software slave management
#define  SPI_CR1_SSI                (1<<8)                  // internal slave select
#define  SPI_CR1_LSBFIRST           (1<<7)                  // LSB transmitted first
#define  SPI_CR1_SPE                (1<<6)                  // enable peripheral
#define  SPI_CR1_BR                 (0x7<<3)                // baud rate control
#define  SPI_CR1_MSTR               0x4                     // master configuration
#define  SPI_CR1_CPOL               0x2                     // clock polarity
#define  SPI_CR1_CPHA               0x1                     // clock phase

#define  SPI_CR2_TXEIE              (1<<7)                  // Tx buffer empty interrupt enable
#define  SPI_CR2_RXNEIE             (1<<6)                  // RX buffer not empty interrupt enable
#define  SPI_CR2_ERRIE              (1<<5)                  // error interrupt enable
#define  SPI_CR2_FRF                (1<<4)                  // SPI TI mode
#define  SPI_CR2_SSOE               0x4                     // SS output enable
#define  SPI_CR2_TXDMAEN            0x2                     // Tx buffer DMA enable
#define  SPI_CR2_RXDMAEN            0x1                     // Rx buffer DMA enable


#define  SPI_SR_FRE                 (1<<8)                  // frame format error
#define  SPI_SR_BSY                 (1<<7)                  // SPI is busy in communication
#define  SPI_SR_OVR                 (1<<6)                  // overrun occurred
#define  SPI_SR_MODF                (1<<5)                  // mode fault occurred
#define  SPI_SR_CRCERR              (1<<4)                  // CRC error flag
#define  SPI_SR_UDR                 (1<<3)                  // underrun occurred
#define  SPI_SR_CHSIDE              0x4                     // channel right has to be transmitted
#define  SPI_SR_TXE                 0x2                     // transmit buffer empty
#define  SPI_SR_RXNE                0x1                     // receive buffer not empty



#define  SPI_DR_DR              0xffff                  // data register
#define  SPI_CRCPR_CRCPOLY          0xffff              // CRC polynomial register
#define  SPI_RXCRCR_RXCRC           0xffff              // Rx CRC register
#define  SPI_TXCRCR_TXCRC           0xffff              // Tx CRC register

#define  SPI_I2SCFGR_I2SMOD             (1<<11)             // I2S mode selection
#define  SPI_I2SCFGR_I2SE               (1<<10)             // enable I2S peripheral
#define  SPI_I2SCFGR_I2SCFG             (0x3<<8)            // I2S configuration mode
#define  SPI_I2SCFGR_PCMSYNC            (1<<7)              // long frame synchronization
#define  SPI_I2SCFGR_I2SSTD             0x30                // I2S standard selection
#define  SPI_I2SCFGR_CKPOL              0x8                 // I2S clock steady state is high level
#define  SPI_I2SCFGR_DATLEN             0x6                 // data length to be transferred
#define  SPI_I2SCFGR_CHLEN              0x1                 // 32-bit channel length


const  uint32_t  SPI_REGS_BASE_ADDR[] = { 0x40013000, 0x40003800,  0x40003C00, 0x40013400,
                                0x40015000,    0x40015400  };
const  uint32_t  I2S_REGS_BASE_ADDR[] =  {0x40003400, 0x40003800, 0x40003C00,  0x40004000};


#define  SPI_CR1_REG_ADDR(spi)              (SPI_REGS_BASE_ADDR[spi])
#define  SPI_CR2_REG_ADDR(spi)              (SPI_REGS_BASE_ADDR[spi] + 0x4)
#define  SPI_SR_REG_ADDR(spi)               (SPI_REGS_BASE_ADDR[spi] + 0x8)
#define  SPI_DR_REG_ADDR(spi)               (SPI_REGS_BASE_ADDR[spi] + 0xC)
#define  SPI_CRCPR_REG_ADDR(spi)            (SPI_REGS_BASE_ADDR[spi] + 0x10)
#define  SPI_RXCRCR_REG_ADDR(spi)           (SPI_REGS_BASE_ADDR[spi] + 0x14)
#define  SPI_TXCRCR_REG_ADDR(spi)           (SPI_REGS_BASE_ADDR[spi] + 0x18)
#define  SPI_I2SCFGR_REG_ADDR(spi)          (SPI_REGS_BASE_ADDR[spi] + 0x1C)
#define  SPI_I2SPR_REG_ADDR(spi)            (SPI_REGS_BASE_ADDR[spi] + 0x20)



int32_t   SPI_init(spi_dev_e  spi_id, SPI_config_t * config)
{
    uint32_t  flag,  mask;
    flag = mask = 0;

    CHECK_PARAM_NULL(config);
    CHECK_PARAM_VALUE(spi_id,  SPI_MAX_ID);

    if (config->bidirectional_mode) {
        flag |=  1 << 15;
    }

    if (config->bidirectional_mode_output_enable) {
        flag  |= 1 << 14;
    }

    if (config->hardware_crc_enable) {
        flag  |=  1 << 13;
    }

    if (config->bit16_data_frame) {
        flag |=  1 << 11;
    }

    if (config->receive_only) {
        flag |=  1  << 10;
    }

    if (config->lsb_transmitted_first) {
        flag |=  1 << 7;
    }

    if (config->master_configuration) {
        flag |= 1 << 2;
    }


    if (config->clock_high_idle) {
        flag |=  0x2;
    }

    if (config->second_clock_data_capture_edge) {
        flag |=  0x1;
    }

    REG32_WRITE(SPI_CR1_REG_ADDR(spi_id), flag);

    flag   =    0;
    if (config->ss_output_enable) {
        flag  =  1 << 2;
    }

    REG32_WRITE(SPI_CR2_REG_ADDR(spi_id), flag);
    return  0;

}



int32_t  enable_or_disable(spi_dev_e  spi_id,  uint32_t  enable)
{
    uint32_t  flag,  mask;
    flag = mask = 0;

    CHECK_PARAM_VALUE(spi_id,  SPI_MAX_ID);

    flag    =  enable?  1 << 6:  0;
    mask    =  SPI_CR1_SPE;

    REG32_UPDATE(SPI_CR1_REG_ADDR(spi_id),  flag,  mask);

    return   0;

}


int32_t  set_SPI_baud_rate(spi_dev_e  spi_id, uint32_t  baud_rate)
{
    uint32_t  is_apb1, flag,  mask;
    int32_t  ret  =  0;
    is_apb1  =  flag  =  mask  =  0;

    CHECK_PARAM_VALUE(spi_id,  SPI_MAX_ID);
    if (!baud_rate) {
        return  -1;
    }

    is_apb1  =  spi_id  ==  SPI1? 0:  1;

    double  apb_clk =  0;

    if (rcc_get_apb_clk_frequency(&apb_clk,  is_apb1)) {
        return  -1;
    }

    apb_clk  *=  1000000;

    double  div  =   apb_clk  /  baud_rate; 
    uint32_t  div_mantissa   =  (uint32_t)div;

    if (div_mantissa > 256) {
        return  -1;
    }

    uint32_t  bits  =  0;
    if ( math_clog2(div_mantissa,  &bits)) {
        return  -1;
    }

    flag  =  (bits - 1) << 3;
    mask  =  SPI_CR1_BR;

    REG32_UPDATE(SPI_CR1_REG_ADDR(spi_id),   flag,  mask);

    return  0;


}




