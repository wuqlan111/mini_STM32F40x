


#ifndef STM32_I2C_H
#define STM32_I2C_H

#include  <stdlib.h>
#include  <stdint.h>


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


#define T_PCLK1         125     // 125ns


enum i2c_dev{

    I2C_DEV0 = 0,
    I2C_DEV1,
    I2C_DEV2,
    I2C_DEV_NUMBER
};


enum  i2c_mode{

    SLAVE_TRANS = 0,
    SLAVE_RECV,
    MASTER_TRANS,
    MASTER_RECV

};


#define I2C_SMODE_FREQ   100
#define I2C_SMODE_TIME   10000
#define I2C_FMODE_FREQ   400
#define I2C_FMODE_TIME   2500


#endif



