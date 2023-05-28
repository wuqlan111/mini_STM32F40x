
#include  <stdbool.h>

#include   "../include/i2c.h"


//I2C_CR1 flags
#define I2C_CR1_RESET     (1<<15)          // i2c under reset state
#define I2C_CR1_ALERT     (1<<13)          // 
#define I2C_CR1_PEC     (1<<12)     // packet error checking
#define I2C_CR1_POS     (1<<11)
#define I2C_CR1_ACK     (1<<10)     // ACK returned after a byte received 
#define I2C_CR1_STOP     (1<<9)     // stop generation
#define I2C_CR1_START     (1<<8)        // start generation
#define I2C_CR1_NOSTRETCH     (1<<7)        // clock stretching disable 
#define I2C_CR1_ENGC     (1<<6)         // enable general call
#define I2C_CR1_ENPEC     (1<<5)        // enable PEC calculation
#define I2C_CR1_ENARP     (1<<4)        // enable ARP
#define I2C_CR1_SMBTYPE     (1<<3)      // SMBus host
#define I2C_CR1_SMBMODE     0x2         // SMBus mode
#define I2C_CR1_PE     0x1          // enable peripheral

#define I2C_CR2_LAST     (1<<12)        // next DMA EOT is the last transfer
#define I2C_CR2_DMAEN     (1<<11)       // DMA request enable
#define I2C_CR2_INTBUFEN     (1<<10)        // buffer interrupt enable
#define I2C_CR2_INTEVTEN    (1<<9)      // event interrupt enable
#define I2C_CR2_ITERREN     (1<<8)      // error interrupt enable
#define I2C_CR2_FREQ     0x3f       // peripheral clock frequency
#define I2C_MIN_FREQ    0x2
#define I2C_MAX_FREQ    50
#define I2C_MIN_PTIME   20  // min clock time(ns)

#define I2C_OAR1_10BITADDR  (1<<15)     //10-bit slave address, 7-bit address not ACK
#define I2C_OAR1_ADDR  (0x3ff)          // interface address

#define I2C_OAR2_ADDR   0xfe        // interface address
#define I2C_OAR2_ENDUAL  0x1        // OAR1 and OAR2 all recognized in 7-bit addressing mode


#define I2C_DR_DATA   0xff          // 8-bit data register


#define I2C_SR1_SMBALERT    (1<<15)         // SMBus alert
#define I2C_SR1_TIMEOUT     (1<<14)         // timeout or tlow error
#define I2C_SR1_PECERR      (1<<12)         // PEC error, receiver returns NACK after PEC reception 
#define I2C_SR1_OVERRUN     (1<<11)         // overrun or underrun
#define I2C_SR1_ACKFAIL     (1<<10)         // ACK failure
#define I2C_SR1_ARLO        (1<<9)          // detecte  arbitration lost 
#define I2C_SR1_BERR        (1<<8)          // misplaced start or stop condition
#define I2C_SR1_TDREMPTY    (1<<7)          // data register empty
#define I2C_SR1_RDRNEMPTY     (1<<6)        // data register not empty
#define I2C_SR1_STOPF     (1<4)             // detecte stop condition 
#define I2C_SR1_10BITADD     0x8            // master has sent first address byte
#define I2C_SR1_BTF        0x4              // data byte transfer succeeded
#define I2C_SR1_ADDRMATCH        0x2        // received address matched or end of address transmission
#define I2C_SR1_SBIT        0x1         // start condition generated


#define I2C_SR2_PEC7_0    (0xff<<8)         // packet error checking register
#define I2C_SR2_DUALF     (1<<7)            // received address matched with OAR2
#define I2C_SR2_SMBHOST      (1<<6)         // receive SMBus host address
#define I2C_SR2_SMBDEFAULT    (1<<5)        // receive SMBus device default address
#define I2C_SR2_GENCALL    (1<<4)           // receive general call address 
#define I2C_SR2_DTRA       0x4          // data bytes transmitted
#define I2C_SR2_BUSY    0x2             // communication ongoing on the bus
#define I2C_SR2_MSL     0x1             // master Mode



#define I2C_CCR_FMODE  (1<<15)          // Fm mode I2C
#define I2C_CCR_DUTY  (1<<14)           // Fm mode tlow/thigh = 16/9 
#define I2C_CCR_CLOCK   0xfff           // clock control register in Fm/Sm mode



#define I2C_TRISE_MAX    0x3f      // maximum rise time in Fm/Sm mode


#define  I2C_FLTR_ANOFF  0x10       // disable analog noise filter
#define  I2C_FLTR_DNF   0xf         // digital noise filter

#define   I2C_REG_ADDR_STEP                (0x400u)
#define   I2C_REGS_BASE_ADDR               (0x40005400u)

#define  I2C_CR1_REG_ADDR(i2c)             (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP )
#define  I2C_CR2_REG_ADDR(i2c)             (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x4)
#define  I2C_OAR1_REG_ADDR(i2c)            (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x8)
#define  I2C_OAR2_REG_ADDR(i2c)            (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0xC)
#define  I2C_DR_REG_ADDR(i2c)              (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x10)
#define  I2C_SR1_REG_ADDR(i2c)             (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x14)
#define  I2C_SR2_REG_ADDR(i2c)             (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x18)
#define  I2C_CCR_REG_ADDR(i2c)             (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x1C)
#define  I2C_TRISE_REG_ADDR(i2c)           (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x20)
#define  I2C_FLTR_REG_ADDR(i2c)            (I2C_REGS_BASE_ADDR + (i2c) * I2C_REG_ADDR_STEP + 0x24)


int32_t  I2C_dev_config(uint32_t  i2c_dev, I2C_config_t * config)
{
    uint32_t  flag, mask;
    flag = mask = 0;
    if ( (i2c_dev > I2C_MAX_DEV) || !config ) {
        return  -1;
    }

    if ( (config->clock_frequency > I2C_MAX_CLOCK_FREQUENCY) || 
            (config->clock_frequency < I2C_MIN_CLOCK_FREQUENCY) ) {
        return  -1;
    }

    if (config->SMBus_alert) {
        flag |= 1 << 13;
    }

    if (config->acknowledge_enable) {
        flag |= 1 << 10;
    }

    if (config->clock_stretch_disable) {
        flag |= 1 << 7;
    }

    if (config->general_call_enable) {
        flag |= 1 << 6;
    }

    if (config->pec_enable) {
        flag |= 1 << 5;
    }

    if (config->arp_enable) {
        flag |= 1 << 4;
    }

    if (config->SMBus_host) {
        flag |= 1 << 3;
    }

    if (config->SMBus_mode) {
        flag |=  0x2;
    }

    mask = 0x44fc;
    REG32_UPDATE(I2C_CR1_REG_ADDR(i2c_dev), flag, mask);

    flag = mask = 0;
    if (config->DMA_request_enable) {
        flag |= 1 << 11;
    }

    if (config->buffer_interrupt_enable) {
        flag |= 1 << 10;
    }

    if (config->event_interrupt_enable) {
        flag |= 1 << 9;
    }

    if (config->error_interrupt_enable) {
        flag |= 1 << 8;
    }

    flag |= config->clock_frequency;
    mask  =  0xf3f;
    REG32_UPDATE(I2C_CR2_REG_ADDR(i2c_dev), flag, mask);

    return  0;

}


int32_t  I2C_start_or_stop_generation(uint32_t i2c_dev, uint32_t start)
{
    uint32_t  flag, mask;
    flag = mask = 0;
    if ( i2c_dev > I2C_MAX_DEV ) {
        return  -1;
    }

    if (start) {
        mask = flag = 1 << 8;
    } else {
        mask = flag = 1 << 9;
    }

    REG32_UPDATE(I2C_CR1_REG_ADDR(i2c_dev), flag,  mask);
    return  0;

}


int32_t  enable_or_disable_I2C(uint32_t i2c_dev, uint32_t enable)
{
    uint32_t  flag = 0;
    if ( i2c_dev > I2C_MAX_DEV ) {
        return  -1;
    }

    flag = enable ? 0x1: 0;
    REG32_UPDATE(I2C_CR1_REG_ADDR(i2c_dev), flag,  0x1);
    return  0;
}


int32_t  set_I2C_slave_address(uint32_t  i2c_dev, I2C_address_t * config)
{
    uint32_t  flag, mask;
    flag = mask = 0;
    if ( (i2c_dev > I2C_MAX_DEV)  || !config ) {
        return  -1;
    }

    if ( (config->address1 > 0x3ff) || (config->address2 > 0x3ff) ) {
        return  -1;
    }

    if (config->dual_address_mode && config->slave_address_10bit ) {
        return  -1;
    }

    if (!config->slave_address_10bit && ((config->address1 > 0x7f) 
            || (config->address2 > 0x7f) )) {
        return  -1;
    }

    if (config->dual_address_mode) {
        flag = config->address1 << 1;
        mask = (1 << 15) | (0x7f << 1);
        REG32_UPDATE(I2C_OAR1_REG_ADDR(i2c_dev), flag,  mask);
        flag = (config->address2 << 1) | 0x1;
        mask = 0xff;
        REG32_UPDATE(I2C_OAR2_REG_ADDR(i2c_dev), flag,  mask);
    } else {
        if (config->slave_address_10bit) {
            flag = (1 << 15) | config->address1;
            mask = (1 << 15) | 0x3ff;
        } else {
            flag = config->address1 << 1;
            mask = (1 << 15) | (0x7f << 1);            
        }

        REG32_UPDATE(I2C_OAR1_REG_ADDR(i2c_dev), flag,  mask);

    }

    return  0;

}




